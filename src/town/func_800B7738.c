#include "common.h"

extern void set_record_value_and_data_pointer();
extern void func_800B4CBC();
extern void initialize_four_slot_object();
void initialize_four_slot_object_owner(u8 *owner) {
    set_record_value_and_data_pointer(owner);
    func_800B4CBC(owner + 0x4C, owner + 0x24, owner + 0x34);
    initialize_four_slot_object(owner);
}
