#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player/item.h"
#include "town/player/position.h"

/* Initialize an object with its handler, two settings, and a state value of 20. */
void initialize_returned_item_action(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *sprite) {
    u16 secondSetting;

    dispatch_selected_entry_if_nonzero(type_three_action_handler_table, object, sprite);
    object->move_target_x = position->x.w.i;
    secondSetting = position->y.w.i;
    object->unk_00 = approach_linked_position_until_timeout;
    object->unk_0A = 0x14;
    object->move_target_y = secondSetting;
}
