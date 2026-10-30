#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/actor_status_ids.h"
#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/system.h"
#include "dungeon/level.h"
#include "engine/graphics.h"
#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad0[0x8C];
    void *handler;
    u8 pad90[6];
    u16 timer;
    u8 pad98[3];
    u8 state;
    u8 pad9C[6];
    u16 flagsa2;
} Arg0Struct;

extern u8 return_magic_frames[];
extern void *D_8008B870;
extern u8 player_sleep_frames;

extern s32 get_entity_effect_value(void *entry, s32 effect_id);

/* Advances actor animation states, periodic events, and handler transitions. */
void update_player_sleep_action(Arg0Struct *controller, void *unused, SpriteAnimationTableView *animation, ActorRecord *actor) {
    s32 event_code;
    GameWork *scene = &g_game_work;

    (void)unused;
    switch (controller->state) {
    case 0:
        if (animation->flags & 0xE000) {
            animation->frame_table = &player_sleep_frames;
            set_sprite_animation_frame(animation, (&player_sleep_frames)[((s32)(scene->view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0,
                1);
            controller->handler = &D_8008B870;
            controller->state = (s8)(controller->state + 1);
        }
        break;

    case 1:
        if (!(controller->timer & 0x1F)) {
            event_code = 0x50F;
            if (controller->timer & 0x20) {
                event_code = 0x50E;
            }
            play_sound_if_enabled(event_code);
        }
        if (!(g_dungeon_status.flags & 4) && (controller->flagsa2 & 0x10)) {
            if ((scene->buttons & 0x20) && (check_action_available_without_nearby_actor() != 0)) {
                g_dungeon_status.flags |= 0x80;
            }
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 0x10) == 0) {
                animation->frame_table = return_magic_frames;
                set_sprite_animation_frame(animation, return_magic_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0, 1);
                controller->handler = NULL;
                g_dungeon_status.activity_counts.parts.pending_action_count += 1;
                controller->state += 1;
            } else {
                process_unflagged_linked_entries_alt(actor->next_actor_header);
                process_unflagged_linked_entries(actor->next_actor_header);
                g_dungeon_status.flags |= 0x812;
            }
        }
        break;

    case 2:
        if (animation->flags & 0xE000) {
            actor->flags1C &= ~ACTOR_ASLEEP;
            process_unflagged_linked_entries_alt(actor->next_actor_header);
            process_unflagged_linked_entries(actor->next_actor_header);
            g_dungeon_status.flags |= 0x812;
            controller->handler =handle_player_input;
            g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
        }
        break;
    }

    controller->timer += 1;
}
