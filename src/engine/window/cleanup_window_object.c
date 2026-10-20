#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035820_0 {
    s32 unk_00;
    u8 pad_04[0x4C];
    u16 unk_50;
    u8 pad_52[0x22];
    s32 unk_74;
} S_80035820_0;   /* arg0 in cleanup_window_object */


void runtime_clear_value();                         /* extern */
void clear_graphics_record();                         /* extern */
void runtime_unlink_doubly_linked_node();                      /* extern */
void unlink_active_node();                      /* extern */
void unlink_node();                      /* extern */

/* Cleans up a type-0x101 record and unlinks its enclosing object. */
void cleanup_window_object(void *record) {
    void *object_base;

    if (((S_80035820_0 *)record)->unk_50 == 0x101) {
        clear_graphics_record(((S_80035820_0 *)record)->unk_74);
        runtime_clear_value(((S_80035820_0 *)record)->unk_00);
        runtime_unlink_doubly_linked_node(record + 0x54);
        object_base = record - 0x20;
        unlink_node(object_base);
        unlink_active_node(object_base);
    }
}
