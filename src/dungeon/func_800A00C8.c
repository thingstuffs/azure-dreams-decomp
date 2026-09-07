#include "common.h"

typedef struct GlobalState {
    s32 pad0;
    u16 flags;
    u8 pad6[6];
} GlobalState;

extern GlobalState D_80083160;
extern s32 D_800814A0[3];

extern s32 func_800644B8(s32);
extern void func_800A58A4(void) __attribute__((noreturn));
extern void func_800A5938(void) __attribute__((noreturn));
extern void func_800A5994(void) __attribute__((noreturn));

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

void func_800A5828(void *arg0, s32 arg1, void *arg2)
{
    s32 step;
    s32 color;
    s32 angle;
    s16 current;
    u16 oscillation;
    void *prim;
    GlobalState *global = &D_80083160;

    if (S16_AT(arg0, 0x64) == 0) {
        if (global->flags & 1) {
            s32 tail_value;

            tail_value = (s16)U16_AT(arg0, 0x6A) >> 1;
            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800A58A4();
        }

        current = U16_AT(arg0, 0x6A);
        U16_AT(arg0, 0x6A) =
            U16_AT(arg0, 0x6A) + (192 - current) / S16_AT(arg0, 0x66);
        color = U8_AT(arg0, 0x6A);
        U8_AT(arg2, 0xE) = color;
        U8_AT(arg2, 0xD) = color;
        U8_AT(arg2, 0xC) = color;

        U16_AT(arg0, 0x66)--;
        if (S16_AT(arg0, 0x66) <= 0) {
            U16_AT(arg0, 0x66) = 16;
            U16_AT(arg0, 0x64)++;
            func_800A5994();
        }
    } else {
        if (global->flags & 1) {
            S32_AT(arg2, 0xC) = 0;
            func_800A5938();
        }

        step = S16_AT(arg0, 0x6A) / S16_AT(arg0, 0x66);
        U16_AT(arg0, 0x6A) -= step;
        color = U8_AT(arg0, 0x6A);
        U8_AT(arg2, 0xE) = color;
        U8_AT(arg2, 0xD) = color;
        U8_AT(arg2, 0xC) = color;

        U16_AT(arg0, 0x66)--;
        if (S16_AT(arg0, 0x66) <= 0) {
            prim = *(void **)((u8 *)(*(void **)((u8 *)arg0 + 4)) - 0x14);
            U8_AT(prim, 0xC) = 0x80;
            U8_AT(prim, 0xD) = 0x80;
            U8_AT(prim, 0xE) = 0x80;
            U16_AT(arg0, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
            return;
        }
    }

    U16_AT(arg0, 0x68)++;
    angle = (func_800644B8((s16)U16_AT(arg0, 0x68) << 9) >> 4) + 0x1000;
    S16_AT(arg2, 0x1C) = angle;
    S16_AT(arg2, 0x1E) = angle;

    oscillation = 0xFFC0;
    if (U16_AT(arg0, 0x68) & 1) {
        oscillation = 64;
    }
    S16_AT(arg2, 0x1A) = oscillation;

    color = ((U16_AT(arg0, 0x68) & 3) << 4) + 64;
    prim = *(void **)((u8 *)(*(void **)((u8 *)arg0 + 4)) - 0x14);
    U8_AT(prim, 0xC) = color;
    U8_AT(prim, 0xD) = color;
    U8_AT(prim, 0xE) = color;
}

/* MECHANISM: A held global base yields the 0x20 s0/s1/ra prologue and shared page load.
   Nested fade arithmetic preserves retail's v1/a0/v0 roles; a guarded v0 carrier sinks sra into the zero-arg noreturn tail.
   The joined u16 oscillation local reproduces the branch polarity and ori 0xFFC0 materialization. */
