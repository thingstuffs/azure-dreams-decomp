/* Mesh and point rendering, star effects, and projectile trails with target hit animation. */
#include "modules/dungeon_native_abi.h"
#include "shared/sprite_frame_state.h"

typedef struct S_func_8187A800_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_func_8187A800_0;

extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void adjust_source_value_and_finalize(void *, void *);
extern s32 try_trigger_target_record_effect(void *, s32);
extern s32 set_or_clear_actor_status_slot(void *, s32, s8);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 get_random_scaled_value(s16 input_value);

void update_projectile_trail_and_hit_effect(void *, void *, void *);
void (*const dungeon_189a800_entry)(void *, void *, void *) = update_projectile_trail_and_hit_effect;
const u8 D_80024004[48] = {0x82,0x73,0x82,0x88,0x82,0x85,0x82,0x92,0x82,0x85,0x81,0x40,0x82,0x97,0x82,0x81,0x82,0x93,0x81,0x40,0x82,0x8e,0x82,0x8f,0x81,0x40,0x82,0x85,0x82,0x86,0x82,0x86,0x82,0x85,0x82,0x83,0x82,0x94,0x81,0x40,0x82,0x8f,0x82,0x8e,0x81,0x40,0x0,0x0};
const u8 D_80024034[4] = {0x81,0x44,0x0,0x0};
extern s32 D_800E1CB0;

void func_800240B8(S_func_8187A800_0 *target, s32 effect_arg, SpriteFrameState *unused);

/* Attempts to apply an effect and reports the outcome for flagged targets. */
void func_800240B8(S_func_8187A800_0 *target, s32 effect_arg, SpriteFrameState *unused)
{
    s32 message;
    s32 message_start;

    if (try_trigger_target_record_effect(target, 4) == 0) {
        if ((set_or_clear_actor_status_slot(target, 0x14,
                           (s8)(get_random_scaled_value(effect_arg & 0xFF) + 2)) << 16) != 0) {
            if (target->unk_14 & 0x4000) {
                adjust_source_value_and_finalize(target, &D_800E1CB0);
                return;
            }
        } else if (target->unk_14 & 0x4000) {
            message = get_unused_text_buffer();
            message_start = message;
            message = expand_text_control_codes(&D_80024004, message);
            message = append_entity_display_text(target, message);
            message = expand_text_control_codes(&D_80024034, message);
            clear_byte_and_advance(message);
            display_text_with_fullwidth_adjustment(message_start);
        }
    }
}
#include "modules/dungeon_ovl_189a800.h"
#include "modules/dungeon_native_abi.h"
#include "shared/game_work.h"

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef struct {} EmptyArg;

typedef struct S_func_800241A8_1 {
    u8 pad_00[0xC];
    union {
        s32 as_s32_0C;
        u16 as_u16_0C;
    } unk_0C;
    union {
        s32 as_s32_10;
        u16 as_u16_10;
    } unk_10;
    union {
        s32 as_s32_14;
        u16 as_u16_14;
    } unk_14;
    union {
        s32 as_s32_18;
        u16 as_u16_18;
    } unk_18;
    u8 pad_1C[0x8];
    void * unk_24;
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    union {
        s16 as_s16_B0;
        u16 as_u16_B0;
    } unk_B0;
    union {
        s16 as_s16_B2;
        u16 as_u16_B2;
    } unk_B2;
    union {
        s16 as_s16_B4;
        u16 as_u16_B4;
    } unk_B4;
    u8 pad_B6[0x2];
    union {
        s16 as_s16_B8;
        u16 as_u16_B8;
    } unk_B8;
    union {
        s16 as_s16_BA;
        u16 as_u16_BA;
    } unk_BA;
    union {
        s16 as_s16_BC;
        u16 as_u16_BC;
    } unk_BC;
    u8 pad_BE[0x2];
    union {
        s16 as_s16_C0;
        u16 as_u16_C0;
    } unk_C0;
    union {
        s16 as_s16_C2;
        u16 as_u16_C2;
    } unk_C2;
    union {
        s16 as_s16_C4;
        u16 as_u16_C4;
    } unk_C4;
    u8 pad_C6[0x2];
    union {
        s16 as_s16_C8;
        u16 as_u16_C8;
    } unk_C8;
    union {
        s16 as_s16_CA;
        u16 as_u16_CA;
    } unk_CA;
    union {
        s16 as_s16_CC;
        u16 as_u16_CC;
    } unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_func_800241A8_1;

typedef struct S_func_800241A8_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_func_800241A8_5;

typedef struct S_func_800241A8_6 {
    union {
        u32 as_u32_00;
        struct {
            u8 pad_00[0x3];
            u8 unk_03;
        } as_u8_03;
    } unk_00;
    union {
        u32 as_u32_04;
        struct {
            u8 pad_04[0x3];
            u8 unk_07;
        } as_u8_07;
    } unk_04;
    union {
        s16 as_s16_08;
        u16 as_u16_08;
    } unk_08;
    union {
        s16 as_s16_0A;
        u16 as_u16_0A;
    } unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    union {
        u16 as_u16_14;
        u8 as_u8_14;
    } unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    union {
        u16 as_u16_1C;
        struct {
            u8 pad_1C[0x1];
            u8 unk_1D;
        } as_u8_1D;
    } unk_1C;
    u8 pad_1E[0x2];
    union {
        s16 as_s16_20;
        u16 as_u16_20;
    } unk_20;
    union {
        s16 as_s16_22;
        u16 as_u16_22;
    } unk_22;
    union {
        u16 as_u16_24;
        u8 as_u8_24;
        struct {
            u8 pad_24[0x1];
            u8 unk_25;
        } as_u8_25;
    } unk_24;
} S_func_800241A8_6;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, EmptyArg);
extern void func_80065820(void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u32, s32);

typedef struct {
    u8 flags;
    u8 texture_flags;
    u8 pad_02[0x2];
    u16 tpage;
    u16 clut;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} MeshTexture;

typedef struct {
    unsigned addr: 24;
    unsigned len: 8;
} P_TAG;
#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u32)(_addr))
#define getaddr(p) (u32)(((P_TAG *)(p))->addr)

