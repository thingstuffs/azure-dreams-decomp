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


extern int abs(int);
extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void *create_actor_spell_effect(void *, void *, s32, void *);
extern void create_actor_linked_effect(void *);

extern u8 pulunpa_action_resume_address[];
extern u8 pulunpa_frame_set_1[];


typedef struct S_80172798_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172798_0;   /* arg0 in advance_selected_item_action */

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
void advance_selected_item_action(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor)
{
    s32 special;
    u8 *selection;
    S_80172798_1_pre *active;
    u8 *scratch_pointer;

    special = 0;
    selection = (u8 *)(((S_80172798_0 *)action)->unk_9B);
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
            ((S_80172798_0 *)action)->unk_98 &= 0xFF7F;
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
                            actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                            (actor->facing), 0x10);
                        actor->target_tile_x = abs(actor->target_tile_x);
                        actor->target_tile_y = abs(actor->target_tile_y);
                    }
                }
            }

            if (create_actor_spell_effect(actor, selection, special,
                              (u8 *)action + 0x98) == 0) {
                return;
            }
            create_actor_linked_effect(actor);
            ((S_80172798_0 *)action)->unk_9B++;
            return;
        }
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
            advance_status_timers(actor);
            actor->pending_turn_updates--;
            ((S_80172798_0 *)action)->unk_8C = pulunpa_action_resume_address;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            (actor->action_flags) &= 0x7FFF;
            return;

    case 1:
        if (get_cd_command_queue_depth()) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_80172798_0 *)action)->unk_9B++;

    case 2:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 7 &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_80172798_0 *)action)->unk_96 = 1;
            ((S_80172798_0 *)action)->unk_98 |= 0x80;
        }
        {
            s16 timer;

            timer = ((S_80172798_0 *)action)->unk_96 - 1;
            ((S_80172798_0 *)action)->unk_96 = timer;
            if (timer <= 0) {
                ((S_80172798_0 *)action)->unk_96 = 0;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            }
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != pulunpa_frame_set_1) {
            u8 *anim_table;
            s32 direction;

            anim_table = pulunpa_frame_set_1;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + (actor->facing) + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, anim_table[direction], 0);
        }
        {
            scratch_pointer = (u8 *)&g_dungeon_status.turn_scale;
            if (((S_80172798_5 *)scratch_pointer)->unk_0C != 0) {
                return;
            }
            ((S_80172798_5 *)scratch_pointer)->unk_0A--;
            ((S_80172798_0 *)action)->unk_8C = pulunpa_action_resume_address;
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
