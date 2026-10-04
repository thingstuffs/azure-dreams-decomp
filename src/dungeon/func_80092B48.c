#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
} Item;

typedef struct {
    u8 pad0[0x1C];
    s32 flags;
    u8 pad20[0x2C];
    Item *field4C;
    u8 pad50[0x34];
    u8 b84;
    u8 b85;
} Arg0;

extern u8 D_800E07C0[];
extern u8 D_800E07D3[];
extern s32 *D_800E3D18[];
extern Item *func_80097F84(Item *, u8 *, u8 *, s32);
/* Retail sets a3 to 10 at 0x80099114 before reading it; no incoming argument. */
extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099368(Item *, s32);
extern s32 func_80099734(Arg0 *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800483AC(s32);
extern void func_80048568(s32);
extern void func_80048590(s32);
extern u8 D_80088B64[];
extern u8 D_800DD2B4[];
extern u8 D_800DD2C4[];
extern u8 D_800DD2D4[];
extern u8 D_800DD2E0[];
extern u8 D_800E080A[];
extern u8 D_800E081C[];
extern u8 D_800E0844[];
extern u8 D_800E0853[];
extern u8 D_800E0862[];
extern u8 D_800E3CF8[];
extern u8 D_800E3D80[];
extern u8 D_800DD2C4_index[] __asm__("D_800DD2C4");
extern u8 D_800DD2B4_index[] __asm__("D_800DD2B4");

void func_800982A8(Arg0 *context, Item *item) {
    s32 value;
    register s32 result_value;
    s32 item_index;
    s16 tail_index;
    s16 state;
    s32 item_b3;
    Item *current_item;
    Item *selected_item;
    u8 *head_c;
    u8 *head_b;
    u8 head_b_value;

    selected_item = item;
    result_value = 0;
    state = 0;
    if (selected_item != NULL) {
        if (selected_item->b1 == 0xF && selected_item->b0 >= 0xD) {
            func_800A56E0(0x506);
            result_value = func_800990FC();
            item_b3 = func_80099368(selected_item, func_80099194(D_800E080A, func_80099734(context, func_8009929C(8, result_value))));
            func_80099290(func_80099194(D_80088B64, item_b3));
            func_800A5720(result_value);
            return;
        }
        selected_item = func_80097F84(selected_item, D_800E07C0, D_800E07D3, 0);
        if (selected_item == NULL) {
            return;
        }
    }

    current_item = context->field4C;
    if (current_item != NULL) {
        value = current_item->b3;
        if (value & 0x40) {
            func_800A56E0(0x70A);
            result_value = func_800990FC();
            item_b3 = func_80099368(current_item, func_8009929C(8, result_value));
            func_80099290(func_80099194(D_800E081C, item_b3));
            func_800A5720(result_value);
            return;
        }
        current_item->b3 = value & 0xDF;
        D_800E3D18[0] = (s32 *)D_800E3CF8;
        if (current_item == selected_item) {
            selected_item = NULL;
        }
        state = 1;
    }

    if (selected_item != NULL) {
        item_b3 = selected_item->b3;
        item_index = selected_item->b0;
        selected_item->b3 = item_b3 & 0x7F;
        result_value = func_800990FC();
        func_80099290(func_80099194(D_800E0844, func_80099368(selected_item, func_8009929C(8, result_value))));
        func_800A5720(result_value);
        D_800E3D18[0] = (s32 *)D_800E3D80;
        tail_index = 0x70A;
        if (selected_item->b3 & 0x40) {
            context->flags |= 0x800;
            func_800A56E0(tail_index);
            result_value = func_800990FC();
            func_80099290(func_80099194(D_800E0853, func_80099368(selected_item, result_value)));
            func_800A5720(result_value);
        }
        selected_item->b3 |= 0x20;
    } else {
        if (state != 0) {
            result_value = func_800990FC();
            value = func_8009929C(8, result_value);
            value = func_80099368(context->field4C, value);
            value = func_80099194(D_800E0862, value);
            func_80099290(value);
            func_800A5720(result_value);
        }
        head_c = D_800DD2C4;
        context->b84 = head_c[0];
        head_b = D_800DD2B4;
        head_b_value = head_b[0];
        item_index = 0;
        context->b85 = head_b_value;
    }
    context->field4C = selected_item;
    func_800A56E0(0x508);
    tail_index = item_index;
    if (selected_item->b1 == 0x10) {
        context->b84 = D_800DD2E0[tail_index];
        context->b85 = D_800DD2D4[tail_index];
        if (tail_index == 0) {
            func_800483AC(1);
            return;
        }
        func_80048590(tail_index);
    } else {
        context->b84 = D_800DD2C4_index[tail_index];
        context->b85 = D_800DD2B4_index[tail_index];
        if (tail_index == 0) {
            func_800483AC(1);
            return;
        }
        func_80048568(tail_index);
    }
    if (item_index == 0) {
        func_800483AC(1);
    }
}
