#include "common.h"
#include "engine/menu.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "dungeon/actor.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void apply_pending_byte_increase(void *, s32, void *, void *);
extern void begin_player_menu_action(void *, s32, void *, void *);
extern void finish_paralyzed_actor_action(void *, s32, SpriteFrameState *, ActorRecord *);

extern s32 menu_action_argument;

/* Apply pending actor updates and handle input-driven state transitions. */
void apply_pending_actor_updates(void *controller, s32 move_state, void *entity, void *actor)
{
    s16 pending_delta = *(s16 *)((u8 *)actor + 0x64);
    GameWork *input_state = &g_game_work;

    if (pending_delta < 0) {
        *(u16 *)((u8 *)entity + 0x14) &= 0xF7FF;
        run_saved_actor_action(controller, move_state, entity, actor);
        return;
    }

    if (pending_delta > 0) {
        apply_pending_byte_increase(controller, move_state, entity, actor);
    }

    if (!(system_update_flags & 1) && (input_state->buttons & 0x80)) {
        *(s16 *)((u8 *)actor + 0x8A) = 2;
        menu_action_argument = 2;
        begin_player_menu_action(controller, move_state, entity, create_animated_selection_menu_owner);
        reference_tile_object.selected_item = 0;
        *(s32 *)((u8 *)controller + 0xC8) = 0;
        *(s32 *)((u8 *)controller + 0x104) = 0;
        return;
    }

    if (*(u8 *)((u8 *)controller + 0x9A) != 0x3A &&
        (*(s32 *)((u8 *)actor + 0x1C) & 0x200)) {
        *(u16 *)((u8 *)entity + 0x14) &= 0xF7FF;
        finish_paralyzed_actor_action(controller, move_state, entity, actor);
    }
}
