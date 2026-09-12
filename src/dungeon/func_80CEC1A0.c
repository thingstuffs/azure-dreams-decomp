#include "common.h"

typedef struct {
    u8 pad00[0x8c];
    void *field8c;
} Obj0;

typedef struct {
    u8 pad00[0x2c];
    u8 *table2c;
} Obj2;

typedef struct {
    u8 pad00[0x1c];
    u32 flags1c;
    u8 pad20[5];
    u8 flag25;
    u8 pad26[4];
    s16 value2a;
    u8 pad2c[0x1c];
    u8 kind48;
} Obj3;

extern s16 D_80083228;
extern u8 D_801724BC[];
extern s32 D_80175DC4;
extern s32 D_80175DCC;
extern s32 D_80175DD4;
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];

extern void func_80047784(Obj2 *, u8, s32);
extern s32 func_800AC82C(Obj0 *, void *, Obj2 *, Obj3 *);
extern s32 func_800AD9B4(Obj2 *, Obj3 *);

/* Updates the display table and directional entry for kinds 13 through 15. */
void func_801759A0(Obj0 *actor, void *context, Obj2 *display_arg, Obj3 *state_arg)
{
    Obj2 *display = display_arg;
    Obj3 *state = state_arg;
    u32 selected_table;
    u32 current_table;
    u8 kind;
    s32 direction_index;

    kind = state->kind48;
    switch (kind) {
    case 13:
        if ((state->flags1c & 0x200) != 0) {
            goto kind13_default;
        }
        if (state->flag25 != 0) {
            goto kind13_alternate;
        }
kind13_default:
        current_table = (u32)display->table2c;
        selected_table = (u32)D_80175E54;
        goto apply_table;
kind13_alternate:
        current_table = (u32)display->table2c;
        selected_table = (u32)D_80175E24;
        goto apply_table;

    case 14:
        if ((state->flags1c & 0x200) != 0) {
            goto kind14_default;
        }
        if (state->flag25 != 0) {
            goto kind14_alternate;
        }
kind14_default:
        current_table = (u32)display->table2c;
        selected_table = (u32)D_80175E5C;
        goto apply_table;
kind14_alternate:
        current_table = (u32)display->table2c;
        selected_table = (u32)D_80175E2C;
        goto apply_table;

    case 15:
        if ((state->flags1c & 0x200) != 0) {
            goto kind15_default;
        }
        if (state->flag25 != 0) {
            goto kind15_alternate;
        }
kind15_default:
        current_table = (u32)display->table2c;
        selected_table = (u32)D_80175E64;
        goto apply_table;
kind15_alternate:
        current_table = (u32)display->table2c;
        selected_table = (u32)D_80175E34;
        goto apply_table;

    default:
        goto update_state;
    }

apply_table:
    if (current_table != selected_table) {
        *(u32 * volatile)((u8 *)display + 0x2c) = selected_table;
        direction_index = (D_80083228 + state->value2a + 0x100) >> 9;
        func_80047784(display, *(u8 *)((direction_index & 7) + selected_table), 0);
    }

update_state:
    if (func_800AC82C(actor, context, display, state) != 0) {
        if ((func_800AD9B4(display, state) << 16) > 0) {
            actor->field8c = D_801724BC;
        }
        return;
    }

    switch (state->kind48) {
    case 13:
        if (display->table2c != D_80175E54 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 * volatile)((u8 *)display + 0x2c) = (u32)&D_80175DC4;
        direction_index = (D_80083228 + state->value2a + 0x100) >> 9;
        func_80047784(display, *(u8 *)((direction_index & 7) + (u32)&D_80175DC4), 0);
        return;
    case 14:
        if (display->table2c != D_80175E5C ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 * volatile)((u8 *)display + 0x2c) = (u32)&D_80175DCC;
        direction_index = (D_80083228 + state->value2a + 0x100) >> 9;
        func_80047784(display, *(u8 *)((direction_index & 7) + (u32)&D_80175DCC), 0);
        return;
    case 15:
        if (display->table2c != D_80175E64 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 * volatile)((u8 *)display + 0x2c) = (u32)&D_80175DD4;
        direction_index = (D_80083228 + state->value2a + 0x100) >> 9;
        func_80047784(display, *(u8 *)((direction_index & 7) + (u32)&D_80175DD4), 0);
        return;
    default:
        return;
    }

}
