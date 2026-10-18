#include "common.h"
#include "shared/sys_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

void begin_player_damage_reaction();
void apply_pending_byte_increase();
void begin_player_menu_action();
void begin_player_sleep_action();
void set_record_integer_tile_center();
extern void * create_animated_selection_menu_owner(void *unused, void *source);
extern s32 D_800E4940[];

/* Reset movement and dispatch actor actions based on state and input flags. */
void handle_sleeping_player_input(Rec_func_8008ACDC_arg0 *controller, EntityRec *move_state, Rec_D_80082E80 *entity,
    EntityRec *actor) {
    s16 action_state;
    GameWork *input_state = &g_game_work;

    move_state->unk_10 = 0;
    move_state->unk_0C = 0;
    set_record_integer_tile_center(move_state, entity->unk_24, entity->unk_25);
    action_state = actor->unk_64;
    if ((action_state < 0) || (controller->unk_10C & 1)) {
        entity->unk_14.at00_u16.v = (u16)(entity->unk_14.at00_u16.v & 0xF7FF);
        begin_player_damage_reaction(controller, move_state, entity, actor);
        return;
    }
    if (action_state > 0) {
        apply_pending_byte_increase(controller, move_state, entity, actor);
    }
    if (!(D_80013714 & 1) && !(g_dungeon_status.flags & 4) && (((s32)input_state->buttons) & 0x80)) {
        actor->unk_8A = 2;
        D_800E4940[0] = 2;
        begin_player_menu_action(controller, move_state, entity, &create_animated_selection_menu_owner);
        D_80082E80.unk_030 = 0;
        controller->unk_C8 = 0;
        controller->unk_104 = 0;
        return;
    }
    if ((controller->unk_9A.as_u8 != 0xD) && (actor->flags1C & 0x200)) {
        entity->unk_14.at00_u16.v = (u16)(entity->unk_14.at00_u16.v & 0xF7FF);
        begin_player_sleep_action(controller, move_state, entity, actor);
    }
}
