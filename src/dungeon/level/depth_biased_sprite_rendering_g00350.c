/* Depth biased sprite rendering (G00350). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B6D74. */
#include "dungeon/level/depth_biased_sprite_rendering_g00350.h"

/* Traverse object nodes backward and process unflagged primitives with their computed depth. */
s32 traverse_nodes_and_render_unflagged(void *start_node) {
    void *node = start_node;
    GameWork *state = &g_game_work;
    u16 *scratch = (u16 *)0x1F800000;
    void *previous;

    scratch[0x80] = -((u16)state->view.camera_rotation.parts.camera_rotation_x);
    scratch[0x81] = -((u16)state->view.camera_rotation.parts.camera_rotation_y);
    scratch[0x82] = ((u16)state->view.view_rotation_offset.parts.view_rotation_offset_z);

    for (;;) {
        S_800BC3E4_1 *object = ((S_800BC3E4_0 *)node)->unk_00;
        S_800BC3E4_2 *primitive = object->unk_0C;

        if (!(primitive->unk_14 & 0x8000)) {
            S_800BC3E4_3 *coord = object->unk_08;
            s16 depth = sample_terrain_surface_height(coord->unk_02, coord->unk_06, coord->unk_0A);
            render_projected_sprite_with_depth_bias(coord, primitive, depth, 0);
            if (is_frame_packet_arena_overflowed(((S_800BC3E4_5 *)(state->draw_buffer))->unk_8D0) != 0) {
                break;
            }
        }
        previous = ((S_800BC3E4_0_pre *)node)[-1].unk_00;
        if (previous == 0) {
            break;
        }
        node = (u8 *)previous + 0x20;
    }
    return 0;
}

