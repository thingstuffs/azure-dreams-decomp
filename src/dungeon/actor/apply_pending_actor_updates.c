#include "common.h"
#include "engine/menu.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

#include "dungeon/player.h"

extern s32 menu_action_argument;

/* Apply pending actor updates and handle input-driven state transitions. */
void apply_pending_actor_updates(ActorRecord *controller, ObjectPosition *move_state, SpriteFrameState *entity, ActorRecord *actor)
{
    PlayerRecord *player = (PlayerRecord *)controller;
    s16 pending_delta = actor->hp_delta;
    GameWork *input_state = &g_game_work;

    if (pending_delta < 0) {
        entity->flags &= 0xF7FF;
        run_saved_actor_action(controller, move_state, entity, actor);
        return;
    }

    if (pending_delta > 0) {
        apply_pending_byte_increase(controller, move_state, entity, actor);
    }

    if (!(system_update_flags & 1) && (input_state->buttons & 0x80)) {
        actor->unk_8A = 2;
        menu_action_argument = 2;
        begin_player_menu_action(controller, move_state, entity, create_animated_selection_menu_owner);
        reference_tile_object.selected_item = 0;
        player->unk_C8 = 0;
        player->unk_104 = 0;
        return;
    }

    if (controller->action_id != 0x3A &&
        (actor->flags1C & 0x200)) {
        entity->flags &= 0xF7FF;
        finish_paralyzed_actor_action(controller, move_state, entity, actor);
    }
}
