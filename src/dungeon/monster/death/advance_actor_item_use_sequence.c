#include "shared/sprite_frame_state.h"
#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"


typedef struct {
    u32 words[3];
} __attribute__((packed)) Packet12;

extern int abs(int);
extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void play_sound_if_enabled(s32);
extern void create_parent_return_effect(void *parent_obj, s16 effect_param, s32 initial_value, s16 duration, s16 offset_x, s16 offset_y, s16 offset_z);
extern void spawn_parent_offset_random_motion_effect(void *parent_arg, s16 effect_param_arg, s32 state_value_arg, s32 unused_arg, s32 offset_x_arg, s32 offset_y_arg, s32 offset_z_arg);

extern u8 D_80171080[];
extern s32 death_action_resume_address;
extern u8 death_direction_frames[];
extern Packet12 D_80174694;


typedef struct S_801732C4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_801732C4_0;   /* arg0 in advance_actor_item_use_sequence_2 */

typedef struct S_801732C4_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801732C4_1_pre;   /* the 0x14 bytes before active in advance_actor_item_use_sequence_2, addressed as active[-1] */

typedef struct S_801732C4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801732C4_2;   /* linked in advance_actor_item_use_sequence_2 */


typedef struct S_801732C4_5 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 pad_05[0x15];
    s16 unk_1A;
    s16 unk_1C;
} S_801732C4_5;   /* object_base in advance_actor_item_use_sequence_2 */

   /* transform in advance_actor_item_use_sequence_2 */

typedef struct S_801732C4_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801732C4_7;   /* display in advance_actor_item_use_sequence_2 */

/* Advances an actor's item-use sequence, animation, and particle effects. */
/* Starts a targeted spell, emits returning particles and a 20-particle burst, then restores the actor's
 * idle state. */
