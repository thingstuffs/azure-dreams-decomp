#include "dungeon/effect.h"
#include "dungeon/item.h"
#include "dungeon/player.h"
#include "dungeon/player/input.h"
#include "shared/dungeon_status.h"
#include "shared/object_node.h"

void begin_targeted_player_action(ActorRecord *action, ObjectPosition *unused_position, SpriteFrameState *unused_sprite, ActorRecord *actor)
{
    action->action_id = 0x28;
    action->action_phase = 0;
    action->unk_8C.handler = NULL;
    clear_player_linked_action_flags();

    g_dungeon_status.active_actor = NODE_HEADER(action);
    select_nearby_target_and_initialize_slot(g_dungeon_status.active_actor, NODE_HEADER(action)->position, 8, 0x300);
    append_packed_action_record(actor, 0xA0, 0, 0);
}
