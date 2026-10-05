#ifdef PERMUTER_PARSER
#define GEOM_SIDE_EFFECTS() (*(GeomSideEffects *)0)
#else
#define GEOM_SIDE_EFFECTS() (GeomSideEffects){}
#endif
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/game_work.h"

#include "m2c_compat.h"
extern u8 D_8006CD10[];
typedef struct S_SCRATCH {
    union {
        s16 s16;
        u16 u16;
    } unk_000;
    u16 unk_002;
    u16 unk_004;
    u8 pad_006[0x2];
    union {
        s32 s32;
        u16 u16;
    } unk_008;
    union {
        s32 s32;
        u16 u16;
    } unk_00C;
    union {
        s32 s32;
        u16 u16;
    } unk_010;
    union {
        s32 s32;
        u16 u16;
    } unk_014;
    u8 *unk_018;
    u8 pad_01C[0x4];
    u8 *unk_020;
    u8 pad_024[0xC];
    s32 unk_030;
    s32 unk_034;
    s32 unk_038;
    u8 pad_03C[0x34];
    u16 unk_070;
    u16 unk_072;
    u16 unk_074;
    u8 pad_076[0x2];
    u16 unk_078;
    u16 unk_07A;
    u16 unk_07C;
    u8 pad_07E[0x2];
    u16 unk_080;
    u16 unk_082;
    u16 unk_084;
    u8 pad_086[0x2];
    u16 unk_088;
    u16 unk_08A;
    u16 unk_08C;
    u8 pad_08E[0x2A];
    u16 unk_0B8;
    u16 unk_0BA;
    u8 pad_0BC[0x4];
    s32 unk_0C0;
    u8 pad_0C4[0x20];
    s32 unk_0E4;
    s32 unk_0E8;
    s32 unk_0EC;
    u16 unk_0F0;
    u16 unk_0F2;
    u16 unk_0F4;
    u16 unk_0F6;
    u16 unk_0F8;
    u16 unk_0FA;
    u16 unk_0FC;
    u16 unk_0FE;
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
} S_SCRATCH;


void func_800478B8();                      /* extern */
M2C_UNK func_80064840(); /* extern */
void func_80064AE0(void *);
M2C_UNK func_80064BC0();              /* extern */
M2C_UNK func_80064CF0();                   /* extern */
M2C_UNK func_80064D80();                   /* extern */
u32 func_80065420(); /* extern */
typedef struct S_800AFA68_part {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_800AFA68_part;
typedef struct GeomSideEffects {
} GeomSideEffects;
u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, GeomSideEffects);
M2C_UNK func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, GeomSideEffects);

M2C_UNK func_80065820();        /* extern */
void func_8006658C(void *, void *);         /* extern */
void func_800666F4(void *);                 /* extern */
u16 func_800BCB04();                   /* extern */
extern M2C_UNK D_8006CD30[8];
extern s32 D_800E296C[3];
extern u8 D_800E3648[128];
typedef struct DebugEntry {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
} DebugEntry;
extern DebugEntry D_800E3648_entries[32] __asm__("D_800E3648");
extern u8 D_800E39C8[1024];

