#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player/item.h"
#include "town/player/position.h"






typedef struct S_800947CC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800947CC_1;   /* arg1 in initialize_returned_item_action */

/* Initialize an object with its handler, two settings, and a state value of 20. */
void initialize_returned_item_action(TownObjectRecord *object, S_800947CC_1 *settings, void *ptr2) {
    u16 secondSetting;
    s32 *handler;

    dispatch_selected_entry_if_nonzero(type_three_action_handler_table, object, ptr2);
    object->unk_30 = (u16) settings->unk_02;
    handler = (s32 *) approach_linked_position_until_timeout;
    secondSetting = settings->unk_06;
    object->unk_00 = handler;
    object->unk_0A = 0x14;
    object->unk_32 = secondSetting;
}
