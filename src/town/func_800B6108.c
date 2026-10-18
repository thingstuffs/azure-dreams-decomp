#include "common.h"

extern void set_record_base_and_data_pointer();
extern void initialize_display_instances();
extern void initialize_four_slot_object_variant();
void func_800B3868(u8 *owner) {
    set_record_base_and_data_pointer(owner);
    initialize_display_instances(owner + 0x98, owner + 0x70, owner + 0x80);
    initialize_four_slot_object_variant(owner);
}
