#include "common.h"
#include "m2c_compat.h"
#include "town/shop/object.h"
#include "town/shop/state.h"


typedef struct S_800B1718_0 {
    u8 pad_00[0x10];
    void (*unk_10)();
} S_800B1718_0;   /* arg0 in set_shop_fade_out_callback */

/* Sets the object's data pointer when the object is present. */
void set_shop_fade_out_callback(S_800B1718_0 *object) {
    if (object != NULL) {
        object->unk_10 = &fade_out_shop_window;
    }
}
