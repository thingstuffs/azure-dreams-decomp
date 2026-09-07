#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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
    register u16 newX ASM_REG("$3");
    register u16 newY ASM_REG("$2");
    register s32 i ASM_REG("$17");
    u8 *array;
    u8 *slot;
    u8 saved;
    s32 index;
    s32 state;
    u16 nextState;

    rect = D_80024038;
    drawRect = D_80024040;
    state = FIELD(arg0, s16, 0);
    D_80025630 = 1;

    switch (state) {
    case 0:
        center.x = rect.x + ((s16)rect.w >> 1);
        center.y = rect.y + 0x48;
        func_800B8FC8(FIELD(arg0, void *, 0x30), &rect, &center, 1, 1);

        object = FIELD(arg0, u8 *, 0x30);
        src = *(s32 **)(object - 0x18);
        arg1[0] = src[0];
        arg1[1] = src[1];
        arg1[2] = src[2];

        FIELD(arg2, u16, 0x1C) -= 0x20;
        FIELD(arg2, u16, 0x1E) += 0x80;
        timer = FIELD(arg0, u16, 2) + 1;
        FIELD(arg0, u16, 2) = timer;
        if (timer < 0x28) {
            return;
        }
        nextState = FIELD(arg0, volatile u16, 0);
        ASM_KEEP(nextState);
        FIELD(arg0, u16, 2) = 0;
        func_800248F4();

    case 1:
        FIELD(arg2, u16, 0x1C) += 0x140;
        arg1[2] -= 0x140000;
        FIELD(arg2, u16, 0x1E) -= 0x500;
        timer = FIELD(arg0, u16, 2) + 1;
        FIELD(arg0, u16, 2) = timer;
        if (timer < 4) {
            return;
        }
        nextState = FIELD(arg0, volatile u16, 0);
        ASM_KEEP(nextState);
        FIELD(arg0, u16, 2) = 0;
        func_800248F4();

    case 2:
        arg1[2] -= 0x100000;
        newY = FIELD(arg2, u16, 0x1E) - 0x200;
        newX = FIELD(arg2, u16, 0x1C) + 0x200;
        ASM_KEEP(newY);
        ASM_TAILSLOT_PIN(newX);
        func_800248E8();

    case 3:
        arg1[2] += 0x180000;
        newY = FIELD(arg2, u16, 0x1E) + 0x300;
        newX = FIELD(arg2, u16, 0x1C) - 0x300;
        ASM_KEEP(newY);
        ASM_TAILSLOT_PIN(newX);
        func_800248E8();

    case 4:
        arg1[2] -= 0x80000;
        newY = FIELD(arg2, u16, 0x1E) - 0x100;
        newX = FIELD(arg2, u16, 0x1C) + 0x100;
        FIELD(arg2, u16, 0x1E) = newY;
        FIELD(arg2, u16, 0x1C) = newX;
        nextState = FIELD(arg0, volatile u16, 0);
        nextState++;
        ASM_KEEP(nextState);
        FIELD(arg0, u16, 0) = nextState;
        func_80024AAC();

    case 5:
        {
            register u8 *cursor ASM_REG("$2");

            i = 0x2F;
            ASM_KEEP(i);
            cursor = D_80025648;
            ASM_KEEP(cursor);
            cursor += 0x2F;
            do {
                *cursor = i;
                i--;
                cursor--;
            } while (i >= 0);
        }
        {
            register u8 *cursor ASM_REG("$2");

            i = 0x2B;
            cursor = D_80025678;
            ASM_KEEP(cursor);
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
        FIELD(arg0, u16, 2) = 0;
        FIELD(arg0, u16, 0)++;
        /* fallthrough */

    case 6:
    {
        register Rect *drawPtr ASM_REG("$4");
        register s32 *drawState ASM_REG("$5");

        i = 0;
        do {
            drawRect.x = D_80025648[i] * 2 + 0x340;
            index = i + FIELD(arg0, s16, 2);
            drawPtr = &drawRect;
            if (index >= 0x2C) {
                index -= 0x2C;
            }
            drawState = D_80025638;
            ASM_KEEP(drawState);
            drawRect.y = D_80025678[index] * 2 + 0x100;
            i++;
            func_800672D8(drawPtr, drawState);
        } while (i < 0x30);

        timer = FIELD(arg0, u16, 2) + 1;
        FIELD(arg0, u16, 2) = timer;
        if (timer < 0x2C) {
            return;
        }
        FIELD(FIELD(arg0, void *, 0x34), s16, 0x90) = 1;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
    }
}

/* MECHANISM: The sibling packed Rect/Point locals force the 0x48 frame and retail save order.
   Duplicated tails plus zero-arg noreturn helpers preserve the five external jumps and v0/v1 ABI.
   Split pinned cursors close both descending fills; held a0/a1 bases and do/while fill the final load slot. */
