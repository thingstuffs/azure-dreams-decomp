#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"

extern void select_sprite_entry(void *, s32, s32);
extern void apply_scaled_entity_velocity(void *);

extern u8 D_801755B4[];
extern u8 D_80175660[];

/*
 * Copies Barong's turn counts into shared state and starts a directional action when the scaled
 * count and dungeon flags allow.
 */
void start_direction_based_action(ActorRecord *body, ObjectPosition *unused, SpriteFrameState *animation, ActorRecord *actor)
{
    u8 *state_data;
    register s32 data_page;
    u8 *direction_table;
    s32 direction_index;

    state_data = D_80175660;
    *(u16 *)(state_data + 0x6C) = *(u16 *)((u8 *)actor + 0x6C);
    *(u16 *)(state_data + 0x6E) = *(u16 *)((u8 *)actor + 0x6E);
    apply_scaled_entity_velocity(state_data);

    if (*(s8 *)(state_data + 0x6D) != 0) {
        u8 *action_data;
        actor->movement_queue_state &= 0x7F;
        action_data = ((u8 *)(&g_dungeon_status));
        if (!(*(u16 *)(action_data + 2) & 0x2000)) {
            direction_table = D_801755B4;
            body->action_id.s = 0x17;
            body->unk_8C.word = 0;
            body->action_phase.s = 0;
            body->action_timer.s = 0;

            animation->frameTable = direction_table;
            data_page = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
            select_sprite_entry(animation, direction_table[data_page & 7], 0);
            advance_status_timers(actor);
            *((u8 *)actor + 0x6D) -= 1;
            *(u16 *)(action_data + 0xA) += 1;
        }
    }
}