/* Transform the mesh and enqueue textured quads or lines in the ordering table. */
void transform_and_queue_mesh_primitives(S_func_800241A8_4 *mesh, SignedPositionView *transform, S_func_800241A8_3 *object, s32 depth_bias)
{
    S_func_800241A8_1 *scratch = (S_func_800241A8_1 *)0x1F800000;
    MeshTexture *texture;
    s32 depth_offset;
    MATRIX matrix;
    u32 render_flags;
    GameWork *game_work;

    game_work = &g_game_work;
    scratch->unk_24 = (u8 *)game_work->draw_buffer + 0xB0;
    scratch->unk_88 = transform->unk_02;
    scratch->unk_8C = transform->unk_06;
    scratch->unk_90 = transform->unk_0A;
    ((SpriteFrameState *)object)->flags |= 0x8000;

    func_800649A0();

    scratch->unk_3C = 0x2000;
    scratch->unk_38 = 0x2000;
    scratch->unk_34 = 0x2000;
    scratch->unk_A4 = ((SpriteFrameState *)object)->angle_x;
    scratch->unk_A8 = ((SpriteFrameState *)object)->angle_z;
    scratch->unk_A6 = ((SpriteFrameState *)object)->angle_y;
    func_80065820(&scratch->unk_A4, (u8 *)scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, (u8 *)scratch + 0x74, (u8 *)scratch + 0x54);
    func_80064BC0((u8 *)scratch + 0x54, &scratch->unk_34);
    func_80064D80((u8 *)scratch + 0x54);
    func_80064CF0((u8 *)scratch + 0x54);

    depth_offset = (s16)depth_bias;
    texture = ((SpriteFrameState *)object)->source;
    scratch->unk_28 = ((SpriteFrameState *)object)->flags;

    for (;;) {
        if (mesh->unk_4E != 0) {
            S_func_800241A8_6 *packet;
            s32 ot_index;
            u8 texture_flags;
            s32 texture_adjust;
            S_func_800241A8_5 *render_state;

            render_state = game_work->draw_buffer;
            packet = render_state->unk_8D0;
            render_state->unk_8D0 = (u8 *)packet + 0x28;

            scratch->unk_0C.as_s32_0C = texture->r;
            scratch->unk_10.as_s32_10 = texture->g;
            scratch->unk_14.as_s32_14 = texture->b;
            scratch->unk_18.as_s32_18 = texture->a;

            scratch->unk_B0.as_u16_B0 = mesh->unk_58.as_u16_58;
            scratch->unk_B8.as_u16_B8 = mesh->unk_5A.as_u16_5A;
            scratch->unk_C0.as_u16_C0 = mesh->unk_5C.as_u16_5C;
            scratch->unk_C8.as_u16_C8 = mesh->unk_5E.as_u16_5E;
            scratch->unk_B2.as_u16_B2 = mesh->unk_60.as_u16_60;
            scratch->unk_BA.as_u16_BA = mesh->unk_62.as_u16_62;
            scratch->unk_C2.as_u16_C2 = mesh->unk_64.as_u16_64;
            scratch->unk_CA.as_u16_CA = mesh->unk_66.as_u16_66;
            scratch->unk_B4.as_u16_B4 = mesh->unk_68.as_u16_68;
            scratch->unk_BC.as_u16_BC = mesh->unk_6A.as_u16_6A;
            scratch->unk_C4.as_u16_C4 = mesh->unk_6C.as_u16_6C;
            scratch->unk_CC.as_u16_CC = mesh->unk_6E.as_u16_6E;

            ot_index = func_80065590(&scratch->unk_B0.as_s16_B0, &scratch->unk_B8.as_s16_B8,
                                     &scratch->unk_C0.as_s16_C0, &scratch->unk_C8.as_s16_C8,
                                     &packet->unk_08.as_s16_08, &packet->unk_10,
                                     &packet->unk_18, &packet->unk_20.as_s16_20,
                                     (u8 *)scratch + 0xD0, (u8 *)scratch + 0xD4,
                                     ({ EmptyArg empty; empty; })) - depth_offset - 6;
            scratch->unk_100 = ot_index;

            if ((u32)ot_index < 0x1E0 &&
                ((((u16)(packet->unk_08.as_u16_08 + 0x20) < 0x181) &&
                  ((u16)(packet->unk_0A.as_u16_0A + 0x20) < 0x121)) |
                 (((u16)(packet->unk_10 + 0x20) < 0x181) &&
                  ((u16)(packet->unk_12 + 0x20) < 0x121)) |
                 (((u16)(packet->unk_18 + 0x20) < 0x181) &&
                  ((u16)(packet->unk_1A + 0x20) < 0x121)) |
                 (((u16)(packet->unk_20.as_u16_20 + 0x20) < 0x181) &&
                  ((u16)(packet->unk_22.as_u16_22 + 0x20) < 0x121)))) {
                packet->unk_00.as_u8_03.unk_03 = 9;
                packet->unk_04.as_u8_07.unk_07 = 0x2C;
                ((SpriteFrameState *)object)->flags &= 0x7FFF;

                scratch->unk_14.as_s32_14 += scratch->unk_0C.as_s32_0C;
                if (scratch->unk_14.as_s32_14 & 0x100) {
                    scratch->unk_14.as_s32_14--;
                }
                scratch->unk_18.as_s32_18 += scratch->unk_10.as_s32_10;
                if (scratch->unk_18.as_s32_18 & 0x100) {
                    scratch->unk_18.as_s32_18--;
                }
                scratch->unk_10.as_s32_10 <<= 8;
                scratch->unk_18.as_s32_18 <<= 8;

                {
                    u32 palette_id;
                    texture_adjust = ((SpriteFrameState *)object)->clut;
                    if (texture_adjust != 0) {
                        if (scratch->unk_28 & 0x100) {
                            packet->unk_0E = texture_adjust;
                        } else {
                            palette_id = texture_adjust + texture->clut;
                            packet->unk_0E = palette_id;
                        }
                    } else {
                        palette_id = texture->clut;
                        packet->unk_0E = palette_id;
                    }
                }

                packet->unk_0C = scratch->unk_10.as_u16_10 +
                                           scratch->unk_0C.as_u16_0C;
                packet->unk_14.as_u16_14 = scratch->unk_10.as_u16_10 +
                                           scratch->unk_14.as_u16_14;

                texture_adjust = ((SpriteFrameState *)object)->tpage_abr;
                if (texture_adjust != 0) {
                    packet->unk_16 = texture_adjust + (texture->tpage & 0xFF9F);
                } else {
                    packet->unk_16 = texture->tpage;
                }

                packet->unk_1C.as_u16_1C = scratch->unk_18.as_u16_18 +
                                           scratch->unk_0C.as_u16_0C;
                packet->unk_24.as_u16_24 = scratch->unk_18.as_u16_18 +
                                           scratch->unk_14.as_u16_14;

                if (packet->unk_08.as_s16_08 > packet->unk_20.as_s16_20) {
                    packet->unk_14.as_u8_14--;
                    packet->unk_24.as_u8_24--;
                }
                if (packet->unk_0A.as_s16_0A > packet->unk_22.as_s16_22) {
                    packet->unk_1C.as_u8_1D.unk_1D--;
                    packet->unk_24.as_u8_25.unk_25--;
                }

                texture_flags = texture->texture_flags;
                ((SpriteFrameState *)object)->color.c.code = texture_flags;
                render_flags = scratch->unk_28;
                if (render_flags & 8) {
                    ((SpriteFrameState *)object)->color.c.code = (render_flags & 4) ?
                        (texture_flags | 2) : (texture_flags & 0xFD);
                }

                packet->unk_04.as_u32_04 = *(u32 *)&((SpriteFrameState *)object)->color.word;
                setaddr(packet, getaddr((u32 *)scratch->unk_24 + scratch->unk_100));
                setaddr((u32 *)scratch->unk_24 + scratch->unk_100, packet);
            }
        }

        if (mesh->unk_4E == 0) {
            s32 ot_index;
            s32 midpoint;
            s32 midpoint_z;
            s32 coord_a;
            s32 coord_b;
            s32 end_z_a;
            s32 end_z_b;
            S_func_800241A8_6 *line;
            S_func_800241A8_6 *tpage;
            S_func_800241A8_5 *render_state;
            S_func_800241A8_5 *tpage_state;

            render_state = game_work->draw_buffer;
            line = render_state->unk_8D0;
            render_state->unk_8D0 = &line->unk_10;

            coord_a = mesh->unk_58.as_s16_58;
            coord_b = mesh->unk_5C.as_s16_5C;
            midpoint = (coord_a + coord_b) / 2;
            scratch->unk_C0.as_s16_C0 = midpoint;
            scratch->unk_B0.as_s16_B0 = midpoint;
            coord_a = mesh->unk_5A.as_s16_5A;
            coord_b = mesh->unk_5E.as_s16_5E;
            midpoint = (coord_a + coord_b) / 2;
            scratch->unk_C8.as_s16_C8 = midpoint;
            scratch->unk_B8.as_s16_B8 = midpoint;
            coord_a = mesh->unk_60.as_s16_60;
            coord_b = mesh->unk_64.as_s16_64;
            midpoint = (coord_a + coord_b) / 2;
            scratch->unk_C2.as_s16_C2 = midpoint;
            scratch->unk_B2.as_s16_B2 = midpoint;
            coord_a = mesh->unk_62.as_s16_62;
            coord_b = mesh->unk_66.as_s16_66;
            midpoint = (coord_a + coord_b) / 2;
            scratch->unk_CA.as_s16_CA = midpoint;
            scratch->unk_BA.as_s16_BA = midpoint;
            coord_a = mesh->unk_68.as_s16_68;
            coord_b = mesh->unk_6C.as_s16_6C;
            midpoint = (coord_a + coord_b) / 2;
            scratch->unk_C4.as_s16_C4 = midpoint;
            scratch->unk_B4.as_s16_B4 = midpoint;
            end_z_a = mesh->unk_6A.as_s16_6A;
            end_z_b = mesh->unk_6E.as_s16_6E;
            midpoint_z = (end_z_a + end_z_b) / 2;
            scratch->unk_CC.as_s16_CC = midpoint_z;
            scratch->unk_BC.as_s16_BC = midpoint_z;

            ot_index = func_80065590(&scratch->unk_B0.as_s16_B0, &scratch->unk_B8.as_s16_B8,
                                     &scratch->unk_C0.as_s16_C0, &scratch->unk_C8.as_s16_C8,
                                     &line->unk_08.as_s16_08, &line->unk_0C,
                                     &line->unk_08.as_s16_08, &line->unk_0C,
                                     (u8 *)scratch + 0xD0, (u8 *)scratch + 0xD4,
                                     ({ EmptyArg empty; empty; })) - depth_offset - 6;
            scratch->unk_100 = ot_index;

            render_flags = scratch->unk_28;
            if (render_flags & 8) {
                if (render_flags & 4) {
                    ((SpriteFrameState *)object)->color.c.code |= 2;
                } else {
                    ((SpriteFrameState *)object)->color.c.code &= 0xFD;
                }
            }

            render_flags = *(u32 *)&((SpriteFrameState *)object)->color.word;
            line->unk_00.as_u8_03.unk_03 = 3;
            line->unk_04.as_u32_04 = render_flags;
            line->unk_04.as_u8_07.unk_07 = 0x42;
            setaddr(line, getaddr((u32 *)scratch->unk_24 + scratch->unk_100));
            setaddr((u32 *)scratch->unk_24 + scratch->unk_100, line);

            tpage_state = game_work->draw_buffer;
            tpage = tpage_state->unk_8D0;
            tpage_state->unk_8D0 = &tpage->unk_0C;
            func_80067F20(tpage, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            setaddr(tpage, getaddr((u32 *)scratch->unk_24 + scratch->unk_100));
            setaddr((u32 *)scratch->unk_24 + scratch->unk_100, tpage);
        }

        if ((s8)texture->flags < 0) {
            break;
        }
        texture++;
    }
    func_80064A40();
}
#include "common.h"
#include "shared/object_node.h"

#include "modules/dungeon_ovl_189a800.h"

/* Retail 8187B1A0 (decrement_object_counter).
 * Draw the record and then every record chained through the previous header's unk_18 link (node + 0x20 is the
 * next record); each node supplies the context and data pointers for its record. */
s32 decrement_object_counter(void *record, void *context, void *data) {
    ObjectNodeHeader *node;

    for (;;) {
        transform_and_queue_mesh_primitives(record, context, data, 0);
        node = ((ObjectNodeHeader *)record - 1)->chain_next;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        context = node->unk_08;
        data = node->unk_0C;
    }
}
#include "modules/dungeon_native_abi.h"
#include "shared/game_work.h"
#include "shared/position_views.h"

typedef struct S_8187B1F4_1 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x12];
    u16 unk_A6;
} S_8187B1F4_1;   /* scratch in project_shaded_points_to_ordering_table */

typedef struct S_8187B1F4_2 {
    u8 pad_00[0x16];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_8187B1F4_2;   /* arg2 in project_shaded_points_to_ordering_table */

typedef struct S_8187B1F4_3_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_8187B1F4_3_pre;   /* the 0x8 bytes before arg0 in project_shaded_points_to_ordering_table, addressed as arg0[-1] */

typedef struct S_8187B1F4_3 {
    s32 unk_00;
    u8 pad_04[0xC];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
} S_8187B1F4_3;   /* arg0 in project_shaded_points_to_ordering_table */

typedef struct S_8187B1F4_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s8 v; } at00u;
        struct { u8 v; } at00p;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; s8 v; } at03;
    } unk_04;   /* overlapping accesses */
} S_8187B1F4_4;

