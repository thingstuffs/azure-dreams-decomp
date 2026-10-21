#include "common.h"
#include "frontend/card.h"

s32 func_800484A4(s32, s32 *);

extern s32 card_ui_dirty_flags;

/* Updates the object's indirect value and sets the object and global 0x8000 flags. */
void refresh_object_value(void *object) {

    if (object != 0) {
        **(s32 ***)(object + 0x20) = func_800484A4(*(s32 *)(object + 0x24) + 6, *(s32 *)(object + 0x20));
        {
            u16 of = *(u16 *)(object + 0x1E);
            s32 gf = card_ui_dirty_flags;

            *(u16 *)(object + 0x1E) = of | 0x8000;
            card_ui_dirty_flags = gf | 0x8000;
        }
    }
}
