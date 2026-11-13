#include "common.h"
#include "town/shop.h"
#include "shared/object_node.h"

/* Set the record's base and offset values and its data pointer. */
void bind_shop_reset_object_ramp(ShopRecordResetObject *record_field, s32 base_value) {
    ShopRecordResetObject *object = record_field;

    object->owner_node = (ObjectNodeHeader *)base_value;
    object->owner_body = (void *)(base_value + 0x20);
    NODE_HEADER(record_field)->update_callback = &advance_five_step_fixed_point_ramp;
}
