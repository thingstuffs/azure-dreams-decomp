#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_8016B9DC;
extern u8 D_8016E634[8];
extern u8 D_8016E644[8];
extern u8 D_8016E654[8];
extern u8 D_8016E65C[8];
extern u8 D_8016E664[8];
extern u8 D_8016E66C[8];
extern Callback D_8016E6A0[];


typedef struct S_8016B3A8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016B3A8_0;   /* arg1 in func_8016B3A8 */


typedef struct S_8016B3A8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_8016B3A8_2;   /* base in func_8016B3A8 */

/* Runs actor callbacks and updates animation, movement, and ground height. */
void func_8016B3A8(void *self, S_8016B3A8_0 *motion, void *sprite)
{
    register void *actor_base ASM_REG("$19") = self;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s16 old_state ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs actor_base+offset); the source shape that makes it unnecessary has not been found */
    register u8 old_state_byte ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *call_self;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call_motion;
    void *call_sprite;
    s32 height_offset;
    register u32 height_bits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 direction;
    s16 floor_height;
    s32 actor_flags;
    register s32 adjustment;
    u16 initial_sprite_flags;
    u16 sprite_flags;
    s32 height_sum;
    register u16 motion_flags ASM_REG("$4");   /* MATCH: keep the merged sprite_flags test in retail's argument register. */

    if (D_80083462 & 0x2000) {
        void *callback_self = self;
        Callback special_callback;

        special_callback = (*(Callback *)((u8 *)self + 0x8C));
        if (special_callback == (Callback)&D_8016B9DC) {
            ASM_KEEP(callback_self);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            special_callback(callback_self, motion, sprite, callback_self);
            return;
        }
        (*(u8 *)((u8 *)self + 0x71)) &= 0x7F;
        return;
    }

    call_self = self;
    call_motion = motion;
    call_sprite = sprite;
    ASM_KEEP4(call_self, call_motion, call_sprite, actor_base);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    old_state_byte = (*(u8 *)((u8 *)self + 0x6D));
    old_state = (s8)old_state_byte;
    if (func_800A9E70(call_self, call_motion, call_sprite, self) != 0) {
        return;
    }

    {
        Callback update_callback = (*(Callback *)((u8 *)self + 0x8C));

        if (update_callback != 0) {
            update_callback(self, motion, sprite, self);
        }
    }
    D_8016E6A0[(*(u8 *)((u8 *)self + 0x9A))](self, motion, sprite, self);
    {
        register s32 state_compare ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        state_compare = (u32)(u16)old_state << 16;
        ASM_KEEP_NV(state_compare);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        state_compare >>= 16;
        if (state_compare != (*(s8 *)((u8 *)self + 0x6D))) {
            func_800AA36C(self, motion, sprite, self);
        }
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if (!((*(s32 *)((u8 *)self + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)self + 0x98)) & 8)) {
        motion->unk_14 += (*(s8 *)((u8 *)self + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)self + 0x9D))++;
    } else {
        (*(u8 *)((u8 *)self + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)self + 0x90)) += motion->unk_14;
    initial_sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;

    if (!(initial_sprite_flags & 0x8000)) {
        direction = ((D_80083228 + ((S_8016B3A8_2 *)actor_base)->unk_2A + 0x100) >> 9) & 7;
        if ((*(s16 *)((u8 *)self + 0x94)) != direction) {
            func_80047738(sprite,
                *(u8 *)(((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 + direction),
                ((Rec_D_80082E80 *)sprite)->unk_04.as_s8);
            (*(s16 *)((u8 *)self + 0x94)) = direction;
        }
        {
            u32 flip_flags;

            if (D_8006CCF8[direction] != 0) {
                flip_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 1;
            } else {
                flip_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xFFFE;
            }
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = flip_flags;
        }
        func_800A020C(((S_8016B3A8_2 *)actor_base)->unk_1C, (u8 *)sprite + 0xC);
        if (!(((S_8016B3A8_2 *)actor_base)->unk_1C & 0x20)) {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                func_800478B8(sprite);
                goto clear_ground_contact;
            }
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x7000;
            ((S_8016B3A8_2 *)actor_base)->unk_1C &= 0xFFFBFFFF;
        }

clear_ground_contact:
        ((S_8016B3A8_2 *)actor_base)->unk_1C &= 0xF7FFFFFF;
        actor_flags = ((S_8016B3A8_2 *)actor_base)->unk_1C;
        if (actor_flags & 0x40000) {
            sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
            if (!(sprite_flags & 0x40)) {
                u8 *anim_table = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;

                if (anim_table == D_8016E634) {
                    if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3 && (sprite_flags & 0x1000)) {
                        (*(s32 *)((u8 *)self + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)self + 0xB0)) = (s32)0xFFFF3000;
                    }
                    (*(s32 *)((u8 *)self + 0xA4)) += (*(s32 *)((u8 *)self + 0xAC));
                    (*(s32 *)((u8 *)self + 0xAC)) += (*(s32 *)((u8 *)self + 0xB0));
                    if ((*(s32 *)((u8 *)self + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)self + 0xA4)) = 0;
                        goto airborne_motion;
                    }
                } else if (anim_table == D_8016E644 || anim_table == D_8016E66C) {
                    (*(s32 *)((u8 *)self + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)self + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)self + 0xA4)) = 0;
                        goto airborne_motion;
                    }
                } else if (anim_table != D_8016E654 && anim_table != D_8016E65C &&
                           anim_table != D_8016E664) {
                    (*(s32 *)((u8 *)self + 0xA4)) = 0;
                }
            }

