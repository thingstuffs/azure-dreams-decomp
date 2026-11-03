#ifndef TOWN_SHOP_CALLBACKS_API_H
#define TOWN_SHOP_CALLBACKS_API_H
#include "common.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/entity.h"
struct ShopEmbeddedDataObject;
void increase_shop_subrecord_value(struct ShopEmbeddedDataObject *record_data);
void move_toward_target_finalize_countdown_expires(void *object_arg, s32 context, ObjectPosition *motion);
void update_subobject_and_normalize_color(void *sub_object);

#endif
