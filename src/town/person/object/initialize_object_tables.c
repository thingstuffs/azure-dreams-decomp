#include "common.h"
#include "shared/object_index_slots.h"

extern void initialize_object_entries(void *state, s32 output, void *entries);
extern u8 person_table_handler_address[];
extern u8 D_800D54DC[];
extern u8 D_800D55E8[];
extern u8 D_800D55F0[];
extern u8 D_800D5618[];
extern u8 D_800D561C[];

/* Initialize the object tables and clear its indexed status byte. */
void initialize_object_tables(void *object, s32 unused, s32 init_value) {
    ((u8 *)object_index_slots)[(*(s32 *)((u8 *)object + 0x60)) * 8] = 0;
    *(void **)((u8 *)object + 0x58) = D_800D5618;
    *(void **)((u8 *)object + 0x5C) = D_800D561C;
    *(void **)((u8 *)object + 0x7C) = D_800D55E8;
    *(void **)((u8 *)object + 0x80) = D_800D55F0;
    initialize_object_entries(object, init_value, D_800D54DC);
    *(void **)((u8 *)object + 0x54) = person_table_handler_address;
}
