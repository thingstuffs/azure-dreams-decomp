#include "shared/audio_commands.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
/* Zu actor spawning, action dispatch, movement, and cylindrical effects. */
#include "dungeon/actor.h"
#include "engine/cd.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/monster_ids.h"
#include "dungeon/monster/zu.h"
void *(*const dungeon_fa7000_entry)(s16,s16,s16,s16) = spawn_zu_actor;
void (*const dungeon_fa7000_update)(void *,void *,void *) = update_bank_actor_movement;
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/position_views.h"

typedef struct S_80F87000_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void * unk_10;
} S_80F87000_0;   /* obj in func_80170880 */

typedef struct S_80F87000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F87000_1;   /* work in func_80170880 */

   /* part_a in func_80170880 */

typedef struct S_80F87000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80F87000_3;   /* part_b in func_80170880 */

typedef struct S_80F87000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x3];
    s16 unk_A0;
} S_80F87000_4;   /* actor in func_80170880 */

extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();

extern u8 zu_frame_set_1[];

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
/* Creates Zu with default frames at D_80174AD4, applies spawn flags, and attempts valid tile placement. */
void *spawn_zu_actor(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    void *work = 0;
    void *obj;
    SignedHeightView *part_a;
    S_80F87000_3 *part_b;
    S_80F87000_4 *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;
    register void *call_a0;
    void *call_a1;

    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80F87000_0 *)obj)->unk_10 = update_bank_actor_movement;
        ((S_80F87000_1 *)work)->unk_13 = MONSTER_ZU;
        register_node(obj, project_sprite_chain);

        part_a = ((S_80F87000_0 *)obj)->unk_08;
        part_a->unk_0A = saved_spawn;
        part_b = ((S_80F87000_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = work;
        part_b->unk_2C = zu_default_frames;
        part_b->unk_24 = saved_kind_id;

        if (kind == 1) {
            left = ((S_80F87000_1 *)work)->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            right = ((S_80F87000_1 *)work)->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((S_80F87000_1 *)work)->unk_14 = left;
            ((S_80F87000_1 *)work)->unk_1C = right;
        } else if (kind >= 2) {
            left = ((S_80F87000_1 *)work)->unk_14 | ACTOR_CLASS_ENABLED;
            right = ((S_80F87000_1 *)work)->unk_1C | ACTOR_PLAYER_SIDE;
            ((S_80F87000_1 *)work)->unk_14 = left;
            ((S_80F87000_1 *)work)->unk_1C = right;
        } else if (((flags & ~3) << 16) == 0) {
            if (!(((S_80F87000_1 *)work)->unk_14 & ACTOR_RESIST_SLEEP)) {
                call_a1 = part_a;
                left = generate_random_value();
                call_a0 = obj;
                if (left & 1) {
                    ((S_80F87000_1 *)work)->unk_1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = zu_frame_set_1;
                }
            }
        }
        call_a0 = obj;
        initialize_actor_sprite_and_animation(call_a0, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = update_bank_actor_state;
        ((S_80F87000_1 *)work)->unk_1C |= 0x40000;
        actor->unk_A0 = 0;
        actor->unk_92 = -0x30;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_trail_views.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void select_indirect_table_entry(void *, u8, s8);
extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);
extern void apply_monster_koyaw_data(s32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern Callback zu_callbacks[];

   /* arg1 in update_bank_actor_movement */

typedef struct S_80170A70_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170A70_1;   /* arg2 in update_bank_actor_movement */

typedef struct S_80170A70_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170A70_2;   /* object in update_bank_actor_movement */

/* Update entity behavior, movement, sprite facing, and ground-relative height. */
void update_bank_actor_movement(void *entity, void *motion_arg, void *sprite_arg)
{
    S_80170A70_2 *object = entity;
    Callback paused_callback;
    Callback update_callback;
    s16 state_or_facing;
    s16 ground_height;
    s32 ground_delta;
    s16 facing;
    s32 bob_offset;
    u16 sprite_flags;
    u16 visibility_flags;
    u32 object_height;

    bob_offset = 0;
    if (g_dungeon_status.flags & 0x2000) {
        paused_callback = (*(Callback *)((u8 *)entity + (0x8C)));
        if (paused_callback == (Callback)update_bank_actor_state) {
            paused_callback(entity, motion_arg, sprite_arg, entity);
            return;
        }
        (*(u8 *)((u8 *)entity + (0x71))) &= 0x7F;
        return;
    }

    state_or_facing = (s8)(*(u8 *)((u8 *)entity + (0x6D)));
    if (refresh_actor_facing_and_lifecycle(entity, motion_arg, sprite_arg, entity) != 0) {
        return;
    }

    update_callback = (*(Callback *)((u8 *)entity + (0x8C)));
    if (update_callback != 0) {
        update_callback(entity, motion_arg, sprite_arg, entity);
    }
    zu_callbacks[(*(u8 *)((u8 *)entity + (0x9A)))](entity, motion_arg, sprite_arg, entity);
    if ((s16)state_or_facing != (*(s8 *)((u8 *)entity + (0x6D)))) {
        try_move_actor_to_valid_position(entity, motion_arg, sprite_arg, entity);
    }

    ((TrailMotion *)motion_arg)->unk_00.unk_00 += ((TrailMotion *)motion_arg)->unk_0C;
    ((TrailMotion *)motion_arg)->unk_04.unk_04 += ((TrailMotion *)motion_arg)->unk_10;

    if (!((*(s32 *)((u8 *)entity + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
        ((TrailMotion *)motion_arg)->unk_14 += (*(s8 *)((u8 *)entity + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)entity + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)entity + (0x9D))) = 0;
    }
    (*(s32 *)((u8 *)entity + (0x90))) += ((TrailMotion *)motion_arg)->unk_14;
    sprite_flags = ((S_80170A70_1 *)sprite_arg)->unk_14;

    if (!(sprite_flags & 0x8000)) {
        facing = ((g_game_work.view.camera_rotation.parts.viewAngle + object->unk_2A + 0x100) >> 9) & 7;
        state_or_facing = facing;
        if ((*(s16 *)((u8 *)entity + (0x94))) != state_or_facing) {
            select_indirect_table_entry(sprite_arg,
                ((u8 *)((S_80170A70_1 *)sprite_arg)->unk_2C)[state_or_facing],
                ((S_80170A70_1 *)sprite_arg)->unk_04);
            (*(s16 *)((u8 *)entity + (0x94))) = facing;
        }

        {

            if (dir_sprite_flag[state_or_facing] != 0) {
                ((S_80170A70_1 *)sprite_arg)->unk_14 |= 1;
            } else {
                ((S_80170A70_1 *)sprite_arg)->unk_14 &= 0xFFFE;
            }
        }

        if ((*(u8 *)((u8 *)entity + (0x9A))) != 8) {
            apply_monster_koyaw_data(object->unk_1C, (u8 *)sprite_arg + 0xC);
        }

        if (!(object->unk_1C & 0x20)) {
            if (!(((S_80170A70_1 *)sprite_arg)->unk_14 & 0x40)) {
                advance_sprite_animation_and_textures(sprite_arg);
            }
        } else {
            ((S_80170A70_1 *)sprite_arg)->unk_14 |= 0x7000;
            object->unk_1C &= 0xFFFBFFFF;
        }

        object->unk_1C &= 0xF7FFFFFF;
        if (object->unk_1C & 0x40000) {
            if (!(((S_80170A70_1 *)sprite_arg)->unk_14 & 0x40)) {
                {
                    s32 bob_wave = rsin(
                        ((*(s16 *)((u8 *)entity + (0xA0))) << 12) / 40);
                    if ((*(u8 *)((u8 *)entity + (0x9A))) == 0x12) {
                        bob_offset = bob_wave >> 10;
                    } else {
                        bob_offset = bob_wave >> 9;
                    }
                }
                (*(s16 *)((u8 *)entity + (0xA0))) = ((*(s16 *)((u8 *)entity + (0xA0))) + 1) % 40;
            }

            if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
                ground_height = (s16)(sample_terrain_surface_height(
                    ((TrailMotion *)motion_arg)->unk_00.unk_02.unk_02, ((TrailMotion *)motion_arg)->unk_04.unk_06.unk_06,
                    (s16)(object->unk_88.u - 0x20)) -
                    object->unk_88.u);
                if ((*(s16 *)((u8 *)entity + (0x92))) > ground_height - 0x30) {
                    (*(s16 *)((u8 *)entity + (0x92))) =
                        (u16)(*(s16 *)((u8 *)entity + (0x92))) - 8;
                } else if (ground_height - 0x3A > (*(s16 *)((u8 *)entity + (0x92)))) {
                    (*(s16 *)((u8 *)entity + (0x92))) =
                        (u16)(*(s16 *)((u8 *)entity + (0x92))) + 8;
                }
            }
        } else {

            (*(s16 *)((u8 *)entity + (0xA0))) = 0;
            if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {

                ground_delta = (s16)sample_terrain_surface_height(
                    ((TrailMotion *)motion_arg)->unk_00.unk_02.unk_02, ((TrailMotion *)motion_arg)->unk_04.unk_06.unk_06,
                    (s16)(object->unk_88.u - 0x20)) - object->unk_88.s;
                if ((*(s16 *)((u8 *)entity + (0x92))) > ground_delta) {
                    (*(s16 *)((u8 *)entity + (0x92))) = ground_delta;
                    (*(u8 *)((u8 *)entity + (0x9D))) = 0;
                    ((TrailMotion *)motion_arg)->unk_14 = 0;
                    object->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        if (sprite_flags & 0x800) {
            ((S_80170A70_1 *)sprite_arg)->unk_14 = sprite_flags & 0x8FFF;
        } else {
            ((S_80170A70_1 *)sprite_arg)->unk_14 = sprite_flags | 0x7000;
        }
        object->unk_1C &= 0xF7FFFFFF;

        if (!(object->unk_1C & 0x40000)) {
            (*(s16 *)((u8 *)entity + (0xA0))) = 0;
            (*(s16 *)((u8 *)entity + (0x92))) = (u16)(*(s16 *)((u8 *)entity + (0x92))) - bob_offset;
            bob_offset = 0;
            if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {

                ground_delta = (s16)sample_terrain_surface_height(
                    ((TrailMotion *)motion_arg)->unk_00.unk_02.unk_02, ((TrailMotion *)motion_arg)->unk_04.unk_06.unk_06,
                    (s16)(object->unk_88.u - 0x20)) - object->unk_88.s;
                if ((*(s16 *)((u8 *)entity + (0x92))) > ground_delta) {
                    (*(s16 *)((u8 *)entity + (0x92))) = ground_delta;
                    (*(u8 *)((u8 *)entity + (0x9D))) = 0;
                    ((TrailMotion *)motion_arg)->unk_14 = 0;
                    object->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(((S_80170A70_1 *)sprite_arg)->unk_14 & 0x40)) {
                {
                    s32 bob_wave = rsin(
                        ((*(s16 *)((u8 *)entity + (0xA0))) << 12) / 40);
                    if ((*(u8 *)((u8 *)entity + (0x9A))) == 0x12) {
                        bob_offset = bob_wave >> 10;
                    } else {
                        bob_offset = bob_wave >> 9;
                    }
                }
                (*(s16 *)((u8 *)entity + (0xA0))) = ((*(s16 *)((u8 *)entity + (0xA0))) + 1) % 40;
            }

            if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
                ground_height = (s16)(sample_terrain_surface_height(
                    ((TrailMotion *)motion_arg)->unk_00.unk_02.unk_02, ((TrailMotion *)motion_arg)->unk_04.unk_06.unk_06,
                    (s16)(object->unk_88.u - 0x20)) -
                    object->unk_88.u);
                if ((*(s16 *)((u8 *)entity + (0x92))) > ground_height - 0x30) {
                    (*(s16 *)((u8 *)entity + (0x92))) =
                        (u16)(*(s16 *)((u8 *)entity + (0x92))) - 8;
                } else if (ground_height - 0x3A > (*(s16 *)((u8 *)entity + (0x92)))) {
                    (*(s16 *)((u8 *)entity + (0x92))) =
                        (u16)(*(s16 *)((u8 *)entity + (0x92))) + 8;
                }
            }
        }

        (*(s16 *)((u8 *)entity + (0xA0))) = 0;
    }

    if (object->unk_1C & 0x40000000) {
        object->unk_1C &= 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (((S_80170A70_1 *)sprite_arg)->unk_24 << 6) | 0x20,
            (((S_80170A70_1 *)sprite_arg)->unk_25 << 6) | 0x20,
            (s16)(object->unk_88.u - 0x20));
        if (ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + (0x92))) =
                (u16)(*(s16 *)((u8 *)entity + (0x92))) +
                (object->unk_88.u - ground_height);
            object->unk_88.u = ground_height;
        }
    }

    ((TrailMotion *)motion_arg)->unk_0A =
        object->unk_88.u + (u16)(*(s16 *)((u8 *)entity + (0x92))) + bob_offset;
    ((S_80170A70_1 *)sprite_arg)->unk_14 |= 0x40;
}

#include "dungeon/monster/zu.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171138_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_80171138_0;   /* arg0 in update_bank_actor_state */

   /* arg3 in update_bank_actor_state */

extern s8 find_active_rect_containing_point(u8, u8);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern u8 D_80174ADC[];
extern u8 D_80174AEC[];
extern u8 zu_action_direction_frames[];
extern u8 zu_frame_set_1[];

/* Updates actor behavior, animation, and facing from its status and dungeon state. */
/* Selects Zu's movement, attacks, spells, and turn processing, then maintains its idle frames and facing
 * near the player. */
void update_bank_actor_state(void *actor_in, void *context_in, void *sprite_in, void *stats_in)
{
    void *actor;
    void *context;
    SpriteFrameState *sprite;
    ActorUnsignedFlagsView *stats;
    s32 angle_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_state;
    u32 dungeon_flags = g_dungeon_status.flags;

    actor = actor_in;
    context = context_in;
    sprite = sprite_in;
    stats = stats_in;

    if (dungeon_flags & 0x1000) {
        ((S_80171138_0 *)actor)->unk_9A = 0xE;
        advance_bank_actor_path(actor_in, context_in);
        return;
    }

    if (stats->unk_25 == 0) {
        advance_actor_pending_action(actor, context, sprite, stats);
        if (sprite->frameTable == zu_frame_set_1) {
            return;
        }
        sprite->frameTable = zu_action_direction_frames;
        select_sprite_entry(sprite,
            zu_action_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + stats->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (stats->unk_1C & 0x200) {
        if (sprite->frameTable == zu_frame_set_1) {
            ((S_80171138_0 *)actor)->unk_9A = 0xD;
            ((S_80171138_0 *)actor)->unk_9B = 1;
            ((S_80171138_0 *)actor)->unk_8C = 0;
            stats->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, zu_action_direction_frames) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (stats->unk_1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, stats);
            return;
        }

        if (((S_80171138_0 *)actor)->unk_9A != 0xE) {
            ((S_80171138_0 *)actor)->unk_9A = 0xE;
        }

        if (sprite->frameTable != zu_default_frames) {
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            sprite->frameTable = zu_default_frames;
            select_sprite_entry(sprite,
                zu_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + stats->unk_2A + 0x100) >> 9) & 7],
                ((S_80171138_0 *)actor)->unk_A0);
        }

        stats->unk_1C |= 0x40000;
        ((S_80171138_0 *)actor)->unk_98 &= 0xFFF7;

        if (stats->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80174ADC) != 0) {
                return;
            }
        }

        if (stats->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, stats);
            ((S_80171138_0 *)actor)->unk_A0 = 0;
            update_bank_actor_sprite_state(actor, context, sprite, stats);
            return;
        }

        if ((can_entity_gain_level(stats) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, stats);
        }
    }

    tile_index = find_active_rect_containing_point(sprite->unk_24, sprite->unk_25);
    sprite->unk_26 = tile_index;

    if (stats->unk_6D > 0) {
        if (stats->unk_1C & 0x20) {
            update_actor_status_and_mp(stats);
            return;
        }
        if (!(*(u16 *)&sprite->unk_24 == reference_tile_object.tile_position.word)) {
            action_state = stats->unk_46;
            if (!(action_state & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(stats,
                            (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((complete_actor_jump_to_destination(actor, context, sprite, 0) << 16) == 0) {
                    return;
                }
                action_state = stats->unk_46 | 0x4000;
                stats->unk_46 = action_state;
            }

            if (action_state & 0x8000) {
                switch (stats->unk_46 & 0x3FFF) {
                case 9:
                    start_bank_actor_hit_reaction(actor, context, sprite, stats);
                    return;

                case 8:
                    if ((begin_bank_directional_effect(actor, context, sprite, stats) << 16) != 0) {
                        return;
                    }
                    initialize_bank_actor_action(actor, context, sprite, stats);
                    return;

                case 12:
                    update_actor_status_and_mp(stats);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    ActorRecord *player;
                    s16 facing_angle;

                    facing_angle = (s16)get_rounded_facing_and_rounding_flag(
                        sprite->unk_24, sprite->unk_25,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &angle_aux);
                    player = primary_actor_record;
                    stats->unk_2A = facing_angle;
                    if (player->unk_9A != 0x11) {
                        update_actor_status_and_mp(stats);
                        return;
                    }
                }

                case 1:
                case 2:
                case 3:
                    begin_actor_spell_action(actor, context, sprite, D_80174AEC, update_bank_actor_state);
                    return;

                case 4:
                case 10:
                case 11:
                default:
                    break;
                }
            }
        }
        select_bank_actor_movement(actor, context, sprite, stats);
        return;
    }

    status_flags = stats->unk_1C;
    if (status_flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (dungeon_rooms[tile_index].flags & 2) {
            return;
        }
    }
    if (status_flags & 0x430) {
        return;
    }

    {

        if ((test_neighbor_position_relation(
                sprite->unk_24, sprite->unk_25,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
            stats->unk_2A = (s16)get_rounded_facing_and_rounding_flag(
                sprite->unk_24, sprite->unk_25,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &angle_aux);
        }
    }
    return;
}

#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/actor_status.h"
#include "shared/sprite_frame_state.h"

typedef struct S_80171670_0 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171670_0;   /* arg3 in advance_bank_actor_path */

   /* arg2 in advance_bank_actor_path */

typedef struct S_80171670_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0x5];
    s16 unk_A0;
} S_80171670_2;   /* arg0 in advance_bank_actor_path */

   /* (u8 *)arg3 + ((S_80171670_0 *)arg3)->unk_8A.s in advance_bank_actor_path */

/* Advance the entity along its stored path and update its movement state. */
void advance_bank_actor_path(void *motion, s32 unused, void *entity, void *path_state)
{
    SpriteTableView *entity_view = entity;
    u8 *anim_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 cell_mask;

    if (((S_80171670_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if (((S_80171670_0 *)path_state)->unk_71.u <= ((S_80171670_0 *)path_state)->unk_8A.s) {
        return;
    }

    anim_table = entity_view->unk_2C;
    if (anim_table != zu_default_frames) {
        (*(u8 **)((u8 *)entity + 0x2C)) = zu_default_frames;
        select_sprite_entry(
            entity,
            zu_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80171670_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80171670_2 *)motion)->unk_A0 = 0;
    }

    old_x = entity_view->unk_24;
    old_y = entity_view->unk_25;
    cell_mask = 0x3000;
    if (((S_80171670_0 *)path_state)->unk_1C.s & 0x2000) {
        cell_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, cell_mask);

    entity_view->unk_24 =
        ((ActorStatusBytesView *)((u8 *)path_state + ((S_80171670_0 *)path_state)->unk_8A.s))->unk_74;
    entity_view->unk_25 =
        ((ActorStatusBytesView *)((u8 *)path_state + ((S_80171670_0 *)path_state)->unk_8A.s))->unk_7C;
    ((S_80171670_0 *)path_state)->unk_8A.u++;

    new_x = entity_view->unk_24;
    new_y = entity_view->unk_25;
    cell_mask = 0x3000;
    if (((S_80171670_0 *)path_state)->unk_1C.s & 0x2000) {
        cell_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, cell_mask);

    ((S_80171670_0 *)path_state)->unk_2A = (s16)get_rounded_facing_and_rounding_flag(
        old_x, old_y, entity_view->unk_24, entity_view->unk_25,
        (u8 *)motion + 0x98);
    ((S_80171670_0 *)path_state)->unk_1C.u |= 0x40000000;
    ((S_80171670_2 *)motion)->unk_9A = 0xF;
    (*(s32 *)((u8 *)motion + 0x8C)) = 0;

    if (g_dungeon_status.flags & 0x80) {
        ((S_80171670_2 *)motion)->unk_96 = 0;
        return;
    }

    ((S_80171670_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((S_80171670_0 *)path_state)->unk_71.u;
        if (step_count > 0) {
            ((S_80171670_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void update_actor_status_and_mp(void *);
extern void update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern void *find_adjacent_actor(void *, u8, u8);
extern s32 generate_random_value(void);
extern s16 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern void select_actor_route_target(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
extern s16 check_directional_move_and_terrain(s16, void *, void *, s32);
extern s16 actor_turn_angle_offsets[];

/* Selects a movement direction and updates the actor's position and movement state.
 * move_data: the movement record (turn flags at +0x98, turn side at +0x9C); position_data: the grid cell
 * the actor stands on; actor_data: the actor. */
void select_bank_actor_movement(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, ActorRecord *actor_data)
{
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;
    EntityRec *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_data->movement_queue_state >= 0) {
        if (((u8 *)&actor_data->unk_10)[2] >= 2 ||
            (s16)begin_bank_directional_effect(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            actor_data->action_flags = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, &move_data->unk_9C.as_s8);
    actor_flags = actor_data->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_data, position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y);
            blocker = (EntityRec *)current_angle;
            if (blocker != 0) {
                EntityRec *blocker_owner = (EntityRec *)((ObjectNodeHeader *)blocker - 1)->sprite;
                s16 target_angle = (s16)get_rounded_facing_and_rounding_flag(
                    position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                    blocker_owner->tileX, blocker_owner->tileY,
                    &move_data->unk_98);
                actor_data->facing = target_angle;
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
            if (!(actor_data->flags14 & 0x80000000)) {
                actor_data->flags14 |= 0x80000000;
                actor_data->facing += (generate_random_value() & 7) << 9;
            }
        } else {
            if (probe_directional_neighbor(actor_data, position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y, actor_data->facing) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((u8 *)&actor_data->unk_44)[1] + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (position_data->tile_position.parts.tile_x == (u16)target_x &&
                    position_data->tile_position.parts.tile_y == (u16)target_y) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }

                turn_data = (u8 *)&move_data->unk_98;
                target_angle = (s16)get_rounded_facing_and_rounding_flag(
                    position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                    (s16)target_x, (s16)target_y, (u16 *)turn_data);
                actor_data->facing = target_angle;
                if (check_directional_move_and_terrain(target_angle, position_data, actor_data, 0x20) <= 0) {
                    actor_data->facing = (s16)get_rounded_facing_and_rounding_flag(
                        position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, (u16 *)turn_data);
                }
                if ((s16)test_neighbor_position_relation(
                        position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    limit_detour = 1;
                }
            } else {
                select_actor_route_target((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                              &move_data->unk_98);
            }
        }
    } else if (position_data->room_index >= 0 &&
               dungeon_rooms[position_data->room_index].flags & 2) {
        select_actor_route_target((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                      &move_data->unk_98);
    } else if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
        current_angle = (s32)probe_directional_neighbor(actor_data, position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y, actor_data->facing);
        blocker = (EntityRec *)current_angle;
        if (blocker != 0 &&
            (blocker->flags1C & 0x2000) &&
            (s16)get_actor_height_difference(blocker, actor_data) < 0x81) {
            if (check_diagonal_side_height(
                    ((s16)*(u16 *)&actor_data->facing >> 9) & 0xFFFF,
                    position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                    (s16)((u16)actor_data->ground_height - 0x20)) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }

        if (actor_data->flags1C & ACTOR_PLAYER_AWARE) {
            TileObject *target_position = &reference_tile_object;
            actor_data->facing = (s16)get_rounded_facing_and_rounding_flag(
                position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y, &move_data->unk_98);
            if ((s16)test_neighbor_position_relation(
                    position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y) != 0) {
                if (get_actor_height_difference(primary_actor_record, actor_data) < 0x81) {
                    if (check_diagonal_side_height(
                            ((s16)*(u16 *)&actor_data->facing >> 9) & 0xFFFF,
                            position_data->tile_position.parts.tile_x,
                                position_data->tile_position.parts.tile_y,
                            (s16)((u16)actor_data->ground_height - 0x20)) != 0) {
                        actor_data->movement_queue_state &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            select_actor_route_target((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                          &move_data->unk_98);
        }
    }

    turn_index = 0;
    turn_table = actor_turn_angle_offsets;

    for (; turn_index < 8; turn_index++) {
        turn_flags = move_data->unk_98;
        current_angle = actor_data->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (check_directional_move_and_terrain(trial_angle, position_data, actor_data, 0x20) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_data->facing = trial_angle;
            /* remember the cell in the actor's trail of visited cells */
            ((u8 *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))[0x74] = position_data->tile_position.parts.tile_x;
            ((u8 *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))[0x7C] = position_data->tile_position.parts.tile_y;
            actor_data->movement_queue_state++;

            update_map_cell_flags_with_item_limit(
                position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                (actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (*(u16 *)&actor_data->facing >> 8) & 0xE;
                x_step += step_offset;
                position_data->tile_position.parts.tile_x += *x_step;
                position_data->tile_position.parts.tile_y += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags(
                position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                (actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&reference_tile_object.tile_position.parts.tile_x) != *(u16 *)&position_data->tile_position.parts.tile_x) {
            if ((s16)check_entity_relation(actor_data,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                return;
            }
        }

    }

    if (turn_index >= 8) {
        actor_data->movement_queue_state &= 0x7F;
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor_data);
        return;
    }

    {
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        move_data->unk_9C.as_u8 = position_data->room_index;
        actor_data->pending_turn_updates--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (actor_data->pending_turn_updates == 0) {
        actor_data->movement_queue_state &= 0x7F;
        return;
    }

    turn_index = sample_terrain_surface_height(
        (position_data->tile_position.parts.tile_x << 6) | 0x20,
        (position_data->tile_position.parts.tile_y << 6) | 0x20,
        (s16)((u16)actor_data->ground_height - 0x20));
    if (turn_index < 0x200) {
        actor_data->ground_height = turn_index;
    }
}

#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void prepare_directional_attack();
extern s32 try_claim_dungeon_action_slot();
extern s32 check_entity_interaction_compatibility();

/* Checks whether the actor can transition and starts its directional effect. */
s32 begin_bank_directional_effect(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->movement_queue_state;
    actor_flags &= 0x7F;
    actor->movement_queue_state = actor_flags;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_angle = probe_directional_neighbor(actor, sprite->unk_24, sprite->unk_25, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((ObjectNodeHeader *)actor - 1, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->unk_9A.as_u8 = 0x11;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        sprite->frameTable = zu_default_frames;
        select_sprite_entry(sprite, (zu_default_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}

#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"

void prepare_directional_attack();
s32 try_claim_dungeon_action_slot();
/* Initialize action state and directional animation when the entity status permits. */
void initialize_bank_actor_action(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite,
    EntityRec *entity) {
    entity->unk_71 &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((ObjectNodeHeader *)entity - 1, motion_param, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            select_sprite_entry(sprite,
                          *((u8 *)sprite->frameTable + (((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)),
                          0);
            entity->unk_6D--;
            prepare_directional_attack(entity, sprite, entity->facing, 1, 0);
            action_state->unk_98 |= 8;
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}

#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

s32 has_pending_dungeon_activity();
void update_actor_status_and_mp();
s32 relink_entity_and_clear_high_flag();
/* Update entity state and flags according to the state query result. */
/* Relinks Zu's state, updates movement or status as needed, and returns 1 only when dungeon activity
 * allows a new action. */
s32 complete_actor_jump_to_destination(ActorRecord *actor, void *primary_context, void *secondary_context, s32 force_move) {
    s16 state_type;
    s32 result;
    ActorRecord *entity = actor;   /* the copy is load-bearing: it changes the callee-save order */

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context, secondary_context, entity, 3, 6, entity->pad_9C);
    if (state_type < 0) return 0;
    if ((force_move << 0x10) != 0) {
        select_bank_actor_movement(entity, primary_context, secondary_context, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        entity->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        select_bank_actor_movement(entity, primary_context, secondary_context, entity);
        result = 0;
        return result;
    case 1:
        entity->movement_queue_state &= 0x7F;
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        entity->movement_queue_state &= 0x7F;
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    return result;
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_actor_movement_to_tile();


/* Select the bank actor callback when the resident checks succeed. */
void select_bank_resident_callback(BankActorState *state, s32 unused, SpriteFrameState *source, EntityRec *target) {
    if (update_actor_movement_to_tile() != 0) {
        spend_actor_mp(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 16) > 0) {
            state->callback = update_bank_actor_state;
            if (g_dungeon_status.flags & 0x80) {
                state->unk_92 = -0x20;
            }
        }
    } else if (g_dungeon_status.flags & 0x80) {
        state->unk_92 = -0x20;
    }
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"


extern s32 update_linked_actor_motion();
/* Select the bank actor callback when the resident checks succeed. */
void select_bank_actor_callback(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if ((update_linked_actor_motion(state, action, source, target) != 0) && ((check_actor_floor_trap(source, target) << 0x10) > 0)) {
        state->callback = update_bank_actor_state;
    }
}

#include "dungeon/monster/zu.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80172494_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172494_0;   /* arg3_reg in update_bank_staged_movement */

typedef struct S_80172494_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172494_1;   /* arg0 in update_bank_staged_movement */

typedef struct S_80172494_3 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172494_3;   /* arg1 in update_bank_staged_movement */

typedef struct S_80172494_4 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80172494_4;

typedef struct S_80172494_5 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u8 pad_1A[0x2E];
    s16 unk_48;
} S_80172494_5;

typedef struct S_80172494_7 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80172494_7;

typedef struct S_80172494_8 {
    u8 pad_00[0x3DE8];
    void * unk_3DE8;
} S_80172494_8;

extern s32 rand(void);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern u8 directional_effect_entries[];
extern void *actor_update_node_cursor;
extern u8 zu_frame_set_2[];

/* Updates a staged movement action, spawns particles, and restores the actor when finished. */
/* Animates Zu's backward windup and forward strike, emits particles while returning, then recenters and
 * spends MP. */
void update_bank_staged_movement(void *action, void *motion, SpriteFrameState *map_actor, void *actor_arg) {
    s32 direction_x;
    s32 direction_y;
    s32 setup_value;
    s32 result;
    s32 velocity;
    s32 actor_flags;
    s32 velocity_y;
    s32 direction_index;
    s32 delta_x;
    s32 delta_z;
    s32 random_value;
    s32 texture_word;
    s32 direction_index_2;
    s32 actor_base;
    s32 velocity_x;
    s32 velocity_z;
    s32 operand;
    s32 operand_4;
    s32 operand_3;
    s32 operand_2;
    s32 index;
    s32 state;
    void *particle_motion;
    SpriteFrameState *particle_sprite;
    void *particle;
    u8 *direction_x_table;
    u8 *direction_y_table;

    index = ((S_80172494_0 *)actor_arg)->unk_2A.s >> 8;
    setup_value = index & 0xE;
    direction_x_table = (u8 *)((s8 *)dir_step_x);
    direction_x_table += setup_value;
    direction_y_table = (u8 *)((s8 *)dir_step_y);
    direction_x = *(s16 *)direction_x_table;
    setup_value = (s32)(direction_y_table + setup_value);
    direction_y = *(s16 *)setup_value;
    state = ((S_80172494_1 *)action)->unk_9B;
    ((S_80172494_1 *)action)->unk_96.s = ((S_80172494_1 *)action)->unk_96.s - 1;

    switch (state) {
    case 0:
        if (map_actor->flags & 0x8000) {
            ((S_80172494_1 *)action)->unk_9B = 0xFF;
            map_actor->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor_arg, map_actor, ((S_80172494_0 *)actor_arg)->unk_2A.u, 1);
            return;
        }
        setup_value = 0xF7FFFFFF;
        operand = 0xFFFBFFFF;
        velocity = -direction_x;
        velocity <<= 18;
        ((S_80172494_3 *)motion)->unk_0C = velocity;
        velocity = -direction_y;
        velocity <<= 18;
        ((S_80172494_3 *)motion)->unk_10 = velocity;
        ((S_80172494_1 *)action)->unk_98 |= 8;
        actor_flags = ((S_80172494_0 *)actor_arg)->unk_1C;
        actor_flags &= setup_value;
        actor_flags &= operand;
        ((S_80172494_0 *)actor_arg)->unk_1C = actor_flags;
        ((S_80172494_1 *)action)->unk_96.s = 4;
        ((S_80172494_3 *)motion)->unk_14 = 0xFFFD0000;
        ((S_80172494_1 *)action)->unk_9B++;
        return;

    case 1:
        velocity_y = ((S_80172494_3 *)motion)->unk_14;
        ((S_80172494_3 *)motion)->unk_14 = velocity_y + (velocity_y >> 2);
        if (((S_80172494_1 *)action)->unk_96.u > 0) {
            return;
        }
        result = ((S_80172494_1 *)action)->unk_9B;
        ((S_80172494_1 *)action)->unk_96.s = 8;
        ((S_80172494_1 *)action)->unk_9B = result + 1;
        return;

    case 2:
        velocity_x = ((S_80172494_3 *)motion)->unk_0C;
        operand_3 = ((S_80172494_3 *)motion)->unk_10;
        ((S_80172494_3 *)motion)->unk_0C = velocity_x - (velocity_x >> 3);
        velocity_z = ((S_80172494_3 *)motion)->unk_14;
        ((S_80172494_3 *)motion)->unk_10 = operand_3 - (operand_3 >> 3);
        ((S_80172494_3 *)motion)->unk_14 = velocity_z - (velocity_z >> 3);
        if ((((S_80172494_1 *)action)->unk_96.u == 4) ||
            (map_actor->flags & 0x8000)) {
            ((S_80172494_3 *)motion)->unk_0C = 0;
            ((S_80172494_3 *)motion)->unk_10 = 0;
            ((S_80172494_3 *)motion)->unk_14 = 0;
            map_actor->frameTable = zu_frame_set_2;
            direction_index = (g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172494_0 *)actor_arg)->unk_2A.u + 0x100) >> 9;
            select_sprite_entry(map_actor, zu_frame_set_2[direction_index & 7], 0);
        }
        if (((S_80172494_1 *)action)->unk_96.u > 0) {
            return;
        }
        if (!(map_actor->flags & 0xE000)) {
            return;
        }
        ((S_80172494_1 *)action)->unk_96.s = 4;
        ((S_80172494_3 *)motion)->unk_0C = (direction_x << 18) + (direction_x << 17);
        ((S_80172494_3 *)motion)->unk_10 = (direction_y << 18) + (direction_y << 17);
        play_sound_if_enabled(0x80E);
        ((S_80172494_1 *)action)->unk_9B++;
        return;

    case 3:
        ((S_80172494_1 *)action)->unk_90 += 0x80000;
        ((S_80172494_3 *)motion)->unk_0C += direction_x << 18;
        ((S_80172494_3 *)motion)->unk_10 += direction_y << 18;
        if (((S_80172494_1 *)action)->unk_96.u > 0) {
            return;
        }
        play_sound_if_enabled(0x808);
        resolve_attack_damage_and_effects(actor_arg, map_actor, ((S_80172494_0 *)actor_arg)->unk_2A.u, 1);

        ((S_80172494_1 *)action)->unk_9B++;
        return;

    case 4:
        ((S_80172494_1 *)action)->unk_90 += 0x80000;
        if (!(map_actor->flags & 0xE000)) {
            return;
        }
        ((S_80172494_3 *)motion)->unk_14 = 0;
        ((S_80172494_1 *)action)->unk_98 &= 0xFFF7;
        ((S_80172494_0 *)actor_arg)->unk_1C |= 0x40000;
        ((S_80172494_0 *)actor_arg)->unk_1C |= ACTOR_GROUNDED;
        ((S_80172494_1 *)action)->unk_96.s = state;
        ((S_80172494_1 *)action)->unk_9B = 0xFF;
        return;

    case 0xFF:
        delta_x = map_actor->unk_24 << 6;
        operand = ((S_80172494_3 *)motion)->unk_02.s - 0x20;
        delta_x -= operand;
        delta_x = (delta_x << 15) >> 1;
        ((S_80172494_3 *)motion)->unk_0C = delta_x;
        delta_z = map_actor->unk_25 << 6;
        operand_2 = ((S_80172494_3 *)motion)->unk_06.s - 0x20;
        delta_z -= operand_2;
        ((S_80172494_3 *)motion)->unk_10 = (delta_z << 15) >> 1;
        if (!(map_actor->flags & 0x8000) &&
            (((S_80172494_1 *)action)->unk_96.u != 0)) {
            index = 9;
            do {
                particle = allocate_list_node(0x312, ((s32 *)&scene_object_list_anchor.next));
                if (particle != NULL) {
                    register_node(particle, project_sprite_chain);
                    particle_motion = (u8 *)particle + 0x20;
                    ((S_80172494_4 *)particle)->unk_10 = update_bank_effect_fade;
                    particle_sprite = ((S_80172494_4 *)particle)->unk_0C;
                    ((S_80172494_5 *)particle_motion)->unk_0C =
                        ((S_80172494_3 *)motion)->unk_02.u - (direction_x * 0x28);
                    ((S_80172494_5 *)particle_motion)->unk_0E =
                        ((S_80172494_3 *)motion)->unk_06.u - (direction_y * 0x28);
                    ((S_80172494_5 *)particle_motion)->unk_10 = ((S_80172494_3 *)motion)->unk_0A;
                    ((S_80172494_5 *)particle_motion)->unk_04 = rand() & 0xF;
                    ((S_80172494_5 *)particle_motion)->unk_06 = 0;
                    ((S_80172494_5 *)particle_motion)->unk_08 = (rand() & 0xF) + 8;
                    random_value = rand();
                    setup_value = 0xC00000;
                    ((S_80172494_5 *)particle_motion)->unk_14 = random_value;
                    operand = ((S_80172494_0 *)actor_arg)->unk_2A.s;
                    ((S_80172494_5 *)particle_motion)->unk_48 = 5;
                    ((S_80172494_5 *)particle_motion)->unk_18 = operand;
                    operand_4 = particle_sprite->flags;
                    particle_sprite->scale_y = 0x1000;
                    particle_sprite->scale_x = 0x1000;
                    particle_sprite->tpage_abr = 0x60;
                    particle_sprite->unk_00 = directional_effect_entries;
                    particle_sprite->flags = operand_4 | 0xC;
                    texture_word = ((S_80172494_7 *)directional_effect_entries)->unk_04;
                    setup_value |= 0xC0C0;
                    particle_sprite->unk_04 = 0;
                    particle_sprite->unk_05 = 0;
                    particle_sprite->color.word = setup_value;
                    particle_sprite->source = texture_word;
                }
                index--;
            } while (index >= 0);
        }
        if (!(map_actor->flags & 0xE000)) {
            return;
        }
        ((S_80172494_3 *)motion)->unk_10 = 0;
        ((S_80172494_3 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, map_actor->unk_24,
                      map_actor->unk_25);
        spend_actor_mp(actor_arg, 0x100);
        ((S_80172494_1 *)action)->unk_8C = update_bank_actor_state;
        g_dungeon_status.active_actor = 0;
        map_actor->frameTable = zu_default_frames;
        direction_index_2 = (g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172494_0 *)actor_arg)->unk_2A.u + 0x100) >> 9;
        select_sprite_entry(map_actor, zu_default_frames[direction_index_2 & 7], 0);
        advance_status_timers(actor_arg);
        if (((S_80172494_0 *)actor_arg)->unk_6D == 0) {
            ((S_80172494_0 *)actor_arg)->unk_46 &= 0x7FFF;
            return;
        }
        operand = (s32)((u8 *)&actor_update_node_cursor - 0x3DE8);
        actor_base = (s32)((u8 *)actor_arg - 0x20);
        ((S_80172494_8 *)((void *)operand))->unk_3DE8 = (void *)actor_base;
        return;

    default:
        return;
    }

    return;
}

#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
extern int abs(int);

extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_source_positioned_object(ObjectPosition *source_pos, s16 initial_value);

typedef struct S_80172A40_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_80172A40_0;   /* arg0 in update_bank_actor_targeted_action */

   /* the 0x14 bytes before target in update_bank_actor_targeted_action, addressed as target[-1] */

   /* record in update_bank_actor_targeted_action */

/* Updates the selected action's targeting, motion, and completion state. */
/* Starts a targeted Zu spell and source effect, eases its vertical offset toward -48, then restores idle
 * and status. */
void update_bank_actor_targeted_action(void *owner_input, ObjectPosition *motion_input, SpriteFrameState *actor_input, ActorRecord *object)
{
    s16 special;
    u8 *item_slot;
    s32 state;
    s32 slot_kind;
    s32 special_copy;
    u8 *item_entry;
    u8 *item_table;
    SpriteLinkPrefixView *target;
    MovingTile *target_record;
    s32 target_x;
    s32 abs_x;
    s32 abs_y;
    s32 target_y;
    s32 slot_index;
    s32 item_id;

    state = ((S_80172A40_0 *)owner_input)->unk_9B;
    special = 0;
    switch (state) {
    case 0:
        if (((u32)object->flags1C) & ACTOR_PLAYER_SIDE) {
            slot_index = (object->action_flags & ACTOR_ACTION_CODE_MASK) - 1;
            switch (slot_index) {
            case 6:
                special = 1;
                /* fall through */
            case 2:
                item_slot = (u8 *)object + 0xE;
                break;
            case 5:
                special = 1;
                /* fall through */
            case 1:
                item_slot = (u8 *)object + 0xB;
                break;
            case 4:
                special = 1;
                /* fall through */
            case 0:
                item_slot = (u8 *)object + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            slot_kind = object->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (slot_kind) {
            case 3:
                item_slot = (u8 *)object + 0xE;
                break;
            case 2:
                item_slot = (u8 *)object + 0xB;
                break;
            case 1:
                item_slot = (u8 *)object + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            ((S_80172A40_0 *)owner_input)->unk_98 &= 0xFF7F;

            special_copy = special;
            if (special_copy) {
                target = primary_actor_record;
                object->target = target;
                target_record = target[-1].unk_00;
                object->target_tile_x = target_record->unk_24;
                object->target_tile_y = target_record->unk_25;
            } else {
                item_table = item_action_definitions;
                item_id = *item_slot;
                item_entry = item_table + item_id * 20;
                if (item_entry[0x12] == 2) {
                    target = object->target;
                    if (target != 0) {
                        target_record = target[-1].unk_00;
                        object->target_tile_x = target_record->unk_24;
                        object->target_tile_y = target_record->unk_25;
                    }
                } else {
                    object->target = scan_actor_along_heading(
                        object, actor_input->unk_24, actor_input->unk_25,
                        object->facing, 0x10);

                    abs_x = abs(object->target_tile_x);
                    abs_y = abs(object->target_tile_y);
                    object->target_tile_x = abs_x;
                    object->target_tile_y = abs_y;
                }
            }

            if (create_actor_spell_effect(object, item_slot, special,
                              (u16 *)((u8 *)owner_input + 0x98)) == 0) {
                return;
            }
            actor_input->flags &= 0xF7FF;
            create_source_positioned_object(motion_input, 4);
            play_sound_if_enabled(0x703);
            ((S_80172A40_0 *)owner_input)->unk_96.u = 4;
            ((S_80172A40_0 *)owner_input)->unk_9B++;
            ((S_80172A40_0 *)owner_input)->unk_98 |= 8;
            (*(u32 *)&object->flags1C) &= ACTOR_GROUNDED_CLEAR_MASK;
            (*(u32 *)&object->flags1C) &= 0xFFFBFFFF;
            return;
        }

        motion_input->velocity_z = 0;
        motion_input->velocity_y = 0;
        motion_input->velocity_x = 0;
        set_record_integer_tile_center(motion_input, actor_input->unk_24, actor_input->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(object);
        (*(u8 *)&object->pending_turn_updates)--;
        ((S_80172A40_0 *)owner_input)->unk_8C = update_bank_actor_state;
        object->target_tile_y = 0;
        object->target_tile_x = 0;
        object->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            actor_input->flags |= 0x800;
            return;
        }
        actor_input->flags &= 0xF7FF;
        ((S_80172A40_0 *)owner_input)->unk_9B++;
                        /* fall through */

    case 2:
        ((S_80172A40_0 *)owner_input)->unk_92 +=
            (-0x30 - ((S_80172A40_0 *)owner_input)->unk_92) >> 3;
        ((S_80172A40_0 *)owner_input)->unk_96.u--;
        if (((S_80172A40_0 *)owner_input)->unk_96.s > 0) {
            if ((actor_input->flags & 0xE000) == 0) {
                return;
            }
        }
        ((S_80172A40_0 *)owner_input)->unk_98 |= 0x80;
        if ((actor_input->flags & 0xE000) == 0) {
            return;
        }

        motion_input->velocity_z = 0;
        motion_input->velocity_y = 0;
        motion_input->velocity_x = 0;
        set_record_integer_tile_center(motion_input, actor_input->unk_24, actor_input->unk_25);
        ((S_80172A40_0 *)owner_input)->unk_98 &= 0xFFF7;
        (*(u32 *)&object->flags1C) |= ACTOR_GROUNDED;
        (*(u32 *)&object->flags1C) |= 0x00040000;

        if (*(u8 **)&actor_input->frameTable != zu_default_frames) {
            (actor_input->frameTable) = zu_default_frames;
            select_sprite_entry(actor_input,
                          zu_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle +
                                       object->facing + 0x100) >> 9) & 7],
                          ((S_80172A40_0 *)owner_input)->unk_A0);
        }

        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        actor_input->flags &= 0xF7FF;
        ((S_80172A40_0 *)owner_input)->unk_8C = update_bank_actor_state;
        advance_status_timers(object);
        if (object->pending_turn_updates > 0) {
            (*(u8 *)&object->pending_turn_updates)--;
        }
        object->target_tile_y = 0;
        object->target_tile_x = 0;
        object->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        break;
    default:
        return;
    }
}

#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172F00_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 p; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172F00_0;   /* arg0 in restore_bank_actor_tile */

extern void set_record_integer_tile_center();
extern void begin_actor_display_action();
extern void apply_clamped_actor_value_delta();

extern u8 D_80174ADC[];

/* Updates staged directional motion, then restores the entity to its tile and animation. */
void restore_bank_actor_tile(void *action, ObjectPosition *motion, void *sprite, EntityRec *entity)
{
    s16 timer_signed;
    s32 direction;
    s32 velocity_x;
    s32 velocity_y;
    s32 rounded_vx;
    s32 rounded_vy;
    s32 tracked_entity;
    s32 state;
    u16 timer;
    s32 timer_wide;

    state = ((S_80172F00_0 *)action)->unk_9B;
    direction = (entity->unk_6A >> 9) & 7;

    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            motion->velocity_z = 0xFFFD0000;
            begin_actor_display_action(action, motion, sprite, D_80174ADC);
            return;
        }

        {
            u32 mask_bit_27 = 0xF7FFFFFF;
            u32 mask_bit_18 = 0xFFFBFFFF;
            u32 entity_flags;
            u16 action_flags;

            motion->velocity_x =
                ((s16 *)((s8 *)dir_step_x))[direction] << 18;
            motion->velocity_y =
                ((s16 *)((s8 *)dir_step_y))[direction] << 18;
            motion->velocity_z = 0x20000;

            action_flags = ((S_80172F00_0 *)action)->unk_98;
            action_flags |= 8;
            ((S_80172F00_0 *)action)->unk_98 = action_flags;
            entity_flags = ((u32)entity->flags1C);
            entity_flags &= mask_bit_27;
            entity_flags &= mask_bit_18;
            entity->flags1C = entity_flags;
        }

        ((S_80172F00_0 *)action)->unk_9B = ((S_80172F00_0 *)action)->unk_9B + 1;
        timer_signed = -1;
        if (((u32)entity->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer_signed = 8;
        }
        ((S_80172F00_0 *)action)->unk_96.s = timer_signed;

        velocity_x = motion->velocity_x;
        rounded_vx = velocity_x;
        if (velocity_x < 0) {
            rounded_vx = velocity_x + 3;
        }
        velocity_y = motion->velocity_y;
        motion->velocity_x = velocity_x - (rounded_vx >> 2);
        rounded_vy = velocity_y;
        motion->velocity_y = velocity_y - (rounded_vy / 4);
        return;
    case 1:
        motion->velocity_x -=
            ((s16 *)((s8 *)dir_step_x))[direction] << 15;
        motion->velocity_y -= ((s16 *)((s8 *)dir_step_y))[direction] << 15;

        timer_signed = ((S_80172F00_0 *)action)->unk_96.s;
        timer_wide = ((S_80172F00_0 *)action)->unk_96.p;
        if (timer_signed > 0) {
            ((S_80172F00_0 *)action)->unk_96.p = timer_wide - 1;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((S_80172F00_0 *)action)->unk_96.p = 0;
        }

        if (((S_80172F00_0 *)action)->unk_96.s != 0) {
            return;
        }
        if (entity->unk_28 == 0) {
            ((S_80172F00_0 *)action)->unk_9B = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            motion->velocity_z = 0xFFFD0000;
            begin_actor_display_action(action, motion, sprite, D_80174ADC);
        } else {
            ((S_80172F00_0 *)action)->unk_96.s = 5;
            ((S_80172F00_0 *)action)->unk_9B = ((S_80172F00_0 *)action)->unk_9B + 1;
        }
        return;
    case 2:
        motion->velocity_z = 0xFFFD0000;
        if (((S_80172F00_0 *)action)->unk_96.s != 0) {
            s32 tile_coord;
            s32 position_offset;

            tile_coord = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
            position_offset = motion->x.w.i;
            position_offset -= 0x20;
            motion->velocity_x = (tile_coord - position_offset) << 15;
            tile_coord = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
            position_offset = motion->y.w.i;
            position_offset -= 0x20;
            motion->velocity_y = (tile_coord - position_offset) << 15;
        }

        timer = ((S_80172F00_0 *)action)->unk_96.p - 1;
        ((S_80172F00_0 *)action)->unk_96.p = timer;
        if ((timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        ((S_80172F00_0 *)action)->unk_98 &= 0xFFF7;
        entity->flags1C |= ACTOR_GROUNDED;
        entity->flags1C |= 0x00040000;
        (*(u8 **)((u8 *)sprite + 0x2C)) = zu_default_frames;
        select_sprite_entry(
            sprite,
            zu_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        ((S_80172F00_0 *)action)->unk_8C = update_bank_actor_state;
        break;
    default:
        return;
    }
}

#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_80173294_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_80173294_0;   /* p3 in slow_directional_motion */

typedef struct S_80173294_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80173294_1;   /* p1 in slow_directional_motion */

typedef struct S_80173294_2 {
    u8 pad_00[0x96];
    union { s16 s16; u8 u8; u16 u16; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173294_2;   /* p0 in slow_directional_motion */

typedef struct S_80173294_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173294_3;   /* p2 in slow_directional_motion */

extern void unlink_entity_node();
extern void distribute_experience_and_report_gains();
extern void detach_record_and_update_slot_state();

/* Advance the object removal animation, fade its sprite, and release it when finished. */
void slow_directional_motion(void *effect_data, void *motion_data, void *sprite_data, void *object_data) {
    s32 direction_offset;
    s32 direction_x;
    u8 *direction_y_table;
    u8 *direction_y_table_2;
    s32 direction_y;
    s32 motion_step;
    s32 state;
    s32 motion_value;
    s32 is_low_state;

    direction_offset = (((S_80173294_0 *)object_data)->unk_6A >> 8) & 0xE;
    direction_x = *(s16 *)((u8 *)((u8 *)dir_step_x) + direction_offset);
    direction_y = *(s16 *)((u8 *)((u8 *)dir_step_y) + direction_offset);
    motion_step = 0xC000;
    motion_value = (((S_80173294_1 *)motion_data)->unk_14) + motion_step;
    ((S_80173294_1 *)motion_data)->unk_14 = motion_value;
    state = ((S_80173294_2 *)effect_data)->unk_9B;

    switch (state) {
    case 0:
        state = 0xFFFE0000;
        state |= 0x8000;
        motion_value = direction_x << 16;
        ((S_80173294_1 *)motion_data)->unk_0C = motion_value;
        motion_value = direction_y << 16;
        (*(s32 *)((u8 *)motion_data + 0x10)) = motion_value;
        (*(s32 *)((u8 *)motion_data + 0x14)) = state;
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0)
            return;
        ((S_80173294_2 *)effect_data)->unk_9B++;
                        /* fall through */
    case 1:
    {
        s32 flags;
        s32 object_flags;
        u16 sprite_x;
        u16 sprite_flags;
        u16 status;
        register s32 clear_bit_27;
        s32 clear_bit_18;

        flags = ((S_80173294_0 *)object_data)->unk_14;
        if (flags & 0x4000) {
            if (!(flags & 0x20000000))
                announce_familiar_defeat(object_data);
        }
        play_sound_if_enabled(0x805);
        clear_bit_27 = 0xF7FFFFFF;
        status = ((S_80173294_2 *)effect_data)->unk_98;
        clear_bit_18 = 0xFFFBFFFF;
        status |= 8;
        ((S_80173294_2 *)effect_data)->unk_98 = status;
        object_flags = ((S_80173294_0 *)object_data)->unk_1C;
        object_flags &= clear_bit_27;
        object_flags &= clear_bit_18;
        ((S_80173294_0 *)object_data)->unk_1C = object_flags;

        ((S_80173294_3 *)sprite_data)->unk_10 = 0x60;
        sprite_x = ((S_80173294_3 *)sprite_data)->unk_12;
        sprite_flags = ((S_80173294_3 *)sprite_data)->unk_14;
        sprite_x -= 0x80;
        sprite_flags |= 0xC;
        ((S_80173294_3 *)sprite_data)->unk_12 = sprite_x;
        ((S_80173294_3 *)sprite_data)->unk_14 = sprite_flags;
        ((S_80173294_2 *)effect_data)->unk_9B++;
        return;
    }
    case 2:
        if (!(((S_80173294_3 *)sprite_data)->unk_14 & 0x6000))
            return;
        ((S_80173294_2 *)effect_data)->unk_96.s16 = 0x80;
        ((S_80173294_2 *)effect_data)->unk_9B++;
        return;
    case 3:
    {
        u8 brightness;
        u16 fade_level;
        s32 linked_object;
        s32 flags;
        s32 tile_mask;
        u8 tile_x;
        u8 tile_y;

        ((S_80173294_0 *)object_data)->unk_1C |= 0x10000000;
        brightness = ((S_80173294_2 *)effect_data)->unk_96.u8;
        ((S_80173294_3 *)sprite_data)->unk_0E = brightness;
        ((S_80173294_3 *)sprite_data)->unk_0D = brightness;
        ((S_80173294_3 *)sprite_data)->unk_0C = brightness;
        fade_level = ((S_80173294_2 *)effect_data)->unk_96.u16 - 0x10;
        ((S_80173294_2 *)effect_data)->unk_96.u16 = fade_level;
        if ((s16)fade_level >= 0x10)
            return;
        linked_object = ((s32)g_dungeon_status.pending_display_owner);
        if (linked_object == (s32)(object_data - 0x20))
            g_dungeon_status.pending_display_owner = linked_object & 0x7FFFFFFF;
        distribute_experience_and_report_gains(object_data);
        detach_record_and_update_slot_state(object_data);
        flags = ((S_80173294_0 *)object_data)->unk_1C;
        tile_x = ((S_80173294_3 *)sprite_data)->unk_24;
        tile_y = ((S_80173294_3 *)sprite_data)->unk_25;
        tile_mask = 0x3000;
        if (flags & 0x2000)
            tile_mask = 0x300;
        update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
        unlink_entity_node(object_data);
        (*(u16 *)((u8 *)object_data + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
        return;
    default:
        return;
    }
}

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_actor_hop_and_shrink(void *, s32,struct SpriteFrameState *, void *);

/* Forward all four bank callback arguments to the resident handler. */
void forward_bank_actor_callback_a(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    update_actor_hop_and_shrink(state, action, source, target);
}

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



/* Forward all four bank callback arguments to the resident handler. */
void forward_bank_actor_callback_b(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    advance_actor_removal(state, action, source, target);
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_actor_hop_and_grow();
/* Restore the bank actor callback after the resident state check succeeds. */
void restore_bank_actor_callback_a(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (update_actor_hop_and_grow(state, action, source, target) != 0) {
        state->callback = update_bank_actor_state;
    }
}

#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/dungeon_trail_views.h"

typedef struct S_8017357C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x4];
    u16 unk_A0;
} S_8017357C_0;   /* arg0 in handle_actor_action_effects */

   /* counter_base in handle_actor_action_effects */

extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern s32 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern u8 zu_frame_set_1[];
extern u8 D_80174B04[];

/* Updates actor state, animation, and transition counters. */
void handle_actor_action_effects(void *controller, EntityRec *motion, void *sprite, ActorRecord *actor)
{
    s32 actor_flags;
    s32 state;

    state = ((S_8017357C_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(void **)((u8 *)sprite + 0x2C)) = zu_frame_set_1;
        select_sprite_entry(sprite,
            zu_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((TrailHeightView *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A = ((TrailHeightView *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A
        - 1;
        ((S_8017357C_0 *)controller)->unk_9B++;
        return;
    case 1:
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) == 0) {
            (*(void **)((u8 *)sprite + 0x2C)) = D_80174B04;
            select_sprite_entry(sprite,
                D_80174B04[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            actor_flags = actor->flags1C | 0x40000;
            actor->flags1C = actor_flags;
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
                actor->flags1C = actor_flags & ~0x200;
                ((S_8017357C_0 *)controller)->unk_8C = update_bank_actor_state;
            } else {
                ((S_8017357C_0 *)controller)->unk_96.s = 3;

                ((TrailHeightView *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A =
                    ((TrailHeightView *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A + 1;
                ((S_8017357C_0 *)controller)->unk_9B++;
            }
            return;
        }
        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if (actor->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, motion, sprite, 0) != 0) {
                return;
            }
        }
        if (actor->mp == 0) {
            if (g_dungeon_status.flags & 0x2008) {
                return;
            }
            advance_actor_pending_action(controller, motion, sprite, actor);
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            return;
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(controller, motion, sprite, actor);
            return;
        }
        if (actor_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, motion, sprite, actor);
            ((S_8017357C_0 *)controller)->unk_A0 = 0;
            update_bank_actor_sprite_state(controller, motion, sprite, actor);
            return;
        }
        if (actor->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            ActorRecord *owner = primary_actor_record;

            if ((check_entity_relation(actor,
                    (u8 *)owner->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_mp(actor);
        on_actor_status_updated(actor);
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
            TileObject *origin = &reference_tile_object;
            s8 tile = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;

            if (((tile == origin->room_index) && (tile >= 0)) ||
                ((s16)get_tile_chebyshev_distance(origin, sprite) < 2)) {
                if (!(generate_random_value() & 7)) {
                    clear_slots_of_type(actor, STATUS_SLEEP);
                }
            }
        }
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
            return;
        }
        (*(void **)((u8 *)sprite + 0x2C)) = D_80174B04;
        select_sprite_entry(sprite,
            D_80174B04[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        actor_flags = actor->flags1C | 0x40000;
        actor->flags1C = actor_flags;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            actor->flags1C = actor_flags & ~0x200;
            ((S_8017357C_0 *)controller)->unk_8C = update_bank_actor_state;
        } else {
            ((S_8017357C_0 *)controller)->unk_96.s = 3;

            ((TrailHeightView *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A =
                ((TrailHeightView *)(u8 *)&g_dungeon_status.turn_scale)->unk_0A + 1;
            ((S_8017357C_0 *)controller)->unk_9B++;
        }
        return;
    case 2:
        ((S_8017357C_0 *)controller)->unk_96.s--;
        if (((S_8017357C_0 *)controller)->unk_96.u <= 0) {
            motion->flags14 = 0xFFF00000;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        ((S_8017357C_0 *)controller)->unk_A0 = 0;
        (*(void **)((u8 *)sprite + 0x2C)) = zu_default_frames;
        select_sprite_entry(sprite,
            zu_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        actor->flags1C &= ~ACTOR_ASLEEP;
        ((S_8017357C_0 *)controller)->unk_8C = update_bank_actor_state;
    }
}

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/position_views.h"

extern s32 has_pending_actor_or_turn_action(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern u8 zu_action_direction_frames[];
extern u8 zu_frame_set_1[];

typedef struct S_801739F8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_801739F8_0;   /* arg0 in advance_bank_actor_animation */

   /* global in advance_bank_actor_animation */

/* Advances entity animation states and updates the shared activity count. */
void advance_bank_actor_animation(void *controller, void *context, void *sprite, void *entity)
{
    void *saved_context;
    register void *dungeon_state;
    void *saved_entity;
    u8 state;
    s32 direction;

    saved_context = context;
#define controller controller
#define context saved_context
#define sprite sprite

    state = ((S_801739F8_0 *)controller)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        DungeonGlobalStatus *activity_counts;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        activity_counts = &g_dungeon_status;
        (*(u16 *)&activity_counts->activity_counts.parts.pending_action_count)--;
        (*(void **)((u8 *)sprite + 0x2C)) = zu_frame_set_1;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite, zu_frame_set_1[direction & 7], 0);
        ((S_801739F8_0 *)controller)->unk_9B++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register DungeonGlobalStatus *activity_counts;

            (*(void **)((u8 *)sprite + 0x2C)) = zu_action_direction_frames;
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            select_sprite_entry(sprite, zu_action_direction_frames[direction & 7], 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            activity_counts = &g_dungeon_status;
            (*(u16 *)&activity_counts->activity_counts.parts.pending_action_count)++;
            ((S_801739F8_0 *)controller)->unk_9B++;
            return;
        }

        dungeon_state = &g_dungeon_status.turn_scale;
        if (((UnsignedPositionXZView *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((EntityRec *)entity)->unk_64 != 0) &&
            begin_ready_actor_directional_action(controller, context, sprite, 0)) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(controller, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(controller, context, sprite, entity);
            ((S_801739F8_0 *)controller)->unk_A0 = 0;
            update_bank_actor_sprite_state(controller, context, sprite, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            ActorRecord *owner = primary_actor_record;

            if ((check_entity_relation(entity,
                    (u8 *)owner->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (*(void **)((u8 *)sprite + 0x2C)) = zu_action_direction_frames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite, zu_action_direction_frames[direction & 7], 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((UnsignedPositionXZView *)dungeon_state)->unk_0A++;

        ((S_801739F8_0 *)controller)->unk_9B++;
        return;

    case 2:
    {
        DungeonGlobalStatus *activity_counts;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        activity_counts = &g_dungeon_status;
        (*(u16 *)&activity_counts->activity_counts.parts.pending_action_count)--;
        ((EntityRec *)entity)->flags1C &= ~(ACTOR_MP_EMPTY | ACTOR_ASLEEP);
        ((S_801739F8_0 *)controller)->unk_8C = update_bank_actor_state;
        return;
    }

    default:
        return;
    }
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_actor_transform_from_parent(BankActorState *, s32, SpriteFrameState *, ActorRecord *);

extern u8 zu_default_frames[9];
extern u8 zu_frame_set_1[9];

/* Update actor and sprite state after checking the target entity. */
void update_bank_actor_sprite_state(BankActorState *actor, s32 action, SpriteFrameState *sprite, ActorRecord *target)
{
    if (update_actor_transform_from_parent(actor, action, sprite, target) != 0) {
        if ((check_actor_floor_trap(sprite, target) << 16) > 0) {
            actor->callback = update_bank_actor_state;
            return;
        }
    } else if (sprite->frameTable == zu_frame_set_1 &&
               !(target->flags1C & (ACTOR_MP_EMPTY | ACTOR_ASLEEP))) {
        sprite->frameTable = zu_default_frames;
        select_sprite_entry(sprite,
                      zu_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + target->facing + 0x100) >> 9) & 7],
                      0);
    }
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"


extern s32 update_thrown_actor_travel();
/* Select the bank actor callback when the resident checks succeed. */
void update_directional_sprite_state_and_signals(BankActorState *state, s32 action, SpriteFrameState *source, ActorRecord *target) {
    if ((update_thrown_actor_travel(state, action, source, target) != 0) && ((check_actor_floor_trap(source, target) << 0x10) > 0)) {
        state->callback = update_bank_actor_state;
    }
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 interpolate_actor_to_terrain_tile();
/* Restore the bank actor callback after the resident state check succeeds. */
void restore_bank_actor_callback_b(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (interpolate_actor_to_terrain_tile(state, action, source, target) != 0) {
        state->callback = update_bank_actor_state;
    }
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_spinning_actor_fall();
/* Restore the bank actor callback after the resident state check succeeds. */
void restore_bank_actor_callback_c(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (update_spinning_actor_fall(state, action, source, target) != 0) {
        state->callback = update_bank_actor_state;
    }
}

#include "dungeon/monster/zu.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_actor_fade_in();
/* Restore the bank actor callback after the resident state check succeeds. */
void restore_bank_actor_callback_d(BankActorState *state, s32 action, SpriteFrameState *source, EntityRec *target) {
    if (update_actor_fade_in(state, action, source, target) != 0) {
        state->callback = update_bank_actor_state;
    }
}

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80173F0C_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u8 pad_0A[0xA];
    u16 unk_14;
    u8 pad_16[0x32];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_80173F0C_0;   /* arg0 in update_bank_effect_fade */

   /* arg1 in update_bank_effect_fade */

typedef struct {
    u8 bytes[8];
} Unaligned8;

typedef struct {
    void *field0;
    void *field4;
    Unaligned8 field8;
    Unaligned8 field10;
    s16 field18;
    s16 field1A;
    u32 unused1C;
} CallRecord;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} OutputVector;

extern void advance_sprite_animation_and_textures(void *);
extern s32 rand(void);
extern void transform_rotated_vertices(void *);

/* Updates the effect's motion and fade, then marks it for removal. */
void update_bank_effect_fade(void *effect, MovingPosition *position, SpriteFrameState *visual)
{
    CallRecord transform;
    OutputVector transformed_pos;
    s16 state;
    s32 quarter_angle;
    u16 angle;

    state = ((S_80173F0C_0 *)effect)->unk_4C.s;
    switch (state) {
    case 0:
        advance_sprite_animation_and_textures(visual);
        if (visual->flags & 0x6000) {
            visual->unk_04 = 0;
            visual->unk_05 = 0;
        }
        visual->color.word += 0xFFE7E7E8;
        if ((u8)visual->color.word < 0x30U) {
            ((S_80173F0C_0 *)effect)->unk_4C.u++;
        }

        angle = ((S_80173F0C_0 *)effect)->unk_08 + 10;
        quarter_angle = (s32)(angle << 16) >> 18;
        ((S_80173F0C_0 *)effect)->unk_08 = angle;
        ((S_80173F0C_0 *)effect)->unk_04 = (u16)(-(quarter_angle * quarter_angle) >> 4);

        {
            s32 height_jitter;
            s32 height;

            height_jitter = rand() & 0x7F;

            height = ((S_80173F0C_0 *)effect)->unk_14;
            height += 0x140;
            height += height_jitter;
            ((S_80173F0C_0 *)effect)->unk_14 = height;
        }
        ((S_80173F0C_0 *)effect)->unk_04 += (s32)(((S_80173F0C_0 *)effect)->unk_48 << 16) >> 17;
        if (((S_80173F0C_0 *)effect)->unk_48 & 1) {
            ((S_80173F0C_0 *)effect)->unk_08++;
        }

        transform.field0 = (u8 *)effect + 4;
        transform.field4 = &transformed_pos;
        transform.field8 = *(Unaligned8 *)((u8 *)effect + 0x14);
        transform.field10 = *(Unaligned8 *)((u8 *)effect + 0xC);
        transform.field18 = 1;
        transform.field1A = 1;
        transform_rotated_vertices(&transform);
        position->unk_02 = transformed_pos.x;
        position->unk_06 = transformed_pos.y;
        position->unk_0A = transformed_pos.z;
        ((S_80173F0C_0 *)effect)->unk_48--;
        break;
    case 1:
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801740F4_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_801740F4_1;   /* work in start_bank_actor_hit_reaction */

extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes();
extern s32 clear_byte_and_advance();
extern s32 append_entity_display_text();
extern s32 has_pending_dungeon_activity();
extern s32 display_text_with_fullwidth_adjustment();
extern s32 generate_random_value(void);

const u8 D_80170854[20] = {129,64,130,146,130,143,130,129,130,146,130,133,130,132,129,68,0,0,0,0};
extern u8 D_80174B0C[];

/* Start the actor's hit reaction, then build and post the damage message for it. */
/* Starts Zu's targeted action when activity permits, randomizes flagged facing, and displays an
 * actor-specific message. */
void start_bank_actor_hit_reaction(void *work, void *part_a, SpriteFrameState *part_b, EntityRec *actor) {
    s32 flags;
    void *call_arg;
    u32 pass_result;
    s32 raw_result;
    s32 result;
    s32 field_60;
    u8 *table_base;

    actor->unk_71 = (u8)(actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 0x10) == 0)) {
        ((S_801740F4_1 *)work)->unk_8C = 0;
        ((S_801740F4_1 *)work)->unk_9A = 0x17;
        ((S_801740F4_1 *)work)->unk_9B = 0;
        if (actor->flags1C & ACTOR_CONFUSED) {
            flags = actor->flags14;
            if (!(flags & 0x80000000)) {
                flags |= 0x80000000;
                actor->flags14 = (s32)flags;
                actor->facing = (u16)(((u16)actor->facing) + ((generate_random_value() & 7) << 9));
            }
        }
        field_60 = probe_directional_neighbor(actor, part_b->unk_24, part_b->unk_25,
            (s16)((u16)actor->facing));
        table_base = D_80174B0C;
        actor->target = field_60;
        part_b->frameTable = table_base;
        select_sprite_entry(part_b, table_base[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + (s16)((u16)actor->facing) + 0x100)
            >> 9) & 7], 0);
        actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        raw_result = get_unused_text_buffer();
        call_arg = actor;
        pass_result = raw_result;
        result = pass_result;
        raw_result = append_entity_display_text(call_arg, pass_result);
        clear_byte_and_advance(expand_text_control_codes(&D_80170854, raw_result));
        display_text_with_fullwidth_adjustment(result);
    }
}

#include "common.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#define U8_AT(p, n)  (*(u8 *)((u8 *)(p) + (n)))
#define S8_AT(p, n)  (*(s8 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))

typedef struct {
    u16 value[5];
} Record10;

extern s32 resolve_record_orientation_or_fallback();
extern u32 advance_eligible_actor_or_perform_action(EntityRec *, s16, s16);

/* Retail stores each five-halfword record in a word-aligned 12-byte slot.
 * Keep the local copies at ten bytes; the storage wrapper owns the two zero
 * tail bytes that genuine ASPSX does not add implicitly at section end. */
typedef struct {
    Record10 values;
} __attribute__((aligned(4))) ParameterRecord5;
const ParameterRecord5 D_80170868 = {{4096,3072,4096,6144,5120}};
const ParameterRecord5 D_80170874 = {{4096,6144,4096,2048,3072}};
extern u8 D_80174688[];
extern u8 D_80174ACC[];
extern u8 D_80174B14[];

/* Updates a timed effect sequence and restores the actor animation when it finishes. */
void update_bank_timed_effect(void *state_input, void *motion_input, void *animation_input, void *actor_input) {
    void *motion = motion_input;
    u16 spawn_offset[3];
    Record10 effect_values_1c = D_80170868.values;
    Record10 effect_values_1e = D_80170874.values;
    s32 active_state = 1;
    s32 state;
    u16 animation_flags;
    s16 timer;
    void *effect_object;
    void *spawned_data;
    s32 effect_data;
    s32 next_state;

    U16_AT(state_input, 0xA0)--;
    state = U8_AT(state_input, 0x9B);

    switch (state) {
    case 0:
        animation_flags = U16_AT(animation_input, 0x14);
        if (animation_flags & 0x8000) {
            effect_data = S32_AT(actor_input, 0x60);
            if (effect_data != 0) {
                advance_eligible_actor_or_perform_action((EntityRec *)effect_data, 0x10, 0x10);
                U8_AT(state_input, 0x9B) = 2;
            } else {
                U8_AT(state_input, 0x9B) = 2;
            }
            return;
        }

        if (!(animation_flags & 0x6000)) {
            return;
        }

        if (resolve_record_orientation_or_fallback(S32_AT(animation_input, 8), animation_input, spawn_offset, 0) == 0) {
            spawn_offset[2] = 0;
            spawn_offset[1] = 0;
            spawn_offset[0] = 0;
        }

        effect_object = allocate_list_node(0x201, ((u8 *)(&scene_object_list_anchor)));
        if (effect_object != NULL) {
            register_node(effect_object, D_80174688);
            PTR_AT(effect_object, 0x10) = create_cylindrical_effect;
            spawned_data = (u8 *)effect_object + 0x20;
            S16_AT(spawned_data, 0x0C) = U16_AT(motion, 2) + spawn_offset[0];
            S16_AT(spawned_data, 0x0E) = U16_AT(motion, 6) + spawn_offset[1];
            S16_AT(spawned_data, 0x10) = U16_AT(motion, 0xA) + spawn_offset[2];
            S32_AT(spawned_data, 0x58) = 0x80;
            S16_AT(spawned_data, 0x48) = active_state;
        }
        play_sound_if_enabled(0x815);
        {

            next_state = U8_AT(state_input, 0x9B);
            state = 0x1E;
            S16_AT(state_input, 0x96) = state;
        }
        U8_AT(state_input, 0x9B) = next_state + 1;
        return;
    case 1:
        effect_data = S32_AT(actor_input, 0x60);
        if (effect_data != 0) {
            timer = S16_AT(state_input, 0x96);
            if (timer >= 0x12) {
                effect_object = (u8 *)(long)effect_data - 0x20;
                if (timer < 0x17) {
                    U16_AT(PTR_AT(effect_object, 0x0C), 0x1C) = effect_values_1c.value[timer - 0x12];
                    U16_AT(PTR_AT(effect_object, 0x0C), 0x1E) = effect_values_1e.value[S16_AT(state_input, 0x96)
                        - 0x12];
                }
            }
        }

        if (S16_AT(state_input, 0x96) == 0x14) {
            effect_data = S32_AT(actor_input, 0x60);
            if (effect_data != 0) {
                advance_eligible_actor_or_perform_action((EntityRec *)effect_data, 0x10, 0x10);
            }
        }

        timer = U16_AT(state_input, 0x96) - 1;
        S16_AT(state_input, 0x96) = timer;
        if (timer > 0) {
            return;
        }

        PTR_AT(animation_input, 0x2C) = D_80174B14;
        select_sprite_entry(animation_input,
            D_80174B14[((g_game_work.view.camera_rotation.parts.viewAngle + S16_AT(actor_input, 0x2A) + 0x100) >> 9) & 7],
            0);
        next_state = U8_AT(state_input, 0x9B);
        U8_AT(state_input, 0x9B) = next_state + 1;
        return;
    case 2:
        if (U16_AT(animation_input, 0x14) & 0xE000) {

            S32_AT(motion, 0x10) = 0;
            S32_AT(motion, 0x0C) = 0;
            spend_actor_mp(actor_input, 0x800);
            PTR_AT(animation_input, 0x2C) = D_80174ACC;
            select_sprite_entry(animation_input,
                D_80174ACC[((g_game_work.view.camera_rotation.parts.viewAngle + S16_AT(actor_input, 0x2A) + 0x100) >> 9) & 7],
                0);
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            advance_status_timers(actor_input);
            U8_AT(actor_input, 0x6D) = 0;
            U16_AT(actor_input, 0x46) &= 0x7FFF;
            PTR_AT(state_input, 0x8C) = update_bank_actor_state;
        }
        break;
    }
}

#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
struct SpriteFrameState;

   /* the 0x2 bytes before arg0 in create_cylindrical_effect, addressed as arg0[-1] */

typedef struct S_80F8ADE0_0 {
    u8 pad_00[0x48];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
    u8 pad_4E[0xA];
    s32 unk_58;
} S_80F8ADE0_0;   /* arg0 in create_cylindrical_effect */

/* Advances a timed state sequence and sets flags when it reaches stage 15. */
/* Advances timed effect stages, toggles a stored value, pauses at stage 7, and removes the object at stage
 * 15. */
void create_cylindrical_effect(void *state) {
    u16 ticks_left;
    u16 next_delay;

    if (((S_80F8ADE0_0 *)state)->unk_4C == 8) {
        ((S_80F8ADE0_0 *)state)->unk_58 = (s32) (((S_80F8ADE0_0 *)state)->unk_58 + 8);
    }
    ticks_left = ((S_80F8ADE0_0 *)state)->unk_48 - 1;
    ((S_80F8ADE0_0 *)state)->unk_48 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        next_delay = 1;
        if (((S_80F8ADE0_0 *)state)->unk_4C == 7) {
            next_delay = 0xA;
        }
        ((S_80F8ADE0_0 *)state)->unk_48 = next_delay;
        ((S_80F8ADE0_0 *)state)->unk_58 = (s32) ((((S_80F8ADE0_0 *)state)->unk_58 == 0) << 7);
        ((S_80F8ADE0_0 *)state)->unk_4C = (s16) ((u16) ((S_80F8ADE0_0 *)state)->unk_4C + 1);
    }
    if (((S_80F8ADE0_0 *)state)->unk_4C == 0xF) {
        ((ObjectStatusPrefix16 *)state)[-1].unk_00 = (u16) (((ObjectStatusPrefix16 *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
