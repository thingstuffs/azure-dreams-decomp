/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

/* Value-preserving cse-equivalence launder for the first callback's 4th
 * argument: a block-scoped $a0-pinned temp with the empty "=r"/"0" tie
 * (expression form of ASM_REG+ASM_KEEP_NV). Port build folds to the plain
 * value. */
#ifdef NON_MATCHING
#define ({ register void *actor_value ASM_REG("$4") = (v); ASM_KEEP_NV(actor_value); actor_value; }) (v)
#else
#endif

void func_80047738(void *, u8, s8);              /* extern */
void func_80047784(void *, u8, s32);             /* extern */
void func_800478B8(void *);                       /* extern */
s32 func_800644B8(s32);                            /* extern */
M2C_UNK func_800A020C(s32, void *);               /* extern */
s32 func_800A9E70(void *, void *, void *, void *); /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
s16 func_800BCB04(s32, s32, s16);                 /* extern */
extern u8 D_8006CCF8[12];
extern s16 D_80083228[5];
extern u16 D_80083462[5];
extern M2C_UNK D_80171400[3];
extern u8 D_80175140[12];
extern u8 D_80175148[12];
extern u8 D_80175170[12];
extern u8 D_80175178[12];
extern void *D_80175198[3];


typedef struct S_80170BF8_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4D];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x1A];
    M2C_UNK (*unk_8C)(void *, void *, void *, void *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x2];
    union { s8 s; u8 u; } unk_9D;   /* accessed as both */
    u8 pad_9E[0xA];
    s16 unk_A8;
} S_80170BF8_0;   /* arg0 in func_80170BF8 */

typedef struct S_80170BF8_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170BF8_1;   /* arg1 in func_80170BF8 */

typedef struct S_80170BF8_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80170BF8_2;   /* arg2 in func_80170BF8 */

typedef struct S_80170BF8_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170BF8_3;   /* actor2 in func_80170BF8 */

