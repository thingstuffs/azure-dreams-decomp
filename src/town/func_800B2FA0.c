#include "common.h"
void finish_item_menu_child_and_release_list(void *record);

typedef struct S_800B0700_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800B0700_0;   /* arg0 in schedule_item_menu_child_release */

/* Sets the object's data pointer when the object is present. */
void schedule_item_menu_child_release(S_800B0700_0 *object) {
    if (object != 0) {
        object->unk_10 = &finish_item_menu_child_and_release_list;
    }
}
