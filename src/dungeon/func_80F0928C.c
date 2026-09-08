#include "common.h"

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern s32 D_80045340;
extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_800E296C;
extern u8 D_80170F74[];
extern EntityCallback D_80173D90[];

extern void func_8004491C(void *, void *);
extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(s32, s32, s16);

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define CB_AT(p, o)  (*(EntityCallback *)((u8 *)(p) + (o)))

#ifndef __mips__
static const u32 D_80F0928C[]
    __attribute__((section(".text.func_80170A8C"))) = {
    0x3C028008,
    0x94423462,
};
#endif

void func_80170A8C(void *arg0, void *arg1, void *arg2)
{
    register void *state ASM_REG("$17") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *motion = arg1;
    register void *part ASM_REG("$19") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *state2 = state;
    register s32 floor_height ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 part_flags;
    u16 old_frame;
    u8 *samples;
    s16 sample_height;
    s16 base_height;
    s32 angle_calc;
    s32 temp;

    if (D_80083462 & 0x2000) {
        EntityCallback early_callback;

        early_callback = CB_AT(state, 0x8C);
        if (early_callback == (EntityCallback)D_80170F74) {
            register void *incoming_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            ASM_KEEP(incoming_a0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            early_callback(incoming_a0, motion, part, incoming_a0);
        } else {
            U8_AT(state, 0x71) &= 0x7F;
        }
        goto done;
    }

    {
    register s32 saved_direction ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    EntityCallback callback;
    s16 old_mode;
    s16 direction;
    u8 direction_enabled;

    {
        register void *call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register void *call_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        register void *call_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        void *call_a3;

        ASM_KEEP(call_a0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(call_a2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        call_a0 = state;
        call_a1 = motion;
        call_a2 = part;
        old_mode = (s8)U8_AT(state, 0x6D);
        call_a3 = state;
        if (func_800A9E70(call_a0, call_a1, call_a2, call_a3) != 0) {
            goto done;
        }
    }

    callback = CB_AT(state, 0x8C);
    if (callback != 0) {
        callback(state, motion, part, state);
    }
    D_80173D90[U8_AT(state, 0x9A)](state, motion, part, state);

    if ((s16)old_mode != S8_AT(state, 0x6D)) {
        func_800AA36C(state, motion, part, state);
    }

    if ((D_800E296C & 4) && (S16_AT(state, 0xA4) < 0)) {
        if (S16_AT(state, 0xA6) != 0) {
            S16_AT(state, 0xA4) = 0;
            S16_AT(state, 0xA6) = 0;
            S32_AT(part, 0xC) = 0;
            func_8004491C((u8 *)state - 0x20, &D_80045340);
        }
    }

    if (S16_AT(state, 0xA4) >= 0) {
        S32_AT(part, 0xC) += 0x101010;
        old_frame = U16_AT(state, 0xA4);
        S16_AT(state, 0xA4) = old_frame + 1;
        if ((s16)old_frame >= 9) {
            S32_AT(part, 0xC) = 0x808080;
            U16_AT(part, 0x14) &= 0xFFF3;
            U16_AT(part, 0x12) += 0x80;
            S16_AT(state, 0xA4) = -1;
        }
    }

    part_flags = U16_AT(part, 0x14);
    if (!(part_flags & 0x8000)) {
        angle_calc = (D_80083228 + S16_AT(state2, 0x2A) + 0x100) >> 9;
        direction = angle_calc & 7;
        if (S16_AT(state, 0x94) != direction) {
            samples = PTR_AT(part, 0x2C);
            if (samples != 0) {
                func_80047738(part, samples[direction], S8_AT(part, 4));
            }
            S16_AT(state, 0x94) = direction;
        }

        saved_direction = direction;
        direction_enabled = D_8006CCF8[saved_direction];
        ASM_KEEP(saved_direction);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        if (direction_enabled != 0) {
            U16_AT(part, 0x14) |= 1;
        } else {
            U16_AT(part, 0x14) &= 0xFFFE;
        }

        if (!(S32_AT(state2, 0x1C) & 0x20)) {
            if (!(U16_AT(part, 0x14) & 0x40)) {
                func_800478B8(part);
            }
        } else {
            U16_AT(part, 0x14) |= 0x7000;
        }
        func_800A020C(S32_AT(state2, 0x1C), (u8 *)part + 0xC);
    } else {
        if (part_flags & 0x800) {
            U16_AT(part, 0x14) = part_flags & 0x8FFF;
        } else {
            U16_AT(part, 0x14) = part_flags | 0x7000;
        }
    }

    S32_AT(motion, 0) += S32_AT(motion, 0xC);
    S32_AT(motion, 4) += S32_AT(motion, 0x10);

    if (U16_AT(state, 0x98) & 8) {
        S8_AT(state, 0x9D) = 0;
    } else {
        S32_AT(motion, 0x14) += S8_AT(state, 0x9D) * 0x14000;
        U8_AT(state, 0x9D)++;
    }

    S32_AT(state, 0x90) += S32_AT(motion, 0x14);
    if (U16_AT(state, 0x98) & 4) {
        goto clear_falling;
    }

    sample_height = func_800BCB04(U16_AT(motion, 2), U16_AT(motion, 6),
                                  (s16)(U16_AT(state2, 0x88) - 0x20));
    if (sample_height >= 0x200) {
        goto clear_falling;
    }

    base_height = U16_AT(state2, 0x88);
    if ((S16_AT(state, 0x92) + base_height) < sample_height) {
        S32_AT(state2, 0x1C) &= 0xF7FFFFFF;
        goto finish_height;
    }

    if (sample_height >= base_height) {
        S32_AT(state, 0x90) = 0;
        S32_AT(motion, 0x14) = 0;
        S32_AT(state2, 0x1C) |= 0x08000000;
        S8_AT(state, 0x9D) = 0;
        goto finish_height;
    }

    S32_AT(motion, 0x14) = 0;
    S32_AT(state2, 0x1C) |= 0x08000000;
    S8_AT(state, 0x9D) = 0;
    S16_AT(state, 0x92) = (s16)sample_height - U16_AT(state2, 0x88);

finish_height:
    temp = S32_AT(state2, 0x1C);
    if (temp & 0x40000000) {
        S32_AT(state2, 0x1C) = temp & 0xBFFFFFFF;
        floor_height = func_800BCB04((U8_AT(part, 0x24) << 6) | 0x20,
                                     (U8_AT(part, 0x25) << 6) | 0x20,
                                     (s16)(U16_AT(state2, 0x88) - 0x20));
        S16_AT(state, 0x92) += U16_AT(state2, 0x88) - floor_height;
        U16_AT(state2, 0x88) = floor_height;
    }
    goto final_update;

clear_falling:
    S32_AT(state2, 0x1C) &= 0xF7FFFFFF;

final_update:
    S16_AT(motion, 0xA) = U16_AT(state2, 0x88) + U16_AT(state, 0x92);
    U16_AT(part, 0x14) |= 0x40;
    }

done:
    return;
}
