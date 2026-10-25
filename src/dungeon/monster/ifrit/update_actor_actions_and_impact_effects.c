#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "engine/cd.h"
extern u8 D_801740FC[];
extern int abs(int);

typedef struct S_801728C4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    union { u16 s; u16 u; } unk_98;   /* accessed as both */
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801728C4_0;   /* arg0 in update_actor_actions_and_impact_effects */

typedef struct S_801728C4_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801728C4_3_pre;   /* the 0x14 bytes before parent in update_actor_actions_and_impact_effects, addressed as parent[-1] */

typedef struct S_801728C4_3 {
    u8 pad_00[0xC];
    union { void * s; s32 u; } unk_0C;   /* accessed as both */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
} S_801728C4_3;   /* parent in update_actor_actions_and_impact_effects */

typedef struct S_801728C4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x3];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    void * unk_2C;
} S_801728C4_4;   /* arg2 in update_actor_actions_and_impact_effects */

typedef struct S_801728C4_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_801728C4_6;   /* global in update_actor_actions_and_impact_effects */

typedef struct S_801728C4_8 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xC];
    s32 unk_A4;
} S_801728C4_8;   /* part in update_actor_actions_and_impact_effects */

extern u8 ifrit_action_resume_address[];
#include "dungeon/monster/ifrit.h"
extern u8 D_80174850[];

extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void project_sprite_chain(void);
extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void *scan_actor_along_heading(void *, s32, s32, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void create_two_row_object_group(void *payload, s16 value_scale);

/* Updates actor action states, movement, and impact effects. */
/* Starts a targeted spell with two rows of effects, emits impact particles at the sprite attachment, then
 * restores idle. */
void update_actor_actions_and_impact_effects(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor)
{
    u16 pos[3];
    u16 delta[3];
    s32 state;
    u32 anim_id;
    u32 action_kind;
    u32 dispatch_index;
    s16 special_mode;
    s32 special_test;
    s32 particle_count;
    s32 current_state;
    u8 *anim;
    u16 timer;
    ObjectNodeHeader *effect;
    void *effect_state;
    void *target_sprite;
    void (*callback)(void);
    void *player_state;
    void *special_target;
    s32 offset_x;
    s32 abs_x;
    s32 abs_y;
    s32 offset_y;
    s32 flags;

    special_mode = 0;
    state = ((S_801728C4_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (actor->flags1C & ACTOR_PLAYER_SIDE) {
            action_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            dispatch_index = action_kind - 1;
            switch (dispatch_index) {
            case 6:
                special_mode = 1;
            case 2:
                anim = (u8 *)actor + 0xE;
                break;
            case 5:
                special_mode = 1;
            case 1:
                anim = (u8 *)actor + 0xB;
                break;
            case 4:
                special_mode = 1;
            case 0:
                anim = (u8 *)actor + 8;
                break;
            default:
                anim = 0;
                break;
            }
        } else {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 3:
                anim = (u8 *)actor + 0xE;
                break;
            case 2:
                anim = (u8 *)actor + 0xB;
                break;
            case 1:
                anim = (u8 *)actor + 8;
                break;
            default:
                anim = 0;
                break;
            }
        }
        if (*anim != 0) {
            ((S_801728C4_0 *)action)->unk_98.s &= 0xFF7F;
            special_test = special_mode;
            if (special_test != 0) {
                special_target = ((u8 *)primary_actor_record);
                actor->target = special_target;
                target_sprite = ((ObjectNodeHeader *)((u8 *)special_target - 0x20))->sprite;
                actor->target_tile_x = ((S_801728C4_3 *)target_sprite)->unk_24;
                actor->target_tile_y = ((S_801728C4_3 *)target_sprite)->unk_25;
            } else {
                anim_id = *anim;
                if (item_action_definitions[anim_id].kind == 2) {
                    target_sprite = actor->target;
                    if (target_sprite != 0) {
                        target_sprite = ((S_801728C4_3_pre *)target_sprite)[-1].unk_00;
                        actor->target_tile_x = ((S_801728C4_3 *)target_sprite)->unk_24;
                        actor->target_tile_y = ((S_801728C4_3 *)target_sprite)->unk_25;
                    }
                } else {
                    actor->target = scan_actor_along_heading(
                        actor, ((S_801728C4_4 *)sprite)->unk_24, ((S_801728C4_4 *)sprite)->unk_25,
                        actor->facing, 0x10);
                    abs_x = abs(actor->target_tile_x);
                    abs_y = abs(actor->target_tile_y);
                    actor->target_tile_x = abs_x;
                    actor->target_tile_y = abs_y;
                }
            }

            pos[0] = ((u16)motion->x.w.i);
            pos[1] = ((u16)motion->y.w.i);
            pos[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(actor, anim, special_mode, (u8 *)action + 0x98) != 0) {
                ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
                play_sound_if_enabled(0x703);
                create_two_row_object_group(pos, (s16)((*anim - 1) % 3));
                current_state = ((S_801728C4_0 *)action)->unk_9B;
                ((S_801728C4_0 *)action)->unk_96 = 30000;
                ((S_801728C4_0 *)action)->unk_9B = current_state + 1;
                return;
            }
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((S_801728C4_4 *)sprite)->unk_24, ((S_801728C4_4 *)sprite)->unk_25);
            player_state = ((u8 *)primary_actor_record);
            g_dungeon_status.active_actor = 0;
            ((S_801728C4_6 *)player_state)->unk_A6--;
            advance_status_timers(actor);
            (*(u8 *)&actor->pending_turn_updates)--;
            ((S_801728C4_0 *)action)->unk_8C = ifrit_action_resume_address;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            return;
        }
    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((S_801728C4_4 *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
        ((S_801728C4_0 *)action)->unk_9B++;
    case 2:
        if (resolve_record_orientation_or_fallback(((S_801728C4_4 *)sprite)->unk_08, sprite, delta, 0) == 0) {
            delta[0] = delta[1] = delta[2] = 0;
        }
        if ((((S_801728C4_4 *)sprite)->unk_04 == 3 && (((S_801728C4_4 *)sprite)->unk_14 & 0x1000)) ||
            (((S_801728C4_4 *)sprite)->unk_14 & 0xE000)) {
            ((S_801728C4_4 *)sprite)->unk_14 |= 0x800;
            ((S_801728C4_0 *)action)->unk_96 = 6;
            ((S_801728C4_0 *)action)->unk_98.u |= 0x80;
            if (!(((S_801728C4_4 *)sprite)->unk_14 & 0x8000)) {
                flags = ((S_801728C4_0 *)action)->unk_98.s;
                ((S_801728C4_0 *)action)->unk_98.u = flags | 0x8000;
                effect = allocate_list_node(0x112, ((u8 *)&scene_object_list_anchor));
                if (effect != 0) {
                    register_node(effect, project_sprite_chain);
                    effect_state = (u8 *)effect + 0x20;
                    effect->update_callback = tick_object_motion_and_expire;
                    effect->position->x.w.i =
                        ((u16)motion->x.w.i) + delta[0];
                    effect->position->y.w.i =
                        ((u16)motion->y.w.i) + delta[1];
                    effect->position->z.w.i =
                        ((u16)motion->z.w.i) + delta[2];
                    ((S_801728C4_8 *)effect_state)->unk_A4 = 0;
                    ((S_801728C4_8 *)effect_state)->unk_96 = 4;
                    target_sprite = effect->sprite;
                    ((S_801728C4_3 *)target_sprite)->unk_28 = ((S_801728C4_4 *)sprite)->unk_28;
                    ((S_801728C4_3 *)target_sprite)->unk_1E = 0x1000;
                    ((S_801728C4_3 *)target_sprite)->unk_1C = 0x1000;
                    ((S_801728C4_3 *)target_sprite)->unk_14 = ((S_801728C4_4 *)sprite)->unk_14;
                    ((S_801728C4_3 *)target_sprite)->unk_12 = ((S_801728C4_4 *)sprite)->unk_12;
                    ((S_801728C4_3 *)target_sprite)->unk_0C.s = ((S_801728C4_4 *)sprite)->unk_0C;
                    select_sprite_entry(target_sprite, 0x2D, 0);
                }
            }
        }

        timer = ((S_801728C4_0 *)action)->unk_96 - 1;
        ((S_801728C4_0 *)action)->unk_96 = timer;
        if ((s32)(timer << 16) <= 0) {
            ((S_801728C4_0 *)action)->unk_98.u &= 0x7FFF;
            ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
        }

        if (((S_801728C4_0 *)action)->unk_98.u & 0x8000) {
            particle_count = 7;
            callback = (void *)D_801740FC;
            do {
                effect = allocate_list_node(0x112, ((u8 *)&scene_object_list_anchor));
                if (effect != 0) {
                    register_node(effect, project_sprite_chain);
                    effect->update_callback = callback;
                    effect->position->x.w.i =
                        ((u16)motion->x.w.i) + delta[0] + (rand() & 0xF) - 8;
                    effect->position->y.w.i =
                        ((u16)motion->y.w.i) + delta[1] + (rand() & 0xF) - 8;
                    effect->position->z.w.i =
                        ((u16)motion->z.w.i) + delta[2] + (rand() & 0xF) - 8;
                    effect->position->velocity_x =
                        ((rand() & 0xFF) - 0x80) << 11;
                    effect->position->velocity_y =
                        ((rand() & 0xFF) - 0x80) << 11;
                    effect->position->velocity_z =
                        -(rand() & 0xFF) << 12;
                    effect_state = (u8 *)effect + 0x20;
                    ((S_801728C4_8 *)effect_state)->unk_A4 = 0;
                    ((S_801728C4_8 *)effect_state)->unk_96 = 7;
                    target_sprite = effect->sprite;
                    ((S_801728C4_3 *)target_sprite)->unk_28 = ((S_801728C4_4 *)sprite)->unk_28;
                    ((S_801728C4_3 *)target_sprite)->unk_1E = 0x1000;
                    ((S_801728C4_3 *)target_sprite)->unk_1C = 0x1000;
                    ((S_801728C4_3 *)target_sprite)->unk_14 = ((S_801728C4_4 *)sprite)->unk_14;
                    ((S_801728C4_3 *)target_sprite)->unk_12 = ((S_801728C4_4 *)sprite)->unk_12 - 0x80;
                    ((S_801728C4_3 *)target_sprite)->unk_10 = 0x60;
                    ((S_801728C4_3 *)target_sprite)->unk_0C.u = 0x00808080;
                    ((S_801728C4_3 *)target_sprite)->unk_14 |= 0xC;
                    select_sprite_entry(target_sprite, 0x2F, 0);
                }
                particle_count--;
            } while (particle_count >= 0);
        }

        if (((S_801728C4_4 *)sprite)->unk_14 & 0xE000) {
            ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174850;
            select_sprite_entry(
                sprite,
                D_80174850[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801728C4_0 *)action)->unk_9B = ((S_801728C4_0 *)action)->unk_9B + 1;
            return;
        }
        return;
    case 3:
        if (!(((S_801728C4_4 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((S_801728C4_4 *)sprite)->unk_24, ((S_801728C4_4 *)sprite)->unk_25);
        if (((S_801728C4_4 *)sprite)->unk_2C != ifrit_direction_frames) {
            (*(void * *)((u8 *)sprite + 0x2C)) = ifrit_direction_frames;
            select_sprite_entry(
                sprite,
                ifrit_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        if ((g_dungeon_status.active_actor) == 0) {
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((S_801728C4_4 *)sprite)->unk_14 &= 0xF7FF;
            ((S_801728C4_0 *)action)->unk_8C = ifrit_action_resume_address;
            advance_status_timers(actor);
            if (actor->pending_turn_updates > 0) {
                (*(u8 *)&actor->pending_turn_updates)--;
            }
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }

        return;
    default:
        return;
    }
}
