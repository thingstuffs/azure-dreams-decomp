#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80047738();
M2C_UNK func_800478B8();
M2C_UNK func_800A020C();
s32 func_800A9E70();
M2C_UNK func_800AA36C();
s32 func_800BCB04();
extern u8 D_8006CCF8[];
extern s16 D_80083228[];
extern u16 D_80083462[];
extern M2C_UNK D_801711A4[];
extern M2C_UNK D_80174174[];
extern M2C_UNK D_8017418C[];
extern M2C_UNK D_801741D4[];


typedef struct S_80170B64_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4D];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x1A];
    M2C_UNK (*unk_8C)(void *, void *, void *, void *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x2];
    union { s8 s; u8 u; } unk_9D;   /* accessed as both */
    u8 pad_9E[0x2];
    union { u16 u; s16 s; } unk_A0;   /* accessed as both */
    u8 pad_A2[0x6];
    s16 unk_A8;
    u8 pad_AA[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_AC;   /* overlapping accesses */
} S_80170B64_0;   /* arg0 in func_80170B64 */

typedef struct S_80170B64_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170B64_1;   /* arg1 in func_80170B64 */

typedef struct S_80170B64_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { void * p; s32 i; } unk_2C;   /* accessed as both */
} S_80170B64_2;   /* arg2 in func_80170B64 */

typedef struct S_80170B64_3 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170B64_3;   /* work in func_80170B64 */

