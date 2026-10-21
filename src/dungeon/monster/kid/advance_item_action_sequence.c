#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
extern int abs(int);

typedef struct S_80172D74_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
    u16 unk_A8;
} S_80172D74_1;   /* arg0 in advance_item_action_sequence */

typedef struct S_80172D74_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172D74_2_pre;   /* the 0x14 bytes before entity in advance_item_action_sequence, addressed as entity[-1] */

typedef struct S_80172D74_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172D74_3;   /* position in advance_item_action_sequence */

typedef struct S_80172D74_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172D74_4;   /* arg2 in advance_item_action_sequence */

typedef struct S_80172D74_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80172D74_5;   /* part20 in advance_item_action_sequence */


typedef struct S_80172D74_7 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80172D74_7;   /* part28 in advance_item_action_sequence */


extern s32 get_cd_command_queue_depth(void);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, s32, s32, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, void *, s32, void *);
extern void create_source_positioned_object(void *, s32);

extern u8 D_80171400[];
extern u8 D_80175140[];
extern u8 D_80175148[];
extern u8 D_80175168[];
extern u8 D_80175170[];

/* Advances an item action through setup, animation, movement, and cleanup. */
void advance_item_action_sequence(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor)
{
    void *owner;
    void *owner_flags;
    void *owner_sprite;
    u8 *item_slot;
    void *entity;
    void *position;
    s32 special_item;
    s32 step_x;
    s32 step_z;
    s32 next_state;
    u8 state_value;

    special_item = 0;
    {
        u32 direction_index = ((u16)actor->facing >> 8) & 0xE;

        owner = ((S_80172D74_1 *)action)->unk_A4;
        owner_flags = (u8 *)owner + 0x20;
        step_x = *(s16 *)(((s8 *)dir_step_x) + direction_index);
        step_z = *(s16 *)(((s8 *)dir_step_y) + direction_index);
        owner_sprite = (u8 *)owner + 0x28;
    }
    ((S_80172D74_1 *)action)->unk_96.s--;
    switch (((S_80172D74_1 *)action)->unk_9B) {
    case 0:
        if (actor->flags1C & 0x2000) {
            s32 kind_index = (actor->action_flags & 0x3FFF) - 1;

            switch (kind_index) {
            case 6:
                special_item = 1;
            case 2:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 5:
                special_item = 1;
            case 1:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 4:
                special_item = 1;
            case 0:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor->action_flags & 0x3FFF) {
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
            ((S_80172D74_1 *)action)->unk_98 &= 0xFF7F;
            {
                s16 special_test;

                special_test = special_item;
                if (special_test != 0) {
                    entity = primary_actor_record;
                    actor->target = entity;
                    position = ((S_80172D74_2_pre *)entity)[-1].unk_00;
                    actor->target_tile_x = ((S_80172D74_3 *)position)->unk_24;
                    actor->target_tile_y = ((S_80172D74_3 *)position)->unk_25;
                } else {
                    u8 *item_defs = item_action_definitions;
                    u8 item_id = *item_slot;

                    if (item_defs[item_id * 20 + 0x12] == 2) {
                        entity = actor->target;

                        if (entity != 0) {
                            position = ((S_80172D74_2_pre *)entity)[-1].unk_00;
                            actor->target_tile_x = ((S_80172D74_3 *)position)->unk_24;
                            actor->target_tile_y = ((S_80172D74_3 *)position)->unk_25;
                        }
                    } else {
                        position = scan_monster_along_heading(actor,
                            ((S_80172D74_4 *)sprite)->unk_24, ((S_80172D74_4 *)sprite)->unk_25,
                            actor->facing, 0x10);
                        actor->target = position;
                        actor->target_tile_x = abs(actor->target_tile_x);
                        actor->target_tile_y = abs(actor->target_tile_y);
                    }
                }
            }

            ((S_80172D74_5 *)owner_flags)->unk_04 &= 0x7FFF;
            (*(u8 * *)((u8 *)owner_sprite + 0x2C)) = D_80175168;
            select_sprite_entry(owner_sprite,
                D_80175168[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            if (!create_actor_spell_effect(actor, item_slot, special_item, (u8 *)action + 0x98)) {
                return;
            }
            ((S_80172D74_4 *)sprite)->unk_14 &= 0xF7FF;
            create_source_positioned_object(motion, 3);
            play_sound_if_enabled(0x703);
            state_value = ((S_80172D74_1 *)action)->unk_9B;
            ((S_80172D74_1 *)action)->unk_96.s = 6;
            ((S_80172D74_1 *)action)->unk_9B = state_value + 1;
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((S_80172D74_4 *)sprite)->unk_24, ((S_80172D74_4 *)sprite)->unk_25);
        {
            void *entity = primary_actor_record;

            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)entity + 0xA6))--;
        }
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        ((S_80172D74_1 *)action)->unk_8C = D_80171400;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            ((S_80172D74_4 *)sprite)->unk_14 |= 0x0800;
            return;
        }
        ((S_80172D74_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172D74_1 *)action)->unk_9B++;

    case 2:
        if (((S_80172D74_1 *)action)->unk_96.u > 0 &&
            !(((S_80172D74_4 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        ((S_80172D74_1 *)action)->unk_96.s = 7;
        ((S_80172D74_1 *)action)->unk_98 |= 0x80;
        if (((S_80172D74_4 *)sprite)->unk_14 & 0x8000) {
            next_state = 0x10;
            ((S_80172D74_1 *)action)->unk_9B = next_state;
            return;
        }
        ((S_80172D74_1 *)action)->unk_9B = ((S_80172D74_1 *)action)->unk_9B + 1;
        return;

    case 3:
        if (((S_80172D74_1 *)action)->unk_96.u < 4) {
            motion->velocity_x = -step_x << 18;
            motion->velocity_y = -step_z << 18;
        }
        if (((S_80172D74_1 *)action)->unk_96.u > 0) {
            return;
        }
        next_state = 4;
        ((S_80172D74_1 *)action)->unk_96.s = next_state;
        next_state = 0x10;
        ((S_80172D74_1 *)action)->unk_9B = next_state;
        return;

    case 16:
    {
        s32 target_x = ((S_80172D74_4 *)sprite)->unk_24 << 6;
        s32 current_x = motion->x.w.i - 0x20;

        motion->velocity_x = (target_x - current_x) << 14;
    }
        {
            s32 target_z = ((S_80172D74_4 *)sprite)->unk_25 << 6;
            s32 current_z = motion->y.w.i - 0x20;

            motion->velocity_y = (target_z - current_z) << 14;
        }
        if (!(((S_80172D74_7 *)owner_sprite)->unk_14 & 0x8000) &&
            ((S_80172D74_1 *)action)->unk_96.u > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((S_80172D74_4 *)sprite)->unk_24, ((S_80172D74_4 *)sprite)->unk_25);
        {
            u8 *animation = ((S_80172D74_4 *)sprite)->unk_2C;
            u8 *next_animation = D_80175140;

            if (animation != D_80175140) {
                u8 *alternate_animation = D_80175148;

                if (animation != alternate_animation && (((S_80172D74_4 *)sprite)->unk_14 & 0x6000)) {
                    ((S_80172D74_5 *)owner_flags)->unk_04 |= 0x8000;
                    ((S_80172D74_1 *)action)->unk_A8 = 0;
                    if (((S_80172D74_4 *)sprite)->unk_2C == D_80175170) {
                        next_animation = alternate_animation;
                    }
                    (*(u8 * *)((u8 *)sprite + 0x2C)) = next_animation;
                    select_sprite_entry(sprite,
                        next_animation[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                        0);
                }
            }
        }
        {

            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((S_80172D74_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_80172D74_1 *)action)->unk_8C = D_80171400;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            (*(u8 *)&actor->pending_turn_updates)--;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        play_sound_if_enabled(0xB4);
    }
}
