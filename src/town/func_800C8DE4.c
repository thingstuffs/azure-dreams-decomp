#include "common.h"

extern void initialize_object_and_register_slot(void *object, s32 slot_index, void *field_58_value, void *field_5c_value,
                          void *field_7c_value, void *field_80_value);
extern void set_linked_data_pointers_variant_1(void *record, s32 first_value, s32 second_value);
extern void func_800C6C10(void *state_value);

extern u8 D_800D5958[];
extern u8 D_800D5960[];
extern u8 D_800D5988[];
extern u8 D_800D598C[];

/* Initialize object slot 9, set its data pointers, and create its display object. */
void initialize_object_slot_9_and_display(void *object, s32 unused_a, s32 unused_b) {
    initialize_object_and_register_slot(object, 9, D_800D5988, D_800D598C, D_800D5958,
                  D_800D5960);
    set_linked_data_pointers_variant_1(object, unused_a, unused_b);
    func_800C6C10(object);
}
