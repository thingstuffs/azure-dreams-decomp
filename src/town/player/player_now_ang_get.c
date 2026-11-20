#include "engine/message/data.h"
#include "engine/message.h"
#include "shared/object_index_slots.h"
#include "shared/object_node.h"
#include "town/person.h"
#include "town/player/record.h"

/* Store the player's facing direction in script variable zero. */
void player_now_ang_get(void)
{
    ScriptController *controller = &runtime_script_state;
    int player_slot = 1; /* BYTES: the slot index keeps the separate table-base addition. */
    ObjectNodeHeader *node;
    s32 player_angle;

    if (object_index_slots[player_slot].active == 0) {
        node = object_index_slots[player_slot].object;
        if (node != 0) {
            TownPlayerRecord *player = NODE_BODY(node);
            player_angle = map_angle_to_cardinal_direction(player->unk_10);
            controller->variables[0] = player_angle;
        }
    }
}
