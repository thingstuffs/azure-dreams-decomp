#include "common.h"

#define S8_AT(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct {
    s32 v[3];
} Copy12;

extern void func_8003EA54();
extern s32 func_80071494();
extern void func_8023FB18();
extern s32 func_80240810();
extern void func_8052DA54() __attribute__((noreturn));
extern void func_8052DC00() __attribute__((noreturn));
extern void func_8052DC20() __attribute__((noreturn));
extern void func_8052DC58() __attribute__((noreturn));

extern s32 D_80012BCC_load[4] __asm__("D_80012BCC");
extern s32 D_80012BCC_store[4] __asm__("D_80012BCC");
extern s32 D_80012BCC_load2[4] __asm__("D_80012BCC");
extern s32 D_80012BCC_store2[4] __asm__("D_80012BCC");
extern s32 D_80012BCC_load3[4] __asm__("D_80012BCC");
extern s32 D_80012BCC_store3[4] __asm__("D_80012BCC");
extern s32 D_80084D5C;
extern u8 D_80132AE8[16];
extern u8 D_80290704[16];
extern Copy12 D_80526760;
extern u8 D_8053016C[16];
extern s32 D_805301C0[4];

void func_80812B70(void *arg0, void *arg1, void *arg2) {
    Copy12 values;
    s32 *valuep;
    s32 object_value;
    s16 state;
    s32 timer1;
    s32 timer3;
    s32 timer4;
    s32 call_result;

    values = D_80526760;
    valuep = values.v;

    S32_AT(arg1, 0) += S32_AT(arg1, 0xC);
    S32_AT(arg1, 4) += S32_AT(arg1, 0x10);
    S32_AT(arg1, 8) += S32_AT(arg1, 0x14);

    U16_AT(PTR_AT(arg0, 0), 0x62) |= 2;
    state = S16_AT(arg0, 4);

    if (state == 2) {
        goto state_2;
    }
    if (state < 3) {
        if (state == 0) {
            goto state_0;
        }
        if (state == 1) {
            goto state_1;
        }
        func_8052DC58();
        return;
    }
    if (state == 4) {
        goto state_4;
    }
    if (state < 4) {
        goto state_3;
    }
    if (state == 255) {
        goto state_255;
    }
    func_8052DC58();
    return;

state_0:
        func_8003EA54(arg2);
        S32_AT(arg1, 0x14) += 0x40000;
        S8_AT(arg0, 0x1D) = 0;
        if (S32_AT(arg1, 8) < 0) {
            return;
        }
        S32_AT(arg1, 8) = 0;
        U16_AT(arg0, 6) = 15;
        S32_AT(arg1, 0xC) = ((func_80071494() % 448) - 128) << 12;
        S32_AT(arg1, 0x10) = ((func_80071494() % 160) + 64) << 12;
        S32_AT(arg1, 0x14) = -0x100000;
        U16_AT(arg0, 4)++;
        func_8052DC58();
        return;

state_1:
        func_8003EA54(arg2);
        S32_AT(arg1, 0x14) += 0x40000;
        timer1 = U16_AT(arg0, 6) - 1;
        U16_AT(arg0, 6) = timer1;
        if (S32_AT(arg1, 8) < 0) {
            return;
        }
        if ((s16)timer1 > 0) {
            S32_AT(arg1, 8) = 0;
            S32_AT(arg1, 0x14) = -S32_AT(arg1, 0x14);
            func_8052DC58();
            return;
        }
        S32_AT(arg1, 8) = 0;
        S32_AT(arg1, 0x10) = 0;
        S32_AT(arg1, 0xC) = 0;
        S32_AT(arg1, 0x14) = ((func_80071494() & 0xFF) << 11) + 0xFFEB0000;
        U16_AT(arg0, 6) = (func_80071494() & 0xF) + 30;
        U16_AT(arg0, 4)++;
        func_8052DC58();
        return;

state_2:
        func_8003EA54(arg2);
        S32_AT(arg1, 0x14) += 0x30000;
        U16_AT(arg0, 6)--;
        if (S32_AT(arg1, 8) >= 0) {
            S32_AT(arg1, 8) = 0;
            if (S16_AT(arg0, 6) < 0) {
                object_value = D_805301C0[S16_AT(arg0, 0x54)];
                S16_AT(arg2, 0x12) = 0;
                S8_AT(arg2, 4) = 0;
                S8_AT(arg2, 5) = 0;
                S32_AT(arg2, 8) = object_value;
                S32_AT(arg1, 0x14) = 0;
                U16_AT(arg0, 6) = 150;
                U16_AT(arg0, 4)++;
                func_8052DA54();
                return;
            }
            S32_AT(arg1, 0x14) = -S32_AT(arg1, 0x14) >> 1;
        }
        call_result = func_80240810(D_8053016C, arg1, D_80290704, D_80132AE8);
        if (call_result != 0) {
            D_80012BCC_store[0] = values.v[S16_AT(arg0, 0x54)] * 1000 + D_80012BCC_load[0];
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            call_result = 255;
            ASM_TAILSLOT_PIN_TIED(call_result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_8052DC20();
        }
        return;

state_3:
        timer3 = U16_AT(arg0, 6);
        timer3--;
        U16_AT(arg0, 6) = timer3;
        if ((s16)timer3 < 0) {
            U16_AT(arg0, 6) = 31;
            U16_AT(arg0, 4)++;
        }
        call_result = func_80240810(D_8053016C, arg1, D_80290704, D_80132AE8);
        if (call_result != 0) {
            D_80012BCC_store2[0] = valuep[S16_AT(arg0, 0x54)] * 1000 + D_80012BCC_load2[0];
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            call_result = 255;
            ASM_TAILSLOT_PIN_TIED(call_result);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_8052DC20();
        }
        return;

state_4:
        if (func_80240810(D_8053016C, arg1, D_80290704, D_80132AE8) != 0) {
            D_80012BCC_store3[0] = valuep[S16_AT(arg0, 0x54)] * 1000 + D_80012BCC_load3[0];
            S16_AT(arg0, 4) = 255;
        }
        if ((U16_AT(arg0, 6) >> 2) & 1) {
            register s32 tail_value;
            tail_value = U16_AT(arg2, 0x14) | 0x80;
            ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8052DC00();
            return;
        }
        U16_AT(arg2, 0x14) &= 0xFF7F;
        timer4 = U16_AT(arg0, 6);
        timer4--;
        U16_AT(arg0, 6) = timer4;
        if ((s16)timer4 > 0) {
            return;
        }
        U16_AT(arg0, 4) = 255;
        func_8052DC58();
        return;

state_255:
        func_8023FB18((u8 *)arg0 + 8);
        U16_AT(arg0, -2) |= 0x8000;
        D_80084D5C |= 0x8000;
        return;

}
