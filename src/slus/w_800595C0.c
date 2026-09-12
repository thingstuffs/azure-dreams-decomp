#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 field_2C;
    u8 pad_30[0x4A - 0x30];
    u8 field_4A;
    u8 pad_4B;
    u8 field_4C;
} Entity;

typedef struct {
    s32 field_00;
    u8 pad_04[0x20 - 0x04];
    s32 field_20;
    s32 field_24;
    u8 pad_28[0x2C - 0x28];
    s32 field_2C;
    u8 pad_30[0x50 - 0x30];
} Slot;

extern Slot D_80085FA8[];
extern s32 D_800869B4[3];
extern void *jtbl_8003310C[];

extern s32 func_800589B8(Entity *);
extern void func_80057948(s32, s32, s32);
extern void func_80056E10(s32, s32, s32);
extern void func_80058494(s32, s32, s32);
extern void func_8005845C(u8, u8);
extern void func_8005914C(Entity *, s32, s32, s32);

/* Processes the next entity command and returns its control flag. */
s32 func_800595C0(Entity *entity)
{
    register Entity *ent ASM_REG("$17") = entity;   /* UNRESOLVED C shape (pin): removing it slus-diff; the source shape that makes it unnecessary has not been found */
    s32 command;
    s16 operand;
    s32 value;
    register s32 saved_command ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 command_index;
    static void *const case_labels[] = {
        &&L_case_46, &&L_case_47, &&L_case_48, &&L_case_49,
        &&L_case_4A, &&L_case_4B, &&L_case_7F, &&L_default
    };
    (void)case_labels;

    command = func_800589B8(ent);
    saved_command = command;
    if (!(command & 0x80)) {
        s32 next_byte = func_800589B8(ent);
        value = next_byte & 0x7F;
        if (value != 0) {
            operand = next_byte;
            func_80056E10(ent->field_4C, command & 0x7F, value);
        } else {
            operand = next_byte;
            func_80057948(ent->field_4C, command & 0x7F, 0);
        }
        ent->field_4A = saved_command;
        goto ret_bool;
    }

    command_index = (command & 0x7F) - 0x46;
    if ((u32)command_index >= 0x3A) {
        goto L_default;
    }
    goto *jtbl_8003310C[command_index];

L_case_46:
    func_80057948(ent->field_4C, ent->field_4A, 0);
    return 0;
L_case_47:
    func_80057948(ent->field_4C, ent->field_4A, 0);
    return 1;
L_case_48: {
    s32 next_byte = func_800589B8(ent);
    u32 slot_count;
    operand = next_byte;
    slot_count = D_800869B4[0];
    ASM_KEEP(slot_count);   /* UNRESOLVED C shape (pin): removing it slus-diff; the source shape that makes it unnecessary has not been found */
    if (slot_count != 0) {
        u32 slot_index = 0;
        s32 slot_value = ((next_byte & 0x7F) << 1) + 2;
        do {
            D_80085FA8[slot_index].field_24 = slot_value;
            slot_index++;
        } while (slot_index < slot_count);
    }
    goto ret_bool;
}
L_case_49: {
    s32 next_byte = func_800589B8(ent);
    operand = next_byte;
    func_80058494(ent->field_4C, 0, next_byte & 0x7F);
    goto ret_bool;
}
L_case_4A: {
    s32 next_byte = func_800589B8(ent);
    operand = next_byte;
    func_8005845C(ent->field_4C, next_byte & 0x7F);
    goto ret_bool;
}
L_case_4B: {
    s32 next_byte = func_800589B8(ent);
    operand = next_byte;
    ent->field_4C = next_byte & 0xF;
    goto ret_bool;
}
L_case_7F:
    operand = func_800589B8(ent);
    ent->field_2C = 1;
    goto ret_bool;
L_default: {
    s32 next_byte = func_800589B8(ent);
    operand = next_byte;
    func_8005914C(ent, (ent->field_4C + 0xB0) & 0xFF,
                  saved_command & 0x7F, next_byte & 0x7F);
}

ret_bool:
    return 0 < (operand & 0x80);
}
