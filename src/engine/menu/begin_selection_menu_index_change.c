#include "common.h"

#include "common.h"
#include "engine/menu.h"
#include "slus.h"

typedef struct S_8004FA2C {
    void (*f0)(void *self);   /* 0x00 - callback, compared to animate_selection_menu_entry_spacing */
    u8 pad04[0x20 - 0x4];
    s32 f20;                  /* 0x20 */
    s32 f24;                  /* 0x24 */
    u8 pad28[0x2C - 0x28];
    s32 f2C;                  /* 0x2C */
    s32 f30;                  /* 0x30 */
    s32 f34;                  /* 0x34 */
} S_8004FA2C;

/* Resets the object's transition state, switches callbacks, and advances its saved value. */
void begin_selection_menu_index_change(S_8004FA2C *object, int target)
{
    object->f2C = 0;
    if (object->f0 == animate_selection_menu_entry_spacing) {
        object->f20 = 0x20;
        animate_selection_menu_entry_spacing(object);
    }
    object->f34 = object->f30;
    object->f0 = animate_selection_menu_index_transition;
    object->f30 = advance_index_with_single_wrap(object->f30, target, object->f24);
}
