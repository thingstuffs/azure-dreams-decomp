#include "common.h"
#include "shared/game_work.h"

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

extern u8 D_8014E4BC[];
extern s32 D_80151DC4;
extern s32 D_80151DCC;
extern s32 D_80151DD4;
extern u8 D_80151E24[];
extern u8 D_80151E2C[];
extern u8 D_80151E34[];
extern u8 D_80151E54[];
extern u8 D_80151E5C[];
extern u8 D_80151E64[];

extern void func_80047784(Obj2 *, u8, s32);
extern s32 func_800AC82C(Obj0 *, void *, Obj2 *, Obj3 *);
extern s32 func_800AD9B4(Obj2 *, Obj3 *);

/* Selects direction-dependent table entries for kinds 13 through 15 around the object update. */
void func_801519A0(Obj0 *owner, void *context, Obj2 *render_arg, Obj3 *state_arg)
{
    Obj2 *render_obj = render_arg;
    Obj3 *state = state_arg;
    u32 selected_table;
    u32 current_table;
    u8 kind;
    s32 direction_index;

    kind = state->kind48;
    switch (kind) {
    case 13:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E54;
        } else {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E24;
        }
        break;

    case 14:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E5C;
        } else {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E2C;
        }
        break;

    case 15:
        if ((state->flags1c & 0x200) != 0 || state->flag25 == 0) {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E64;
        } else {
            current_table = (u32)render_obj->table2c;
            selected_table = (u32)D_80151E34;
        }
        break;

    default:
        goto update_object;
    }

apply_table:
    if (current_table != selected_table) {
        *(u32 *)((u8 *)render_obj + 0x2c) = selected_table;
        direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
        func_80047784(render_obj, *(u8 *)((direction_index & 7) + selected_table), 0);
    }

update_object:
    if (func_800AC82C(owner, context, render_obj, state) != 0) {
        if ((func_800AD9B4(render_obj, state) << 16) > 0) {
            owner->field8c = D_8014E4BC;
        }
        return;
    }

    switch (state->kind48) {
    case 13:
        if (render_obj->table2c != D_80151E54 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)render_obj + 0x2c) = (u32)&D_80151DC4;
        direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
        func_80047784(render_obj, *(u8 *)((direction_index & 7) + (u32)&D_80151DC4), 0);
        return;
    case 14:
        if (render_obj->table2c != D_80151E5C ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)render_obj + 0x2c) = (u32)&D_80151DCC;
        direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
        func_80047784(render_obj, *(u8 *)((direction_index & 7) + (u32)&D_80151DCC), 0);
        return;
    case 15:
        if (render_obj->table2c != D_80151E64 ||
            (state->flags1c & 0x208) != 0) {
            return;
        }
        *(u32 *)((u8 *)render_obj + 0x2c) = (u32)&D_80151DD4;
        direction_index = (gameWork.view.viewAngle + state->value2a + 0x100) >> 9;
        func_80047784(render_obj, *(u8 *)((direction_index & 7) + (u32)&D_80151DD4), 0);
        return;
    default:
        return;
    }

}