/* Updates actor callbacks, movement, animation, and terrain-relative height. */
void func_80170BF8(void *actor_arg, void *motion_arg, void *object_arg) {
    u16 initial_flags = D_80083462[0];
    register void *actor ASM_REG("$17") = actor_arg;
    register void *motion = motion_arg;
    register void *object ASM_REG("$20") = object_arg;
    s32 bob_offset = 0;
    void *actor_base = actor;

    M2C_UNK (*update_callback)(void *, void *, void *, void *);
    M2C_UNK (*paused_callback)(void *, void *, void *, void *);
    u8 *anim_table;
    u8 *hidden_anim_table;
    u8 *next_anim;
    u8 *hidden_next_anim;
    s16 base_height;
    s16 hidden_base_height;
    s16 height_offset;
    s16 hover_ground_offset;
    s16 ground_height;
    s16 hidden_ground_height;
    s16 hidden_hover_offset;
    s16 tile_height;
    s32 ground_offset;
    s32 height_flags;
    s32 actor_flags;
    s32 hidden_actor_flags;
    s32 display_height;
    u32 frame_addr;
    register u32 anim_addr ASM_REG("$5");
    u32 facing_flags;
    u16 motion_flags;
    u16 object_flags;
    u16 anim_flags;
    u16 hidden_anim_flags;
    u16 old_height_offset;
    s32 facing;
    s16 state_or_facing;
    if (initial_flags & 0x2000) {
        paused_callback = ((S_80170BF8_0 *)actor)->unk_8C;
        if (paused_callback == &D_80171400) {
            paused_callback(actor_arg, motion_arg, object_arg, ({ register void *actor_value ASM_REG("$4") = (actor_arg); ASM_KEEP_NV(actor_value); actor_value; }));
            return;
        }
        ((S_80170BF8_0 *)actor)->unk_71 = (u8) (((S_80170BF8_0 *)actor)->unk_71 & 0x7F);
        return;
    }
    ASM_KEEP_NV(actor);
    ASM_KEEP_NV(motion);
    ASM_KEEP_NV(object);
    state_or_facing = (s8) ((S_80170BF8_0 *)actor)->unk_6D;
    if (func_800A9E70(actor, motion, object, actor) == 0) {
        update_callback = ((S_80170BF8_0 *)actor)->unk_8C;
        if (update_callback != NULL) {
            update_callback(actor, motion, object, actor);
        }
        ((void (*)(void *, void *, void *, void *))D_80175198[((S_80170BF8_0 *)actor)->unk_9A])(actor, motion, object, actor);
        if ((s16) state_or_facing != (s8) ((S_80170BF8_0 *)actor)->unk_6D) {
            func_800AA36C(actor, motion, object, actor);
        }
        ((S_80170BF8_1 *)motion)->unk_00.at00.v = (s32) (((S_80170BF8_1 *)motion)->unk_00.at00.v + ((S_80170BF8_1 *)motion)->unk_0C);
        ((S_80170BF8_1 *)motion)->unk_04.at00.v = (s32) (((S_80170BF8_1 *)motion)->unk_04.at00.v + ((S_80170BF8_1 *)motion)->unk_10);
        if (!(((S_80170BF8_0 *)actor)->unk_1C & 0x40000) && !(((S_80170BF8_0 *)actor)->unk_98 & 8)) {
            ((S_80170BF8_1 *)motion)->unk_14 = (s32) (((S_80170BF8_1 *)motion)->unk_14 + (((S_80170BF8_0 *)actor)->unk_9D.s * 0x14000));
            ((S_80170BF8_0 *)actor)->unk_9D.u = (u8) (((S_80170BF8_0 *)actor)->unk_9D.u + 1);
            goto update_height;
        }
        ((S_80170BF8_0 *)actor)->unk_9D.s = 0;
update_height:

        ((S_80170BF8_0 *)actor)->unk_90.at00.v = (s32) (((S_80170BF8_0 *)actor)->unk_90.at00.v + ((S_80170BF8_1 *)motion)->unk_14);
        object_flags = ((S_80170BF8_2 *)object)->unk_14;
        if (!(object_flags & 0x8000)) {
            facing = ((s32) (D_80083228[0] + ((S_80170BF8_3 *)actor_base)->unk_2A + 0x100) >> 9) & 7;
            state_or_facing = (s16) facing;
            if (((S_80170BF8_0 *)actor)->unk_94 != state_or_facing) {
                func_80047738(object, *(((S_80170BF8_2 *)object)->unk_2C + state_or_facing), ((S_80170BF8_2 *)object)->unk_04);
                ((S_80170BF8_0 *)actor)->unk_94 = facing;
            }
            if (D_8006CCF8[state_or_facing] != 0) {
                facing_flags = ((S_80170BF8_2 *)object)->unk_14;
                facing_flags |= 1;
            } else {
                facing_flags = ((S_80170BF8_2 *)object)->unk_14 & 0xFFFE;
            }
            ((S_80170BF8_2 *)object)->unk_14 = (u16) facing_flags;
            if (((S_80170BF8_0 *)actor)->unk_9A != 8) {
                func_800A020C(((S_80170BF8_3 *)actor_base)->unk_1C, object + 0xC);
            }
            if (!(((S_80170BF8_3 *)actor_base)->unk_1C & 0x20)) {
                if (!(((S_80170BF8_2 *)object)->unk_14 & 0x40)) {
                    func_800478B8(object);
                    goto update_motion_flags;
                }
                goto update_motion_flags;
            }
            ((S_80170BF8_2 *)object)->unk_14 = (u16) (((S_80170BF8_2 *)object)->unk_14 | 0x7000);
            ((S_80170BF8_3 *)actor_base)->unk_1C = (s32) (((S_80170BF8_3 *)actor_base)->unk_1C & 0xFFFBFFFF);
update_motion_flags:
            actor_flags = ((S_80170BF8_3 *)actor_base)->unk_1C & 0xF7FFFFFF;
            ((S_80170BF8_3 *)actor_base)->unk_1C = actor_flags;
            if (actor_flags & 0x40000) {
                if (!(((S_80170BF8_2 *)object)->unk_14 & 0x40)) {
                    anim_flags = ((S_80170BF8_0 *)actor)->unk_98;
                    if (anim_flags & 0x8000) {
                        ((S_80170BF8_0 *)actor)->unk_98 = (u16) (anim_flags & 0x7FFF);
                        anim_table = ((S_80170BF8_2 *)object)->unk_2C;
                        next_anim = D_80175148;
                        if (anim_table == D_80175148) {
                            anim_addr = (u32) D_80175140;
                            goto apply_anim;
                        }
                        if (anim_table != D_80175140) {
                            next_anim = D_80175170;
                            if (anim_table == D_80175170) {
                                anim_addr = (u32) D_80175178;
                                goto apply_anim;
                            }
                            if (anim_table == D_80175178) {
                                goto select_anim;
                            }
                            goto update_bob;
                        }
select_anim:
                        anim_addr = (u32) next_anim;
apply_anim:
                        next_anim = (u8 *) anim_addr;
                        ((S_80170BF8_2 *)object)->unk_2C = next_anim;
                        frame_addr = (u32) ((((s32) (D_80083228[0] + ((S_80170BF8_3 *)actor_base)->unk_2A + 0x100) >> 9) & 7));
                        frame_addr += (u32) next_anim;
                        func_80047784(object, *(u8 *) frame_addr, 0);
                        goto update_bob;
                    }
update_bob:
                    if (((S_80170BF8_2 *)object)->unk_14 & 0x6000) {
                        ((S_80170BF8_0 *)actor)->unk_98 = (u16) (((S_80170BF8_0 *)actor)->unk_98 | 0x8000);
                        if (((S_80170BF8_2 *)object)->unk_2C == D_80175140) {
                            ((S_80170BF8_0 *)actor)->unk_A8 = 0;
                        }
                    }
                    bob_offset = func_800644B8((((S_80170BF8_0 *)actor)->unk_A8 << 0xC) / 20) >> 0xA;
                    ((S_80170BF8_0 *)actor)->unk_A8 = (s16) ((u16) ((S_80170BF8_0 *)actor)->unk_A8 + 1);
                    goto adjust_hover_height;
                }
adjust_hover_height:
                if (!(((S_80170BF8_0 *)actor)->unk_98 & 8)) {
                    hover_ground_offset = (s16) (func_800BCB04(((S_80170BF8_1 *)motion)->unk_00.at02.v, ((S_80170BF8_1 *)motion)->unk_04.at02.v, (s16) (((S_80170BF8_3 *)actor_base)->unk_88.u - 0x20)) - ((S_80170BF8_3 *)actor_base)->unk_88.u);
                    old_height_offset = (u16) ((S_80170BF8_0 *)actor)->unk_90.at02.v;
                    if (((S_80170BF8_0 *)actor)->unk_90.at02.v > (hover_ground_offset - 0x20)) {
                        ((S_80170BF8_0 *)actor)->unk_90.at02.v = (s16) (old_height_offset - 8);
                        goto update_display_height;
                    }

                    if (((S_80170BF8_0 *)actor)->unk_90.at02.v < (hover_ground_offset - 0x2A)) {
                        ((S_80170BF8_0 *)actor)->unk_90.at02.v = (s16) (old_height_offset + 8);
                        goto update_display_height;
                    }
                    goto update_display_height;
                }
                goto update_display_height;
            }
            motion_flags = ((S_80170BF8_0 *)actor)->unk_98;
            ((S_80170BF8_0 *)actor)->unk_A8 = 0;
            ((S_80170BF8_0 *)actor)->unk_98 = (u16) (motion_flags & 0x7FFF);
            if (!(motion_flags & 8)) {
                ground_offset = func_800BCB04(((S_80170BF8_1 *)motion)->unk_00.at02.v, ((S_80170BF8_1 *)motion)->unk_04.at02.v, (s16) (((S_80170BF8_3 *)actor_base)->unk_88.u - 0x20));
                ground_height = (s16) ground_offset;
                base_height = ((S_80170BF8_3 *)actor_base)->unk_88.s;
                ground_offset = (s32) ground_height - base_height;
                if (ground_offset < ((S_80170BF8_0 *)actor)->unk_90.at02.v) {
                    ((S_80170BF8_0 *)actor)->unk_90.at02.v = ground_offset;
                    ((S_80170BF8_0 *)actor)->unk_9D.s = 0;
                    ((S_80170BF8_1 *)motion)->unk_14 = 0;
                    ((S_80170BF8_3 *)actor_base)->unk_1C = ((S_80170BF8_3 *)actor_base)->unk_1C | 0x08000000;
                    goto update_display_height;
                }
            }
            goto update_display_height;
        }
        ((S_80170BF8_2 *)object)->unk_14 = (object_flags & 0x800) ? (object_flags & 0x8FFF) : (object_flags | 0x7000);
        hidden_actor_flags = ((S_80170BF8_3 *)actor_base)->unk_1C & 0xF7FFFFFF;
        ((S_80170BF8_3 *)actor_base)->unk_1C = hidden_actor_flags;
        if (!(hidden_actor_flags & 0x40000)) {
            ((S_80170BF8_0 *)actor)->unk_A8 = 0;
            ((S_80170BF8_0 *)actor)->unk_90.at02.v = (s16) ((u16) ((S_80170BF8_0 *)actor)->unk_90.at02.v - bob_offset);
            bob_offset = 0;
            if (!(((S_80170BF8_0 *)actor)->unk_98 & 8)) {
                ground_offset = func_800BCB04(((S_80170BF8_1 *)motion)->unk_00.at02.v, ((S_80170BF8_1 *)motion)->unk_04.at02.v, (s16) (((S_80170BF8_3 *)actor_base)->unk_88.u - 0x20));
                hidden_ground_height = (s16) ground_offset;
                hidden_base_height = ((S_80170BF8_3 *)actor_base)->unk_88.s;
                ground_offset = (s32) hidden_ground_height - hidden_base_height;
                if (ground_offset < ((S_80170BF8_0 *)actor)->unk_90.at02.v) {
                    ((S_80170BF8_0 *)actor)->unk_90.at02.v = ground_offset;
                    ((S_80170BF8_0 *)actor)->unk_9D.s = 0;
                    ((S_80170BF8_1 *)motion)->unk_14 = 0;
                    ((S_80170BF8_3 *)actor_base)->unk_1C = ((S_80170BF8_3 *)actor_base)->unk_1C | 0x08000000;
                    goto reset_bob;
                }
            }
            goto reset_bob;
        }
        if (!(((S_80170BF8_2 *)object)->unk_14 & 0x40)) {
            hidden_anim_flags = ((S_80170BF8_0 *)actor)->unk_98;
            if (hidden_anim_flags & 0x8000) {
                ((S_80170BF8_0 *)actor)->unk_98 = (u16) (hidden_anim_flags & 0x7FFF);
                hidden_anim_table = ((S_80170BF8_2 *)object)->unk_2C;
                hidden_next_anim = D_80175148;
                if (hidden_anim_table == D_80175148) {
                    anim_addr = (u32) D_80175140;
                    goto apply_hidden_anim;
                }
                if (hidden_anim_table != D_80175140) {
                    hidden_next_anim = D_80175170;
                    if (hidden_anim_table == D_80175170) {
                        anim_addr = (u32) D_80175178;
                        goto apply_hidden_anim;
                    }
                    if (hidden_anim_table == D_80175178) {
                        goto select_hidden_anim;
                    }
                    goto update_hidden_bob;
                }
select_hidden_anim:
                anim_addr = (u32) hidden_next_anim;
apply_hidden_anim:
                hidden_next_anim = (u8 *) anim_addr;
                ((S_80170BF8_2 *)object)->unk_2C = hidden_next_anim;
                frame_addr = (u32) ((((s32) (D_80083228[0] + ((S_80170BF8_3 *)actor_base)->unk_2A + 0x100) >> 9) & 7));
                frame_addr += (u32) hidden_next_anim;
                func_80047784(object, *(u8 *) frame_addr, 0);
                goto update_hidden_bob;
            }
update_hidden_bob:
            if (((S_80170BF8_2 *)object)->unk_14 & 0x6000) {
                ((S_80170BF8_0 *)actor)->unk_98 = (u16) (((S_80170BF8_0 *)actor)->unk_98 | 0x8000);
                if (((S_80170BF8_2 *)object)->unk_2C == D_80175140) {
                    ((S_80170BF8_0 *)actor)->unk_A8 = 0;
                }
            }
            bob_offset = func_800644B8((((S_80170BF8_0 *)actor)->unk_A8 << 0xC) / 20) >> 0xA;
            ((S_80170BF8_0 *)actor)->unk_A8 = (s16) ((u16) ((S_80170BF8_0 *)actor)->unk_A8 + 1);
            goto adjust_hidden_hover;
        }
adjust_hidden_hover:
        if (!(((S_80170BF8_0 *)actor)->unk_98 & 8)) {
            hidden_hover_offset = func_800BCB04(((S_80170BF8_1 *)motion)->unk_00.at02.v, ((S_80170BF8_1 *)motion)->unk_04.at02.v, (s16) (((S_80170BF8_3 *)actor_base)->unk_88.u - 0x20)) - ((S_80170BF8_3 *)actor_base)->unk_88.u;
            height_offset = ((S_80170BF8_0 *)actor)->unk_90.at02.v;
            if (height_offset > (hidden_hover_offset - 0x20)) {
                old_height_offset = (u16) ((S_80170BF8_0 *)actor)->unk_90.at02.v;
                ((S_80170BF8_0 *)actor)->unk_90.at02.v = (s16) (old_height_offset - 8);
            } else if (height_offset < (hidden_hover_offset - 0x2A)) {
                old_height_offset = (u16) ((S_80170BF8_0 *)actor)->unk_90.at02.v;
                ((S_80170BF8_0 *)actor)->unk_90.at02.v = (s16) (old_height_offset + 8);
            }
        }
reset_bob:
        ((S_80170BF8_0 *)actor)->unk_A8 = 0;
        ((S_80170BF8_0 *)actor)->unk_98 = (u16) (((S_80170BF8_0 *)actor)->unk_98 & 0x7FFF);
update_display_height:
        height_flags = ((S_80170BF8_3 *)actor_base)->unk_1C;
        if (height_flags & 0x40000000) {
            ((S_80170BF8_3 *)actor_base)->unk_1C = (s32) (height_flags & 0xBFFFFFFF);
            tile_height = func_800BCB04((((S_80170BF8_2 *)object)->unk_24 << 6) | 0x20, (((S_80170BF8_2 *)object)->unk_25 << 6) | 0x20, (s16) (((S_80170BF8_3 *)actor_base)->unk_88.u - 0x20));
            if (tile_height < 0x200) {
                ((S_80170BF8_0 *)actor)->unk_90.at02.v = (s16) ((u16) ((S_80170BF8_0 *)actor)->unk_90.at02.v + (((S_80170BF8_3 *)actor_base)->unk_88.u - tile_height));
                ((S_80170BF8_3 *)actor_base)->unk_88.u = (u16) tile_height;
            }
        }
        display_height = (s32) (((S_80170BF8_3 *)actor_base)->unk_88.u + (u16) ((S_80170BF8_0 *)actor)->unk_90.at02.v + bob_offset);
        ((S_80170BF8_1 *)motion)->unk_0A = (s16) display_height;
        ((S_80170BF8_2 *)object)->unk_14 = (u16) (((S_80170BF8_2 *)object)->unk_14 | 0x40);
    }
}
