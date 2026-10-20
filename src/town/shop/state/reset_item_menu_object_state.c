#include "common.h"

typedef struct {
    s8 pad00[0xA8];
    s32 field_A8;
} Inner;

typedef struct {
    u8 pad00[0x1E];
    u16 flags;
    Inner inner;
} Object;

extern void release_null_terminated_entries(void *entries);
extern void clear_item_menu_entry_groups(s32 slot_table);
extern s32 D_800814A0;

// Process a non-null object and set its local and global 0x8000 flags.
void reset_item_menu_object_state(Object *object)
{
    Inner *inner;

    if (object != 0) {
        inner = &object->inner;
        release_null_terminated_entries((u8 *)object + 0xCC);
        clear_item_menu_entry_groups(inner->field_A8);
        object->flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
