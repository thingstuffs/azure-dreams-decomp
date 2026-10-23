#include "common.h"
#include "shared/object_node.h"

extern s32 D_800A5638;
extern s32 D_800A5A98;
extern s32 map_view_transition_address;
extern s32 map_fallback_handler_address;

/* Set the record parameters and handler when the global handlers do not match. */
void set_fallback_record_handler(void *record) {
    ObjectNodeHeader *base = ((u8 *)(&scene_object_list_anchor));

    if ((*(s32 * *)&base->update_callback != &D_800A5638) ||
        ((*(s32 **) (((u8 *)base) + 0x20) != &D_800A5A98) &&
         (*(s32 **) (((u8 *)base) + 0x20) != &map_view_transition_address))) {
        *(s16 *) ((u8 *) record + 2) = 0x20;
        *(s16 *) ((u8 *) record + 4) = 0x400;
        *(void **) ((u8 *) record + 0x1C) = &map_fallback_handler_address;
    }
}
