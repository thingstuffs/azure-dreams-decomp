#include "common.h"
#include "town/map.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

/* Process the initial value and each linked record value until the chain ends. */
s32 process_linked_record_values(void *object, s32 x, s32 initial_value) {
    s32 current_value;


    current_value = initial_value;
    for (;;) {

        draw_shaded_quad_ring(current_value, x);
        current_value = (s32)NODE_HEADER(object)->chain_next;
        object = NODE_BODY((ObjectNodeHeader *)current_value);
        if (current_value == 0) {
            break;
        }

        x = (s32)((ObjectNodeHeader *)current_value)->position;

        current_value = (s32)((ObjectNodeHeader *)current_value)->sprite;
    }
    return 0;
}
