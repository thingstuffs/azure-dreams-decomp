#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();
extern void func_8016B53C() __attribute__((noreturn));
extern void func_8016B5E4() __attribute__((noreturn));
extern void func_8016B650() __attribute__((noreturn));
extern void func_8016B74C() __attribute__((noreturn));
extern void func_8016B7E4() __attribute__((noreturn));
extern void func_8016B8D4() __attribute__((noreturn));
extern void func_8016B8D8() __attribute__((noreturn));
extern void func_8016B910() __attribute__((noreturn));

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

void func_8016B3A8(void *arg0, S_8016B3A8_0 *arg1, void *arg2)
{
    register void *base ASM_REG("$19") = arg0;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s16 old_state ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 old_raw ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *call_arg0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call_arg1;
    void *call_arg2;
    s32 motion_value;
    register u32 motion_raw ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 index;
    s16 value;
    s32 flags;
    register s32 amount ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u16 initial_mode;
    u16 mode;

    if (D_80083462 & 0x2000) {
        void *entry_self = arg0;
        Callback entry_callback;

        entry_callback = (*(Callback *)((u8 *)arg0 + 0x8C));
        if (entry_callback == (Callback)&D_8016B9DC) {
            ASM_KEEP(entry_self);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            entry_callback(entry_self, arg1, arg2, entry_self);
            return;
        }
        (*(u8 *)((u8 *)arg0 + 0x71)) &= 0x7F;
        return;
    }

    call_arg0 = arg0;
    call_arg1 = arg1;
    call_arg2 = arg2;
    ASM_KEEP4(call_arg0, call_arg1, call_arg2, base);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    old_raw = (*(u8 *)((u8 *)arg0 + 0x6D));
    old_state = (s8)old_raw;
    if (func_800A9E70(call_arg0, call_arg1, call_arg2, arg0) != 0) {
        return;
    }

    {
        Callback ordinary_callback = (*(Callback *)((u8 *)arg0 + 0x8C));

        if (ordinary_callback != 0) {
            ordinary_callback(arg0, arg1, arg2, arg0);
        }
    }
    D_8016E6A0[(*(u8 *)((u8 *)arg0 + 0x9A))](arg0, arg1, arg2, arg0);
    {
        register s32 old_compare ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        old_compare = (u32)(u16)old_state << 16;
        ASM_KEEP_NV(old_compare);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        old_compare >>= 16;
        if (old_compare != (*(s8 *)((u8 *)arg0 + 0x6D))) {
            func_800AA36C(arg0, arg1, arg2, arg0);
        }
    }

    arg1->unk_00.at00.v += arg1->unk_0C;
    arg1->unk_04.at00.v += arg1->unk_10;

    if (!((*(s32 *)((u8 *)arg0 + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
        arg1->unk_14 += (*(s8 *)((u8 *)arg0 + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)arg0 + 0x9D))++;
        func_8016B53C();
        return;
    }

    do { (*(u8 *)((u8 *)arg0 + 0x9D)) = 0; } while (0);
    (*(s32 *)((u8 *)arg0 + 0x90)) += arg1->unk_14;
    initial_mode = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;

    if (!(initial_mode & 0x8000)) {
        index = ((D_80083228 + ((S_8016B3A8_2 *)base)->unk_2A + 0x100) >> 9) & 7;
        if ((*(s16 *)((u8 *)arg0 + 0x94)) != index) {
            func_80047738(arg2,
                *(u8 *)(((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 + index),
                ((Rec_D_80082E80 *)arg2)->unk_04.as_s8);
            (*(s16 *)((u8 *)arg0 + 0x94)) = index;
        }
        if (D_8006CCF8[index] != 0) {
            u32 tail_value;

            tail_value = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 1;
            ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8016B5E4();
            return;
        }

        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xFFFE;
        func_800A020C(((S_8016B3A8_2 *)base)->unk_1C, (u8 *)arg2 + 0xC);
        if (!(((S_8016B3A8_2 *)base)->unk_1C & 0x20)) {
            if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x40)) {
                func_800478B8(arg2);
                goto clear_8000000;
            }
        } else {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x7000;
            ((S_8016B3A8_2 *)base)->unk_1C &= 0xFFFBFFFF;
        }

clear_8000000:
        ((S_8016B3A8_2 *)base)->unk_1C &= 0xF7FFFFFF;
        flags = ((S_8016B3A8_2 *)base)->unk_1C;
        if (flags & 0x40000) {
            mode = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
            if (!(mode & 0x40)) {
                u8 *kind = ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8;

                if (kind == D_8016E634) {
                    if (((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 3 && (mode & 0x1000)) {
                        (*(s32 *)((u8 *)arg0 + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)arg0 + 0xB0)) = (s32)0xFFFF3000;
                    }
                    (*(s32 *)((u8 *)arg0 + 0xA4)) += (*(s32 *)((u8 *)arg0 + 0xAC));
                    (*(s32 *)((u8 *)arg0 + 0xAC)) += (*(s32 *)((u8 *)arg0 + 0xB0));
                    if ((*(s32 *)((u8 *)arg0 + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)arg0 + 0xA4)) = 0;
                        func_8016B74C();
                        return;
                    }
                } else if (kind == D_8016E644 || kind == D_8016E66C) {
                    (*(s32 *)((u8 *)arg0 + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)arg0 + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)arg0 + 0xA4)) = 0;
                        func_8016B74C();
                        return;
                    }
                } else if (kind != D_8016E654 && kind != D_8016E65C &&
                           kind != D_8016E664) {
                    (*(s32 *)((u8 *)arg0 + 0xA4)) = 0;
                }
            }

            amount = (*(u16 *)((u8 *)arg0 + 0x98)) & 8;
            if (amount == 0) {
                motion_value = (*(s16 *)((u8 *)arg0 + 0x92));
                motion_raw = (*(u16 *)((u8 *)arg0 + 0x92));
                if (amount < motion_value) {
                    amount = motion_raw - 8;
                    (*(s16 *)((u8 *)arg0 + 0x92)) = amount;
                    func_8016B910();
                    return;
                }
                goto adjust_positive;
            }
            goto finish_motion;
        }

        {
            s32 tail_sum;
            register u16 tail_mode ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

            amount = (*(s32 *)((u8 *)arg0 + 0xA4));
            tail_sum = (*(s32 *)((u8 *)arg0 + 0x90));
            tail_mode = (*(u16 *)((u8 *)arg0 + 0x98));
            (*(s16 *)((u8 *)arg0 + 0xB8)) = 0;
            (*(s32 *)((u8 *)arg0 + 0xA4)) = 0;
            tail_sum += amount;
            ASM_USE_NV(tail_mode);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            ASM_TAILSLOT_PIN(tail_sum);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8016B7E4();
            return;
        }
    }

    if (initial_mode & 0x800) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = initial_mode & 0x8FFF;
    } else {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = initial_mode | 0x7000;
    }
    ((S_8016B3A8_2 *)base)->unk_1C &= 0xF7FFFFFF;
    flags = ((S_8016B3A8_2 *)base)->unk_1C;

    if (!(flags & 0x40000)) {
        amount = (*(s32 *)((u8 *)arg0 + 0xA4));
        (*(s16 *)((u8 *)arg0 + 0xB8)) = 0;
        (*(s32 *)((u8 *)arg0 + 0xA4)) = 0;
        (*(s32 *)((u8 *)arg0 + 0x90)) -= amount;
        if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
            value = func_800BCB04(arg1->unk_00.at02.v,
                                  arg1->unk_04.at02.v,
                                  (s16)(((S_8016B3A8_2 *)base)->unk_88 - 0x20)) -
                    ((S_8016B3A8_2 *)base)->unk_88;
            if (value < (*(s16 *)((u8 *)arg0 + 0x92))) {
                (*(s16 *)((u8 *)arg0 + 0x92)) = value;
                (*(u8 *)((u8 *)arg0 + 0x9D)) = 0;
                arg1->unk_14 = 0;
                ((S_8016B3A8_2 *)base)->unk_1C |= 0x08000000;
                func_8016B910();
                return;
            }
        }
        goto finish_motion;
    }

    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x40)) {
        u8 *kind = ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8;

        if (kind == D_8016E634) {
            (*(s32 *)((u8 *)arg0 + 0xAC)) = 0;
            func_8016B8D4();
            return;
        }
        if (kind == D_8016E644 || kind == D_8016E66C) {
            (*(s32 *)((u8 *)arg0 + 0xA4)) -= 0x40000;
            if ((*(s32 *)((u8 *)arg0 + 0xA4)) <= 0) {
                (*(s32 *)((u8 *)arg0 + 0xA4)) = 0;
                func_8016B8D8();
                return;
            }
        } else if (kind != D_8016E654 && kind != D_8016E65C &&
                   kind != D_8016E664) {
            (*(s32 *)((u8 *)arg0 + 0xA4)) = 0;
        }
    }

    amount = (*(u16 *)((u8 *)arg0 + 0x98)) & 8;
    if (amount == 0) {
        motion_value = (*(s16 *)((u8 *)arg0 + 0x92));
        motion_raw = (*(u16 *)((u8 *)arg0 + 0x92));
        if (amount < motion_value) {
            amount = motion_raw - 8;
            goto store_adjustment;
        }
adjust_positive:
        amount = motion_value < -8;
        if (amount != 0) {
            amount = motion_raw + 8;
        } else {
            goto finish_motion;
        }
store_adjustment:
        (*(s16 *)((u8 *)arg0 + 0x92)) = amount;
    }
finish_motion:
    flags = ((S_8016B3A8_2 *)base)->unk_1C;
    if (flags & 0x40000000) {
        ((S_8016B3A8_2 *)base)->unk_1C = flags & 0xBFFFFFFF;
        value = func_800BCB04((((Rec_D_80082E80 *)arg2)->unk_24 << 6) | 0x20,
                              (((Rec_D_80082E80 *)arg2)->unk_25 << 6) | 0x20,
                              (s16)(((S_8016B3A8_2 *)base)->unk_88 - 0x20));
        if (value < 0x200) {
            (*(s16 *)((u8 *)arg0 + 0x92)) =
                (u16)(*(s16 *)((u8 *)arg0 + 0x92)) +
                (((S_8016B3A8_2 *)base)->unk_88 - value);
            ((S_8016B3A8_2 *)base)->unk_88 = value;
        }
    }
    arg1->unk_0A = ((S_8016B3A8_2 *)base)->unk_88 +
                             (u16)(*(s16 *)((u8 *)arg0 + 0x92)) -
                             (*(u16 *)((u8 *)arg0 + 0xA6));
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x40;
}