/* Render active dungeon sprite parts and their ground shadows into the ordering table. */
s32 func_800B51C8(void *unused_0, void *unused_1, void *render_params)
{
    u8 saved_matrix[0x20];
    register u8 *transform_dst ASM_REG("$4") = saved_matrix;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 entry_index = 0;
    u8 *rotation_matrix = (u8 *) 0x1F8000D0;
    u8 *view_matrix = (u8 *) 0x1F800050;
    u8 *depth_cue = (u8 *) 0x1F800090;
    u8 *transform_flags = (u8 *) 0x1F800094;

    u8 *game_base = (u8 *)&gameWork;
    u8 *matrix_base;

    S_SCRATCH *scr;
    struct { u16 pitch; u16 yaw; u16 roll; } camera;

    s32 shadow_scale[3];
    u8 *entry_table;
    s32 world_x;
    s32 depth_or_height;
    u16 world_pos_x;
    u16 world_pos_y;
    u16 sprite_yaw;
    u16 view_yaw;
    s32 shadow_yaw;
    u8 world_x_byte;
    u8 world_y_byte;
    u8 sprite_x_byte;
    u8 sprite_y_byte;
    s16 world_corner_x;
    s32 world_corner_y;
    s16 sprite_corner_x;
    s32 sprite_corner_y;
    s32 texture_v;
    s32 scale_component;
    s32 texture_width;
    s32 texture_u;
    s32 texture_height;
    s32 height_scale;
    s32 texture_right;
    s32 texture_bottom;
    s32 texture_extent;
    s32 world_third_visible;
    s32 world_first_visible;
    s32 sprite_third_visible;
    s32 sprite_pair_visible;
    s32 world_second_visible;
    s32 world_fourth_visible;
    s32 world_triple_visible;
    s32 world_pair_visible;
    s32 sprite_triple_visible;
    s32 sprite_second_visible;
    s32 sprite_fourth_visible;
    u16 corner_y_or_height;
    u16 pitch_bits;
    s32 bottom_right_uv;

    u16 ground_height;
    u16 projected_y;
    s32 ground_height_shifted;
    u16 world_z;
    u16 world_y;
    u16 entry_height;
    u32 quad_depth;
    u32 sprite_depth;
    u32 sort_depth;
    u32 adjusted_depth;
    u8 texture_u_byte;
    u8 texture_v_byte;
    u8 texture_width_byte;
    u8 texture_height_byte;
    void *primitive_buffer;
    void *sprite_entry;
    void *quad;
    S_800AFA68_part *part_header;
    void *entry_flags;
    void *render_state;
    scr = (S_SCRATCH *) 0x1F800000;
    render_state = *((void **) (((s8 *) (((struct S_8003E2D8 *)&gameWork))) + 0));
    primitive_buffer = *((void **) (((s8 *) render_state) + 0x8D0));
    scr->unk_020 = render_state + 0xB0;
    scr->unk_08C = 0;
    scr->unk_084 = 0;
    scr->unk_07C = 0;
    scr->unk_074 = 0;
    camera.pitch = *((u16 *) (((s8 *) game_base) + 0xC4));
    camera.yaw = *((u16 *) (((s8 *) game_base) + 0xC6));
    camera.roll = *((u16 *) (((s8 *) game_base) + 0xC8));
    scr->unk_018 = primitive_buffer;
    func_80064AE0(saved_matrix);
    matrix_base = (u8 *)&D_8006CD10 + 32;
    do {
    entry_table = (u8 *) (&D_800E3648);

    entry_flags = (void *) ((entry_index * 4) + ((s32) entry_table));
    if ((((!((*((u8 *) (((s8 *) entry_flags) + 3))) & 0x80)) || (D_800E296C[0] & 8))
         && ((*((u8 *) (((s8 *) entry_flags) + 1))) != 0)) && ((*((u8 *) (((s8 *) entry_flags) + 0))) != 0)) {
        u8 *entry_table;
        entry_table = &D_800E39C8;
        sprite_entry = (entry_index * 0x18) + entry_table;
        if ((*((u16 *) (((s8 *) sprite_entry) + 0x14))) & 0x40) {
            func_800478B8(sprite_entry);
        }
        scr->unk_000.u16 = (s16) (((*((u8 *) (((s8 *) sprite_entry) + 6))) << 6) + 0x20);
        scr->unk_002 = (u16) (((*((u8 *) (((s8 *) sprite_entry) + 7))) << 6) + 0x20);
        entry_height = *((u16 *) (((s8 *) sprite_entry) + 0x12));
        scr->unk_004 = entry_height;
        part_header = *((S_800AFA68_part **) (((s8 *) sprite_entry) + 8));
        *((u16 *) (((s8 *) sprite_entry) + 0x10)) = entry_height;
        if (part_header != 0) {
            if ((*((u16 *) (((s8 *) sprite_entry) + 0x14))) & 0x100) {
                transform_dst = (u8 *)&scr->unk_100;
                world_x = scr->unk_000.s16;
                world_y = scr->unk_002;
                scr->unk_030 = (s32) 0x2000;
                scr->unk_034 = (s32) 0x2000;
                scr->unk_038 = (s32) 0x2000;
                world_z = scr->unk_004;
                scr->unk_100 = 0;
                scr->unk_102 = 0U;
                scr->unk_104 = 0;
                scr->unk_0E4 = (s32) world_x;
                scr->unk_0E8 = (s32) ((s16) world_y);
                scr->unk_0EC = (s32) ((s16) world_z);
                func_80065820(transform_dst, rotation_matrix, world_x);
                func_80064840(&saved_matrix, rotation_matrix, view_matrix);
                func_80064BC0(view_matrix, (u8 *)&scr->unk_030);
                func_80064D80((M2C_UNK *) view_matrix);
                func_80064CF0((M2C_UNK *) view_matrix);
                for (;;) {
                if (!(part_header->unk_00 & 0x20)) {
                    texture_u_byte = part_header->unk_08;
                    scr->unk_008.s32 = (s32) texture_u_byte;
                    texture_width_byte = part_header->unk_0A;
                    scr->unk_010.s32 = (s32) texture_width_byte;
                    if ((texture_u_byte + texture_width_byte) >= 0x100) {
                        scr->unk_010.s32 = texture_width_byte - 1;
                    }
                    texture_v_byte = part_header->unk_09;
                    scr->unk_00C.s32 = (s32) texture_v_byte;
                    texture_height_byte = part_header->unk_0B;
                    scr->unk_014.s32 = (s32) texture_height_byte;
                    if ((texture_v_byte + texture_height_byte) >= 0x100) {
                        scr->unk_014.s32 = texture_height_byte - 1;
                    }
                    {
                        world_x_byte = part_header->unk_02;
                        world_corner_x = (s8) world_x_byte;
                        quad = scr->unk_018;
                        scr->unk_080 = world_corner_x;
                        scr->unk_070 = world_corner_x;
                        world_corner_x += (u16) (scr->unk_010.u16);
                        scr->unk_088 = world_corner_x;
                        scr->unk_078 = world_corner_x;
                        world_y_byte = part_header->unk_03;
                        scr->unk_018 = quad + 0x28;
                        quad_depth = func_80065590((u8 *)&scr->unk_070, (void *)((u8 *)&scr->unk_078), (u8 *)&scr->unk_080,
                            (u8 *)&scr->unk_088, quad + 8, quad + 0x10, quad + 0x18, quad + 0x20,
                            depth_cue, transform_flags,
                            (world_corner_y = (s8) world_y_byte, scr->unk_07A = world_corner_y,
                             scr->unk_072 = world_corner_y,
                             world_corner_y += (u16) (scr->unk_014.u16), scr->unk_08A =
                             world_corner_y, scr->unk_082 = world_corner_y, *((GeomSideEffects *) 0)));
                        scr->unk_0C0 = quad_depth;
                    }
                    if (quad_depth < 0x1E0U) {
                        world_first_visible = 0;
                        if (((u32) (((*((u16 *) (((s8 *) quad) + 8))) + 0x20) & 0xFFFF)) < 0x181U) {
                            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0xA))) + 0x20);
                            world_first_visible = visibility_y < 0x121U;
                        }
                        world_second_visible = 0;
                        if (((u32) (((*((u16 *) (((s8 *) quad) + 0x10))) + 0x20) & 0xFFFF)) < 0x181U) {
                            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x12))) + 0x20);
                            world_second_visible = visibility_y < 0x121U;
                        }
                        world_third_visible = 0;
                        world_pair_visible = world_first_visible | world_second_visible;
                        if (((u32) (((*((u16 *) (((s8 *) quad) + 0x18))) + 0x20) & 0xFFFF)) < 0x181U) {
                            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x1A))) + 0x20);
                            world_third_visible = visibility_y < 0x121U;
                        }
                        world_fourth_visible = 0;
                        world_triple_visible = world_pair_visible | world_third_visible;
                        if (((u32) (((*((u16 *) (((s8 *) quad) + 0x20))) + 0x20) & 0xFFFF)) < 0x181U) {
                            u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x22))) + 0x20);
                            world_fourth_visible = visibility_y < 0x121U;
                        }
                        if ((world_triple_visible | world_fourth_visible) != 0) {
                            texture_width = scr->unk_010.s32;
                            texture_u = scr->unk_008.s32;
                            texture_height = scr->unk_014.s32;
                            texture_v = scr->unk_00C.s32;
                            scr->unk_010.s32 = texture_width + texture_u;
                            scr->unk_014.s32 = texture_height + texture_v;
                            scr->unk_00C.s32 <<= 8;
                            scr->unk_014.s32 <<= 8;
                            *((u16 *) (((s8 *) quad) + 0xE)) = part_header->unk_06;
                            *((s16 *) (((s8 *) quad) + 0xC)) = (s16) (((u16) (scr->unk_00C.u16))
                                + ((u16) (scr->unk_008.u16)));
                            *((s16 *) (((s8 *) quad) + 0x14)) = (s16) (((u16) (scr->unk_00C.u16))
                                + ((u16) (scr->unk_010.u16)));
                            *((u16 *) (((s8 *) quad) + 0x16)) = part_header->unk_04;
                            *((s16 *) (((s8 *) quad) + 0x1C)) = (s16) (((u16) (scr->unk_014.u16))
                                + ((u16) (scr->unk_008.u16)));
                            *((s16 *) (((s8 *) quad) + 0x24)) = (s16) (((u16) (scr->unk_014.u16))
                                + ((u16) (scr->unk_010.u16)));

                            *((s32 *) (((s8 *) quad) + 4)) = (s32) (*((s32 *) (((s8 *) render_params) + 0xC)));
                            func_800666F4(quad);
                            *((u8 *) (((s8 *) quad) + 7)) = (u8) ((*((u8 *) (((s8 *) quad) + 7))) | 2);
                            func_8006658C(((u8 *) (scr->unk_020))
                                + (((s32) (scr->unk_0C0)) * 4), quad);
                        }
                    }
                }

                if ((s8) part_header->unk_00 < 0) {
                    break;
                }
                part_header = part_header + 1;
                }
            } else {
            scr->unk_0E4 = 0;
            scr->unk_0E8 = 0;
            scr->unk_0EC = 0;
            sprite_depth = func_80065420((u8 *)scr, (u8 *)&scr->unk_0B8, (u8 *)scr + 0x90, (u8 *)scr + 0x94);
            scr->unk_0C0 = sprite_depth;
            sprite_depth <<= 2;
            *((s32 *) (((s8 *) matrix_base) + 0x1C)) = sprite_depth;
            sort_depth = scr->unk_0C0;
            adjusted_depth = sort_depth - 4;
            scr->unk_0C0 = adjusted_depth;
            if (adjusted_depth >= 0x1E0U) {
                continue;
            }
            {
                transform_dst = (u8 *)&scr->unk_100;
                scr->unk_0B8 = (u16) ((scr->unk_0B8) - 0xA0);
                pitch_bits = camera.pitch;
                scr->unk_0BA = (u16) ((scr->unk_0BA) - 0x78);

                scr->unk_100 = (s16) ((*((u16 *) (((s8 *) render_params) + 0x16)))
                    + (((s32) (pitch_bits << 0x10)) >> 0x11));
                sprite_yaw = *((u16 *) (((s8 *) render_params) + 0x1A));
                view_yaw = camera.yaw;
                scr->unk_104 = (s16) ((*((u16 *) (((s8 *) game_base) + 0xB8))) + (sprite_yaw
                    - view_yaw));

                scr->unk_102 = (u16) (*((u16 *) (((s8 *) render_params) + 0x18)));
                func_80065820(transform_dst, rotation_matrix, view_yaw);
                func_80064840(&D_8006CD30, rotation_matrix, view_matrix);
                func_80064D80((M2C_UNK *) view_matrix);
                func_80064CF0((M2C_UNK *) view_matrix);
                for (;;) {
                if (!(part_header->unk_00 & 0x20)) {
                    scr->unk_008.s32 = (s32) part_header->unk_08;
                    scr->unk_00C.s32 = (s32) part_header->unk_09;
                    scr->unk_010.s32 = (s32) part_header->unk_0A;
                    scr->unk_014.s32 = (s32) part_header->unk_0B;
                    sprite_x_byte = part_header->unk_02;
                    sprite_corner_x = (s8) sprite_x_byte;
                    scr->unk_080 = sprite_corner_x;
                    scr->unk_070 = sprite_corner_x;
                    sprite_corner_x += (u16) (scr->unk_010.u16);
                    scr->unk_088 = sprite_corner_x;
                    scr->unk_078 = sprite_corner_x;
                    sprite_y_byte = part_header->unk_03;
                    func_800654B0((u8 *)&scr->unk_070, (u8 *)&scr->unk_078, (u8 *)&scr->unk_080, (u8 *)&scr->unk_088, (u8 *)&scr->unk_0F0,
                        (u8 *)&scr->unk_0F4, (u8 *)&scr->unk_0F8, (u8 *)&scr->unk_0FC, depth_cue, transform_flags,
                        (sprite_corner_y = (s8) sprite_y_byte, scr->unk_07A = sprite_corner_y,
                         scr->unk_072 = sprite_corner_y,
                         sprite_corner_y += (u16) (scr->unk_014.u16), scr->unk_08A =
                         sprite_corner_y, scr->unk_082 = sprite_corner_y, *((GeomSideEffects *) 0)));
                    quad = scr->unk_018;
                    scr->unk_018 = quad + 0x28;
                    *((u16 *) (((s8 *) quad) + 8)) = (u16) (((s32) (scr->unk_0F0))
                        + ((s32) (scr->unk_0B8)));
                    *((u16 *) (((s8 *) quad) + 0xA)) = (u16) (((s32) (scr->unk_0F2))
                        + ((s32) (scr->unk_0BA)));
                    *((u16 *) (((s8 *) quad) + 0x10)) = (u16) (((s32) (scr->unk_0F4))
                        + ((s32) (scr->unk_0B8)));
                    *((u16 *) (((s8 *) quad) + 0x12)) = (u16) (((s32) (scr->unk_0F6))
                        + ((s32) (scr->unk_0BA)));
                    *((u16 *) (((s8 *) quad) + 0x18)) = (u16) (((s32) (scr->unk_0F8))
                        + ((s32) (scr->unk_0B8)));
                    *((u16 *) (((s8 *) quad) + 0x1A)) = (u16) (((s32) (scr->unk_0FA))
                        + ((s32) (scr->unk_0BA)));
                    sprite_pair_visible = 0;
                    *((u16 *) (((s8 *) quad) + 0x20)) = (u16) (((s32) (scr->unk_0FC))
                        + ((s32) (scr->unk_0B8)));
                    corner_y_or_height = (u16) (((s32) (scr->unk_0FE)) + ((s32) (*((u16 *) ((u8 *)scr
                        + 0x0ba)))));
                    *((u16 *) (((s8 *) quad) + 0x22)) = corner_y_or_height;
                    if (((u32) (((*((u16 *) (((s8 *) quad) + 8))) + 0x20) & 0xFFFF)) < 0x181U) {
                        u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0xA))) + 0x20);
                        sprite_pair_visible = visibility_y < 0x121U;
                    }
                    sprite_second_visible = 0;
                    if (((u32) (((*((u16 *) (((s8 *) quad) + 0x10))) + 0x20) & 0xFFFF)) < 0x181U) {
                        u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x12))) + 0x20);
                        sprite_second_visible = visibility_y < 0x121U;
                    }
                    sprite_third_visible = 0;
                    sprite_pair_visible |= sprite_second_visible;
                    if (((u32) (((*((u16 *) (((s8 *) quad) + 0x18))) + 0x20) & 0xFFFF)) < 0x181U) {
                        u16 visibility_y = (u16) ((*((u16 *) (((s8 *) quad) + 0x1A))) + 0x20);
                        sprite_third_visible = visibility_y < 0x121U;
                    }
                    sprite_fourth_visible = 0;
                    sprite_triple_visible = sprite_pair_visible | sprite_third_visible;
                    if (((u32) (((*((u16 *) (((s8 *) quad) + 0x20))) + 0x20) & 0xFFFF)) < 0x181U) {
                        u16 visibility_y = (u16) (corner_y_or_height + 0x20);
                        sprite_fourth_visible = visibility_y < 0x121U;
                    }
                    if ((sprite_triple_visible | sprite_fourth_visible) != 0) {
                        *((s8 *) (((s8 *) quad) + 3)) = 9;
                        texture_extent = ((s32) (scr->unk_010.s32)) - 1;
                        texture_right = texture_extent + ((s32) (scr->unk_008.s32));
                        scr->unk_010.s32 = texture_right;
                        if (texture_right & 0x100) {
                            scr->unk_010.s32 = texture_right - 1;
                        }
                        texture_extent = ((s32) (scr->unk_014.s32)) - 1;
                        texture_bottom = texture_extent + ((s32) (scr->unk_00C.s32));
                        scr->unk_014.s32 = texture_bottom;
                        if (texture_bottom & 0x100) {
                            scr->unk_014.s32 = texture_bottom - 1;
                        }
                        scr->unk_00C.s32 <<= 8;
                        scr->unk_014.s32 <<= 8;
                        *((s16 *) (((s8 *) quad) + 0xC)) = (s16) (((u16) (scr->unk_00C.u16))
                            + ((u16) (scr->unk_008.u16)));
                        *((u16 *) (((s8 *) quad) + 0xE)) = part_header->unk_06;
                        *((s16 *) (((s8 *) quad) + 0x14)) = (s16) (((u16) (scr->unk_00C.u16))
                            + ((u16) (scr->unk_010.u16)));
                        *((u16 *) (((s8 *) quad) + 0x16)) = part_header->unk_04;
                        *((s16 *) (((s8 *) quad) + 0x1C)) = (s16) (((u16) (scr->unk_014.u16))
                            + ((u16) (scr->unk_008.u16)));
                        bottom_right_uv = ((u16) (scr->unk_014.u16)) + ((u16) (*((u16 *) ((u8 *)scr
                            + 0x010))));
                        *((s16 *) (((s8 *) quad) + 0x24)) = (s16) bottom_right_uv;
                        if (((s16) (*((u16 *) (((s8 *) quad) + 8)))) > ((s16) (*((u16 *) (((s8 *) quad) + 0x20))))) {
                            *((u8 *) (((s8 *) quad) + 0x14)) = (u8) ((*((u8 *) (((s8 *) quad) + 0x14))) - 1);
                            *((u8 *) (((s8 *) quad) + 0x24)) = (u8) ((*((u8 *) (((s8 *) quad) + 0x24))) - 1);
                        }
                        if (((s16) (*((u16 *) (((s8 *) quad) + 0xA)))) > ((s16) (*((u16 *) (((s8 *) quad) + 0x22))))) {
                            *((u8 *) (((s8 *) quad) + 0x1D)) = (u8) ((*((u8 *) (((s8 *) quad) + 0x1D))) - 1);
                            *((u8 *) (((s8 *) quad) + 0x25)) = (u8) ((*((u8 *) (((s8 *) quad) + 0x25))) - 1);
                        }

                        *((s32 *) (((s8 *) quad) + 4)) = (s32) (*((s32 *) (((s8 *) render_params) + 0xC)));
                        *((u8 *) (((s8 *) quad) + 7)) = 0x2CU;
                        if ((D_800E296C[0] & 8) && (D_800E3648_entries[entry_index].b3 & 0x80)) {
                            *((u8 *) (((s8 *) quad) + 7)) = 0x2EU;
                        }
                        func_8006658C(((u8 *) (scr->unk_020))
                            + (((s32) (scr->unk_0C0)) * 4), quad);
                        if (!((*((u8 *) (((s8 *) quad) + 7))) & 2)) {
                            func_80064D80(&saved_matrix);
                            func_80064CF0(&saved_matrix);
                            world_pos_x = scr->unk_000.u16;
                            world_pos_y = scr->unk_002;
                            corner_y_or_height = scr->unk_004;
                            ASM_USE2_NV(world_pos_x, corner_y_or_height);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                            depth_or_height = (s16) corner_y_or_height;
                            depth_or_height -= 4;
                            shadow_scale[2] = depth_or_height;
                            scr->unk_004 = func_800BCB04(world_pos_x, world_pos_y,
                                (s16) depth_or_height);
                            depth_or_height = func_80065420((u8 *)scr, (u8 *)&scr->unk_0B8, depth_cue, transform_flags);
                            scr->unk_0C0 = depth_or_height;
                            depth_or_height = (u32)depth_or_height * 4;
                            *((s32 *) (((s8 *) matrix_base) + 0x1C)) = depth_or_height;
                            scr->unk_0C0 -= 3;
                            projected_y = scr->unk_0BA;
                            scr->unk_0B8 = (u16) ((scr->unk_0B8) - 0xA0);
                            ground_height = scr->unk_004;
                            ground_height_shifted = ((s32) ground_height) << 0x10;
                            scr->unk_0BA = (u16) (projected_y - 0x78);
                            height_scale = ((shadow_scale[2] - (ground_height_shifted >> 0x10)) << 5) + 0x1000;
                            shadow_scale[2] = height_scale;
                            if (height_scale < 0) {
                                shadow_scale[2] = 0;
                            }
                            transform_dst = (u8 *)&scr->unk_100;
                            scale_component = shadow_scale[2];
                            scr->unk_102 = 0U;
                            shadow_scale[0] = scale_component;
                            scale_component += (s32) (((u32) scale_component) >> 0x1F);
                            scale_component >>= 1;
                            shadow_scale[1] = scale_component;
                            {
                                u16 shadow_pitch = (u16) (0 - camera.pitch);
                                u16 shadow_roll = (u16) ((*((u16 *) (((s8 *) game_base) + 0xB8))) - camera.yaw);
                                scr->unk_100 = (s16) shadow_pitch;
                                scr->unk_104 = (s16) shadow_roll;
                            }
                            func_80065820(transform_dst, rotation_matrix);
                            func_80064840(&D_8006CD30, rotation_matrix, view_matrix);
                            func_80064BC0(view_matrix, shadow_scale);
                            func_80064D80((M2C_UNK *) view_matrix);
                            func_80064CF0((M2C_UNK *) view_matrix);
                            {
                                u16 right_x;
                                u16 left_x;
                                quad = scr->unk_018;
                                func_800654B0((u8 *)&scr->unk_070, (void *)((u8 *)&scr->unk_078), (u8 *)&scr->unk_080,
                                    (u8 *)&scr->unk_088, (u8 *)&scr->unk_0F0, (u8 *)&scr->unk_0F4, (u8 *)&scr->unk_0F8, (u8 *)&scr->unk_0FC,
                                    depth_cue, transform_flags,
                                    (left_x = scr->unk_070,
                                     scr->unk_018 = ((u8 *) quad) + 0x28, right_x =
                                     scr->unk_078, left_x += 6, scr->unk_070 = left_x,
                                     right_x += 6, scr->unk_078 = right_x, *((GeomSideEffects *) 0)));
                            }
                            *((u16 *) (((s8 *) quad) + 8)) =
                                (u16) (((s32) (scr->unk_0F0)) + ((s32) (scr->unk_0B8)));
                            *((u16 *) (((s8 *) quad) + 0xA)) =
                                (u16) (((s32) (scr->unk_0F2)) + ((s32) (scr->unk_0BA)));
                            *((u16 *) (((s8 *) quad) + 0x10)) =
                                (u16) (((s32) (scr->unk_0F4)) + ((s32) (scr->unk_0B8)));
                            *((u16 *) (((s8 *) quad) + 0x12)) =
                                (u16) (((s32) (scr->unk_0F6)) + ((s32) (scr->unk_0BA)));
                            *((u16 *) (((s8 *) quad) + 0x18)) =
                                (u16) (((s32) (scr->unk_0F8)) + ((s32) (scr->unk_0B8)));
                            *((u16 *) (((s8 *) quad) + 0x1A)) =
                                (u16) (((s32) (scr->unk_0FA)) + ((s32) (scr->unk_0BA)));
                            *((u16 *) (((s8 *) quad) + 0x20)) =
                                (u16) (((s32) (scr->unk_0FC)) + ((s32) (scr->unk_0B8)));
                            *((u16 *) (((s8 *) quad) + 0x22)) =
                                (u16) (((s32) (scr->unk_0FE)) + ((s32) (scr->unk_0BA)));
                            *((s8 *) (((s8 *) quad) + 3)) = 9;
                            *((s32 *) (((s8 *) quad) + 0xC)) =
                                (((s32) (scr->unk_00C.s32)) + ((s32) (scr->unk_008.s32)))
                            + 0x7FC00000;
                            shadow_yaw = (s32) (scr->unk_00C.s32);
                            shadow_yaw += ((s32) (scr->unk_010.s32));
                            *((s32 *) (((s8 *) quad) + 0x14)) =
                                shadow_yaw + ((*(s16 *)&part_header->unk_04) << 0x10);
                            *((s16 *) (((s8 *) quad) + 0x1C)) =
                                (s16) (((u16) (scr->unk_014.u16)) + ((u16) (scr->unk_008.u16)));
                            *((s16 *) (((s8 *) quad) + 0x24)) =
                                (s16) (((u16) (scr->unk_014.u16)) + ((u16) (scr->unk_010.u16)));
                            if (((s16) (*((u16 *) (((s8 *) quad) + 8))))
                                > ((s16) (*((u16 *) (((s8 *) quad) + 0x20))))) {
                                *((u8 *) (((s8 *) quad) + 0x14)) =
                                    (u8) ((*((u8 *) (((s8 *) quad) + 0x14))) - 1);
                                *((u8 *) (((s8 *) quad) + 0x24)) =
                                    (u8) ((*((u8 *) (((s8 *) quad) + 0x24))) - 1);
                            }
                            if (((s16) (*((u16 *) (((s8 *) quad) + 0xA))))
                                > ((s16) (*((u16 *) (((s8 *) quad) + 0x22))))) {
                                *((u8 *) (((s8 *) quad) + 0x1D)) =
                                    (u8) ((*((u8 *) (((s8 *) quad) + 0x1D))) - 1);
                                *((u8 *) (((s8 *) quad) + 0x25)) =
                                    (u8) ((*((u8 *) (((s8 *) quad) + 0x25))) - 1);
                            }

                            *((s32 *) (((s8 *) quad) + 4)) =
                                (s32) (*((s32 *) (((s8 *) render_params) + 0xC)));
                            *((u8 *) (((s8 *) quad) + 7)) = 0x2CU;
                            func_8006658C(((u8 *) (scr->unk_020))
                                + (((s32) (scr->unk_0C0)) * 4), quad);
                        }
                    }
                }

                if ((s8) part_header->unk_00 < 0) {
                    break;
                }
                part_header = part_header + 1;
                }
            }
            }
            func_80064D80(&saved_matrix);
            func_80064CF0(&saved_matrix);
        }
    }
    } while (++entry_index < 0x20);
    *((void **) (((s8 *) (*((void **) (((s8 *) game_base) + 0)))) + 0x8D0)) =
        (void *) (scr->unk_018);
    return 0;
}
