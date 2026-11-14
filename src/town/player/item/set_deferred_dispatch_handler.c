#include "common.h"
#include "town/player.h"
#include "town/player/action_initializers.h"
#include "town/player/item.h"


/* Stores the address of D_800933FC in the output pointer. */
void set_deferred_dispatch_handler(void *object, void *unused_position, void *unused_context) {
    s32 **out_ptr = object;

    *out_ptr = dispatch_deferred_callback;
}
