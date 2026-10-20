#include "common.h"

extern void set_record_base_and_data_pointer_alt();
extern void initialize_entity_display_parts();
struct Rec_func_800B3FB8_arg0; void initialize_object_data_blocks_and_entries(struct Rec_func_800B3FB8_arg0 *);
void initialize_entity_display_owner(u8 *owner) {
    set_record_base_and_data_pointer_alt(owner);
    initialize_entity_display_parts(owner + 0x4C, owner + 0x24, owner + 0x34);
    initialize_object_data_blocks_and_entries((struct Rec_func_800B3FB8_arg0 *)(owner));
}
