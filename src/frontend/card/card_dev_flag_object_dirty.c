#include "common.h"
#include "frontend/card.h"

typedef struct {
    s32 v;
    s32 pad[2];
} D_8008DAB4_View; /* real D_8008DAB4 is >8B so hi/lo addressing is used */

/* Set bit 0x8000 in the object and global flags when the object exists. */
void card_dev_flag_object_dirty(void *object) {
    if (object != 0) {
        u16 *flags_ptr = (u16 *)((u8 *)object + 0x1E);
        u16 object_flags = *flags_ptr;
        s32 global_flags;
        {
            extern s32 card_ui_dirty_flags;
            global_flags = card_ui_dirty_flags;
        }
        object_flags |= 0x8000;
        global_flags |= 0x8000;
        *flags_ptr = object_flags;
        {
            extern D_8008DAB4_View card_ui_dirty_flags;
            card_ui_dirty_flags.v = global_flags;
        }
    }
}
