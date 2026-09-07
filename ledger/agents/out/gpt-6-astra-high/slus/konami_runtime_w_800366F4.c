#include "common.h"

#include "common.h"

typedef struct Child {
    u8 unk00[0x26];
    u8 unk26;
    u8 unk27;
} Child;

typedef struct Object Object;

struct Object {
    u8 unk00[0x4D];
    u8 unk4D;
    u8 unk4E[0x26];
    Child *child;
};

extern u8 D_80083160[];
extern void func_80036880(Object *arg0, void *arg1, void *arg2);
extern void func_80053DA8(s32 arg0);

/* Move the two-column menu cursor and handle confirmation input. */
void func_800366F4(Object *menu, void *confirm_arg1, void *confirm_arg2) {
    s32 next_cursor;
    s32 prev_cursor;
    s32 cursor;
    s32 item_count;
    u32 buttons;
    u8 *input_state;

    input_state = D_80083160;
    cursor = menu->unk4D;
    buttons = *(u32 *)(input_state + 0x10);
    if (buttons & 0x2000) {
        goto switch_column;
    }
    if (!(buttons & 0x8000)) {
        goto after_switch_column;
    }
switch_column:
    next_cursor = cursor + 1;
    if (cursor & 1) {
        cursor -= 1;
    } else if (next_cursor < menu->child->unk26) {
        cursor = next_cursor;
    }
    buttons = *(u32 *)(input_state + 0x10);
after_switch_column:

    if (buttons & 0x4000) {
        next_cursor = cursor + 2;
        if (next_cursor < menu->child->unk26) {
            cursor = next_cursor;
        } else {
            cursor %= 2;
        }
    } else {
        if (buttons & 0x1000) {
            prev_cursor = cursor - 2;
            if (prev_cursor >= 0) {
                cursor = prev_cursor;
            } else {
                item_count = menu->child->unk26;
                if (!(item_count & 1)) {
                    cursor = (cursor % 2) + item_count - 2;
                } else if (cursor & 1) {
                    cursor = item_count - 2;
                } else {
                    cursor = item_count - 1;
                }
            }
        }
    }

    if (menu->unk4D != cursor) {
        func_80053DA8(0x502);
        menu->unk4D = cursor;
    }
    if (*(u32 *)(input_state + 0x10) & 0x40) {
        func_80036880(menu, confirm_arg1, confirm_arg2);
    }
}
