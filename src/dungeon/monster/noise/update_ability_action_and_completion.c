#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8017364C_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017364C_0;   /* arg0 in update_ability_action_and_completion */

typedef struct S_8017364C_2 {
    u8 * unk_00;
} S_8017364C_2;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 get_cd_command_queue_depth(void);                 /* extern */
void select_sprite_entry();         /* extern */
s32 func_80069EF8();                                /* extern */
void *scan_monster_along_heading();      /* extern */
void set_record_integer_tile_center();              /* extern */
s32 advance_status_timers();                      /* extern */
s32 play_sound_if_enabled();                     /* extern */
s32 create_actor_spell_effect();       /* extern */
void spawn_random_velocity_offset_effect(); /* extern */
extern M2C_UNK D_80171760;
extern u8 D_80174E88[9];

/* Updates an actor's ability action, effects, and completion state. */
/* Starts a targeted Noise spell, emits batches of ten offset particles during casting, then restores idle
 * and status. */
void update_ability_action_and_completion(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor) {
    s16 next_effect;
    s16 effect_count;
    s32 ability_id;
    s32 normal_ability;
    s16 use_player;
    u16 effect_ticks;
    u16 finish_ticks;
    u8 *ability;
    s32 phase;
    void *target;
    u8 *target_sprite;

    phase = ((S_8017364C_0 *)action)->unk_9B;
    use_player = 0;
    switch (phase) {
    case 0:
        if (actor->flags1C & 0x2000) {
            ability_id = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (ability_id) {
            case 7:
                use_player = 1;
            case 3:
                ability = (u8 *)actor + 0xE;
                break;
            case 6:
                use_player = 1;
            case 2:
                ability = (u8 *)actor + 0xB;
                break;
            case 5:
                use_player = 1;
            case 1:
                ability = (u8 *)actor + 8;
                break;
            default:
                ability = NULL;
                break;
            }
        } else {
            normal_ability = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (normal_ability) {
            case 3:
                ability = (u8 *)actor + 0xE;
                break;
            case 2:
                ability = (u8 *)actor + 0xB;
                break;
            case 1:
                ability = (u8 *)actor + 8;
                break;
            default:
                ability = NULL;
                break;
            }
        }
        if (*ability != 0) {
            ((S_8017364C_0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 player_target = use_player;
                if (player_target) {
                    target = primary_actor_record;
                    actor->target = target;
                    {
                        target_sprite =
                            ((S_8017364C_2 *)((u8 *)target - 0x14))->unk_00;
                        actor->target_tile_x = target_sprite[0x24];
                        actor->target_tile_y = target_sprite[0x25];
                    }
                } else {
                    u8 *ability_table;
                    u8 ability_kind;
                    u32 ability_entry;

                    ability_kind = *ability;
                    ability_table = (u8 *)item_action_definitions;
                    ability_entry = ability_kind * 20;
                    ability_entry += (u32)ability_table;
                    if (((u8 *)ability_entry)[0x12] == 2) {
                        target = actor->target;
                        if (target != NULL) {
                            {
                                target_sprite =
                                    ((S_8017364C_2 *)((u8 *)target - 0x14))->unk_00;
                                actor->target_tile_x = target_sprite[0x24];
                                actor->target_tile_y = target_sprite[0x25];
                            }
                        }
                    } else {
                        {
                            s32 x = (s32)scan_monster_along_heading(actor, ((SpriteFrameState *)sprite)->unk_24,
                                          ((SpriteFrameState *)sprite)->unk_25,
                                          actor->facing, 0x10);
                            s32 y;

                            *(void * volatile *)((u8 *)actor + 0x60) = (void *)x;
                            x = actor->target_tile_x;
                            y = actor->target_tile_y;
                            if (x < 0) {
                                x = -x;
                            }
                            if (y < 0) {
                                y = -y;
                            }
                            actor->target_tile_x = x;
                            actor->target_tile_y = y;
                        }
                    }
                }
            }
            if (create_actor_spell_effect(actor, ability, use_player, action + 0x98) == 0) {
                return;
            }
            ((S_8017364C_0 *)action)->unk_96 = 0x13U;
            ((S_8017364C_0 *)action)->unk_9B = (u8) (((S_8017364C_0 *)action)->unk_9B + 1);
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)&primary_actor_record->unk_A4 + 2)) = (u16) ((*(u16 *)((u8 *)primary_actor_record + 0xA6)) - 1);
            advance_status_timers(actor);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            ((S_8017364C_0 *)action)->unk_8C = &D_80171760;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
            return;
        }
    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteFrameState *)sprite)->flags = (u16) (((SpriteFrameState *)sprite)->flags
                | 0x800);
            return;
        }
        ((SpriteFrameState *)sprite)->flags = (u16) (((SpriteFrameState *)sprite)->flags & 0xF7FF);
        ((S_8017364C_0 *)action)->unk_9B = (u8) (((S_8017364C_0 *)action)->unk_9B + 1);
        play_sound_if_enabled(0x703);
    case 2:
        effect_ticks = ((S_8017364C_0 *)action)->unk_96 - 1;
        ((S_8017364C_0 *)action)->unk_96 = effect_ticks;
        if ((effect_ticks << 0x10) <= 0 || (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((S_8017364C_0 *)action)->unk_98 = (u16) (((S_8017364C_0 *)action)->unk_98 | 0x80);
            ((S_8017364C_0 *)action)->unk_9B = (u8) (((S_8017364C_0 *)action)->unk_9B + 1);
            ((SpriteFrameState *)sprite)->flags = (u16) (((SpriteFrameState *)sprite)->flags
                | 0x800);
            ((S_8017364C_0 *)action)->unk_96 = 0xFU;
        }
        if ((u32) (((S_8017364C_0 *)action)->unk_96 - 9) >= 6U) {
            return;
        }
        effect_count = 0;
        do {
            spawn_random_velocity_offset_effect(action - 0x20, 0, 0xC0C0, (func_80069EF8() & 0xFF) | 0x80, 0, 0, 0);
            next_effect = effect_count + 1;
            effect_count = next_effect;
        } while (next_effect < 0xA);
        return;
    case 3:
        if (((s32)g_dungeon_status.active_actor) == 0) {
            ((S_8017364C_0 *)action)->unk_96 = 0U;
        }
        finish_ticks = ((S_8017364C_0 *)action)->unk_96 - 1;
        ((S_8017364C_0 *)action)->unk_96 = finish_ticks;
        if ((finish_ticks << 0x10) <= 0) {
            ((S_8017364C_0 *)action)->unk_96 = 0U;
            ((SpriteFrameState *)sprite)->flags =
                (u16) (((SpriteFrameState *)sprite)->flags & 0xF7FF);
        }
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        if ((*(M2C_UNK * *)&((SpriteFrameState *)sprite)->frameTable) != D_80174E88) {
            ((SpriteFrameState *)sprite)->frameTable = D_80174E88;
            select_sprite_entry(sprite, D_80174E88[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            ((SpriteFrameState *)sprite)->flags =
                (u16) (((SpriteFrameState *)sprite)->flags & 0xF7FF);
        }
        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        ((S_8017364C_0 *)action)->unk_8C = &D_80171760;
        advance_status_timers(actor);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
        actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        play_sound_if_enabled(0xB4);
        return;
    }
}
