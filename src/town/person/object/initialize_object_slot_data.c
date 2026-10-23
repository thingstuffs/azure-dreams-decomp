#include "common.h"

extern void initialize_object_and_register_slot(void *object, s32 slot_index, void *field_58_value, void *field_5c_value,
                          void *field_7c_value, void *field_80_value);
extern void set_object_referenced_data_pointers(void *object, s32 setup_arg1, s32 setup_arg2);

extern u8 D_800D5958[];
extern u8 D_800D5960[];
extern u8 D_800D5988[];
extern u8 D_800D598C[];

/* Initialize object slot 9 and set its data pointers. */
void initialize_object_slot_9_data(void *object, s32 unused_1, s32 unused_2) {
    initialize_object_and_register_slot(object, 9, D_800D5988, D_800D598C, D_800D5958,
                  D_800D5960);
    set_object_referenced_data_pointers(object, unused_1, unused_2);
}
