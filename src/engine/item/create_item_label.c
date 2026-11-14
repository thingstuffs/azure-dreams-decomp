#include "common.h"
#include "engine/item.h"
#include "engine/resource.h"

/* Allocator wrapper: the retail definition of allocate_node_body (code7.c, gcc 2.8.1)
 * declares "void allocate_node_body(int,int,int,int)" but is a tail-call forwarder to
 * create_node_with_record_pair, whose return value passes through in $v0 untouched. This call
 * site only ever sets $a0 (the size), so we prototype/call it with just that one
 * argument and treat it as value-returning, matching the "value-returning wrapper"
 * idiom (v0 flows through from the tail jal, never re-touched before jr). */

/* format_item_name: init routine for the freshly-allocated 0x104-byte object,
 * takes the object pointer and this function's original argument. Returns
 * nonzero on success. */

/* func_8004B1A4 (code5.c): sets a "used" flag bit on a 16-bit
 * flags field 2 bytes before the object pointer, plus a global flags word. */

/* Allocates and initializes a 0x104-byte object, returning NULL on failure. */
void *create_item_label(void *init_data)
{
    void *object;

    object = allocate_node_body(0x104);
    if (object != 0) {
        if (format_item_name(object, init_data) == 0) {
            flag_object_for_removal(object);
            object = 0;
        }
    }
    return object;
}