airborne_motion:
            adjustment = (*(u16 *)((u8 *)self + 0x98)) & 8;
            if (adjustment == 0) {
                height_offset = (*(s16 *)((u8 *)self + 0x92));
                height_bits = (*(u16 *)((u8 *)self + 0x92));
                if (adjustment < height_offset) {
                    adjustment = height_bits - 8;
                    ASM_SCHED_BARRIER(); /* MATCH: keep the first motion arm separate from the later adjustment tail. */
                    (*(s16 *)((u8 *)self + 0x92)) = adjustment;
                    goto finish_motion;
                }
                goto adjust_positive;
            }
            goto finish_motion;
        }

        adjustment = (*(s32 *)((u8 *)self + 0xA4));
        height_sum = (*(s32 *)((u8 *)self + 0x90));
        motion_flags = (*(u16 *)((u8 *)self + 0x98));
        (*(s16 *)((u8 *)self + 0xB8)) = 0;
        (*(s32 *)((u8 *)self + 0xA4)) = 0;
        height_sum += adjustment;
        goto apply_height;
    }

    if (initial_sprite_flags & 0x800) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = initial_sprite_flags & 0x8FFF;
    } else {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = initial_sprite_flags | 0x7000;
    }
    ((S_8016B3A8_2 *)actor_base)->unk_1C &= 0xF7FFFFFF;
    actor_flags = ((S_8016B3A8_2 *)actor_base)->unk_1C;

    if (!(actor_flags & 0x40000)) {
        adjustment = (*(s32 *)((u8 *)self + 0xA4));
        height_sum = (*(s32 *)((u8 *)self + 0x90));
        motion_flags = (*(u16 *)((u8 *)self + 0x98));
        (*(s16 *)((u8 *)self + 0xB8)) = 0;
        (*(s32 *)((u8 *)self + 0xA4)) = 0;
        height_sum -= adjustment;
apply_height:
        (*(s32 *)((u8 *)self + 0x90)) = height_sum;
        motion_flags &= 8;
        if (!motion_flags) {
            floor_height = func_800BCB04(motion->unk_00.at02.v,
                                  motion->unk_04.at02.v,
                                  (s16)(((S_8016B3A8_2 *)actor_base)->unk_88 - 0x20)) -
                    ((S_8016B3A8_2 *)actor_base)->unk_88;
            if (floor_height < (*(s16 *)((u8 *)self + 0x92))) {
                (*(s16 *)((u8 *)self + 0x92)) = floor_height;
                (*(u8 *)((u8 *)self + 0x9D)) = 0;
                motion->unk_14 = 0;
                ((S_8016B3A8_2 *)actor_base)->unk_1C |= 0x08000000;
                goto finish_motion;
            }
        }
        goto finish_motion;
    }

    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
        u8 *anim_table = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;

        if (anim_table == D_8016E634) {
            (*(s32 *)((u8 *)self + 0xAC)) = 0;
            goto clear_height;
        }
        if (anim_table == D_8016E644 || anim_table == D_8016E66C) {
            (*(s32 *)((u8 *)self + 0xA4)) -= 0x40000;
            if ((*(s32 *)((u8 *)self + 0xA4)) <= 0) {
                (*(s32 *)((u8 *)self + 0xA4)) = 0;
                goto grounded_motion;
            }
        } else if (anim_table != D_8016E654 && anim_table != D_8016E65C &&
                   anim_table != D_8016E664) {
clear_height:
            (*(s32 *)((u8 *)self + 0xA4)) = 0;
        }
    }

grounded_motion:
    adjustment = (*(u16 *)((u8 *)self + 0x98)) & 8;
    if (adjustment == 0) {
        height_offset = (*(s16 *)((u8 *)self + 0x92));
        height_bits = (*(u16 *)((u8 *)self + 0x92));
        if (adjustment < height_offset) {
            adjustment = height_bits - 8;
            goto store_adjustment;
        }
adjust_positive:
        adjustment = height_offset < -8;
        if (adjustment != 0) {
            adjustment = height_bits + 8;
        } else {
            goto finish_motion;
        }
store_adjustment:
        (*(s16 *)((u8 *)self + 0x92)) = adjustment;
    }
finish_motion:
    actor_flags = ((S_8016B3A8_2 *)actor_base)->unk_1C;
    if (actor_flags & 0x40000000) {
        ((S_8016B3A8_2 *)actor_base)->unk_1C = actor_flags & 0xBFFFFFFF;
        floor_height = func_800BCB04((((Rec_D_80082E80 *)sprite)->unk_24 << 6) | 0x20,
                              (((Rec_D_80082E80 *)sprite)->unk_25 << 6) | 0x20,
                              (s16)(((S_8016B3A8_2 *)actor_base)->unk_88 - 0x20));
        if (floor_height < 0x200) {
            (*(s16 *)((u8 *)self + 0x92)) =
                (u16)(*(s16 *)((u8 *)self + 0x92)) +
                (((S_8016B3A8_2 *)actor_base)->unk_88 - floor_height);
            ((S_8016B3A8_2 *)actor_base)->unk_88 = floor_height;
        }
    }
    motion->unk_0A = ((S_8016B3A8_2 *)actor_base)->unk_88 +
                             (u16)(*(s16 *)((u8 *)self + 0x92)) -
                             (*(u16 *)((u8 *)self + 0xA6));
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x40;
}
