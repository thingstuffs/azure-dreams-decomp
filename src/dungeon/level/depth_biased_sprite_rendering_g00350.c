#include "shared/sprite_frame_state.h"
/* Depth biased sprite rendering (G00350). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B6D74. */
#include "dungeon/level/depth_biased_sprite_rendering_g00350.h"
#include "dungeon/level.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "engine/graphics/sprite_scratch.h"
#include "sdk/libgpu_packets.h"
#include "sdk/libgpu_types.h"
#include "shared/sprite_part_command.h"

/* Traverse object nodes backward and process unflagged primitives with their computed depth. */
s32 traverse_nodes_and_render_unflagged(void *start_node) {
    S_800BC3E4_0_pre *node = start_node;
    GameWork *state = &g_game_work;
    SpriteQuadScratch *scratch = (SpriteQuadScratch *)0x1F800000;
    ObjectNodeHeader *previous;

    scratch->angles.vx = -state->view.camera_rotation.parts.camera_rotation_x;
    scratch->angles.vy = -state->view.camera_rotation.parts.camera_rotation_y;
    scratch->angles.vz = state->view.view_rotation_offset.parts.view_rotation_offset_z;

    for (;;) {
        S_800BC3E4_1 *object = node->unk_00;
        SpriteFrameState *primitive = object->unk_0C;

        if (!(primitive->flags & 0x8000)) {
            S_800BC3E4_3 *coord = object->unk_08;
            s16 depth = sample_terrain_surface_height(coord->unk_02, coord->unk_06, coord->unk_0A);
            render_projected_sprite_with_depth_bias(coord, primitive, depth, 0);
            if (is_frame_packet_arena_overflowed(((GpuContext *)state->draw_buffer)->packetCursor) != 0) {
                break;
            }
        }
        previous = NODE_HEADER(node)->chain_next;
        if (previous == 0) {
            break;
        }
        node = NODE_BODY(previous);
    }
    return 0;
}