typedef struct S_8187B1F4_6 {
    u32 unk_00;
    u8 pad_04[0x4];
    u8 * unk_08;
    u8 * unk_0C;
} S_8187B1F4_6;   /* tail in project_shaded_points_to_ordering_table */

#define VFIELD(base, type, offset) (((struct { u8 _pad_[offset]; type v; } *)(base))->v)

typedef struct GlobalState {
    u8 pad[0x8D0];
    u8 *next;
} GlobalState;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065420(void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u32, s32);

typedef struct GlobalRef {
    GlobalState *cur;
} GlobalRef;

typedef struct PrimitiveTag { unsigned addr : 24; unsigned len : 8; } PrimitiveTag;

/* Projects points and adds brightness-scaled pixel primitives to the ordering table. */
s32 project_shaded_points_to_ordering_table(u8 *points, u8 *position, u8 *orientation) {
    s32 view_matrix[8];
    void *model_matrix;
    u8 *scratch;
    u8 *transform_matrix;
    GlobalRef *global;
    register GlobalState *state;
    GlobalState *cur_state;
    GlobalState *tag_state;
    u8 *ordering_table;
    u8 *point_packet;
    u8 *draw_mode_packet;
    u8 *unused_ptr;
    s32 point_index;
    u16 *point_coords;
    u32 depth;
    s32 point_count;
    s32 hard_zero = 0;
    u16 component;
    void *vertex;
    void *depth_cue;
    void *projection_flags;
    u8 *tail;
    u8 *tail_2;

    global = (GlobalRef *)((GlobalState * *)(&g_game_work));
    scratch = (u8 *)0x1F800000;
    model_matrix = (u8 *)((u32)scratch | 0x74);
    transform_matrix = (u8 *)((u32)scratch | 0x54);
    do {
        VFIELD(scratch, s32, 0x88) = ((SignedPositionView *)position)->unk_02;
        VFIELD(scratch, s32, 0x8C) = ((SignedPositionView *)position)->unk_06;
        ((S_8187B1F4_1 *)scratch)->unk_90 = ((SignedPositionView *)position)->unk_0A;
        func_800649A0();
        VFIELD(scratch, s32, 0x3C) = 0x1000;
        VFIELD(scratch, s32, 0x38) = 0x1000;
        VFIELD(scratch, s32, 0x34) = 0x1000;
        VFIELD(scratch, u16, 0xA4) = ((S_8187B1F4_2 *)orientation)->unk_16;
        VFIELD(scratch, u16, 0xA8) = ((S_8187B1F4_2 *)orientation)->unk_1A;
        component = ((S_8187B1F4_2 *)orientation)->unk_18;
        ((S_8187B1F4_1 *)scratch)->unk_A6 = component;
        func_80065820(scratch + 0xA4, ((u8 *)model_matrix));
        func_80064AE0(&view_matrix);
        func_80064840(&view_matrix, model_matrix, transform_matrix);
        func_80064BC0(transform_matrix, scratch + 0x34);
        func_80064D80(transform_matrix);
        func_80064CF0(transform_matrix);
        state = global->cur;
        ordering_table = (u8 *)state;
        state = (GlobalState *)state->next;
        ordering_table += 0xB0;
        VFIELD(scratch, void *, 0x24) = ordering_table;
        VFIELD(scratch, void *, 0x1C) = state;
        point_index = 0;
        if (((S_8187B1F4_3 *)points)->unk_14 > 0) {
            point_coords = (u16 *)points;
            do {
                VFIELD(scratch, u16, 4) = point_coords[point_index + 0xB];
                VFIELD(scratch, u16, 6) = point_coords[point_index + 0x22];
                vertex = scratch + 4;
                component = point_coords[point_index + 0x39];
                cur_state = global->cur;
                depth_cue = scratch + 0xD0;
                VFIELD(scratch, u16, 8) = component;
                point_packet = cur_state->next;
                projection_flags = scratch + 0xD4;
                cur_state->next = point_packet + 0xC;
                depth = func_80065420(vertex, point_packet + 8,
                                      depth_cue, projection_flags);
                VFIELD(scratch, u32, 0x100) = depth;
                if (depth < 0x1E0U) {
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at00.v = ((S_8187B1F4_3 *)points)->unk_00;
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at00u.v =
                        (s8)((((S_8187B1F4_4 *)point_packet)->unk_04.at00p.v *
                        ((S_8187B1F4_3 *)points)->unk_10) / ((S_8187B1F4_3 *)points)->unk_12);
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at01.v =
                        (u8)((((S_8187B1F4_4 *)point_packet)->unk_04.at01.v *
                        ((S_8187B1F4_3 *)points)->unk_10) / ((S_8187B1F4_3 *)points)->unk_12);
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at02.v =
                        (u8)((((S_8187B1F4_4 *)point_packet)->unk_04.at02.v *
                        ((S_8187B1F4_3 *)points)->unk_10) / ((S_8187B1F4_3 *)points)->unk_12);
                    ((S_8187B1F4_4 *)point_packet)->unk_00.at03.v = 2;
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at03.v = 0x6A;
                    ((PrimitiveTag *)point_packet)->addr =
                        ((PrimitiveTag *)((u8 *)VFIELD(scratch, void *, 0x24) +
                               VFIELD(scratch, u32, 0x100) * 4))->addr;
                    tail = (u8 *)(VFIELD(scratch, u32, 0x100) * 4);
                    tail += (u32)VFIELD(scratch, void *, 0x24);
                    ((PrimitiveTag *)tail)->addr = (u32)point_packet;
                    draw_mode_packet = global->cur->next;
                    global->cur->next = draw_mode_packet + 0xC;
                    func_80067F20(draw_mode_packet, 0, 0,
                                  func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
                    ((PrimitiveTag *)draw_mode_packet)->addr =
                        ((PrimitiveTag *)((u8 *)VFIELD(scratch, void *, 0x24) +
                               VFIELD(scratch, u32, 0x100) * 4))->addr;
                    tag_state = (GlobalState *)(VFIELD(scratch, u32, 0x100) * 4);
                    tag_state = (GlobalState *)((u8 *)tag_state +
                                                (u32)VFIELD(scratch, void *, 0x24));
                    ((PrimitiveTag *)tag_state)->addr = (u32)draw_mode_packet;
                    point_count = ((S_8187B1F4_3 *)points)->unk_14;
                } else {
                    point_count = ((S_8187B1F4_3 *)points)->unk_14;
                }
                point_index += 1;
            } while (point_index < point_count);
        }
        func_80064A40();
        tail_2 = ((S_8187B1F4_3_pre *)points)[-1].unk_00;
        points = tail_2 + 0x20;
        if (tail_2 == 0) {
            break;
        }
        point_packet = ((S_8187B1F4_6 *)tail_2)->unk_0C;
        position = ((u8 *)(((S_8187B1F4_6 *)tail_2)->unk_08));
        orientation = point_packet;
    } while (1);
#ifndef __mips__
    hard_zero = 0;
#endif
    return hard_zero;
}
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"

typedef struct S_8187B540_0 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_8187B540_0;   /* arg2 in func_80024D40 */

typedef struct S_8187B540_1 {
    u8 pad_00[0x10];
    u16 unk_10;
    u8 pad_12[0x8E];
    u16 unk_A0;
} S_8187B540_1;   /* obj in func_80024D40 */

extern s16 D_8002694C[5];

/* Add the object increment to the target and flag completion when its countdown expires. */
void rotate_point_cloud_until_expired(void *object, s32 unused, void *target) {
    u8 *object_data = object;
    u8 *global_base = (u8 *)&D_8002694C - 0x694C;
    u16 remaining;

    ((S_8187B540_0 *)target)->unk_1A += ((S_8187B540_1 *)object_data)->unk_A0;
    remaining = ((S_8187B540_1 *)object_data)->unk_10 - 0x20;
    *(s16 *)(global_base + 0x694C) = 1;
    ((S_8187B540_1 *)object_data)->unk_10 = remaining;
    if ((s16)remaining <= 0) {
        (*(u16 *)((u8 *)object_data + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "modules/dungeon_native_abi.h"

#define FIELD_U8(base, off)  (*(u8 *)((u8 *)(base) + (off)))
#define FIELD_S16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define FIELD_U16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define FIELD_U32(base, off) (*(u32 *)((u8 *)(base) + (off)))
#define FIELD_PTR(base, off) (*(u8 **)((u8 *)(base) + (off)))

extern u8 resident_globals_page[];
extern u32 func_80065420();
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u32, s32);

/* Projects a colored point and links its drawing packets into the ordering table. */
s32 project_colored_point_to_ordering_table(u8 *render_data, u8 *source_vertex)
{
    u8 **context_slot;
    u8 *scratch;
    u8 *context;
    u8 *point_packet;
    u8 *mode_packet;
    u8 *next_node;
    u8 *vertex = source_vertex;
    u16 vertex_x;
    u8 blue;
    u32 depth_index;
    u32 length_mask;
    u32 address_mask;
    u32 *mode_ot_entry;

    context = FIELD_PTR(resident_globals_page, 0x3160);
    context_slot = (u8 **)(resident_globals_page + 0x3160);
    address_mask = 0x00FFFFFF;
    length_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;
    FIELD_PTR(scratch, 0x18) = FIELD_PTR(context, 0x8D0);
    FIELD_PTR(scratch, 0x20) = context + 0xB0;
    do {
        point_packet = FIELD_PTR(scratch, 0x18);
        vertex_x = FIELD_U16(vertex, 2);
        FIELD_U16(scratch, 0) = vertex_x;
        FIELD_U16(scratch, 2) = FIELD_U16(vertex, 6);
        FIELD_U16(scratch, 4) = FIELD_U16(vertex, 0xA);
        FIELD_PTR(scratch, 0x18) = point_packet + 0xC;

        depth_index = func_80065420(scratch, point_packet + 8, scratch + 0x90, scratch + 0x94);
        FIELD_U32(scratch, 0xC0) = depth_index;
        if (depth_index < 0x1E0U) {
            FIELD_U32(point_packet, 4) = FIELD_U32(render_data, 0);
            FIELD_U8(point_packet, 4) = (u8)((FIELD_U8(point_packet, 4) * FIELD_S16(render_data, 0x10)) /
                                      FIELD_S16(render_data, 0x12));
            FIELD_U8(point_packet, 5) = (u8)((FIELD_U8(point_packet, 5) * FIELD_S16(render_data, 0x10)) /
                                      FIELD_S16(render_data, 0x12));
            blue = (u8)((FIELD_U8(point_packet, 6) * FIELD_S16(render_data, 0x10)) /
                        FIELD_S16(render_data, 0x12));
            FIELD_U8(point_packet, 3) = 2;
            FIELD_U8(point_packet, 7) = 0x6A;
            FIELD_U8(point_packet, 6) = blue;

            FIELD_U32(point_packet, 0) = (FIELD_U32(point_packet, 0) & length_mask) |
                (*(u32 *)((FIELD_U32(scratch, 0xC0) * 4) + (u32)FIELD_PTR(scratch, 0x20)) & address_mask);
            {
                u32 *ot_entry;
                u32 ot_tag;
                ot_entry = (u32 *)((FIELD_U32(scratch, 0xC0) * 4) +
                                   (u32)FIELD_PTR(scratch, 0x20));
                ot_tag = *ot_entry;
                *ot_entry = (ot_tag & length_mask) |
                           ((u32)point_packet & address_mask);
            }

            mode_packet = FIELD_PTR(scratch, 0x18);
            FIELD_PTR(scratch, 0x18) = mode_packet + 0xC;
            func_80067F20(mode_packet, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);

            FIELD_U32(mode_packet, 0) = (FIELD_U32(mode_packet, 0) & length_mask) |
                (*(u32 *)((FIELD_U32(scratch, 0xC0) * 4) + (u32)FIELD_PTR(scratch, 0x20)) & address_mask);
            mode_ot_entry = (u32 *)((FIELD_U32(scratch, 0xC0) * 4) + (u32)FIELD_PTR(scratch, 0x20));
            *mode_ot_entry = (*mode_ot_entry & length_mask) | ((u32)mode_packet & address_mask);
        }

        next_node = FIELD_PTR(render_data, -8);
        render_data = next_node + 0x20;
        if (next_node == 0) {
            break;
        }
        vertex = FIELD_PTR(next_node, 8);
    } while (1);
    FIELD_PTR(*context_slot, 0x8D0) = FIELD_PTR(scratch, 0x18);
    return 0;
}
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"

extern s16 D_8002694C[5];

/* Conditionally advances the position and decrements a counter, setting flags when it expires. */
void advance_colored_point_toward_terrain(void *object, s16 *position)
{
    s16 *object_fields = object;
    s16 counter;

    s16 minimum_height = position[5] + 2;
    u16 query_x = (u16)position[1];
    u16 query_y = (u16)position[3];

    *(s16 *)D_8002694C = 1;
    if (position[5] < (s16)sample_terrain_surface_height(query_x, query_y, minimum_height)) {
        ((s32 *)position)[2] += *(s32 *)((u8 *)object + 0xB4);
    }

    counter = (u16)object_fields[8] - 4;
    object_fields[8] = counter;
    if ((counter << 16) <= 0) {
        ((u16 *)object_fields)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "modules/dungeon_native_abi.h"
#include "shared/dungeon_moving_views.h"
#include "shared/position_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_800250B0_0 {
    u8 pad_00[0x08];
    void *unk_08;
    u8 pad_0C[0x04];
    s32 unk_10;
    u8 pad_14[0x0C];
    s32 unk_20;
} S_func_800250B0_0;

typedef struct S_func_800250B0_3 {
    u8 pad_00[0x04];
    s16 unk_04;
    u8 pad_06[0x0A];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0xA0];
    s32 unk_B4;
} S_func_800250B0_3;

extern s32 rand();

/* Creates an object at a randomized offset from the source and initializes its actor data. */
void create_terrain_seeking_colored_point(
    void *source,
    s32 field_04_value,
    s32 field_00_value,
    s16 paired_value,
    s16 x_offset,
    s16 y_offset,
    s32 z_offset)
{
    S_func_800250B0_0 *source_obj = source;
    s16 saved_field_04 = field_04_value;
    u32 saved_field_00 = field_00_value;
    s16 saved_pair ;
    s32 saved_z_offset = z_offset;
    S_func_800250B0_0 *spawned_obj;
    S_func_800250B0_3 *actor_data;
    s32 y_jitter;
    s32 z_jitter;
    s16 x_bias;
    s16 y_bias;
    s32 z_bias;
    s16 x_pos;
    s16 y_pos;
    s32 z_pos;
    void *init_obj;
    void *init_data;
    SignedPositionView *x_dest;
    SignedPositionView *y_dest;
    SignedPositionView *z_dest;

    spawned_obj = allocate_list_node(0x211, source_obj);
    if (spawned_obj != NULL) {
        saved_pair = paired_value;
        spawned_obj->unk_10 = (s32)advance_colored_point_toward_terrain;
        z_offset = rand() & 0x1F;
        x_pos = ((MovingPosition *)source_obj->unk_08)->unk_02;
        x_dest = spawned_obj->unk_08;
        x_pos += z_offset;
        x_bias = x_offset - 0x10;
        x_pos += x_bias;
        x_dest->unk_02 = (s16)x_pos;

        y_jitter = rand() & 0x1F;
        y_pos = ((MovingPosition *)source_obj->unk_08)->unk_06;
        y_dest = spawned_obj->unk_08;
        y_pos += y_jitter;
        y_bias = y_offset - 0x10;
        y_pos += y_bias;
        y_dest->unk_06 = (s16)y_pos;

        z_jitter = rand();
        init_obj = spawned_obj;
        init_data = project_colored_point_to_ordering_table;
        z_jitter &= 0x1F;
        z_pos = ((MovingPosition *)source_obj->unk_08)->unk_0A;
        actor_data = (S_func_800250B0_3 *)((u8 *)spawned_obj + 0x20);
        z_dest = spawned_obj->unk_08;
        z_pos += z_jitter;
        z_bias = saved_z_offset - 0x10;
        z_pos += z_bias;
        z_dest->unk_0A = (s16)z_pos;
        actor_data->unk_04 = saved_field_04;
        actor_data->unk_10 = saved_pair;
        actor_data->unk_12 = saved_pair;
        register_node(init_obj, init_data);
        actor_data->unk_B4 = rand() + 0x10000;
        spawned_obj->unk_20 = saved_field_00;
    }
}

#include "modules/dungeon_ovl_189a800.h"
#include "modules/dungeon_native_abi.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_projectile_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8187B9E8_0 {
    u8 pad_00[0x16];
    s16 unk_16[23];
    s16 unk_44[23];
    s16 unk_72[23];
} S_8187B9E8_0;   /* v in func_800251E8 */

   /* r0 in func_800251E8 */

typedef struct S_8187B9E8_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8187B9E8_3;   /* r1 in func_800251E8 */

typedef struct S_8187B9E8_4 {
    s32 unk_00;
    u8 pad_04[0xC];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x8A];
    s16 unk_A0;
} S_8187B9E8_4;   /* q in func_800251E8 */

extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80069EF8();

/* Create an effect with 23 random radial vectors and initialize its position and state. */
void func_800251E8(s32 radius, s32 initial_value, s16 extent, s32 position_x_word, s32 position_y_word, s32 position_z_word) {
    /* Retail accepts word arguments, then carries their low halves across calls. */
    u16 position_x = (u16)position_x_word;
    u16 position_y = (u16)position_y_word;
    u16 position_z = (u16)position_z_word;
    s32 point_count;
    s32 angle_a;
    s32 angle_b;
    s32 plane_radius;
    u32 component;
    MovingPosition *position;
    ProjectileObject *effect;
    S_8187B9E8_4 *state;
    S_8187B9E8_3 *scale;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        point_count = 0;
        state = (u8 *)effect + 0x20;
        do {
            angle_a = func_80069EF8() & 0xFFF;
            angle_b = func_80069EF8() & 0xFFF;
            plane_radius = (radius * func_80064584(angle_a)) >> 12;
            component = (plane_radius * func_800644B8(angle_b)) >> 12;
            ((S_8187B9E8_0 *)state)->unk_16[point_count] = component;
            component = (plane_radius * func_80064584(angle_b)) >> 12;
            ((S_8187B9E8_0 *)state)->unk_44[point_count] = component;
            component = (radius * func_800644B8(angle_a)) >> 12;
            ((S_8187B9E8_0 *)state)->unk_72[point_count] = component;
            point_count++;
        } while (point_count < 0x17);
        position = effect->unk_08;
        position->unk_02 = position_x;
        position->unk_06 = position_y;
        position->unk_0A = position_z;
        scale = effect->unk_0C;
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        state->unk_14 = 0x17;
        effect->unk_10 = rotate_point_cloud_until_expired;
        state->unk_A0 = (func_80069EF8() & 0x3F) + 0x3C;
        state->unk_10 = extent;
        state->unk_12 = extent;
        register_node(effect, project_shaded_points_to_ordering_table);
        state->unk_00 = initial_value;
    }
}
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"

typedef struct S_8187BB80_0 {
    u8 pad_00[0x2];
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u8 pad_04[0x1A];
    union { s16 s; u16 u; } unk_1E;   /* accessed as both */
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x8];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x8];
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 pad_39[0x7];
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; } unk_40;   /* overlapping accesses */
    u8 pad_44[0x8];
    u8 unk_4C;
    u8 unk_4D;
    u8 unk_4E;
    u8 unk_4F;
    u8 pad_50[0x8];
    s16 unk_58;
    u16 unk_5A;
    u8 pad_5C[0x2];
    u16 unk_5E;
    s16 unk_60;
    u16 unk_62;
    u8 pad_64[0x2];
    u16 unk_66;
} S_8187BB80_0;   /* obj in advance_fading_effect_animation */

