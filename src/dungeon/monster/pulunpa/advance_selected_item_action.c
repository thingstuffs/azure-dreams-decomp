#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"


extern int abs(int);
extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void create_actor_linked_effect(void *);

extern u8 pulunpa_action_resume_address[];
extern u8 pulunpa_frame_set_1[];


typedef struct S_80172798_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172798_1_pre;   /* the 0x14 bytes before active in advance_selected_item_action, addressed as active[-1] */

typedef struct S_80172798_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172798_2;   /* linked in advance_selected_item_action */


typedef struct S_80172798_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172798_5;   /* global in advance_selected_item_action */

/* Advances the selected item action and resets movement when it ends. */
void advance_selected_item_action(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 special;
    u8 *selection;
    S_80172798_1_pre *active;
    u8 *scratch_pointer;

    special = 0;
    selection = (u8 *)(body->action_phase.u);
    switch ((u8)selection) {
    case 0:
        if ((((u32)actor->flags1C)) & ACTOR_PLAYER_SIDE) {
            switch (((actor->action_flags) & 0x3FFF)) {
            case 7:
                special = 1;
                /* fallthrough */
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 6:
                special = 1;
                /* fallthrough */
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 5:
                special = 1;
                /* fallthrough */
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        } else {
            switch ((actor->action_flags) & 0x3FFF) {
            case 3:
                selection = (u8 *)actor + 0xE;
                break;
            case 2:
                selection = (u8 *)actor + 0xB;
                break;
            case 1:
                selection = (u8 *)actor + 8;
                break;
            default:
                selection = 0;
                break;
            }
        }

        if (*selection != 0) {
            body->action_state_flags &= 0xFF7F;
            {
                s16 special_test;

                special_test = special;
                if (special_test != 0) {
                    active = (S_80172798_1_pre *)primary_actor_record;
                    (actor->target) = active;
                    scratch_pointer = active[-1].unk_00;
                    actor->target_tile_x = ((S_80172798_2 *)scratch_pointer)->unk_24;
                    actor->target_tile_y = ((S_80172798_2 *)scratch_pointer)->unk_25;
                } else {
                    u8 item_id;

                    item_id = *selection;
                    if (item_action_definitions[item_id].kind == 2) {
                        active = (actor->target);
                        if (active != 0) {
                            scratch_pointer = active[-1].unk_00;
                            actor->target_tile_x = ((S_80172798_2 *)scratch_pointer)->unk_24;
                            actor->target_tile_y = ((S_80172798_2 *)scratch_pointer)->unk_25;
                        }
                    } else {



                        (actor->target) = scan_actor_along_heading(
                            actor, sprite->tile_x, sprite->tile_y,
                            (actor->facing), 0x10);
                        actor->target_tile_x = abs(actor->target_tile_x);
                        actor->target_tile_y = abs(actor->target_tile_y);
                    }
                }
            }

            if (create_actor_spell_effect(actor, selection, special,
                              (u8 *)body + 0x98) == 0) {
                return;
            }
            create_actor_linked_effect(actor);
            body->action_phase.u++;
            return;
        }
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            g_dungeon_status.active_actor = 0;
            primary_actor_record->unk_A4.halves.high.u--;
            advance_status_timers(actor);
            actor->pending_turn_updates--;
            body->unk_8C.address = pulunpa_action_resume_address;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            (actor->action_flags) &= 0x7FFF;
            return;

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        body->action_phase.u++;

    case 2:
        if ((sprite->unk_04 == 7 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            body->action_timer.u = 1;
            body->action_state_flags |= 0x80;
        }
        {
            s16 timer;

            timer = body->action_timer.u - 1;
            body->action_timer.u = timer;
            if (timer <= 0) {
                body->action_timer.u = 0;
                sprite->flags &= 0xF7FF;
            }
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != pulunpa_frame_set_1) {
            u8 *anim_table;
            s32 direction;

            anim_table = pulunpa_frame_set_1;
            sprite->frameTable = anim_table;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + (actor->facing) + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, anim_table[direction], 0);
        }
        {
            scratch_pointer = (u8 *)&g_dungeon_status.turn_scale;
            if (((S_80172798_5 *)scratch_pointer)->unk_0C != 0) {
                return;
            }
            ((S_80172798_5 *)scratch_pointer)->unk_0A--;
            body->unk_8C.address = pulunpa_action_resume_address;
            advance_status_timers(actor);
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->pending_turn_updates--;
            (actor->action_flags) &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }

        return;
    default:
        return;
    }
}
