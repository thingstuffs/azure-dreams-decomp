#include "common.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#define U8_AT(p, n)  (*(u8 *)((u8 *)(p) + (n)))
#define S8_AT(p, n)  (*(s8 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))

typedef struct {
    u16 value[5];
} Record10;

extern s32 func_8003DE58();
extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80047784();
extern void func_800A4ACC();
extern void func_800A56E0();
extern void func_800AD594();
extern void func_800C8150();

extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80083498[];
extern Record10 D_80170868;
extern Record10 D_80170874;
extern u8 D_80171138[];
extern u8 D_801745E0[];
extern u8 D_80174688[];
extern u8 D_80174ACC[];
extern u8 D_80174B14[];

void func_80174260(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *p0 = arg0;
    void *p1 = arg1;
    void *p2 = arg2;
    void *p3 = arg3;
    u16 position[3];
    Record10 first = D_80170868;
    Record10 second = D_80170874;
    s32 one = 1;
    s32 state;
    u16 flags;
    s16 timer;
    void *object;
    void *base;
    s32 effect;
    s32 next_state;

    ASM_KEEP(p0);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p2);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p3);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    U16_AT(p0, 0xA0)--;
    state = U8_AT(p0, 0x9B);

    if (state == one) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
        flags = U16_AT(p2, 0x14);
        if (flags & 0x8000) {
            effect = S32_AT(p3, 0x60);
            if (effect != 0) {
                func_800C8150(effect, 0x10, 0x10);
            }
            U8_AT(p0, 0x9B) = 2;
            return;
        }

        if (!(flags & 0x6000)) {
            goto end;
        }

        if (func_8003DE58(S32_AT(p2, 8), p2, position, 0) == 0) {
            position[2] = 0;
            position[1] = 0;
            position[0] = 0;
        }

        object = func_8003FD64(0x201, D_80083498);
        if (object != NULL) {
            func_8004491C(object, D_80174688);
            PTR_AT(object, 0x10) = D_801745E0;
            base = (u8 *)object + 0x20;
            S16_AT(base, 0x0C) = U16_AT(p1, 2) + position[0];
            S16_AT(base, 0x0E) = U16_AT(p1, 6) + position[1];
            S16_AT(base, 0x10) = U16_AT(p1, 0xA) + position[2];
            S32_AT(base, 0x58) = 0x80;
            S16_AT(base, 0x48) = one;
        }
        func_800A56E0(0x815);
        {
            register s32 end_timer ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            next_state = U8_AT(p0, 0x9B);
            end_timer = 0x1E;
            S16_AT(p0, 0x96) = end_timer;
        }
        goto advance_state;
state_one:
        effect = S32_AT(p3, 0x60);
        if (effect != 0) {
            timer = S16_AT(p0, 0x96);
            if (timer >= 0x12) {
                object = (u8 *)(long)effect - 0x20;
                if (timer < 0x17) {
                    U16_AT(PTR_AT(object, 0x0C), 0x1C) = first.value[timer - 0x12];
                    U16_AT(PTR_AT(object, 0x0C), 0x1E) = second.value[S16_AT(p0, 0x96) - 0x12];
                }
            }
        }

        if (S16_AT(p0, 0x96) == 0x14) {
            effect = S32_AT(p3, 0x60);
            if (effect != 0) {
                func_800C8150(effect, 0x10, 0x10);
            }
        }

        timer = U16_AT(p0, 0x96) - 1;
        S16_AT(p0, 0x96) = timer;
        if (timer > 0) {
            goto end;
        }

        PTR_AT(p2, 0x2C) = D_80174B14;
        func_80047784(p2,
            D_80174B14[((D_80083228 + S16_AT(p3, 0x2A) + 0x100) >> 9) & 7],
            0);
        next_state = U8_AT(p0, 0x9B);
advance_state:
        U8_AT(p0, 0x9B) = next_state + 1;
        return;
state_two:
        if (U16_AT(p2, 0x14) & 0xE000) {
            u16 *global_base;

            S32_AT(p1, 0x10) = 0;
            S32_AT(p1, 0x0C) = 0;
            func_800AD594(p3, 0x800);
            PTR_AT(p2, 0x2C) = D_80174ACC;
            func_80047784(p2,
                D_80174ACC[((D_80083228 + S16_AT(p3, 0x2A) + 0x100) >> 9) & 7],
                0);
            global_base = (u16 *)&D_80083460;
            global_base[5]--;
            func_800A4ACC(p3);
            U8_AT(p3, 0x6D) = 0;
            U16_AT(p3, 0x46) &= 0x7FFF;
            PTR_AT(p0, 0x8C) = D_80171138;
        }
end:
    return;
}