/* Update actor callbacks, movement, sprite direction, and terrain-relative height. */
void func_80170B64(void *actor_arg, void *motion_arg, void *sprite_arg)
{
    register void *actor ASM_REG("$17") = actor_arg;
    register void *motion ASM_REG("$21") = motion_arg;
    register void *sprite ASM_REG("$20") = sprite_arg;
    register void *actor_base ASM_REG("$18") = actor;
    M2C_UNK (*update_callback)(void *, void *, void *, void *);
    M2C_UNK (*pause_callback)(void *, void *, void *, void *);
    s16 floor_offset;
    s16 view_direction;
    s16 tile_height;
    s32 hover_floor_offset;
    s32 height_adjustment;
    s32 animated_flags;
    s32 animation_table;
    s32 static_flags;
    s32 static_animation_table;
    s32 actor_flags;
    s16 previous_state;
    u16 sprite_flags;

    if (D_80083462[0] & 0x2000) {
        void *paused_actor = actor_arg;
        pause_callback = ((S_80170B64_0 *)actor)->unk_8C;
        if (pause_callback == &D_801711A4) {
            ASM_KEEP(paused_actor);
            pause_callback(paused_actor, motion, sprite, paused_actor);
            return;
        }
        ((S_80170B64_0 *)actor)->unk_71 &= 0x7F;
        return;
    }

    ASM_KEEP(actor);
    ASM_KEEP(motion);
    ASM_KEEP(sprite);

    previous_state = (s8)((S_80170B64_0 *)actor)->unk_6D;
    if (func_800A9E70(actor, motion, sprite, actor) == 0) {
        update_callback = ((S_80170B64_0 *)actor)->unk_8C;
        if (update_callback != 0) {
            update_callback(actor, motion, sprite, actor);
        }
        ((M2C_UNK (**)(void *, void *, void *, void *))&D_801741D4)
            [((S_80170B64_0 *)actor)->unk_9A](actor, motion, sprite, actor);
        if ((s16)previous_state != (s8)((S_80170B64_0 *)actor)->unk_6D) {
            func_800AA36C(actor, motion, sprite, actor);
        }
        ((S_80170B64_1 *)motion)->unk_00.at00.v += ((S_80170B64_1 *)motion)->unk_0C;
        ((S_80170B64_1 *)motion)->unk_04.at00.v += ((S_80170B64_1 *)motion)->unk_10;
        if (!(((S_80170B64_0 *)actor)->unk_1C & 0x40000) &&
            !(((S_80170B64_0 *)actor)->unk_98 & 8)) {
            ((S_80170B64_1 *)motion)->unk_14 = ((S_80170B64_1 *)motion)->unk_14 +
                (((S_80170B64_0 *)actor)->unk_9D.s * 0x14000);
            ((S_80170B64_0 *)actor)->unk_9D.u++;
        } else {
            ((S_80170B64_0 *)actor)->unk_9D.s = 0;
        }

        ((S_80170B64_0 *)actor)->unk_90.at00.v = ((S_80170B64_0 *)actor)->unk_90.at00.v +
            ((S_80170B64_1 *)motion)->unk_14;
        sprite_flags = ((S_80170B64_2 *)sprite)->unk_14;
        if (!(sprite_flags & 0x8000)) {
            view_direction = ((D_80083228[0] + ((S_80170B64_3 *)actor_base)->unk_2A + 0x100) >> 9) & 7;
            if (((S_80170B64_0 *)actor)->unk_94 != view_direction) {
                func_80047738(sprite,
                    *(((u8 *)((S_80170B64_2 *)sprite)->unk_2C.p) + view_direction),
                    ((S_80170B64_2 *)sprite)->unk_04.s8);
                ((S_80170B64_0 *)actor)->unk_94 = view_direction;
            }
            if (D_8006CCF8[view_direction] != 0) {
                ((S_80170B64_2 *)sprite)->unk_14 |= 1;
            } else {
                ((S_80170B64_2 *)sprite)->unk_14 &= 0xFFFE;
            }
            func_800A020C(((S_80170B64_3 *)actor_base)->unk_1C.s, sprite + 0xC);
            if (!(((S_80170B64_3 *)actor_base)->unk_1C.s & 0x20)) {
                if (!(((S_80170B64_2 *)sprite)->unk_14 & 0x40)) {
                    func_800478B8(sprite);
                }
                goto update_animated_height;
            }
            ((S_80170B64_2 *)sprite)->unk_14 |= 0x7000;
            ((S_80170B64_3 *)actor_base)->unk_1C.s &= 0xFFFBFFFF;
update_animated_height:
            animated_flags = ((S_80170B64_3 *)actor_base)->unk_1C.s & 0xF7FFFFFF;
            ((S_80170B64_3 *)actor_base)->unk_1C.s = animated_flags;
            if (animated_flags & 0x40000) {
                if (!(((S_80170B64_2 *)sprite)->unk_14 & 0x40)) {
                    animation_table = ((S_80170B64_2 *)sprite)->unk_2C.i;
                    if (animation_table == (s32)&D_8017418C) {
                        ((S_80170B64_0 *)actor)->unk_AC.at00.v = 0;
                        goto adjust_animated_hover;
                    }
                    if (animation_table == (s32)&D_80174174) {
                        ((S_80170B64_0 *)actor)->unk_A0.u++;
                        if (((S_80170B64_2 *)sprite)->unk_04.u16 == 0x100) {
                            ((S_80170B64_0 *)actor)->unk_A0.u = 0;
                            ((S_80170B64_0 *)actor)->unk_AC.at00.v = 0;
                        }
                        if (((S_80170B64_0 *)actor)->unk_A0.s < 5) {
                            ((S_80170B64_0 *)actor)->unk_AC.at00.v += -0x33333;
                        } else {
                            ((S_80170B64_0 *)actor)->unk_AC.at00.v += 0x12492;
                        }
                        goto adjust_animated_hover;
                    }
                    goto adjust_animated_hover;
                }
adjust_animated_hover:
                if (!(((S_80170B64_0 *)actor)->unk_98 & 8)) {
                    hover_floor_offset = func_800BCB04(((S_80170B64_1 *)motion)->unk_00.at02.v,
                        ((S_80170B64_1 *)motion)->unk_04.at02.v,
                        (s16)(((S_80170B64_3 *)actor_base)->unk_88 - 0x20)) -
                        ((S_80170B64_3 *)actor_base)->unk_88;
                    if (((S_80170B64_0 *)actor)->unk_90.at02.v > ((s16)hover_floor_offset - 0x20)) {
                        ((S_80170B64_0 *)actor)->unk_90.at02.v =
                            ((S_80170B64_0 *)actor)->unk_90.at02u.v - 8;
                    } else if (((S_80170B64_0 *)actor)->unk_90.at02.v <
                               ((s16)hover_floor_offset - 0x28)) {
                        ((S_80170B64_0 *)actor)->unk_90.at02.v =
                            ((S_80170B64_0 *)actor)->unk_90.at02u.v + 8;
                    }
                }
                goto update_world_height;
            }
            goto apply_floor_height;
        }
        if (sprite_flags & 0x800) {
            ((S_80170B64_2 *)sprite)->unk_14 = sprite_flags & 0x8FFF;
        } else {
            ((S_80170B64_2 *)sprite)->unk_14 = sprite_flags | 0x7000;
        }
        static_flags = ((S_80170B64_3 *)actor_base)->unk_1C.s & 0xF7FFFFFF;
        ((S_80170B64_3 *)actor_base)->unk_1C.s = static_flags;
        if (!(static_flags & 0x40000)) {
apply_floor_height:
            height_adjustment = ((S_80170B64_0 *)actor)->unk_AC.at00.v;
            ((S_80170B64_0 *)actor)->unk_A8 = 0;
            ((S_80170B64_0 *)actor)->unk_AC.at00.v = 0;
            ((S_80170B64_0 *)actor)->unk_90.at00.v -= height_adjustment;
            if (!(((S_80170B64_0 *)actor)->unk_98 & 8)) {
                floor_offset = func_800BCB04(((S_80170B64_1 *)motion)->unk_00.at02.v,
                    ((S_80170B64_1 *)motion)->unk_04.at02.v,
                    (s16)(((S_80170B64_3 *)actor_base)->unk_88 - 0x20)) -
                    ((S_80170B64_3 *)actor_base)->unk_88;
                if (floor_offset < ((S_80170B64_0 *)actor)->unk_90.at02.v) {
                    ((S_80170B64_0 *)actor)->unk_90.at02.v = floor_offset;
                    ((S_80170B64_0 *)actor)->unk_9D.s = 0;
                    ((S_80170B64_1 *)motion)->unk_14 = 0;
                    ((S_80170B64_3 *)actor_base)->unk_1C.u |= 0x08000000;
                    goto update_world_height;
                }
            }
            goto update_world_height;
        }
        if (!(((S_80170B64_2 *)sprite)->unk_14 & 0x40)) {
            static_animation_table = ((S_80170B64_2 *)sprite)->unk_2C.i;
            if (static_animation_table == (s32)&D_8017418C) {
                ((S_80170B64_0 *)actor)->unk_AC.at00.v = 0;
                goto adjust_static_hover;
            }
            if (static_animation_table == (s32)&D_80174174) {
                ((S_80170B64_0 *)actor)->unk_A0.u++;
                if (((S_80170B64_2 *)sprite)->unk_04.u16 == 0x100) {
                    ((S_80170B64_0 *)actor)->unk_A0.u = 0;
                    ((S_80170B64_0 *)actor)->unk_AC.at00.v = 0;
                }
                if (((S_80170B64_0 *)actor)->unk_A0.s < 5) {
                    ((S_80170B64_0 *)actor)->unk_AC.at00.v += -0x33333;
                } else {
                    ((S_80170B64_0 *)actor)->unk_AC.at00.v += 0x12492;
                }
                goto adjust_static_hover;
            }
            goto adjust_static_hover;
        }
adjust_static_hover:
        if (!(((S_80170B64_0 *)actor)->unk_98 & 8)) {
            hover_floor_offset = func_800BCB04(((S_80170B64_1 *)motion)->unk_00.at02.v,
                ((S_80170B64_1 *)motion)->unk_04.at02.v,
                (s16)(((S_80170B64_3 *)actor_base)->unk_88 - 0x20)) -
            ((S_80170B64_3 *)actor_base)->unk_88;
            if (((S_80170B64_0 *)actor)->unk_90.at02.v > ((s16)hover_floor_offset - 0x20)) {
                ((S_80170B64_0 *)actor)->unk_90.at02.v =
                    ((S_80170B64_0 *)actor)->unk_90.at02u.v - 8;
            } else if (((S_80170B64_0 *)actor)->unk_90.at02.v < ((s16)hover_floor_offset - 0x28)) {
                ((S_80170B64_0 *)actor)->unk_90.at02.v =
                    ((S_80170B64_0 *)actor)->unk_90.at02u.v + 8;
            }
        }
update_world_height:
        actor_flags = ((S_80170B64_3 *)actor_base)->unk_1C.s;
        if (actor_flags & 0x40000000) {
            ((S_80170B64_3 *)actor_base)->unk_1C.s = actor_flags & 0xBFFFFFFF;
            tile_height = func_800BCB04(
                (((S_80170B64_2 *)sprite)->unk_24 << 6) | 0x20,
                (((S_80170B64_2 *)sprite)->unk_25 << 6) | 0x20,
                (s16)(((S_80170B64_3 *)actor_base)->unk_88 - 0x20));
            if (tile_height < 0x200) {
                ((S_80170B64_0 *)actor)->unk_90.at02.v = (u16)((S_80170B64_0 *)actor)->unk_90.at02.v +
                    (((S_80170B64_3 *)actor_base)->unk_88 - tile_height);
                ((S_80170B64_3 *)actor_base)->unk_88 = tile_height;
            }
        }
        ((S_80170B64_1 *)motion)->unk_0A = ((S_80170B64_0 *)actor)->unk_AC.at02.v +
            (((S_80170B64_3 *)actor_base)->unk_88 + (u16)((S_80170B64_0 *)actor)->unk_90.at02.v);
        ((S_80170B64_2 *)sprite)->unk_14 |= 0x40;
    }

}
