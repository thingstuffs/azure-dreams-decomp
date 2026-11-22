#include "common.h"
#include "m2c_compat.h"
#include "town/shop/object.h"
#include "town/shop/state.h"

/* Sets the object's data pointer when the object is present. */
void set_shop_fade_out_callback(ObjectNodeHeader *object) {
    if (object != NULL) {
        object->update_callback = &fade_out_shop_window;
    }
}
