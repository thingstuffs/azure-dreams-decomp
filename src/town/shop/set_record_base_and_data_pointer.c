#include "common.h"
#include "town/shop.h"
#include "shared/object_node.h"

/* Set the record's base and offset values and its data pointer. */
void set_record_base_and_data_pointer(ShopRecordResetObject *record_field, s32 base_value) {
    ShopRecordResetObject *object = record_field;

    object->owner_node = (ObjectNodeHeader *)base_value;
    object->owner_body = (void *)(base_value + 0x20);
    ((ObjectNodeHeader *)record_field - 1)->update_callback = &advance_five_step_fixed_point_ramp;
}
