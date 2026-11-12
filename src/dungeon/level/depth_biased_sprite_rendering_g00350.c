#include "shared/sprite_frame_state.h"
/* Depth biased sprite rendering (G00350). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B6D74. */
#include "dungeon/level/depth_biased_sprite_rendering_g00350.h"
#include "dungeon/level.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "engine/graphics/sprite_scratch.h"

/* Traverse object nodes backward and process unflagged primitives with their computed depth. */
s32 traverse_nodes_and_render_unflagged(void *start_node) {
    S_800BC3E4_0_pre *node = start_node;
    GameWork *state = &g_game_work;
    u16 *scratch = (u16 *)0x1F800000;
    void *previous;

    scratch[0x80] = -((u16)state->view.camera_rotation.parts.camera_rotation_x);
    scratch[0x81] = -((u16)state->view.camera_rotation.parts.camera_rotation_y);
    scratch[0x82] = ((u16)state->view.view_rotation_offset.parts.view_rotation_offset_z);

    for (;;) {
        S_800BC3E4_1 *object = node->unk_00;
        SpriteFrameState *primitive = object->unk_0C;

        if (!(primitive->flags & 0x8000)) {
            S_800BC3E4_3 *coord = object->unk_08;
            s16 depth = sample_terrain_surface_height(coord->unk_02, coord->unk_06, coord->unk_0A);
            render_projected_sprite_with_depth_bias(coord, primitive, depth, 0);
            if (is_frame_packet_arena_overflowed(((S_800BC3E4_5 *)(state->draw_buffer))->unk_8D0) != 0) {
                break;
            }
        }
        previous = node[-1].unk_00;
        if (previous == 0) {
            break;
        }
        node = (S_800BC3E4_0_pre *)((u8 *)previous + 0x20);
    }
    return 0;
}

