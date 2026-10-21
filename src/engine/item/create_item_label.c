#include "common.h"
#include "engine/item.h"

/* Allocator wrapper: the retail definition of create_callback_pair_default (code7.c, gcc 2.8.1)
 * declares "void create_callback_pair_default(int,int,int,int)" but is a tail-call forwarder to
 * create_callback_pair_payload, whose return value passes through in $v0 untouched. This call
 * site only ever sets $a0 (the size), so we prototype/call it with just that one
 * argument and treat it as value-returning, matching the "value-returning wrapper"
 * idiom (v0 flows through from the tail jal, never re-touched before jr). */
extern void *create_callback_pair_default(s32 a0);

/* format_item_name: init routine for the freshly-allocated 0x104-byte object,
 * takes the object pointer and this function's original argument. Returns
 * nonzero on success. */
extern s32 format_item_name(void *a0, void *a1);

/* func_8004B1A4 (code5.c): sets a "used" flag bit on a 16-bit
 * flags field 2 bytes before the object pointer, plus a global flags word. */
extern void flag_object_for_removal(u16 *a0);

/* Allocates and initializes a 0x104-byte object, returning NULL on failure. */
void *create_item_label(void *init_data)
{
    void *object;

    object = create_callback_pair_default(0x104);
    if (object != 0) {
        if (format_item_name(object, init_data) == 0) {
            flag_object_for_removal(object);
            object = 0;
        }
    }
    return object;
}
