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

/* Advances the object animation and draws rectangles in randomized order. */
void func_8190AEB4(void *effect, s32 *position, void *transform)
{
    Rect rect;
    Rect draw_rect;
    Point center;
    s32 *source_position;
    u8 *model;
    s16 timer;
    u16 next_x;
    u16 next_y;
    register s32 entry ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *shuffle_order;
    u8 *slot;
    u8 saved_entry;
    s32 order_index;
    s32 state;
    u16 next_state;

    rect = D_80024038;
    draw_rect = D_80024040;
    state = ((S_8190AEB4_0 *)effect)->unk_00.s;
    D_80025630 = 1;

    switch (state) {
    case 0:
        center.x = rect.x + ((s16)rect.w >> 1);
        center.y = rect.y + 0x48;
        func_800B8FC8(((S_8190AEB4_0 *)effect)->unk_30.s, &rect, &center, 1, 1);

        model = ((S_8190AEB4_0 *)effect)->unk_30.u;
        source_position = *(s32 **)(model - 0x18);
        position[0] = source_position[0];
        position[1] = source_position[1];
        position[2] = source_position[2];

        ((S_8190AEB4_1 *)transform)->unk_1C -= 0x20;
        ((S_8190AEB4_1 *)transform)->unk_1E += 0x80;
        timer = ((S_8190AEB4_0 *)effect)->unk_02.s + 1;
        ((S_8190AEB4_0 *)effect)->unk_02.s = timer;
        if (timer < 0x28) {
            return;
        }
        next_state = ((S_8190AEB4_0 *)effect)->unk_00.u;
        ((S_8190AEB4_0 *)effect)->unk_02.s = 0;
        func_800248F4();

    case 1:
        ((S_8190AEB4_1 *)transform)->unk_1C += 0x140;
        position[2] -= 0x140000;
        ((S_8190AEB4_1 *)transform)->unk_1E -= 0x500;
        timer = ((S_8190AEB4_0 *)effect)->unk_02.s + 1;
        ((S_8190AEB4_0 *)effect)->unk_02.s = timer;
        if (timer < 4) {
            return;
        }
        next_state = ((S_8190AEB4_0 *)effect)->unk_00.u;
        ((S_8190AEB4_0 *)effect)->unk_02.s = 0;
        func_800248F4();

    case 2:
        position[2] -= 0x100000;
        next_y = ((S_8190AEB4_1 *)transform)->unk_1E - 0x200;
        next_x = ((S_8190AEB4_1 *)transform)->unk_1C + 0x200;
        ASM_KEEP(next_y);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(next_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_800248E8();

    case 3:
        position[2] += 0x180000;
        next_y = ((S_8190AEB4_1 *)transform)->unk_1E + 0x300;
        next_x = ((S_8190AEB4_1 *)transform)->unk_1C - 0x300;
        ASM_KEEP(next_y);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(next_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_800248E8();

    case 4:
        position[2] -= 0x80000;
        next_y = ((S_8190AEB4_1 *)transform)->unk_1E - 0x100;
        next_x = ((S_8190AEB4_1 *)transform)->unk_1C + 0x100;
        ((S_8190AEB4_1 *)transform)->unk_1E = next_y;
        ((S_8190AEB4_1 *)transform)->unk_1C = next_x;
        next_state = ((S_8190AEB4_0 *)effect)->unk_00.u;
        next_state++;
        ((S_8190AEB4_0 *)effect)->unk_00.p = next_state;
        func_80024AAC();

    case 5:
        {
            u8 *cursor;

            entry = 0x2F;
            cursor = D_80025648;
            cursor += 0x2F;
            do {
                *cursor = entry;
                entry--;
                cursor--;
            } while (entry >= 0);
        }
        {
            u8 *cursor;

            entry = 0x2B;
            cursor = D_80025678;
            cursor += 0x2B;
            do {
                *cursor = entry;
                entry--;
                cursor--;
            } while (entry >= 0);
        }

        for (entry = 0; entry < 0x30; entry++) {
            shuffle_order = D_80025648;
            slot = shuffle_order + entry;
            saved_entry = *slot;
            order_index = func_80024590(0x30);
            *slot = shuffle_order[order_index];
            shuffle_order[order_index] = saved_entry;
        }
        for (entry = 0; entry < 0x2C; entry++) {
            shuffle_order = D_80025678;
            slot = shuffle_order + entry;
            saved_entry = *slot;
            order_index = func_80024590(0x2C);
            *slot = shuffle_order[order_index];
            shuffle_order[order_index] = saved_entry;
        }

        D_80025638[0] = 0;
        D_80025638[1] = 0;
        D_80025638[2] = 0;
        D_80025638[3] = 0;
        ((S_8190AEB4_0 *)effect)->unk_02.s = 0;
        ((S_8190AEB4_0 *)effect)->unk_00.p++;
        /* fallthrough */

    case 6:
    {
        register Rect *draw_rect_ptr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 *draw_data;

        entry = 0;
        do {
            draw_rect.x = D_80025648[entry] * 2 + 0x340;
            order_index = entry + ((S_8190AEB4_0 *)effect)->unk_02.u;
            draw_rect_ptr = &draw_rect;
            if (order_index >= 0x2C) {
                order_index -= 0x2C;
            }
            draw_data = D_80025638;
            ASM_KEEP(draw_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            draw_rect.y = D_80025678[order_index] * 2 + 0x100;
            entry++;
            func_800672D8(draw_rect_ptr, draw_data);
        } while (entry < 0x30);

        timer = ((S_8190AEB4_0 *)effect)->unk_02.s + 1;
        ((S_8190AEB4_0 *)effect)->unk_02.s = timer;
        if (timer < 0x2C) {
            return;
        }
        ((S_8190AEB4_2 *)(((S_8190AEB4_0 *)effect)->unk_34))->unk_90 = 1;
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
    }
}

/* MECHANISM: The sibling packed Rect/Point locals force the 0x48 frame and retail save order.
   Duplicated tails plus zero-arg noreturn helpers preserve the five external jumps and v0/v1 ABI.
   Split pinned cursors close both descending fills; held a0/a1 bases and do/while fill the final load slot. */