typedef struct S_8187BB80_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_8187BB80_1;   /* aux in advance_fading_effect_animation */

extern s16 D_8002694C[5];

/* Advance the effect animation, fade its colors, and mark it for removal when its lifetime ends. */
void advance_fading_effect_animation(void *effect_data, s32 unused_arg, void *color_data) {
    u8 *colors = color_data;
    register s32 tick_limit;
    s32 phase_state;

    D_8002694C[0] = 1;
    ((S_8187BB80_0 *)effect_data)->unk_02.u--;

    if (((S_8187BB80_0 *)effect_data)->unk_40.at00.v == 0) {
        s32 mid_y;
        u16 mid_x;

        ((S_8187BB80_0 *)effect_data)->unk_20.s =
            (((S_8187BB80_0 *)effect_data)->unk_1E.s + ((S_8187BB80_0 *)effect_data)->unk_58) / 2;
        mid_y = (((S_8187BB80_0 *)effect_data)->unk_2A.s + ((S_8187BB80_0 *)effect_data)->unk_60) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_2C.s = mid_y;
        mid_x = *(u16 *)(effect_data + 0x20);
        ((S_8187BB80_0 *)effect_data)->unk_66 = mid_y;
        ((S_8187BB80_0 *)effect_data)->unk_62 = mid_y;
        ((S_8187BB80_0 *)effect_data)->unk_5E = mid_x;
        ((S_8187BB80_0 *)effect_data)->unk_5A = mid_x;
    }

    phase_state = ((S_8187BB80_0 *)effect_data)->unk_40.at00.v;
    tick_limit = 1;
    if (phase_state == tick_limit) {
        ((S_8187BB80_0 *)effect_data)->unk_20.s =
            (((S_8187BB80_0 *)effect_data)->unk_1E.s + ((S_8187BB80_0 *)effect_data)->unk_58) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_20.s =
            (((S_8187BB80_0 *)effect_data)->unk_1E.s + ((S_8187BB80_0 *)effect_data)->unk_20.s) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_2C.s =
            (((S_8187BB80_0 *)effect_data)->unk_2A.s + ((S_8187BB80_0 *)effect_data)->unk_60) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_2C.s =
            (((S_8187BB80_0 *)effect_data)->unk_2A.s + ((S_8187BB80_0 *)effect_data)->unk_2C.s) / 2;
        ((S_8187BB80_0 *)effect_data)->unk_5A = ((S_8187BB80_0 *)effect_data)->unk_5E =
            ((S_8187BB80_0 *)effect_data)->unk_20.u;
        ((S_8187BB80_0 *)effect_data)->unk_62 = ((S_8187BB80_0 *)effect_data)->unk_66 =
            ((S_8187BB80_0 *)effect_data)->unk_2C.u;
    }

    if (*(s32 *)(effect_data + 0x40) == 0x10000) {
        u32 start_x = ((S_8187BB80_0 *)effect_data)->unk_1E.u;
        u32 start_y = ((S_8187BB80_0 *)effect_data)->unk_2A.u;

        ((S_8187BB80_0 *)effect_data)->unk_5E = start_x;
        ((S_8187BB80_0 *)effect_data)->unk_5A = start_x;
        ((S_8187BB80_0 *)effect_data)->unk_66 = start_y;
        ((S_8187BB80_0 *)effect_data)->unk_62 = start_y;
    }

    if (((S_8187BB80_0 *)effect_data)->unk_40.at00u.v == tick_limit) {
        s32 phase;
        ((S_8187BB80_0 *)effect_data)->unk_40.at00u.v = 0;
        phase = ((S_8187BB80_0 *)effect_data)->unk_40.at02.v;
        switch (phase) {
        case 0:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 1;
        break;

        case 1:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 2;
        ((S_8187BB80_0 *)effect_data)->unk_4C += 0x20;
        break;

        case 2:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 3;
        ((S_8187BB80_0 *)effect_data)->unk_4C += 0x20;
        break;

        case 3:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 4;
        ((S_8187BB80_0 *)effect_data)->unk_4C += 0x20;
        break;

        case 4:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 5;
        ((S_8187BB80_0 *)effect_data)->unk_4C = 0x80;
        ((S_8187BB80_0 *)effect_data)->unk_4D += 0x20;
        break;

        case 5:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 6;
        ((S_8187BB80_0 *)effect_data)->unk_4C += 0x20;
        break;

        case 6:
        ((S_8187BB80_0 *)effect_data)->unk_40.at02.v = 7;
        ((S_8187BB80_0 *)effect_data)->unk_4C += 0x20;
        break;

        case 7:
        ((S_8187BB80_0 *)effect_data)->unk_4E = 0;
        ((S_8187BB80_0 *)effect_data)->unk_4F = 0;
        ((S_8187BB80_1 *)colors)->unk_0D = 0xFF;
        ((S_8187BB80_1 *)colors)->unk_0C = 0xFF;
        ((S_8187BB80_1 *)colors)->unk_0E = 0;
        ((S_8187BB80_0 *)effect_data)->unk_37 = 0xFF;
        ((S_8187BB80_0 *)effect_data)->unk_36 = 0xFF;
        ((S_8187BB80_0 *)effect_data)->unk_38 = 0;
        ((S_8187BB80_1 *)colors)->unk_14 |= 0xC;
        break;
        case 8:
        default:
            break;
        }
    } else {
        ((S_8187BB80_0 *)effect_data)->unk_40.at00p.v++;
    }

    if (((S_8187BB80_0 *)effect_data)->unk_02.s < 30) {
        ((S_8187BB80_1 *)colors)->unk_0C =
            (((S_8187BB80_0 *)effect_data)->unk_36 * ((S_8187BB80_0 *)effect_data)->unk_02.s) / 30;
        ((S_8187BB80_1 *)colors)->unk_0D =
            (((S_8187BB80_0 *)effect_data)->unk_37 * ((S_8187BB80_0 *)effect_data)->unk_02.s) / 30;
        ((S_8187BB80_1 *)colors)->unk_0E =
            (((S_8187BB80_0 *)effect_data)->unk_38 * ((S_8187BB80_0 *)effect_data)->unk_02.s) / 30;
    }

    if (((S_8187BB80_0 *)effect_data)->unk_02.s <= 0) {
        (*(u16 *)((u8 *)effect_data + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"

typedef struct S_8187BE9C_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    s16 unk_04;
    u8 pad_06[0x30];
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 pad_39[0x9];
    s16 unk_42;
    u8 pad_44[0x8];
    u8 unk_4C;
} S_8187BE9C_0;   /* arg0 in create_object_offset */

typedef struct S_8187BE9C_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_8187BE9C_1;   /* arg2 in create_object_offset */

extern s16 D_8002694C[5];

/* Advance the effect fade, scale primitive colors, and flag completion. */
void create_object_offset(void *effect, s32 unused, S_8187BE9C_1 *primitive)
{
    s16 phase;

    D_8002694C[0] = 1;
    ((S_8187BE9C_0 *)effect)->unk_02.s--;

    phase = ((S_8187BE9C_0 *)effect)->unk_42;
    switch (phase) {
    case 0:
        ((S_8187BE9C_0 *)effect)->unk_42 = 1;
        ((S_8187BE9C_0 *)effect)->unk_4C += 24;
        break;
    case 1:
        ((S_8187BE9C_0 *)effect)->unk_42 = 0;
        ((S_8187BE9C_0 *)effect)->unk_4C -= 24;
        break;
    }

    primitive->unk_0C =
        ((S_8187BE9C_0 *)effect)->unk_36 * ((S_8187BE9C_0 *)effect)->unk_02.u /
        ((S_8187BE9C_0 *)effect)->unk_04;
    primitive->unk_0D =
        ((S_8187BE9C_0 *)effect)->unk_37 * ((S_8187BE9C_0 *)effect)->unk_02.u /
        ((S_8187BE9C_0 *)effect)->unk_04;
    primitive->unk_0E =
        ((S_8187BE9C_0 *)effect)->unk_38 * ((S_8187BE9C_0 *)effect)->unk_02.u /
        ((S_8187BE9C_0 *)effect)->unk_04;

    if (((S_8187BE9C_0 *)effect)->unk_02.u <= 0) {
        ((u16 *)effect)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    if (primitive->unk_14 & 0x8000) {
        ((u16 *)effect)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "modules/dungeon_ovl_189a800.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_8187BFE0_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x6];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0xE];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u8 pad_28[0x2];
    u16 unk_2A;
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
    u16 unk_32;
} S_8187BFE0_0;   /* state in initialize_star_effect_sequence */

typedef struct S_8187BFE0_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    s16 unk_1E;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_8187BFE0_1;   /* node in initialize_star_effect_sequence */

typedef struct S_8187BFE0_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x1A];
    union { u16 s; s16 u; } unk_1E;   /* accessed as both */
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x8];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x8];
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 pad_39[0x1F];
    union { u16 s; s16 u; } unk_58;   /* accessed as both */
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    union { u16 s; s16 u; } unk_60;   /* accessed as both */
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} S_8187BFE0_2;   /* work in initialize_star_effect_sequence */

typedef struct S_8187BFE0_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8187BFE0_3;   /* sprite in initialize_star_effect_sequence */

   /* dst in initialize_star_effect_sequence */

   /* source in initialize_star_effect_sequence */

typedef struct {
    u8 bytes[12];
} Data12;

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

extern u8 D_80026940[12];
extern s16 D_8002694C[5];

/* Initializes a five-point star and spawns its edge effects over successive updates. */
void initialize_star_effect_sequence(void *state_data, void *source_data) {
    MovingPosition *source_position;
    u8 *node;
    u8 *edge_data;
    u8 *sprite;
    MovingPosition *dest_position;
    u8 *globals_page = (u8 *)0x80020000;
    s32 vertex_index;
    s32 angle_offset;
    s16 blended_coord;
    s32 mode;

    source_position = source_data;
    mode = ((S_8187BFE0_0 *)state_data)->unk_00.s;
    *(s16 *)((u8 *)&D_8002694C) = 1;

    switch (mode) {
    default:
        return;
    case 0:
        vertex_index = 0;
        do {
            angle_offset = (vertex_index << 12) / 5;
            ((S_8187BFE0_1 *)((u8 *)state_data + vertex_index * 2))->unk_1E =
                (((S_8187BFE0_0 *)state_data)->unk_0A *
                 func_80064584(((S_8187BFE0_0 *)state_data)->unk_0C + angle_offset)) >> 12;
            ((S_8187BFE0_1 *)((u8 *)state_data + vertex_index * 2))->unk_2A =
                (((S_8187BFE0_0 *)state_data)->unk_0A *
                 func_800644B8(((S_8187BFE0_0 *)state_data)->unk_0C + angle_offset)) >> 12;
            vertex_index++;
        } while (vertex_index < 5);

        ((S_8187BFE0_0 *)state_data)->unk_1C.s = 0;
        ((S_8187BFE0_0 *)state_data)->unk_02.s = 0;
        ((S_8187BFE0_0 *)state_data)->unk_00.u++;
                        /* fallthrough */
    case 1:
        if (((S_8187BFE0_0 *)state_data)->unk_02.s == 0) {
            ((S_8187BFE0_0 *)state_data)->unk_02.u++;
            node = (u8 *)allocate_flagged_object_node(0x212);
            if (node == 0) {
                break;
            }

            edge_data = node + 0x20;
            ((S_8187BFE0_2 *)edge_data)->unk_02 = 0x37 - (((S_8187BFE0_0 *)state_data)->unk_1C.s * 4);
            ((S_8187BFE0_1 *)node)->unk_10 = advance_fading_effect_animation;
            register_node(node, decrement_object_counter);

            sprite = ((S_8187BFE0_1 *)node)->unk_0C;
            ((S_8187BFE0_3 *)sprite)->unk_14 &= 0xFFF3;

            dest_position = ((S_8187BFE0_1 *)node)->unk_08;
            dest_position->unk_02 = source_position->unk_02;
            dest_position->unk_06 = source_position->unk_06;
            dest_position->unk_0A = source_position->unk_0A;

            switch (((S_8187BFE0_0 *)state_data)->unk_1C.s) {
            case 0:
                ((S_8187BFE0_2 *)edge_data)->unk_58.s = ((S_8187BFE0_2 *)edge_data)->unk_5C =
                    ((S_8187BFE0_0 *)state_data)->unk_1E;
                ((S_8187BFE0_2 *)edge_data)->unk_5A = ((S_8187BFE0_2 *)edge_data)->unk_5E =
                    ((S_8187BFE0_0 *)state_data)->unk_22;
                ((S_8187BFE0_2 *)edge_data)->unk_60.s = ((S_8187BFE0_2 *)edge_data)->unk_64 =
                    ((S_8187BFE0_0 *)state_data)->unk_2A;
                {
                    u16 next_coord = ((S_8187BFE0_0 *)state_data)->unk_2E;

                    ((S_8187BFE0_2 *)edge_data)->unk_68 = ((S_8187BFE0_2 *)edge_data)->unk_6A = 0;
                    ((S_8187BFE0_2 *)edge_data)->unk_6C = ((S_8187BFE0_2 *)edge_data)->unk_6E = 0x18;
                    ((S_8187BFE0_2 *)edge_data)->unk_62 = ((S_8187BFE0_2 *)edge_data)->unk_66 = next_coord;
                }
                break;
            case 1:
                ((S_8187BFE0_2 *)edge_data)->unk_58.s = ((S_8187BFE0_2 *)edge_data)->unk_5C =
                    ((S_8187BFE0_0 *)state_data)->unk_22;
                ((S_8187BFE0_2 *)edge_data)->unk_5A = ((S_8187BFE0_2 *)edge_data)->unk_5E =
                    ((S_8187BFE0_0 *)state_data)->unk_26;
                ((S_8187BFE0_2 *)edge_data)->unk_60.s = ((S_8187BFE0_2 *)edge_data)->unk_64 =
                    ((S_8187BFE0_0 *)state_data)->unk_2E;
                {
                    u16 next_coord = ((S_8187BFE0_0 *)state_data)->unk_32;

                    ((S_8187BFE0_2 *)edge_data)->unk_68 = ((S_8187BFE0_2 *)edge_data)->unk_6A = 0;
                    ((S_8187BFE0_2 *)edge_data)->unk_6C = ((S_8187BFE0_2 *)edge_data)->unk_6E = 0x18;
                    ((S_8187BFE0_2 *)edge_data)->unk_62 = ((S_8187BFE0_2 *)edge_data)->unk_66 = next_coord;
                }
                break;
            case 2:
                ((S_8187BFE0_2 *)edge_data)->unk_58.s = ((S_8187BFE0_2 *)edge_data)->unk_5C =
                    ((S_8187BFE0_0 *)state_data)->unk_26;
                ((S_8187BFE0_2 *)edge_data)->unk_5A = ((S_8187BFE0_2 *)edge_data)->unk_5E =
                    ((S_8187BFE0_0 *)state_data)->unk_20;
                ((S_8187BFE0_2 *)edge_data)->unk_60.s = ((S_8187BFE0_2 *)edge_data)->unk_64 =
                    ((S_8187BFE0_0 *)state_data)->unk_32;
                {
                    u16 next_coord = ((S_8187BFE0_0 *)state_data)->unk_2C;

                    ((S_8187BFE0_2 *)edge_data)->unk_68 = ((S_8187BFE0_2 *)edge_data)->unk_6A = 0;
                    ((S_8187BFE0_2 *)edge_data)->unk_6C = ((S_8187BFE0_2 *)edge_data)->unk_6E = 0x18;
                    ((S_8187BFE0_2 *)edge_data)->unk_62 = ((S_8187BFE0_2 *)edge_data)->unk_66 = next_coord;
                }
                break;
            case 3:
                ((S_8187BFE0_2 *)edge_data)->unk_58.s = ((S_8187BFE0_2 *)edge_data)->unk_5C =
                    ((S_8187BFE0_0 *)state_data)->unk_20;
                ((S_8187BFE0_2 *)edge_data)->unk_5A = ((S_8187BFE0_2 *)edge_data)->unk_5E =
                    ((S_8187BFE0_0 *)state_data)->unk_24;
                ((S_8187BFE0_2 *)edge_data)->unk_60.s = ((S_8187BFE0_2 *)edge_data)->unk_64 =
                    ((S_8187BFE0_0 *)state_data)->unk_2C;
                {
                    u16 next_coord = ((S_8187BFE0_0 *)state_data)->unk_30;

                    ((S_8187BFE0_2 *)edge_data)->unk_68 = ((S_8187BFE0_2 *)edge_data)->unk_6A = 0;
                    ((S_8187BFE0_2 *)edge_data)->unk_6C = ((S_8187BFE0_2 *)edge_data)->unk_6E = 0x18;
                    ((S_8187BFE0_2 *)edge_data)->unk_62 = ((S_8187BFE0_2 *)edge_data)->unk_66 = next_coord;
                }
                break;
            case 4:
                ((S_8187BFE0_2 *)edge_data)->unk_58.s = ((S_8187BFE0_2 *)edge_data)->unk_5C =
                    ((S_8187BFE0_0 *)state_data)->unk_24;
                ((S_8187BFE0_2 *)edge_data)->unk_5A = ((S_8187BFE0_2 *)edge_data)->unk_5E =
                    ((S_8187BFE0_0 *)state_data)->unk_1E;
                ((S_8187BFE0_2 *)edge_data)->unk_60.s = ((S_8187BFE0_2 *)edge_data)->unk_64 =
                    ((S_8187BFE0_0 *)state_data)->unk_30;
                {
                    u16 next_coord = ((S_8187BFE0_0 *)state_data)->unk_2A;

                    ((S_8187BFE0_2 *)edge_data)->unk_68 = ((S_8187BFE0_2 *)edge_data)->unk_6A = 0;
                    ((S_8187BFE0_2 *)edge_data)->unk_6C = ((S_8187BFE0_2 *)edge_data)->unk_6E = 0x18;
                    ((S_8187BFE0_2 *)edge_data)->unk_62 = ((S_8187BFE0_2 *)edge_data)->unk_66 = next_coord;
                }
                break;
            default:
                break;
            }

            ((S_8187BFE0_2 *)edge_data)->unk_1E.s = ((S_8187BFE0_2 *)edge_data)->unk_5A;
            ((S_8187BFE0_2 *)edge_data)->unk_2A.s = ((S_8187BFE0_2 *)edge_data)->unk_62;

            blended_coord = (((S_8187BFE0_2 *)edge_data)->unk_1E.u + ((S_8187BFE0_2 *)edge_data)->unk_58.u) / 2;
            ((S_8187BFE0_2 *)edge_data)->unk_20.s = blended_coord;
            blended_coord = (blended_coord + ((S_8187BFE0_2 *)edge_data)->unk_58.u) / 2;
            ((S_8187BFE0_2 *)edge_data)->unk_20.s = blended_coord;

            blended_coord = (((S_8187BFE0_2 *)edge_data)->unk_2A.u + ((S_8187BFE0_2 *)edge_data)->unk_60.u) / 2;
            ((S_8187BFE0_2 *)edge_data)->unk_2C.s = blended_coord;
            blended_coord = (blended_coord + ((S_8187BFE0_2 *)edge_data)->unk_60.u) / 2;
            ((S_8187BFE0_2 *)edge_data)->unk_2C.s = blended_coord;

            ((S_8187BFE0_2 *)edge_data)->unk_5A = ((S_8187BFE0_2 *)edge_data)->unk_5E =
                ((S_8187BFE0_2 *)edge_data)->unk_20.u;
            ((S_8187BFE0_2 *)edge_data)->unk_62 = ((S_8187BFE0_2 *)edge_data)->unk_66 =
                ((S_8187BFE0_2 *)edge_data)->unk_2C.u;

            sprite = ((S_8187BFE0_1 *)node)->unk_0C;
            ((S_8187BFE0_3 *)sprite)->unk_0C = ((S_8187BFE0_3 *)sprite)->unk_0D = 0xE0;
            ((S_8187BFE0_3 *)sprite)->unk_0E = 0x20;
            ((S_8187BFE0_2 *)edge_data)->unk_36 = ((S_8187BFE0_2 *)edge_data)->unk_37 = 0xE0;
            ((S_8187BFE0_2 *)edge_data)->unk_38 = 0x20;
            ((S_8187BFE0_3 *)sprite)->unk_1C = ((S_8187BFE0_3 *)sprite)->unk_1E = 0x1000;

            *(Data12 *)(edge_data + 0x44) = *(Data12 *)D_80026940;
            ((S_8187BFE0_3 *)sprite)->unk_08 = edge_data + 0x44;
            return;
        } else {
            ((S_8187BFE0_0 *)state_data)->unk_02.u++;
            if (((S_8187BFE0_0 *)state_data)->unk_02.s >= 4) {
                ((S_8187BFE0_0 *)state_data)->unk_02.s = 0;
                ((S_8187BFE0_0 *)state_data)->unk_1C.u++;
                if (((S_8187BFE0_0 *)state_data)->unk_1C.s >= 5) {
                    (*(u16 *)((u8 *)state_data + -2)) |= NODE_REMOVE;
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                }
            }
            break;
        }
    }
}

/* MECHANISM: A held 0x80020000 page and s32 mode local fix the prologue/store slot.
   Scoped $v1 edge/$v0 span tails plus scheduling fences preserve coordinate load delays.
   Default-first noreturn layout encodes true-space joins; division by 5 restores the magic divide. */
#include "modules/dungeon_ovl_189a800.h"
#include "shared/entity_height_offsets.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct { u8 b[12]; } AggU12;

typedef struct {
    s16 x;
    u16 y;
} Point __attribute__((packed));

typedef struct {
    Point p[8];
} PointTable __attribute__((packed));

typedef struct {
    u32 w[3];
} Copy12 __attribute__((packed));

typedef struct {
    u8 pad[0x98];
    Copy12 copy;
} PackedArg0 __attribute__((packed));

typedef struct {
    u8 pad[0x64];
    Copy12 copy;
} PackedSpawn __attribute__((packed));

const PointTable D_80024074 = {{{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,65504},{0,65504},{32,65504}}};
extern Copy12 D_80026934;
extern u8 D_80026940[12];
extern s16 D_8002694C[5];
extern u8 D_8007CCD8[];
extern s32 get_sprite_attachment_vector(void *, void *, void *, s32);
extern s32 func_80069EF8(void);
extern s32 check_adjacent_tile_height_clearance(u16, u16, s16, void *);
extern void *memcpy(void *, const void *, unsigned int);

extern void project_sprite_chain(void);

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

/* Update a projectile effect, its trail, and the target hit animation. */
void update_projectile_trail_and_hit_effect(void *effect, void *motion, void *sprite) {
    u16 origin_offset[4];
    PointTable direction_steps;
    void *owner;
    void *object;
    void *object_data;
    void *effect_object;
    void *owner_sprite;
    void *origin_sprite;
    void *target_data;
    u16 offset_value;
    void *spawn_sprite;
    void *hit_target;
    void *target;
    u16 render_flags;
    s32 trail_color;
    s32 state_index;
    s32 particle_index;
    s32 finish_tick;
    s32 particle_color;
    s32 effect_busy;
    s32 fade_out_tick;
    s32 target_tick;
    s32 blue_scaled;
    s32 green_scaled;
    s32 red_scaled;
    s32 owner_z;
    s32 effect_z;
    s32 tile_distance;

    owner = PTR(effect, 0);
    direction_steps = D_80024074;
    state_index = S16(effect, 0xA);
    object = (u8 *)owner - 0x20;
    object_data = PTR(object, 8);

    switch (state_index) {

    case 0:
        U32(sprite, 0xC) = 0x00808080;
        U16(sprite, 0x1E) = 0x1000;
        U16(sprite, 0x1C) = 0x1000;
        *(AggU12 *)((u8 *)effect + 0x98) = *(AggU12 *)&D_80026934;
        PTR(sprite, 8) = (u8 *)effect + 0x98;
        {
            u16 facing = U16(owner, 0x2A);
            D_8002694C[0] = 1;
            U16(effect, 0x7E) = (facing >> 9) & 7;
        }
        U16(effect, 0xA) += 1;

    case 1:
        origin_sprite = PTR(object, 0xC);
        if (get_sprite_attachment_vector(PTR(origin_sprite, 8), origin_sprite, origin_offset, 0) == 0) {
            if (!(U16(PTR(object, 0xC), 0x14) & 0x8000)) {
                return;
            }
        }

        U16(motion, 2) = U16(object_data, 2);
        U16(motion, 6) = U16(object_data, 6);
        owner_z = U16(object_data, 0xA);
        U16(motion, 0xA) = owner_z;
        if (!(U16(PTR(object, 0xC), 0x14) & 0x8000)) {
            U16(motion, 2) = U16(motion, 2) + origin_offset[0];
            U16(motion, 6) = U16(motion, 6) + origin_offset[1];
            effect_z = U16(motion, 0xA) + origin_offset[2];
            U16(motion, 0xA) = effect_z;
        } else {
            U16(motion, 0xA) = owner_z - 0x40;
        }

        if (!(U16(PTR(effect, 4), 0) & 0x80)) {
            return;
        }

        if (!(U8(effect, 0x7A) & 4)) {
            effect_object = (u8 *)effect - 0x20;
            register_node(effect_object, project_sprite_chain);
            U16(sprite, 0x10) = 0x20;
            U8(sprite, 0xD) = 0x80;
            U8(sprite, 0xC) = 0x80;
            U8(sprite, 0xE) = 0x20;
            U16(sprite, 0x14) |= 0xC;
            U8(effect, 0x7A) |= 4;
        }

        hit_target = PTR(owner, 0x60);
        offset_value = 0x10;
        if (hit_target != 0) {
            object = PTR(hit_target, -0x18);
            U16(effect, 0x74) = U16(object, 2);
            U16(effect, 0x76) = U16(object, 6);
            {
                s32 height = entity_height_offsets[U8(PTR(owner, 0x60), 0x13)] + 0x20;
                U16(effect, 0x78) = U16(object, 0xA) - height;
            }
            owner_sprite = PTR(owner, -0x14);
            U8(effect, 0xA4) = U8(owner_sprite, 0x24) + *(u8 *)&dir_step_x[S16(effect, 0x7E)];
            U8(effect, 0xA5) = U8(owner_sprite, 0x25) + *(u8 *)&dir_step_y[S16(effect, 0x7E)];
            {
                s32 grid;
                tile_distance = S8(owner, 0x72);
                grid = U8(owner_sprite, 0x24);
                if (tile_distance != grid) {
                    tile_distance -= grid;
                } else {
                    tile_distance = S8(owner, 0x73);
                    grid = U8(owner_sprite, 0x25);
                    tile_distance -= grid;
                }
            }
            if (tile_distance < 0) {
                tile_distance = -tile_distance;
            }
            U8(effect, 0x7B) = tile_distance * 2 - 1;
        } else {
            U8(effect, 0x7B) = (u32)offset_value;
            offset_value = (u16)direction_steps.p[S16(effect, 0x7E)].x << 4;
            {
                s16 travel_ticks;
                u16 y_step;
                U16(effect, 0x74) = U16(motion, 2) + (u32)offset_value;
                y_step = direction_steps.p[S16(effect, 0x7E)].y;
                travel_ticks = U8(effect, 0x7B);
                travel_ticks = (s8)travel_ticks;
                U16(effect, 0x76) = U16(motion, 6) + y_step * (s8)travel_ticks;
            }
            U16(effect, 0x78) = U16(owner, 0x88) - 0x50;
        }

        S32(motion, 0xC) = direction_steps.p[S16(effect, 0x7E)].x << 16;
        S32(motion, 0x10) = direction_steps.p[S16(effect, 0x7E)].y << 16;
        S32(motion, 0x14) = ((S16(effect, 0x78) << 16) - S32(motion, 8)) / S8(effect, 0x7B);
        U16(effect, 0x82) = 0;
        U16(effect, 0xA) += 1;
        return;

    case 2:
        trail_color = 0x60;
        do {
            object = allocate_flagged_object_node(0x12);
            object_data = (u8 *)object + 0x20;
            if (object != 0) {
                U16(object_data, 2) = 8;
                U16(object_data, 4) = 8;
                PTR(object, 0x10) = create_object_offset;
                register_node(object, project_sprite_chain);

                spawn_sprite = PTR(object, 0xC);

                U16(spawn_sprite, 0x10) = 0x20;
                U16(spawn_sprite, 0x14) |= 0xC;
                {
                    void *spawn_pos = PTR(object, 8);
                    U16(spawn_pos, 2) = U16(motion, 2);
                    U16(spawn_pos, 6) = U16(motion, 6);
                    U16(spawn_pos, 0xA) = U16(motion, 0xA);
                }
                spawn_sprite = PTR(object, 0xC);
                U16(spawn_sprite, 0x1E) = 0x1000;
                U16(spawn_sprite, 0x1C) = 0x1000;
                U8(spawn_sprite, 0xD) = trail_color;
                U8(spawn_sprite, 0xC) = trail_color;
                U8(spawn_sprite, 0xE) = 0x10;
                U8(object_data, 0x38) = 0x10;
                U8(object_data, 0x37) = trail_color;
                U8(object_data, 0x36) = trail_color;
                *(AggU12 *)((u8 *)object + 0x64) = *(AggU12 *)&D_80026934;
                PTR(spawn_sprite, 8) = (u8 *)object + 0x64;
            }

            if ((s16)check_adjacent_tile_height_clearance(U16(motion, 2), U16(motion, 6), S16(motion, 0xA),
                                   PTR(owner, 0x60)) != 0) {
                {
                    U16(effect, 0xA) = 7;
                    U16(effect, 0x82) = 0;
                    render_flags = U16(sprite, 0x14);
                    render_flags |= 0x80;
                    U16(sprite, 0x14) = render_flags;
                    return;
                }
            }

            U8(effect, 0x7B) = U8(effect, 0x7B) - 1;
            if (S8(effect, 0x7B) <= 0) {
                if (PTR(owner, 0x60) != 0) {
                    {
                        U16(effect, 0xA) = 3;
                        U16(effect, 0x82) = 0;
                        object = PTR(PTR(owner, 0x60), -0x18);
                        U16(motion, 2) = U16(object, 2);
                        U16(motion, 6) = U16(object, 6);
                        U16(motion, 0xA) = U16(effect, 0x78);
                        play_sound_if_enabled(0x300);
                        return;
                    }
                }
                U16(effect, 0xA) = 7;
                U16(effect, 0x82) = 0;
                render_flags = U16(sprite, 0x14);
                U8(sprite, 0xE) = 0;
                U8(sprite, 0xD) = 0;
                U8(sprite, 0xC) = 0;
                render_flags |= 0x80;
                U16(sprite, 0x14) = render_flags;
                return;
            }

            S32(motion, 0xC) = ((S16(effect, 0x74) << 16) - S32(motion, 0)) / S8(effect, 0x7B);
            S32(motion, 0x10) = ((S16(effect, 0x76) << 16) - S32(motion, 4)) / S8(effect, 0x7B);
            S32(motion, 0x14) = ((S16(effect, 0x78) << 16) - S32(motion, 8)) / S8(effect, 0x7B);
            S32(motion, 0) += S32(motion, 0xC);
            S32(motion, 4) += S32(motion, 0x10);
            S32(motion, 8) += S32(motion, 0x14);
        } while (1);

    case 3:
        if (S16(effect, 0x96) == 0) {
            U16(effect, 0x96) = 1;
            U8(effect, 0xA0) = U8(effect, 0xA0) + 0x18;
        } else {
            U16(effect, 0x96) = 0;
            U8(effect, 0xA0) = U8(effect, 0xA0) - 0x18;
        }

        object = allocate_flagged_object_node(0x12);
        object_data = (u8 *)object + 0x20;
        if (object != 0) {
            U16(object_data, 2) = 8;
            U16(object_data, 4) = 8;
            U16(object_data, 0xA) = 0x30;
            S16(object_data, 0xC) = -0xDE;
            PTR(object, 0x10) = initialize_star_effect_sequence;
            spawn_sprite = PTR(object, 0xC);
            U16(spawn_sprite, 0x10) = 0x20;
            U16(spawn_sprite, 0x14) |= 0xC;
            {
                void *spawn_pos = PTR(object, 8);
                U16(spawn_pos, 2) = U16(motion, 2);
                U16(spawn_pos, 6) = U16(motion, 6);
                U16(spawn_pos, 0xA) = U16(motion, 0xA);
            }
            *(AggU12 *)((u8 *)object + 0x64) = *(AggU12 *)&D_80026940;
            PTR(spawn_sprite, 8) = (u8 *)object + 0x64;
        }
        U8(effect, 0x92) = 0;
        U8(effect, 0x91) = 0;
        U8(effect, 0x90) = 0;
        U16(effect, 0xA) = 4;
        U16(effect, 0x82) = 0;
        return;

    case 4:
    {
        u16 next_tick = U16(effect, 0x82) + 1;
        fade_out_tick = (s16)next_tick;
        U16(effect, 0x82) = next_tick;
    }
        if (fade_out_tick >= 0x14) {
            goto finish_fade;
        }

        U8(sprite, 0xC) = ((0x14 - fade_out_tick) * 0xE0) / 0x14;
        U8(sprite, 0xD) = ((0x14 - S16(effect, 0x82)) * 0xE0) / 0x14;
        U8(sprite, 0xE) = ((0x14 - S16(effect, 0x82)) * 0x20) / 0x14;
        if (S16(effect, 0x96) == 0) {
            U16(effect, 0x96) = 1;
            U8(effect, 0xA0) = U8(effect, 0xA0) + 0x18;
        } else {
            U16(effect, 0x96) = 0;
            U8(effect, 0xA0) = U8(effect, 0xA0) - 0x18;
        }

        particle_index = 0;
loop_0:
        {
            particle_color = func_80069EF8();
            {
                s32 base_color;
                s32 brightness;
                target = (u8 *)effect - 0x20;
                base_color = 0x0020E0E0;
                particle_color &= 0xFF;
                brightness = particle_color | 0x80;
                create_terrain_seeking_colored_point(target, S16(effect, 0x7E), base_color, brightness, 0, 0, 0);
            }
            particle_index += 1;
        }
        if (particle_index < 4)
            goto loop_0;
        return;

finish_fade:
        U16(effect, 0x82) = 0;
        U16(effect, 0xA) += 1;
        return;

    case 5:
        U16(effect, 0x82) = U16(effect, 0x82) + 1;
        blue_scaled = S16(effect, 0x82) * 0x20;
        U8(effect, 0x92) = blue_scaled / 0x28;
        green_scaled = S16(effect, 0x82) * 8;
        green_scaled = (green_scaled - S16(effect, 0x82)) * 32;
        U8(effect, 0x91) = green_scaled / 0x28;
        red_scaled = S16(effect, 0x82) * 8;
        red_scaled = (red_scaled - S16(effect, 0x82)) * 32;
        U8(effect, 0x90) = red_scaled / 0x28;

        object = PTR(PTR(owner, 0x60), -0x18);
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle_color = (U8(effect, 0x92) << 16) + (U8(effect, 0x91) << 8) + U8(effect, 0x90);
            func_800251E8((entity_height_offsets[U8(PTR(owner, 0x60), 0x13)] >> 1) + 4,
                          particle_color, 0x80, S16(object, 2), S16(object, 6),
                          (s16)(U16(object, 0xA) -
                                (entity_height_offsets[U8(PTR(owner, 0x60), 0x13)] >> 1)));
        }
        if (S16(effect, 0x82) >= 0x28) {
            U16(effect, 0x82) = 0;
            U16(effect, 0xA) += 1;
            return;
        }
        return;

    case 6:
    {
        u16 next_tick = U16(effect, 0x82) + 1;
        target_tick = (s16)next_tick;
        U16(effect, 0x82) = next_tick;
    }
        if (target_tick >= 0x24) {
            U8(effect, 0x92) = ((0x46 - target_tick) * 0x20) / 0x23;
            U8(effect, 0x91) = ((0x46 - S16(effect, 0x82)) * 0xE0) / 0x23;
            U8(effect, 0x90) = ((0x46 - S16(effect, 0x82)) * 0xE0) / 0x23;
        }

        object = PTR(PTR(owner, 0x60), -0x18);
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle_color = (U8(effect, 0x92) << 16) + (U8(effect, 0x91) << 8) + U8(effect, 0x90);
            func_800251E8((entity_height_offsets[U8(PTR(owner, 0x60), 0x13)] >> 1) + 4,
                          particle_color, 0x80, S16(object, 2), S16(object, 6),
                          (s16)(U16(object, 0xA) -
                                (entity_height_offsets[U8(PTR(owner, 0x60), 0x13)] >> 1)));
        }

        target = PTR(owner, 0x60);
        U32(target, 0x1C) |= 0x10000000;
        target_data = PTR(target, -0x14);
        if (S16(effect, 0x82) >= 0x24) {
            U8(target_data, 0xC) -= 3;
            U8(target_data, 0xD) -= 3;
            U8(target_data, 0xE) += 2;
        } else {
            U8(target_data, 0xC) += 3;
            U8(target_data, 0xD) += 3;
            U8(target_data, 0xE) -= 2;
        }
        if (S16(effect, 0x82) < 0x46) {
            return;
        }

        {
            void *released = PTR(owner, 0x60);
            target_data = PTR(released, -0x14);
            U32(released, 0x1C) &= 0xEFFFFFFF;
        }
        U8(target_data, 0xE) = 0x80;
        U8(target_data, 0xD) = 0x80;
        U8(target_data, 0xC) = 0x80;
        func_800240B8(PTR(owner, 0x60), U8(effect, 9), owner);
        U16(effect, 0x82) = 0x14;
        U16(effect, 0xA) += 1;
        return;

    case 7:
        finish_tick = U16(effect, 0x82);
        U16(effect, 0x82) = finish_tick + 1;
        if ((s16)finish_tick < 0x15) {
            return;
        }
        effect_busy = D_8002694C[0];
        U16(effect, 0x82) = finish_tick;
        if (effect_busy == 0) {
            S32(D_8007CCD8 + 13096, 0x346C) = 0;
            U16(effect, -2) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        {
            D_8002694C[0] = 0;

            return;
        }
    default:
        return;
    }
}
