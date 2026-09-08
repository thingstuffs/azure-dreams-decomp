#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80024078_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    u8 unk_A8;
    u8 pad_A9[0x4B];
    void * unk_F4;
} S_80024078_0;   /* object in func_80024078 */


typedef struct S_80024078_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80024078_2_pre;   /* the 0x18 bytes before parent in func_80024078, addressed as parent[-1] */

typedef struct S_80024078_3 {
    u8 pad_00[0xA];
    volatile s16 unk_0A;
} S_80024078_3;   /* arg0 in func_80024078 */

typedef struct S_80024078_4 {
    u8 pad_00[0x2C];
    s16 unk_2C;
} S_80024078_4;   /* arg0->child in func_80024078 */



typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

typedef struct {
    void *field_0;
    u16 *field_4;
    u8 field_8;
    u8 field_9;
    s16 state;
    void *child;
    u8 pad_10[0xA];
    s16 timer_1A;
    s16 timer_1C;
    u8 pad_1E[2];
    s16 phase_20;
    s16 timer_22;
} State;

typedef struct {
    u8 pad_0[0xA];
    u16 count_A;
    s32 field_C;
} GlobalState;

extern s32 func_80040490(u8 *, Rect *);
extern s32 func_8003F80C();
extern void *func_80024578(void *);
extern void func_80024264(void) __attribute__((noreturn));
extern void func_800242D8(void) __attribute__((noreturn));
extern void func_80024334(void) __attribute__((noreturn));
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);

extern u8 D_80028F68[];
extern u8 D_8002964C[];
extern s16 D_8002966C[6];
extern u8 D_8002966E[12];
extern s32 D_80029670[3];
extern u16 D_800281F8[];
extern u8 D_800281FC[12];
extern s32 D_800814A0;
extern void *D_800814A8;
extern u8 D_80083160[];
extern s32 D_80083460;

void func_80024078(State *arg0)
{
    u8 *screen = D_80083160;

    switch (arg0->state) {
    case 0: {
        s32 rect[2];
        s32 phase;
        s32 duration;
        register void *parent ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        void *object;
        void *child;

        rect[0] = 0x010003A0;
        rect[1] = 0x00400020;
        func_80040490(D_80028F68, (Rect *)rect);
        func_8003F80C(D_8002964C, 0x7AC0, 1, 2);
        D_8002966C[0] = 1;
        D_8002966E[0] = arg0->field_9;
        D_80029670[0] = (s32)arg0->field_0;

        object = D_800814A8;
        ((S_80024078_0 *)object)->unk_F4 = D_800281FC;
        ((S_80024078_0 *)object)->unk_96 = 0x14;
        ((S_80024078_0 *)object)->unk_A8 = arg0->field_8;
        ((Rec_D_800814A8 *)D_800814A8)->unk_102 = 1;

        arg0->state++;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if ((*arg0->field_4 & 0x80) == 0) {
            break;
        }

        parent = arg0->field_0;
        child = func_80024578(((S_80024078_2_pre *)parent)[-1].unk_00);
        arg0->child = child;
        if (child == 0) {
            break;
        }

        duration = 0x20;
        {
            register s16 discarded_state ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            discarded_state = ((S_80024078_3 *)arg0)->unk_0A;
            ASM_KEEP(discarded_state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        }
        phase = -1;
        arg0->timer_1A = duration;
        arg0->phase_20 = phase;
        arg0->timer_22 = duration;
        func_80024264();
        return;
    }

    case 1:
        if (((S_80024078_4 *)(arg0->child))->unk_2C != 1) {
            break;
        }
        arg0->timer_1C = 0x18;
        arg0->state++;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        arg0->timer_1C--;
        if (arg0->timer_1C >= 0xB) {
            break;
        }
        ((Rec_D_800814A8 *)D_800814A8)->unk_A6--;
        if (func_80053EF0(4) != 2) {
            func_800A56E0(0x300);
        } else {
            func_800A56E0(0x4300);
        }
        func_800242D8();
        return;

    case 2:
        if (D_8002966C[0] != 0) {
            break;
        }
        arg0->timer_1A = 0x20;
        arg0->phase_20 = 0;
        arg0->state++;
        func_80024334();
        return;

    case 3:
        screen[0xA9] += (0x80 - screen[0xA9]) / arg0->timer_1A;
        screen[0xAA] += (0x80 - screen[0xAA]) / arg0->timer_1A;
        arg0->timer_1A--;
        if (arg0->timer_1A > 0) {
            break;
        }
        screen[0xA9] = 0x80;
        screen[0xAA] = 0x80;
        arg0->state++;
        func_80024334();
        return;

    case 4:
        if ((s16)D_800281F8[0] != 0) {
            break;
        } else {
            GlobalState *state = (GlobalState *)&D_80083460;
            state->field_C = 0;
            state->count_A--;
        }
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;

    case 5:
    case 6:
    default:
        break;
    }

    if (arg0->phase_20 < 0) {
        screen[0xA9] += (0x20 - screen[0xA9]) / arg0->timer_22;
        screen[0xAA] += (0x20 - screen[0xAA]) / arg0->timer_22;
        arg0->timer_22--;
        if (arg0->timer_22 <= 0) {
            arg0->phase_20 = 0;
        }
    }
    D_800281F8[0] = 0;
}

/* MECHANISM: The 0x28 frame comes from two sibling rect words plus held s0=state and s1=screen.
   Memory barriers retain the post-store pointer reload and the state-1 timer reload/order.
   Guarded a0/a1/v1 roles plus a separate phase scalar close the dead read and final store order. */
