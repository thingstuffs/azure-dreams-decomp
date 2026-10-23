#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"

s32 func_80403CD4(void *);
extern s32 card_ui_dirty_flags;

/* Process embedded data and set object and global flags when the object exists. */
void card_dev_refresh_options_object(void *object) {
    if (object != 0) {
        func_80403CD4(object + 0x20);
        (*(u16 *)((u8 *)object + 0x1E)) = (u16) (((ObjectNodeHeader *)object)->flags | 0x8000);
        card_ui_dirty_flags |= 0x8000;
    }
}