/* Project sprite tiles and append textured quads to the ordering table. */
void render_projected_sprite_with_depth_bias(ObjectPosition *position, SpriteFrameState *sprite, s16 world_z, s32 depth_bias)
{
    SpriteQuadScratch *scratch_view = (SpriteQuadScratch *)0x1F800000;
    GpuContext **root_ptr;
    MATRIX *matrix;
    POLY_FT4 *packet;
    POLY_FT4 *packet_next;
    DR_PRIO *priority;
    SpritePartCommand *part;
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

    part = sprite->source;
    sprite_flags = sprite->flags;
    scratch_view->sprite_flags = sprite_flags;
    world_x = ((u16) position->x.w.i);
    scratch_view->position.vx = world_x;
    world_y = ((u16) position->y.w.i);
    root_ptr = (GpuContext **)&g_game_work;
    scratch_view->position.vy = world_y;
    scratch_view->position.vz = world_z;

    projected_depth = RotTransPers(&scratch_view->position, (s32 *)&scratch_view->screen_origin,
                              &scratch_view->depth_cue, &scratch_view->gte_flag);
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
        RotMatrix(&scratch_view->angles, &scratch_view->local_matrix);

        CompMatrix(matrix, &scratch_view->local_matrix, &scratch_view->matrix);
        ScaleMatrix(&scratch_view->matrix, &scratch_view->input);

        scratch_view->input.vx = sprite->scale_x;
        scratch_view->input.vy = sprite->scale_y;
        scratch_view->input.vz = 0x1000;
        ScaleMatrix(&scratch_view->matrix, &scratch_view->input);
        SetTransMatrix(&scratch_view->matrix);
        SetRotMatrix(&scratch_view->matrix);

        for (;;) {
            if (!(part->flags & 0x20)) {
                scratch_view->uv_u_start = part->data.texture.u0;
                scratch_view->uv_v_start = part->data.texture.v0;
                scratch_view->uv_u_extent = part->data.texture.width;
                scratch_view->uv_v_extent = part->data.texture.height;
                priority = (DR_PRIO *)packet;
                SetPriority(priority, 0, 0);
                AddPrim(scratch_view->ordering_table + scratch_view->sort_depth, priority);
                packet_next = (POLY_FT4 *)(priority + 1);
                packet = packet_next;

                if ((part->flags ^ scratch_view->sprite_flags) & 1) {
                    coord_x = -part->offset_x;
                    scratch_view->vertices[2].vx = coord_x;
                    scratch_view->vertices[0].vx = coord_x;
                    coord_x -= scratch_view->uv_u_extent;
                    scratch_view->vertices[3].vx = coord_x;
                    scratch_view->vertices[1].vx = coord_x;
                } else {
                    coord_x = part->offset_x;
                    scratch_view->vertices[2].vx = coord_x;
                    scratch_view->vertices[0].vx = coord_x;
                    coord_x += scratch_view->uv_u_extent;
                    scratch_view->vertices[3].vx = coord_x;
                    scratch_view->vertices[1].vx = coord_x;
                }

                if ((part->flags ^ scratch_view->sprite_flags) & 2) {
                    coord_y = -part->offset_y;
                    scratch_view->vertices[1].vy = coord_y;
                    scratch_view->vertices[0].vy = coord_y;
                    coord_y -= scratch_view->uv_v_extent;
                    scratch_view->vertices[3].vy = coord_y;
                    scratch_view->vertices[2].vy = coord_y;
                } else {
                    coord_y = part->offset_y;
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

                packet->x0 = scratch_view->projected_vertices[0].x
                    + scratch_view->screen_origin.x;
                packet->y0 = scratch_view->projected_vertices[0].y
                    + scratch_view->screen_origin.y;
                packet->x1 = scratch_view->projected_vertices[1].x
                    + scratch_view->screen_origin.x;
                packet->y1 = scratch_view->projected_vertices[1].y
                    + scratch_view->screen_origin.y;
                packet->x2 = scratch_view->projected_vertices[2].x
                    + scratch_view->screen_origin.x;
                packet->y2 = scratch_view->projected_vertices[2].y
                    + scratch_view->screen_origin.y;
                packet->x3 = scratch_view->projected_vertices[3].x
                    + scratch_view->screen_origin.x;
                {
                    u16 bottom_y = scratch_view->projected_vertices[3].y;
                    u16 screen_y = scratch_view->screen_origin.y;

                    ((GpuLinkTag *)&packet->tag)->len = 9;
                    packet->y3 = bottom_y + screen_y;
                }

                scratch_view->uv_u_extent += scratch_view->uv_u_start;
                scratch_view->uv_v_extent = (scratch_view->uv_v_start
                    + scratch_view->uv_v_extent) << 8;
                scratch_view->uv_v_start <<= 8;
                uv_word = scratch_view->uv_v_start + scratch_view->uv_u_start;

                {
                    register u32 texture_page;

                    if (part->tpage & 0x80) {

                        texture_page = 0x7F800000;
                        uv_word += texture_page;
                    } else {
                        texture_page = 0x7FC00000;
                        uv_word += texture_page;
                    }

                }
                /* BYTES: retail stores u0, v0 and the CLUT with one sw of the combined word; member stores compile to sb, sb, sh */
                *(s32 *)&packet->u0 = uv_word;
                /* BYTES: retail stores u1, v1 and the texture page with one sw of the combined word; member stores compile to sb, sb, sh */
                *(s32 *)&packet->u1 = scratch_view->uv_v_start +
                                                      scratch_view->uv_u_extent +
                                                      ((s16)part->tpage << 16);
                {
                    s32 bottom_left_uv;
                    s32 u_left;
                    s32 left_x;

                    bottom_left_uv = (u16)scratch_view->uv_v_extent;
                    u_left = (u16)scratch_view->uv_u_start;
                    left_x = packet->x0;
                    bottom_left_uv += u_left;
                    /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                    *(s16 *)&packet->u2 = bottom_left_uv;
                    {
                        s32 bottom_right_uv;
                        s32 u_right;
                        s32 right_x;

                        bottom_right_uv = (u16)scratch_view->uv_v_extent;
                        u_right = (u16)scratch_view->uv_u_extent;
                        right_x = packet->x3;
                        bottom_right_uv += u_right;
                        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                        *(s16 *)&packet->u3 = bottom_right_uv;

                        if (right_x < left_x) {
                            packet->u1--;
                            packet->u3--;
                        }
                    }
                }
                if (packet->y0 > packet->y3) {
                    packet->v2--;
                    packet->v3--;
                }

                /* BYTES: retail copies the sprite colour word (r0, g0, b0 and code) with one lw/sw; member copies compile to four lbu/sb */
                *(s32 *)&packet->r0 = sprite->color.word;
                packet->code = 0x2E;
                AddPrim(scratch_view->ordering_table + scratch_view->sort_depth, packet);
                packet++;
                priority = (DR_PRIO *)packet;
                SetPriority(priority, 1, 0);
                AddPrim(scratch_view->ordering_table + scratch_view->sort_depth, priority);
                packet = (POLY_FT4 *)(priority + 1);
            }

            if ((s8)part->flags >= 0) {

                part++;
                continue;
            }
            break;
        }
        PopMatrix();
    }

    (*root_ptr)->packetCursor = packet;
}