/* Project sprite tiles and append textured quads to the ordering table. */
void render_projected_sprite_with_depth_bias(void *position, void *sprite, s16 world_z, s32 depth_bias)
{
    u8 *scratch_base = (u8 *)0x1F800000;
    u8 *screen_pos = scratch_base;
    u8 *perspective;
    u8 *clip_flags;
    u8 *scratch;
    u8 **root_ptr;
    u8 *matrix;
    u8 *packet;
    u8 *packet_next;
    u8 *texture;
    u8 *root;
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

    screen_pos = (u8 *)((u32)screen_pos | 0xB8);
    perspective = scratch_base;
    scratch = scratch_base;
    perspective = (u8 *)((u32)perspective | 0x90);
    root = *(u8 **)((u8 *)(&g_game_work));
    packet = ((GpuContext *)root)->packetCursor;
    ((S_800BC4D4_1 *)scratch)->unk_20 = root + 0xB0;
    ((S_800BC4D4_1 *)scratch)->unk_EC = 0;
    ((S_800BC4D4_1 *)scratch)->unk_E8 = 0;
    ((S_800BC4D4_1 *)scratch)->unk_E4 = 0;
    ((S_800BC4D4_1 *)scratch)->unk_8C = 0;
    ((S_800BC4D4_1 *)scratch)->unk_84 = 0;
    ((S_800BC4D4_1 *)scratch)->unk_7C = 0;
    ((S_800BC4D4_1 *)scratch)->unk_74 = 0;

    texture = ((S_800BC4D4_2 *)sprite)->unk_08;
    sprite_flags = ((S_800BC4D4_2 *)sprite)->unk_14;
    clip_flags = scratch_base;
    ((S_800BC4D4_1 *)scratch)->unk_24 = sprite_flags;
    world_x = ((S_800BC4D4_3 *)position)->unk_02;
    clip_flags = (u8 *)((u32)clip_flags | 0x94);
    ((S_800BC4D4_1 *)scratch)->unk_00 = world_x;
    world_y = ((S_800BC4D4_3 *)position)->unk_06;
    root_ptr = (u8 **)&g_game_work;
    ((S_800BC4D4_1 *)scratch)->unk_02 = world_y;
    ((S_800BC4D4_1 *)scratch)->unk_04 = world_z;

    projected_depth = func_80065420(scratch_base, screen_pos,
                              perspective, clip_flags);
    matrix = sprite_projection_matrix;
    ((S_800BC4D4_1 *)scratch)->unk_C0 = projected_depth;
    ((S_800BC4D4_4 *)matrix)->unk_1C = projected_depth * 4;
    biased_depth = projected_depth - 7;
    ot_index = biased_depth - depth_bias;
    ((S_800BC4D4_1 *)scratch)->unk_C0 = ot_index;

    if (ot_index < 0x1E0U) {
        func_800649A0();

        screen_x = ((S_800BC4D4_1 *)scratch)->unk_B8;
        sprite_z = ((S_800BC4D4_1 *)scratch)->unk_04;
        ((S_800BC4D4_1 *)scratch)->unk_B8 = screen_x - 0xA0;
        ((S_800BC4D4_1 *)scratch)->unk_BA -= 0x78;
        scale = ((((S_800BC4D4_3 *)position)->unk_0A - (s16)sprite_z) << 5) + 0x1000;
        ((S_800BC4D4_1 *)scratch)->unk_38 = scale;
        if (scale < 0) {
            ((S_800BC4D4_1 *)scratch)->unk_38 = 0;
        }

        clamped_scale = ((S_800BC4D4_1 *)scratch)->unk_38;
        ((S_800BC4D4_1 *)scratch)->unk_30.s = clamped_scale;
        ((S_800BC4D4_1 *)scratch)->unk_34.s = (s32)(clamped_scale + ((u32)clamped_scale >> 31)) >> 1;
        func_80065820((void *)0x1F800100, (void *)0x1F8000D0);

        func_80064840(matrix, (void *)0x1F8000D0, (void *)0x1F800050);
        func_80064BC0((void *)0x1F800050, (void *)0x1F800030);

        ((S_800BC4D4_1 *)scratch)->unk_30.u = ((S_800BC4D4_2 *)sprite)->unk_1C;
        ((S_800BC4D4_1 *)scratch)->unk_34.u = ((S_800BC4D4_2 *)sprite)->unk_1E;
        ((S_800BC4D4_1 *)scratch)->unk_38 = 0x1000;
        func_80064BC0((void *)0x1F800050, (void *)0x1F800030);
        func_80064D80((void *)0x1F800050);
        func_80064CF0((void *)0x1F800050);

        for (;;) {
            if (!(texture[0] & 0x20)) {
                ((S_800BC4D4_1 *)scratch)->unk_08.u32 = texture[8];
                ((S_800BC4D4_1 *)scratch)->unk_0C.u = texture[9];
                ((S_800BC4D4_1 *)scratch)->unk_10.u32 = texture[10];
                ((S_800BC4D4_1 *)scratch)->unk_14.u32 = texture[11];
                func_80067EF4(packet, 0, 0);
                                func_8006658C(((S_800BC4D4_1 *)scratch)->unk_20 +
                              ((S_800BC4D4_1 *)scratch)->unk_C0 * 4,
                              packet);
                packet_next = packet + 0xC;
                packet = packet_next;

                if ((texture[0] ^ ((S_800BC4D4_1 *)scratch)->unk_24) & 1) {
                    coord_x = -(s8)texture[2];
                    ((S_800BC4D4_1 *)scratch)->unk_80 = coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_70.s = coord_x;
                    coord_x -= ((S_800BC4D4_1 *)scratch)->unk_10.u16;
                    ((S_800BC4D4_1 *)scratch)->unk_88 = coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_78.s = coord_x;
                } else {
                    coord_x = (s8)texture[2];
                    ((S_800BC4D4_1 *)scratch)->unk_80 = coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_70.s = coord_x;
                    coord_x += ((S_800BC4D4_1 *)scratch)->unk_10.u16;
                    ((S_800BC4D4_1 *)scratch)->unk_88 = coord_x;
                    ((S_800BC4D4_1 *)scratch)->unk_78.s = coord_x;
                }

                if ((texture[0] ^ ((S_800BC4D4_1 *)scratch)->unk_24) & 2) {
                    coord_y = -(s8)texture[3];
                    ((S_800BC4D4_1 *)scratch)->unk_7A = coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_72 = coord_y;
                    coord_y -= ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                    ((S_800BC4D4_1 *)scratch)->unk_8A = coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_82 = coord_y;
                } else {
                    coord_y = (s8)texture[3];
                    ((S_800BC4D4_1 *)scratch)->unk_7A = coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_72 = coord_y;
                    coord_y += ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                    ((S_800BC4D4_1 *)scratch)->unk_8A = coord_y;
                    ((S_800BC4D4_1 *)scratch)->unk_82 = coord_y;
                }

                ((S_800BC4D4_1 *)scratch)->unk_70.u += 6;
                ((S_800BC4D4_1 *)scratch)->unk_78.u += 6;
                func_800654B0((s16 *)(scratch + 0x70), (s16 *)(scratch + 0x78),
                              (s16 *)(scratch + 0x80), (s16 *)(scratch + 0x88),
                              (s16 *)(scratch + 0xF0), (s16 *)(scratch + 0xF4),
                              (s16 *)(scratch + 0xF8), (s16 *)(scratch + 0xFC),
                              (s16 *)(scratch + 0x90), (s16 *)(scratch + 0x94));

                (*(s16 *)(packet + 8)) = ((S_800BC4D4_1 *)scratch)->unk_F0
                    + ((S_800BC4D4_1 *)scratch)->unk_B8;
                (*(s16 *)(packet + 10)) = ((S_800BC4D4_1 *)scratch)->unk_F2
                    + ((S_800BC4D4_1 *)scratch)->unk_BA;
                (*(s16 *)(packet + 16)) = ((S_800BC4D4_1 *)scratch)->unk_F4
                    + ((S_800BC4D4_1 *)scratch)->unk_B8;
                (*(s16 *)(packet + 18)) = ((S_800BC4D4_1 *)scratch)->unk_F6
                    + ((S_800BC4D4_1 *)scratch)->unk_BA;
                (*(s16 *)(packet + 24)) = ((S_800BC4D4_1 *)scratch)->unk_F8
                    + ((S_800BC4D4_1 *)scratch)->unk_B8;
                (*(s16 *)(packet + 26)) = ((S_800BC4D4_1 *)scratch)->unk_FA
                    + ((S_800BC4D4_1 *)scratch)->unk_BA;
                (*(s16 *)(packet + 32)) = ((S_800BC4D4_1 *)scratch)->unk_FC
                    + ((S_800BC4D4_1 *)scratch)->unk_B8;
                {
                    u16 bottom_y = ((S_800BC4D4_1 *)scratch)->unk_FE;
                    u16 screen_y = ((S_800BC4D4_1 *)scratch)->unk_BA;

                    ((S_800BC4D4_5_pre *)(packet + 7))[-1].unk_00 = 9;
                    (*(s16 *)(packet + 34)) = bottom_y + screen_y;
                }

                ((S_800BC4D4_1 *)scratch)->unk_10.s32 += ((S_800BC4D4_1 *)scratch)->unk_08.s32;
                ((S_800BC4D4_1 *)scratch)->unk_14.s32 = (((S_800BC4D4_1 *)scratch)->unk_0C.s
                    + ((S_800BC4D4_1 *)scratch)->unk_14.s32) << 8;
                ((S_800BC4D4_1 *)scratch)->unk_0C.s <<= 8;
                uv_word = ((S_800BC4D4_1 *)scratch)->unk_0C.s + ((S_800BC4D4_1 *)scratch)->unk_08.s32;

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
                (*(s32 *)(packet + 20)) = ((S_800BC4D4_1 *)scratch)->unk_0C.s +
                                                      ((S_800BC4D4_1 *)scratch)->unk_10.s32 +
                                                      ((s16)((S_800BC4D4_6 *)(texture + 4))->unk_00 << 16);
                {
                    s32 uv_left;
                    s32 u_left;
                    s32 left_x;

                    uv_left = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                    u_left = (*(u16 *)((u8 *)scratch + 8));
                    left_x = (*(s16 *)(packet + 8));
                    uv_left += u_left;
                    (*(s16 *)(packet + 28)) = uv_left;
                    {
                        s32 uv_right;
                        s32 u_right;
                        s32 right_x;

                        uv_right = ((S_800BC4D4_1 *)scratch)->unk_14.u16;
                        u_right = ((S_800BC4D4_1 *)scratch)->unk_10.u16;
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

                (*(s32 *)(packet + 4)) = ((S_800BC4D4_2 *)sprite)->unk_0C;
                ((S_800BC4D4_5 *)(packet + 7))->unk_00 = 0x2E;
                                func_8006658C(((S_800BC4D4_1 *)scratch)->unk_20 +
                              ((S_800BC4D4_1 *)scratch)->unk_C0 * 4,
                              packet);
                                packet += 0x28;
                func_80067EF4(packet, 1, 0);
                func_8006658C(((S_800BC4D4_1 *)scratch)->unk_20 +
                              ((S_800BC4D4_1 *)scratch)->unk_C0 * 4,
                              packet);
                packet += 0xC;
            }

            if ((s8)texture[0] >= 0) {

                texture += 0xC;
                continue;
            }
            break;
        }
        func_80064A40();
    }

    ((GpuContext *)(*root_ptr))->packetCursor = packet;
}
