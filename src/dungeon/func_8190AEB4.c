#include "common.h"

typedef struct S_8190AEB4_0 {
    union { s16 s; volatile u16 u; u16 p; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2C];
    union { void * s; u8 * u; } unk_30;   /* accessed as both */
    void * unk_34;
} S_8190AEB4_0;   /* arg0 in func_800246B4 */

typedef struct S_8190AEB4_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_8190AEB4_1;   /* arg2 in func_800246B4 */

typedef struct S_8190AEB4_2 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_8190AEB4_2;   /* ((S_8190AEB4_0 *)arg0)->unk_34 in func_800246B4 */



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
extern void func_800672D8(Rect *, s32 *);
extern void func_800B8FC8(void *, Rect *, Point *, s32, s32);

/* Advances the object animation and draws rectangles in randomized order. */
void func_800246B4(void *effect, s32 *position, void *transform)
{
    Rect rect;
    Rect draw_rect;
    Point center;
    s32 *source_position;
    u8 *model;
    s16 timer;
    u16 next_x;
    u16 next_y;
    s32 entry;
    u8 *shuffle_order;
    u8 *slot;
    u8 *slot_2;
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
        next_state++;
        ((S_8190AEB4_0 *)effect)->unk_00.p = next_state;
        return;

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
        next_state++;
        ((S_8190AEB4_0 *)effect)->unk_00.p = next_state;
        return;

    case 2:
        position[2] -= 0x100000;
        next_y = ((S_8190AEB4_1 *)transform)->unk_1E - 0x200;
        next_x = ((S_8190AEB4_1 *)transform)->unk_1C + 0x200;
        goto store_xy;

    case 3:
        position[2] += 0x180000;
        next_y = ((S_8190AEB4_1 *)transform)->unk_1E + 0x300;
        next_x = ((S_8190AEB4_1 *)transform)->unk_1C - 0x300;
        goto store_xy;

    case 4:
        position[2] -= 0x80000;
        next_y = ((S_8190AEB4_1 *)transform)->unk_1E - 0x100;
        next_x = ((S_8190AEB4_1 *)transform)->unk_1C + 0x100;
store_xy:
        ((S_8190AEB4_1 *)transform)->unk_1E = next_y;
        ((S_8190AEB4_1 *)transform)->unk_1C = next_x;
        next_state = ((S_8190AEB4_0 *)effect)->unk_00.u;
        next_state++;
        ((S_8190AEB4_0 *)effect)->unk_00.p = next_state;
        return;

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
            slot_2 = shuffle_order + entry;
            saved_entry = *slot_2;
            order_index = func_80024590(0x30);
            *slot_2 = shuffle_order[order_index];
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
        s32 *draw_data;

        entry = 0;
        do {
            draw_rect.x = D_80025648[entry] * 2 + 0x340;
            order_index = entry + ((S_8190AEB4_0 *)effect)->unk_02.u;
            if (order_index >= 0x2C) {
                order_index -= 0x2C;
            }
            draw_data = D_80025638;
            draw_rect.y = D_80025678[order_index] * 2 + 0x100;
            func_800672D8(&draw_rect, draw_data);
            entry++;
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
