#include "common.h"

typedef struct {
    u8 pad0[8];
    u32 field_8;
    u8 padC[4];
    u32 field_10;
} GlobalState;

typedef struct {
    void *field_0;
    s16 field_4;
    s16 field_6;
    u8 pad8[2];
    u8 field_A;
    u8 field_B;
    u8 padC[3];
    u8 field_F;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 pad14;
    u8 field_15;
    u8 field_16;
    u8 field_17[2];
    u8 pad19[0x43];
} Object;

extern GlobalState D_80083160;
extern u8 D_80082E6B;
extern int D_800814A0;
extern s8 D_80080A84;
extern s8 D_80129728;

extern u8 func_80123200(u8);
extern void func_80053DA8(s32);
extern void func_801237A4(Object *);
extern void func_80044144(s32, s32, s32, s32);
extern void func_8004B248(void *);
extern void func_801231DC(void);

/* Handles input to update object selections, action states, and exit behavior. */
void func_801249A0(Object *object)
{
    GlobalState *input_state = &D_80083160;
    u32 input_flags;
    register u32 side_value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 active_value;
    u8 alternate_value;
    u8 target_value;
    s32 entry_index;
    s32 **reset_entries;

    input_flags = input_state->field_10;
    if (input_flags & 0x40) {
        s32 slot_index;
        register Object *slot_object ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */

        if (!func_80123200(object->field_13)) {
            goto end;
        }
        func_80053DA8(0x702);
        slot_index = object->field_16;
        target_value = object->field_13;
        active_value = *((u8 *)object + slot_index + 0x17);
        if (active_value == target_value) {
            goto matched_six;
        }
        slot_index ^= 1;
        alternate_value = *((u8 *)object + slot_index + 0x17);
        if (alternate_value != target_value) {
            goto check_five;
        }
        slot_object = object;
        object->field_16 = slot_index;
        func_801237A4(slot_object);
matched_six:
        object->field_A = 6;
        object->field_4 = 1;
        object->field_6 = 0x19;
        goto end;
check_five:
        if (active_value == 0xFF) {
            goto matched_five;
        }
        if (alternate_value == 0xFF) {
            slot_object = object;
            object->field_16 = slot_index;
            func_801237A4(slot_object);
        }
matched_five:
        object->field_A = 5;
        object->field_B = 0;
        goto end;
    }

    if (input_flags & 0x20) {
        func_80053DA8(0x700);
        if (D_80082E6B == 0x17) {
            func_80044144(0, 0, 0, 0);
            reset_entries = (s32 **)&D_80129728;
            for (entry_index = 0; entry_index < 98; entry_index++) {
                *reset_entries[entry_index] = 0;
            }
            *(u16 *)((u8 *)object->field_0 + 0x1E) |= 0x2000;
            func_8004B248((u8 *)object + 0x5C);
            *(u16 *)((u8 *)object - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
            func_801231DC();
            D_80080A84 = 2;
            goto end;
        }
    }

    input_flags = input_state->field_10;
    if (input_flags & 0x8000) {
        u8 selection_group;

        if (object->field_10 == 0) {
            (*(volatile u8 *)&object->field_F) += 3;
            (*(volatile u8 *)&object->field_F) &= 3;
        }
        selection_group = object->field_F;
        object->field_10 ^= 1;
        if ((selection_group == 3) && (object->field_15 != 0)) {
            object->field_F = 2;
        }
        object->field_A = 0;
        goto end;
    }
    if (input_flags & 0x2000) {
        u8 selection_group;

        if (object->field_10 != 0) {
            (*(volatile u8 *)&object->field_F) += 1;
            (*(volatile u8 *)&object->field_F) &= 3;
        }
        selection_group = object->field_F;
        object->field_10 ^= 1;
        if ((selection_group == 3) && (object->field_15 != 0)) {
            object->field_F = 0;
        }
        object->field_A = 0;
        goto end;
    }

    input_flags = input_state->field_8;
    if (input_flags & 0x1000) {
        if (object->field_F == 3) {
            goto reset_four;
        }
        {
            u32 selection_value;
            s32 previous_selection;

            selection_value = 1;
            (*(volatile s16 *)&object->field_4) = selection_value;
            selection_value = object->field_11;
            previous_selection = selection_value;
            ASM_KEEP(previous_selection);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            *(volatile u8 *)&object->field_11 = selection_value + 7;
            object->field_6 = 4;
            (*(volatile u8 *)&object->field_11) &= 7;
            object->field_12 = previous_selection;
        }
        if ((*(volatile u8 *)&object->field_11) != 7) {
            goto set_two;
        }
        side_value = object->field_10;
        object->field_A = 3;
        goto toggle;
    }
    if (!(input_flags & 0x4000)) {
        goto end;
    }
    {
        u32 selection_value;
        s32 previous_selection;
        register s32 start_step ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */

        start_step = 1;
        if (object->field_F == 3) {
            goto reset_four;
        }
        selection_value = object->field_11;
        previous_selection = selection_value;
        ASM_KEEP(previous_selection);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        *(volatile u8 *)&object->field_11 = selection_value + 1;
        object->field_4 = start_step;
        (*(volatile u8 *)&object->field_11) &= 7;
        object->field_12 = previous_selection;
    }
    object->field_6 = 4;
    if ((*(volatile u8 *)&object->field_11) != 0) {
        goto set_two;
    }
    side_value = object->field_10;
    ASM_KEEP(side_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    object->field_A = 3;
    goto toggle;

set_two:
    object->field_A = 2;
    goto end;
reset_four:
    side_value = 1;
    object->field_4 = side_value;
    side_value = object->field_10;
    object->field_6 = 4;
    object->field_A = 4;
toggle:
    object->field_10 = side_value ^ 1;
end:
    return;
}
