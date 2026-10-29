#include "shared/dungeon_actor_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/player.h"
#include "engine/graphics.h"
#include "slus.h"

typedef struct S_8008E504_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x80];
    void * unk_124;
} S_8008E504_0;   /* arg0 in update_player_landing_recovery */

extern s32 held_item_record;
extern s32 saved_held_item_word;

extern u8 player_landing_frame_set[];

#include "dungeon/player/input.h"

/* Advances an actor's timed animation state and selects its next behavior. */
void update_player_landing_recovery(S_8008E504_0 *actor, ObjectPosition *action, SpriteAnimationTableView *sprite, ActorRecord *entity) {
    u16 state_or_ticks;
    u16 sprite_flags;
    s32 state;
    s32 saved_status;
    s32 entity_flags;
    s32 object_flags;
    ActorRecord *linked_object;

    state = actor->unk_9B;
    switch (state) {
    case 0:
        if (!(actor->unk_A2 & 0x10)) {
            return;
        }
        action->velocity_z = 0;
        if ((entity->ground_height - entity->unk_8A) >= 0x41) {
            initialize_timed_motion_step(8, 0x10);
            if (entity->flags1C & 0x100000) {
                linked_object = actor->unk_124;
                saved_status = held_item_record;
                object_flags = linked_object->flags1C;
                held_item_record = 0;
                linked_object->flags1C = object_flags & 0xFFF7FFFF;
                entity_flags = entity->flags1C;
                saved_held_item_word = saved_status;
                entity->flags1C = entity_flags & 0xFFEFFFFF;
            }
            state_or_ticks = 0xC;
            actor->unk_96 = state_or_ticks;
        } else {
            actor->unk_96 = 1U;
        }
        actor->unk_9B = (u8)(actor->unk_9B + 1);
                /* fall through */
    case 1:
        if (entity->flags1C & 0x100000) {
            actor->unk_8C = handle_carrying_player_input;
            return;
        }
        sprite->frame_table = player_landing_frame_set;
        set_sprite_animation_frame(sprite,
            player_landing_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0, 1);
        sprite->flags = (u16)(sprite->flags | 0x800);
        actor->unk_9B = (u8)(actor->unk_9B + 1);
        return;

    case 2:
        state_or_ticks = actor->unk_96 - 1;
        actor->unk_96 = state_or_ticks;
        if ((state_or_ticks << 0x10) > 0) {
            return;
        }
        sprite_flags = sprite->flags;
        sprite->flags = (u16)(sprite_flags & 0xF7FF);
        if ((sprite_flags & 0xE000) != 0 || ((has_action_input_without_modifier() << 0x10) != 0)) {
            actor->unk_8C =handle_player_input;
        }
        return;
    }
}
