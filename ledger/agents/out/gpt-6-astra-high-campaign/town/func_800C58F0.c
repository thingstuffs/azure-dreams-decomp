#include "common.h"

typedef struct {
    s32 active;
    void *object;
} ObjectSlot;

typedef struct {
    void *value;
} PointerField;

typedef struct {
    s32 value;
} WordField;

extern s32 D_800C3174;
extern s32 D_800C3438;
extern ObjectSlot D_80082660[];

/* Initializes object fields and registers the object in its slot. */
void func_800C3050(void *object, s32 slot_index, s32 field_58_value, s32 field_5c_value, s32 field_7c_value, s32 field_80_value)
{
    s32 registered_slot;

    ((PointerField *)((u8 *)object - 0x10))->value = &D_800C3174;
    ((PointerField *)((u8 *)object + 0x50))->value = &D_800C3438;
    ((WordField *)((u8 *)object + 0x60))->value = slot_index;
    ((WordField *)((u8 *)object + 0x58))->value = field_58_value;
    ((WordField *)((u8 *)object + 0x5C))->value = field_5c_value;
    ((WordField *)((u8 *)object + 0x7C))->value = field_7c_value;
    registered_slot = ((WordField *)((u8 *)object + 0x60))->value;
    ((WordField *)((u8 *)object + 0x80))->value = field_80_value;
    D_80082660[registered_slot].object = (u8 *)object - 0x20;
}
