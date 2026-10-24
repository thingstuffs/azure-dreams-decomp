#include "town/player/carry_item.h"

extern s32 scene_object_payload_alias;

/* Run plt_carry_on_chk_ext using the global record and its context values. */
void *plt_carry_on_chk_ext(void) {
    s32 *record = &scene_object_payload_alias;
    s32 *context = record - 8;


    return get_linked_carry_item_data(record, context[2], context[3]);
}