void advance_actor_item_use_sequence_2(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor)
{
    u8 *item_slot;
    s32 special;
    s32 i;
    u8 state;
    u8 next_state;
    S_801732C4_1_pre *target;

    special = 0;
    state = ((S_801732C4_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((((u32)actor->flags1C)) & ACTOR_PLAYER_SIDE) {
            u32 kind_index;

            kind_index = ((actor->action_flags) & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                special = 1;
            case 2:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 5:
                special = 1;
            case 1:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 4:
                special = 1;
            case 0:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 action_kind;

            action_kind = (actor->action_flags) & 0x3FFF;
            switch (action_kind) {
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            ((S_801732C4_0 *)action)->unk_98 &= 0xFF7F;
            {
                s16 special_test;

                special_test = special;
                if (special_test != 0) {
                    target = (S_801732C4_1_pre *)primary_actor_record;
                    (actor->target) = target;
                    {
                        S_801732C4_2 *item_id;

                        item_id = target[-1].unk_00;
                        actor->target_tile_x = item_id->unk_24;
                        actor->target_tile_y = item_id->unk_25;
                    }
                } else {
                    u8 *item_id;
                    u8 *item_defs;

                    item_defs = item_action_definitions;
                    item_id = (u8 *)(*item_slot);
                    if (item_defs[((u8)item_id) * 20 + 0x12] == 2) {
                        target = (actor->target);
                        if (target != 0) {
                            item_id = target[-1].unk_00;
                            actor->target_tile_x = ((S_801732C4_2 *)item_id)->unk_24;
                            actor->target_tile_y = ((S_801732C4_2 *)item_id)->unk_25;
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

            if (create_actor_spell_effect(actor, item_slot, special, (u8 *)action + 0x98) == 0) {
                return;
            }
            next_state = ((S_801732C4_0 *)action)->unk_9B;
            next_state++;
            ((S_801732C4_0 *)action)->unk_9B = next_state;
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
        ((S_801732C4_0 *)action)->unk_8C = &death_action_resume_address;
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
        ((S_801732C4_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x703);

    case 2:
    {
        u16 flags;
        s16 timer;

        flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
        if (flags & 0x8000) {
            next_state = ((S_801732C4_0 *)action)->unk_9B;
            ((S_801732C4_0 *)action)->unk_96.u = 0;
            next_state++;
            ((S_801732C4_0 *)action)->unk_9B = next_state;
            return;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2 && (flags & 0x1000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = flags | 0x800;
            ((S_801732C4_0 *)action)->unk_96.u = 0x16;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 < 2) {
            return;
        }
        timer = ((S_801732C4_0 *)action)->unk_96.u - 1;
        ((S_801732C4_0 *)action)->unk_96.u = timer;
        if (timer <= 0) {
            ((S_801732C4_0 *)action)->unk_96.u = 0;
            ((S_801732C4_0 *)action)->unk_9B++;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (((S_801732C4_0 *)action)->unk_96.s >= 7) {
            i = 0;
            do {
                s32 brightness;
                register s32 offset_x;
                register s32 offset_y;
                s16 offset_z;

                i++;
                brightness = (rand() & 0xFF) | 0x80;
                offset_x = (s16)((rand() & 0x7F) - 0x40);
                offset_y = (s16)((rand() & 0x7F) - 0x40);
                offset_z = (rand() & 0x7F) - 0x40;
                create_parent_return_effect((u8 *)action - 0x20, 0, 0x00C0C0C0,
                              brightness, offset_x, offset_y, offset_z);
            } while ((u16)i < 5);
        }
    }

        {
            ObjectNodeHeader * object;
            S_801732C4_5 *object_base;
            ObjectPosition *transform;
            SpriteFrameState *display;
            u16 timer;
            u16 flags;

            timer = ((S_801732C4_0 *)action)->unk_96.u;
            if (!(timer & 1) || (s16)timer < 0x13) {
                return;
            }
            object = allocate_flagged_object_node(0x212);
            if (object == 0) {
                return;
            }
            object_base = (S_801732C4_5 *)((u8 *)object + 0x20);
            object_base->unk_1A = 0x19;
            object_base->unk_1C = 0x19;
            (object->update_callback) = D_80171080;
            register_node(object, project_sprite_chain);
            transform = object->position;
            transform->x.w.i = ((u16)motion->x.w.i);
            transform->y.w.i = ((u16)motion->y.w.i);
            transform->z.w.i = ((u16)motion->z.w.i) - 0x60;
            display = object->sprite;
            (*(Packet12 *)((u8 *)object + 0x48)) = D_80174694;
            display->source = (u8 *)object + 0x48;
            display->tpage_abr = 0x40;
            display->scale_y = 0x32C8;
            display->scale_x = 0x32C8;
            display->depth_bias = 0x64;
            display->color.word = 0;
            flags = display->flags;
            display->flags = flags | 0xC;
            object_base->unk_04 = 0x80;
            object_base->unk_03 = 0x80;
            object_base->unk_02 = 0x80;
        }
        return;

    case 3:
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 5 &&
             (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            ((S_801732C4_0 *)action)->unk_96.u = 0x14;
            ((S_801732C4_0 *)action)->unk_98 |= 0x80;
            ((S_801732C4_0 *)action)->unk_9B++;
            i = 0;
            do {
                {
                    s32 brightness;

                    i++;
                    brightness = (rand() & 0xFF) | 0x80;
                    spawn_parent_offset_random_motion_effect((u8 *)action - 0x20, 0, 0x00C0C0C0,
                                  brightness, 0, 0, 0);
                }
                if ((u16)i >= 20) {
                    return;
                }
            } while (1);
        }
        return;

    case 4:
    {
        s16 timer;

        if ((g_dungeon_status.active_actor) == 0) {
            ((S_801732C4_0 *)action)->unk_96.u = 0;
        }
        timer = ((S_801732C4_0 *)action)->unk_96.u - 1;
        ((S_801732C4_0 *)action)->unk_96.u = timer;
        if (timer > 0 && !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        ((S_801732C4_0 *)action)->unk_96.u = 0;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        next_state = ((S_801732C4_0 *)action)->unk_9B;
        next_state++;
        ((S_801732C4_0 *)action)->unk_9B = next_state;
        return;
    }

    case 5:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != death_direction_frames) {
            u8 *anim_table;
            s32 direction;
            s32 saved_a4;

            anim_table = death_direction_frames;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + (actor->facing) + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, anim_table[direction], 2);
            ((Rec_D_80082E80 *)sprite)->unk_05.as_u8 = 1;
            saved_a4 = ((S_801732C4_0 *)action)->unk_A4.at00.v;
            ((S_801732C4_0 *)action)->unk_A4.at02.v = 0;
            ((S_801732C4_0 *)action)->unk_B8 = 0;
            ((S_801732C4_0 *)action)->unk_AC = 0;
            ((S_801732C4_0 *)action)->unk_B0 = 0;
            ((S_801732C4_0 *)action)->unk_A8 = saved_a4;
        }
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((S_801732C4_0 *)action)->unk_8C = &death_action_resume_address;
            advance_status_timers(actor);
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->pending_turn_updates--;
            (actor->action_flags) &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }

        return;
    }
}
