#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

typedef struct Copy48 {
    u32 words[12];
} Copy48;

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, u8, s32);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void *create_actor_spell_effect(void *actor, void *effect_record, s16 mode, void *context);
extern void create_owner_linked_directional_object(void *, void *, void *);

extern u8 D_800D58D8[];
extern s8 view_direction_depth_biases[];
extern u8 uboat_default_frames[];
extern u8 D_800E2410[];
#include "dungeon/monster/u_boat.h"

typedef struct S_80173A60_0 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x60];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u8 unk_B0;
} S_80173A60_0;   /* arg0 in advance_actor_item_action */

typedef struct S_80173A60_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    u16 unk_96;
    u8 pad_98[0x14];
    void * unk_AC;
} S_80173A60_4;   /* state in advance_actor_item_action */

   /* target in advance_actor_item_action */

typedef struct S_80173A60_9 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80173A60_9;   /* global in advance_actor_item_action */

/* Advances an actor's item action, spawning its visual effect and restoring idle state. */
/* Starts a targeted spell, creates a directional sprite copy at frame 3, signals it at frame 19, then
 * updates status. */
void advance_actor_item_action(void *actor_state, ObjectPosition *motion, SpriteFrameState *sprite, void *actor)
{
    s16 use_player;
    u8 *item_id;
    s32 offset_x;

    use_player = 0;
    switch (((S_80173A60_0 *)actor_state)->unk_9B) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            u32 kind_index;

            kind_index = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                use_player = 1;
            case 2:
                item_id = (u8 *)actor + 0xE;
                break;
            case 5:
                use_player = 1;
            case 1:
                item_id = (u8 *)actor + 0xB;
                break;
            case 4:
                use_player = 1;
            case 0:
                item_id = (u8 *)actor + 8;
                break;
            default:
                item_id = 0;
                break;
            }
        } else {
            switch ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) {
            case 3:
                item_id = (u8 *)actor + 0xE;
                break;
            case 2:
                item_id = (u8 *)actor + 0xB;
                break;
            case 1:
                item_id = (u8 *)actor + 8;
                break;
            default:
                item_id = 0;
                break;
            }
        }

        if (*item_id != 0) {
            s32 use_player_test;
            void *linked_actor;

            ((S_80173A60_0 *)actor_state)->unk_98 &= 0xFF7F;
            use_player_test = use_player;
            if (use_player_test != 0) {
                u8 *linked_sprite;

                linked_actor = primary_actor_record;
                (*(void * *)((u8 *)actor + 0x60)) = linked_actor;
                linked_sprite = *(u8 * *)&((ObjectNodeHeader *)((u8 *)linked_actor - 0x20))->sprite;
                (*(u8 *)((u8 *)actor + 0x72)) = linked_sprite[0x24];
                offset_x = linked_sprite[0x25];
                (*(u8 *)((u8 *)actor + 0x73)) = offset_x;
            } else if (item_action_definitions[*item_id].kind == 2) {
                linked_actor = (*(void * *)((u8 *)actor + 0x60));
                if (linked_actor != 0) {
                    u8 *linked_sprite;

                    linked_sprite = *(u8 * *)&((ObjectNodeHeader *)((u8 *)linked_actor - 0x20))->sprite;
                    (*(u8 *)((u8 *)actor + 0x72)) = linked_sprite[0x24];
                    offset_x = linked_sprite[0x25];
                    (*(u8 *)((u8 *)actor + 0x73)) = offset_x;
                }
            } else {
                s32 offset_y;

                s32 abs_x;
                offset_x = (s32)scan_actor_along_heading(actor,
                                       sprite->tile_x,
                                       sprite->tile_y,
                                       (*(s16 *)((u8 *)actor + 0x2A)), 0x10);
                (*(void * *)((u8 *)actor + 0x60)) = (void *)offset_x;
                abs_x = abs(*(s8 *)((u8 *)actor + 0x72));
                offset_y = abs(*(s8 *)((u8 *)actor + 0x73));
                (*(u8 *)((u8 *)actor + 0x72)) = abs_x;
                (*(u8 *)((u8 *)actor + 0x73)) = offset_y;
            }

            if (create_actor_spell_effect(actor, item_id, use_player,
                              (u16 *)((u8 *)actor_state + 0x98)) == 0) {
                return;
            }
            ((S_80173A60_0 *)actor_state)->unk_96.u = 0;
            ((S_80173A60_0 *)actor_state)->unk_9B++;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)((u8 *)actor + 0x6D))--;
        ((S_80173A60_0 *)actor_state)->unk_8C = uboat_behavior_entry;
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x0800;
            return;
        }
        sprite->flags &= 0xF7FF;
        ((S_80173A60_0 *)actor_state)->unk_9B++;
        play_sound_if_enabled(0x703);
                        /* fall through */

    case 2:
    {
        u16 timer;

        timer = ((S_80173A60_0 *)actor_state)->unk_96.u + 1;
        ((S_80173A60_0 *)actor_state)->unk_96.u = timer;
        if ((s16)timer == 3) {
            ObjectNodeHeader *effect;

            effect = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
            if (effect != 0) {
                u8 *effect_state;
                SpriteFrameState *effect_sprite;
                ObjectPosition *effect_pos;
                u8 *anim_table;
                u8 *anim_entry;
                s8 *height_offsets;
                s32 direction_index;

                effect_state = ((u8 *)effect) + 0x20;
                ((S_80173A60_4 *)effect_state)->unk_96 = 0x10;
                effect->update_callback = D_800D58D8;
                ((S_80173A60_4 *)effect_state)->unk_AC = motion;
                ((S_80173A60_4 *)effect_state)->unk_94 = (*(u16 *)((u8 *)actor + 0x2A));
                effect_sprite = effect->sprite;
                *(Copy48 *)effect_sprite = *(Copy48 *)sprite;
                effect_sprite->scale_y = 0x1000;
                effect_sprite->scale_x = 0x1000;
                effect_sprite->color.c.b = 0x80;
                effect_sprite->color.c.g = 0x80;
                effect_sprite->color.c.r = 0x80;
                register_node(effect, project_sprite_chain);

                anim_table = D_800E2410;
                effect_sprite->frameTable = anim_table;
                anim_entry = (u8 *)((u32)(((g_game_work.view.camera_rotation.parts.viewAngle +
                          (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7) + (u32)anim_table);
                select_sprite_entry(effect_sprite, *anim_entry, 0);
                effect_sprite->flags &= 0xFFF3;

                direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle +
                          ((S_80173A60_0 *)actor_state)->unk_2A.s + 0x100) >> 9) & 7;
                height_offsets = view_direction_depth_biases;
                effect_sprite->depth_bias = -(height_offsets[direction_index] * 4);
                ((S_80173A60_4 *)effect_state)->unk_94 =
                    (((S_80173A60_0 *)actor_state)->unk_2A.u >> 9) & 7;
                ((S_80173A60_4 *)effect_state)->unk_2A = ((S_80173A60_0 *)actor_state)->unk_2A.u;

                effect_pos = effect->position;
                effect_pos->x.w.i = ((u16)motion->x.w.i);
                effect_pos->y.w.i = ((u16)motion->y.w.i);
                effect_pos->z.w.i = ((u16)motion->z.w.i);
            }
        }

        if (((S_80173A60_0 *)actor_state)->unk_96.s == 0x10) {
            u8 *anim_table;
            s32 direction_index;

            anim_table = uboat_default_frames;
            sprite->frameTable = anim_table;
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, anim_table[direction_index], 3);
            if (((S_80173A60_0 *)actor_state)->unk_B0 == 0) {
                create_owner_linked_directional_object(actor_state, motion, sprite);
            }
        }

        if (((S_80173A60_0 *)actor_state)->unk_96.s == 0x13 ||
            (sprite->flags & 0xE000)) {
            ((S_80173A60_0 *)actor_state)->unk_98 |= 0x80;
            play_sound_if_enabled(0x81B);
        }

        if (((S_80173A60_0 *)actor_state)->unk_96.s < 0x19 &&
            !(sprite->flags & 0xE000)) {
            return;
        }
        ((S_80173A60_0 *)actor_state)->unk_9B++;
        return;
    }

    case 3:
    {
        u8 *action_status;

        action_status = ((u8 *)(&g_dungeon_status));
        if (((S_80173A60_9 *)action_status)->unk_0C != 0) {
            return;
        }
        ((S_80173A60_0 *)actor_state)->unk_96.u = 0;
        if (((S_80173A60_9 *)action_status)->unk_0C != 0) {
            return;
        }
        ((S_80173A60_9 *)action_status)->unk_0A--;
        ((S_80173A60_0 *)actor_state)->unk_8C = uboat_behavior_entry;
        advance_status_timers(actor);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u8 *)((u8 *)actor + 0x6D))--;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    }
    }
}
