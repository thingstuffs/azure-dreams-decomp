#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "engine/object.h"
#include "engine/window.h"

typedef struct S_80035820_0 {
    s32 unk_00;
    u8 pad_04[0x4C];
    u16 unk_50;
    u8 pad_52[0x22];
    s32 unk_74;
} S_80035820_0;   /* arg0 in cleanup_window_object */

/* Cleans up a type-0x101 record and unlinks its enclosing object. */
void cleanup_window_object(void *record_arg) {
    S_80035820_0 *record = record_arg;
    void *object_base;

    if (record->unk_50 == 0x101) {
        clear_graphics_record(record->unk_74);
        runtime_clear_value(record->unk_00);
        runtime_unlink_doubly_linked_node(record_arg + 0x54);
        object_base = record_arg - 0x20;
        unlink_node(object_base);
        unlink_active_node(object_base);
    }
}