/* Project sprite tiles and append textured quads to the ordering table. */
void render_projected_sprite_with_depth_bias(ObjectPosition *position, SpriteFrameState *sprite, s16 world_z, s32 depth_bias)
{
    u8 *scratch_base = (u8 *)0x1F800000;
    s32 *screen_pos = (s32 *)scratch_base;
    s32 *perspective;
    s32 *clip_flags;
    SpriteQuadScratch *scratch_view;
    GpuContext **root_ptr;
    MATRIX *matrix;
    u8 *packet;
    u8 *packet_next;
    u8 *texture;
    GpuContext *root;
    u32 projected_depth;
    u32 biased_depth;
    u32 ot_index;
    s32 scale;
    s32 clamped_scale;
    s32 uv_word;
    s16 coord_x;
    s16 coord_y;
    u16 screen_x;
    u16 sprite_z;
    u16 sprite_flags;
    u16 world_x;
    u16 world_y;

    screen_pos = (s32 *)((u32)screen_pos | 0xB8);
    perspective = (s32 *)scratch_base;
    scratch_view = (SpriteQuadScratch *)scratch_base;
    perspective = (s32 *)((u32)perspective | 0x90);
    root = g_game_work.draw_buffer;
    packet = root->packetCursor;
    scratch_view->ordering_table = (u32 *)&root->orderTag;
    scratch_view->local_matrix.t[2] = 0;
    scratch_view->local_matrix.t[1] = 0;
    scratch_view->local_matrix.t[0] = 0;
    scratch_view->vertices[3].vz = 0;
    scratch_view->vertices[2].vz = 0;
    scratch_view->vertices[1].vz = 0;
    scratch_view->vertices[0].vz = 0;

    texture = sprite->source;
    sprite_flags = sprite->flags;
    clip_flags = (s32 *)scratch_base;
    scratch_view->sprite_flags = sprite_flags;
    world_x = ((u16) position->x.w.i);
    clip_flags = (s32 *)((u32)clip_flags | 0x94);
    scratch_view->position.vx = world_x;
    world_y = ((u16) position->y.w.i);
    root_ptr = (GpuContext **)&g_game_work;
    scratch_view->position.vy = world_y;
    scratch_view->position.vz = world_z;

    projected_depth = RotTransPers(&scratch_view->position, screen_pos,
                              perspective, clip_flags);
    matrix = &sprite_projection_matrix;
    scratch_view->sort_depth = projected_depth;
    matrix->t[2] = projected_depth * 4;
    biased_depth = projected_depth - 7;
    ot_index = biased_depth - depth_bias;
    scratch_view->sort_depth = ot_index;

    if (ot_index < 0x1E0U) {
        PushMatrix();

        screen_x = scratch_view->screen_origin.x;
        sprite_z = scratch_view->position.vz;
        scratch_view->screen_origin.x = screen_x - 0xA0;
        scratch_view->screen_origin.y -= 0x78;
        scale = ((position->z.w.i - (s16)sprite_z) << 5) + 0x1000;
        scratch_view->input.vz = scale;
        if (scale < 0) {
            scratch_view->input.vz = 0;
        }

        clamped_scale = scratch_view->input.vz;
        scratch_view->input.vx = clamped_scale;
        scratch_view->input.vy = (s32)(clamped_scale + ((u32)clamped_scale >> 31)) >> 1;
        RotMatrix((void *)0x1F800100, (void *)0x1F8000D0);

        CompMatrix(matrix, (void *)0x1F8000D0, (void *)0x1F800050);
        ScaleMatrix((void *)0x1F800050, (void *)0x1F800030);

        scratch_view->input.vx = sprite->scale_x;
        scratch_view->input.vy = sprite->scale_y;
        scratch_view->input.vz = 0x1000;
        ScaleMatrix((void *)0x1F800050, (void *)0x1F800030);
        SetTransMatrix((void *)0x1F800050);
        SetRotMatrix((void *)0x1F800050);

        for (;;) {
            if (!(texture[0] & 0x20)) {
                scratch_view->uv_u_start = texture[8];
                scratch_view->uv_v_start = texture[9];
                scratch_view->uv_u_extent = texture[10];
                scratch_view->uv_v_extent = texture[11];
                func_80067EF4(packet, 0, 0);
                                AddPrim(scratch_view->ordering_table + scratch_view->sort_depth,
                              packet);
                packet_next = packet + 0xC;
                packet = packet_next;

                if ((texture[0] ^ scratch_view->sprite_flags) & 1) {
                    coord_x = -(s8)texture[2];
                    scratch_view->vertices[2].vx = coord_x;
                    scratch_view->vertices[0].vx = coord_x;
                    coord_x -= scratch_view->uv_u_extent;
                    scratch_view->vertices[3].vx = coord_x;
                    scratch_view->vertices[1].vx = coord_x;
                } else {
                    coord_x = (s8)texture[2];
                    scratch_view->vertices[2].vx = coord_x;
                    scratch_view->vertices[0].vx = coord_x;
                    coord_x += scratch_view->uv_u_extent;
                    scratch_view->vertices[3].vx = coord_x;
                    scratch_view->vertices[1].vx = coord_x;
                }

                if ((texture[0] ^ scratch_view->sprite_flags) & 2) {
                    coord_y = -(s8)texture[3];
                    scratch_view->vertices[1].vy = coord_y;
                    scratch_view->vertices[0].vy = coord_y;
                    coord_y -= scratch_view->uv_v_extent;
                    scratch_view->vertices[3].vy = coord_y;
                    scratch_view->vertices[2].vy = coord_y;
                } else {
                    coord_y = (s8)texture[3];
                    scratch_view->vertices[1].vy = coord_y;
                    scratch_view->vertices[0].vy = coord_y;
                    coord_y += scratch_view->uv_v_extent;
                    scratch_view->vertices[3].vy = coord_y;
                    scratch_view->vertices[2].vy = coord_y;
                }

                scratch_view->vertices[0].vx += 6;
                scratch_view->vertices[1].vx += 6;
                RotTransPers4(&scratch_view->vertices[0], &scratch_view->vertices[1],
                              &scratch_view->vertices[2], &scratch_view->vertices[3],
                              (s32 *)&scratch_view->projected_vertices[0], (s32 *)&scratch_view->projected_vertices[1],
                              (s32 *)&scratch_view->projected_vertices[2], (s32 *)&scratch_view->projected_vertices[3],
                              &scratch_view->depth_cue, &scratch_view->gte_flag);

                (*(s16 *)(packet + 8)) = scratch_view->projected_vertices[0].x
                    + scratch_view->screen_origin.x;
                (*(s16 *)(packet + 10)) = scratch_view->projected_vertices[0].y
                    + scratch_view->screen_origin.y;
                (*(s16 *)(packet + 16)) = scratch_view->projected_vertices[1].x
                    + scratch_view->screen_origin.x;
                (*(s16 *)(packet + 18)) = scratch_view->projected_vertices[1].y
                    + scratch_view->screen_origin.y;
                (*(s16 *)(packet + 24)) = scratch_view->projected_vertices[2].x
                    + scratch_view->screen_origin.x;
                (*(s16 *)(packet + 26)) = scratch_view->projected_vertices[2].y
                    + scratch_view->screen_origin.y;
                (*(s16 *)(packet + 32)) = scratch_view->projected_vertices[3].x
                    + scratch_view->screen_origin.x;
                {
                    u16 bottom_y = scratch_view->projected_vertices[3].y;
                    u16 screen_y = scratch_view->screen_origin.y;

                    ((S_800BC4D4_5_pre *)(packet + 7))[-1].unk_00 = 9;
                    (*(s16 *)(packet + 34)) = bottom_y + screen_y;
                }

                scratch_view->uv_u_extent += scratch_view->uv_u_start;
                scratch_view->uv_v_extent = (scratch_view->uv_v_start
                    + scratch_view->uv_v_extent) << 8;
                scratch_view->uv_v_start <<= 8;
                uv_word = scratch_view->uv_v_start + scratch_view->uv_u_start;

                {
                    register u32 texture_page;

                    if (((S_800BC4D4_6 *)(texture + 4))->unk_00 & 0x80) {

                        texture_page = 0x7F800000;
                        uv_word += texture_page;
                    } else {
                        texture_page = 0x7FC00000;
                        uv_word += texture_page;
                    }

                }
                (*(s32 *)(packet + 12)) = uv_word;
                (*(s32 *)(packet + 20)) = scratch_view->uv_v_start +
                                                      scratch_view->uv_u_extent +
                                                      ((s16)((S_800BC4D4_6 *)(texture + 4))->unk_00 << 16);
                {
                    s32 uv_left;
                    s32 u_left;
                    s32 left_x;

                    uv_left = (u16)scratch_view->uv_v_extent;
                    u_left = (u16)scratch_view->uv_u_start;
                    left_x = (*(s16 *)(packet + 8));
                    uv_left += u_left;
                    (*(s16 *)(packet + 28)) = uv_left;
                    {
                        s32 uv_right;
                        s32 u_right;
                        s32 right_x;

                        uv_right = (u16)scratch_view->uv_v_extent;
                        u_right = (u16)scratch_view->uv_u_extent;
                        right_x = (*(s16 *)(packet + 32));
                        uv_right += u_right;
                        (*(s16 *)(packet + 36)) = uv_right;

                        if (right_x < left_x) {
                            ((S_800BC4D4_5 *)(packet + 7))->unk_0D--;
                            ((S_800BC4D4_5 *)(packet + 7))->unk_1D--;
                        }
                    }
                }
                if ((*(s16 *)(packet + 10)) > (*(s16 *)(packet + 34))) {
                    ((S_800BC4D4_5 *)(packet + 7))->unk_16--;
                    ((S_800BC4D4_5 *)(packet + 7))->unk_1E--;
                }

                (*(s32 *)(packet + 4)) = sprite->color.word;
                ((S_800BC4D4_5 *)(packet + 7))->unk_00 = 0x2E;
                                AddPrim(scratch_view->ordering_table + scratch_view->sort_depth,
                              packet);
                                packet += 0x28;
                func_80067EF4(packet, 1, 0);
                AddPrim(scratch_view->ordering_table + scratch_view->sort_depth,
                              packet);
                packet += 0xC;
            }

            if ((s8)texture[0] >= 0) {

                texture += 0xC;
                continue;
            }
            break;
        }
        PopMatrix();
    }

    (*root_ptr)->packetCursor = packet;
}
