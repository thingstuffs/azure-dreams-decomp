#include "common.h"

typedef struct S_8190AEB4_0 {
    union { s16 s; volatile u16 u; u16 p; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2C];
    union { void * s; u8 * u; } unk_30;   /* accessed as both */
    void * unk_34;
} S_8190AEB4_0;   /* arg0 in func_8190AEB4 */

typedef struct S_8190AEB4_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8190AEB4_1;   /* arg2 in func_8190AEB4 */

typedef struct S_8190AEB4_2 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_8190AEB4_2;   /* ((S_8190AEB4_0 *)arg0)->unk_34 in func_8190AEB4 */



typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} __attribute__((packed)) Rect;

typedef struct {
    s16 x;
    s16 y;
} Point;

extern Rect D_80024038;
extern Rect D_80024040;
extern s16 D_80025630;
extern s32 D_80025638[4];
extern u8 D_80025648[48];
extern u8 D_80025678[44];
extern s32 D_800814A0;

extern s32 func_80024590(s32);
extern void func_800248E8(void) __attribute__((noreturn));
extern void func_800248F4(void) __attribute__((noreturn));
extern void func_80024AAC(void) __attribute__((noreturn));
extern void func_800672D8(Rect *, s32 *);
extern void func_800B8FC8(void *, Rect *, Point *, s32, s32);

void func_8190AEB4(void *arg0, s32 *arg1, void *arg2)
{
    Rect rect;
    Rect drawRect;
    Point center;
    s32 *src;
    u8 *object;
    s16 timer;
    u16 newX;
    u16 newY;
    register s32 i ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    u8 *array;
    u8 *slot;
    u8 saved;
    s32 index;
    s32 state;
    u16 nextState;

    rect = D_80024038;
    drawRect = D_80024040;
    state = ((S_8190AEB4_0 *)arg0)->unk_00.s;
    D_80025630 = 1;

    switch (state) {
    case 0:
        center.x = rect.x + ((s16)rect.w >> 1);
        center.y = rect.y + 0x48;
        func_800B8FC8(((S_8190AEB4_0 *)arg0)->unk_30.s, &rect, &center, 1, 1);

        object = ((S_8190AEB4_0 *)arg0)->unk_30.u;
        src = *(s32 **)(object - 0x18);
        arg1[0] = src[0];
        arg1[1] = src[1];
        arg1[2] = src[2];

        ((S_8190AEB4_1 *)arg2)->unk_1C -= 0x20;
        ((S_8190AEB4_1 *)arg2)->unk_1E += 0x80;
        timer = ((S_8190AEB4_0 *)arg0)->unk_02.s + 1;
        ((S_8190AEB4_0 *)arg0)->unk_02.s = timer;
        if (timer < 0x28) {
            return;
        }
        nextState = ((S_8190AEB4_0 *)arg0)->unk_00.u;
        ((S_8190AEB4_0 *)arg0)->unk_02.s = 0;
        func_800248F4();

    case 1:
        ((S_8190AEB4_1 *)arg2)->unk_1C += 0x140;
        arg1[2] -= 0x140000;
        ((S_8190AEB4_1 *)arg2)->unk_1E -= 0x500;
        timer = ((S_8190AEB4_0 *)arg0)->unk_02.s + 1;
        ((S_8190AEB4_0 *)arg0)->unk_02.s = timer;
        if (timer < 4) {
            return;
        }
        nextState = ((S_8190AEB4_0 *)arg0)->unk_00.u;
        ((S_8190AEB4_0 *)arg0)->unk_02.s = 0;
        func_800248F4();

    case 2:
        arg1[2] -= 0x100000;
        newY = ((S_8190AEB4_1 *)arg2)->unk_1E - 0x200;
        newX = ((S_8190AEB4_1 *)arg2)->unk_1C + 0x200;
        ASM_KEEP(newY);   /* MATCH pin: retail keeps a computation the compiler would drop */
        ASM_TAILSLOT_PIN(newX);   /* MATCH pin: load-bearing for the whole function shape */
        func_800248E8();

    case 3:
        arg1[2] += 0x180000;
        newY = ((S_8190AEB4_1 *)arg2)->unk_1E + 0x300;
        newX = ((S_8190AEB4_1 *)arg2)->unk_1C - 0x300;
        ASM_KEEP(newY);   /* MATCH pin: retail keeps a computation the compiler would drop */
        ASM_TAILSLOT_PIN(newX);   /* MATCH pin: load-bearing for the whole function shape */
        func_800248E8();

    case 4:
        arg1[2] -= 0x80000;
        newY = ((S_8190AEB4_1 *)arg2)->unk_1E - 0x100;
        newX = ((S_8190AEB4_1 *)arg2)->unk_1C + 0x100;
        ((S_8190AEB4_1 *)arg2)->unk_1E = newY;
        ((S_8190AEB4_1 *)arg2)->unk_1C = newX;
        nextState = ((S_8190AEB4_0 *)arg0)->unk_00.u;
        nextState++;
        ((S_8190AEB4_0 *)arg0)->unk_00.p = nextState;
        func_80024AAC();

    case 5:
        {
            u8 *cursor;

            i = 0x2F;
            cursor = D_80025648;
            cursor += 0x2F;
            do {
                *cursor = i;
                i--;
                cursor--;
            } while (i >= 0);
        }
        {
            u8 *cursor;

            i = 0x2B;
            cursor = D_80025678;
            cursor += 0x2B;
            do {
                *cursor = i;
                i--;
                cursor--;
            } while (i >= 0);
        }

        for (i = 0; i < 0x30; i++) {
            array = D_80025648;
            slot = array + i;
            saved = *slot;
            index = func_80024590(0x30);
            *slot = array[index];
            array[index] = saved;
        }
        for (i = 0; i < 0x2C; i++) {
            array = D_80025678;
            slot = array + i;
            saved = *slot;
            index = func_80024590(0x2C);
            *slot = array[index];
            array[index] = saved;
        }

        D_80025638[0] = 0;
        D_80025638[1] = 0;
        D_80025638[2] = 0;
        D_80025638[3] = 0;
        ((S_8190AEB4_0 *)arg0)->unk_02.s = 0;
        ((S_8190AEB4_0 *)arg0)->unk_00.p++;
        /* fallthrough */

    case 6:
    {
        register Rect *drawPtr ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
        s32 *drawState;

        i = 0;
        do {
            drawRect.x = D_80025648[i] * 2 + 0x340;
            index = i + ((S_8190AEB4_0 *)arg0)->unk_02.u;
            drawPtr = &drawRect;
            if (index >= 0x2C) {
                index -= 0x2C;
            }
            drawState = D_80025638;
            ASM_KEEP(drawState);   /* MATCH pin: retail schedule: same instructions, different order without it */
            drawRect.y = D_80025678[index] * 2 + 0x100;
            i++;
            func_800672D8(drawPtr, drawState);
        } while (i < 0x30);

        timer = ((S_8190AEB4_0 *)arg0)->unk_02.s + 1;
        ((S_8190AEB4_0 *)arg0)->unk_02.s = timer;
        if (timer < 0x2C) {
            return;
        }
        ((S_8190AEB4_2 *)(((S_8190AEB4_0 *)arg0)->unk_34))->unk_90 = 1;
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
    }
}

/* MECHANISM: The sibling packed Rect/Point locals force the 0x48 frame and retail save order.
   Duplicated tails plus zero-arg noreturn helpers preserve the five external jumps and v0/v1 ABI.
   Split pinned cursors close both descending fills; held a0/a1 bases and do/while fill the final load slot. */
