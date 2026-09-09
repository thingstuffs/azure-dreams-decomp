#include "common.h"

typedef struct S_8003E2D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} S_8003E2D8;

typedef struct S_800274F0_Nested {
    u8 pad[0x28];
    s32 unk28;
} S_800274F0_Nested;

typedef struct S_800274F0_Arg {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x10];
    void *unk28;
    u8 pad2C[0x0C];
    u8 unk38;
    u8 pad39[3];
    s32 unk3C;
    u8 *unk40;
    void *unk44;
    S_800274F0_Nested *unk48;
    u8 pad4C[0x3C];
    void *unk88;
} S_800274F0_Arg;

extern S_8003E2D8 D_80083160;
extern u8 D_80027E84[];

extern s16 SD_Call(s32, S_8003E2D8 *);
extern void func_800274A8(S_800274F0_Arg *);
extern void func_80027454(void *, s32, s32, void *);
extern void *func_8002553C(void *);
extern void func_800255AC(void *);
extern void func_800265B8(void *, void *);
extern s32 func_80026BFC(s32);
extern void func_80026D0C(void *);
extern void func_80026CD8(void *);

/* Handles menu actions and repeated grid navigation, updating the selection and page. */
void func_800274F0(S_800274F0_Arg *menu) {
    S_8003E2D8 *input;
    s32 held_buttons;
    s32 pressed_buttons;
    s32 index_step = 0;
    s32 repeat_ticks;
    s32 next_index;
    s32 selected_index;
    s32 item_count;
    s32 remaining_items;
    s32 repeat_buttons;

    input = &D_80083160;
    held_buttons = input->unk8;
    if (held_buttons == 0)
        goto done;
    pressed_buttons = input->unk10;
    if (pressed_buttons & 0x20) {
        SD_Call(0x515, input);
        func_800274A8(menu);
        goto done;
    }
    if (pressed_buttons & 0x10) {
        SD_Call(0x503, input);
        goto finish_effect;
    }
    if (pressed_buttons & 0x40) {
        SD_Call(0x503, input);
        func_80027454(&menu->unk38, menu->unk14,
                      (menu->unk8 / 72) * 72, menu->unk28);
        func_800265B8(func_8002553C(menu->unk44),
                      menu->unk40 + ((menu->unk8 % 72) * 2));
        if (menu->unk14 == 1 ||
            func_80026BFC(menu->unk48->unk28) != 0)
            goto finish_effect;
        goto done;
    }

    goto direction_entry;

finish_effect:
    func_800274A8(menu);
    func_800255AC(menu->unk44);
    goto done;

direction_entry:
    if (!(held_buttons & 0xF000))
        goto direction_common;
    if (pressed_buttons & 0xF000) {
        menu->unkC = 0;
        pressed_buttons = input->unk10;
        if (pressed_buttons & 0x8000) {
            index_step = -1;
            goto direction_common;
        }
        if (pressed_buttons & 0x2000) {
            index_step = 1;
            goto direction_common;
        }
        if (pressed_buttons & 0x1000) {
            index_step = -9;
            goto direction_common;
        }
        if (pressed_buttons & 0x4000)
            index_step = 9;
        goto direction_common;
    }

    repeat_ticks = menu->unkC;
    if (repeat_ticks < 9)
        goto increment_done;
    menu->unkC = repeat_ticks - 1;
    repeat_buttons = input->unk8;
    if (repeat_buttons & 0x8000) {
        index_step = -1;
        goto direction_common;
    }
    if (repeat_buttons & 0x2000) {
        index_step = 1;
        goto direction_common;
    }
    if (repeat_buttons & 0x1000) {
        index_step = -9;
        goto direction_common;
    }
    if (repeat_buttons & 0x4000)
        index_step = 9;
    goto direction_common;

increment_done:
    menu->unkC = repeat_ticks + 1;

direction_common:
    if (index_step == 0)
        goto done;
    SD_Call(0x502, input);
    selected_index = menu->unk8;
    item_count = menu->unk3C;
    next_index = selected_index + index_step;
    remaining_items = item_count - next_index;
    if (!(remaining_items > 0 && item_count >= remaining_items))
        goto done;
    menu->unk8 = next_index;
    if ((next_index - index_step) / 72 == next_index / 72) {
        func_80026D0C(menu->unk88);
        goto done;
    }
    func_80026CD8(menu->unk88);
    *(void **)((u8 *)menu - 0x10) = D_80027E84;
    menu->unk0 = menu->unk4;

done:
    return;
}
