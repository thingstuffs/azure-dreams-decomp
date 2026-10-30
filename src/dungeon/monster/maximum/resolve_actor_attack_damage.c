#include "sdk/libc.h"
#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "engine/cd.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0xA6];
    u16 field_A6;
} D800814A8FieldView_810AF0B4;

typedef struct S_801728B4_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    void * unk_A0;
} S_801728B4_0;   /* arg0 in resolve_actor_attack_damage */

typedef struct S_801728B4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801728B4_3;

typedef struct S_801728B4_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x6F];
    s8 unk_BB;
} S_801728B4_6;

typedef struct S_801728B4_9 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xAB];
    u8 unk_BB;
} S_801728B4_9;

typedef struct S_801728B4_11 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801728B4_11;

extern void effect_update_tag();
void dispatch_monster_move_attack_spell(ActorRecord *, ObjectPosition *, SpriteFrameState *, ActorRecord *);
extern u8 maximum_frame_set_4[];

/* Updates an actor action, its visual effect, and completion cleanup. */
/* Starts a targeted spell with a child sprite on frame 45, releases the child after animation, and
 * restores movement. */
void resolve_actor_attack_damage(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *action) {
    s32 action_id;
    s32 action_value;
    s32 effect_anim;
    s16 use_player;
    u16 saved_pos[4];
    u16 sprite_flags;
    u16 ticks_left;
    u16 sprite_angle;
    u8 *slot_or_effect;
    s32 state;
    SpriteFrameState *effect_sprite;
    void *new_effect;
    void *target;

    state = actor->action_phase.u;
    use_player = 0;
    switch (state) {
    case 0:
        if (action->flags1C & ACTOR_PLAYER_SIDE) {
            action_id = action->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (action_id - 1) {
            case 6:
                use_player = 1;
            case 2:
                slot_or_effect = (u8 *)action + 0xE;
                break;
            case 5:
                use_player = 1;
            case 1:
                slot_or_effect = (u8 *)action + 0xB;
                break;
            case 4:
                use_player = 1;
            case 0:
                slot_or_effect = (u8 *)action + 8;
                break;
            default:
                slot_or_effect = NULL;
                break;
            }
        } else {
            switch (action->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 3:
                slot_or_effect = (u8 *)action + 0xE;
                break;
            case 2:
                slot_or_effect = (u8 *)action + 0xB;
                break;
            case 1:
                slot_or_effect = (u8 *)action + 8;
                break;
            default:
                slot_or_effect = NULL;
                break;
            }
        }
        if (*slot_or_effect != 0) {
            actor->action_state_flags = (u16) (actor->action_state_flags & 0xFF7F);
            if (use_player != 0) {
                target = primary_actor_record;
                action->target = target;
                action_value = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                action->target_tile_x = (s8) ((S_801728B4_3 *)action_value)->unk_24;
                action->target_tile_y = (s8) ((S_801728B4_3 *)action_value)->unk_25;
            } else if (item_action_definitions[*slot_or_effect].kind == 2) {
                target = action->target;
                if (target != NULL) {
                    action_value = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    action->target_tile_x = (s8) ((S_801728B4_3 *)action_value)->unk_24;
                    action->target_tile_y = (s8) ((S_801728B4_3 *)action_value)->unk_25;
                }
            } else {
                action->target = scan_actor_along_heading(action, sprite->tile_x, sprite->tile_y,
                    action->facing, 0x10);
                action->target_tile_x = abs(action->target_tile_x);
                action->target_tile_y = abs(action->target_tile_y);
            }
            saved_pos[0] = ((u16)motion->x.w.i);
            saved_pos[1] = ((u16)motion->y.w.i);
            saved_pos[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(action, slot_or_effect, use_player, ((u8 *)actor + 0x98)) == 0) {
                return;
            }
            sprite->flags = (u16) (sprite->flags & 0xF7FF);
            play_sound_if_enabled(0x703);
            actor->action_phase.u = (u8) (actor->action_phase.u + 1);
            new_effect = allocate_list_node(0x112, &scene_object_list_anchor.next);
            ((S_801728B4_0 *)actor)->unk_A0 = new_effect;
            if (new_effect == NULL) {
                return;
            }
            register_node(new_effect, project_sprite_chain);
            ((S_801728B4_6 *)new_effect)->unk_10 = &effect_update_tag;
            ((S_801728B4_11 *)(((S_801728B4_6 *)new_effect)->unk_08))->unk_00 = (s32) motion->x.v;
            ((S_801728B4_11 *)(((S_801728B4_6 *)new_effect)->unk_08))->unk_04 = (s32) motion->y.v;
            ((S_801728B4_11 *)(((S_801728B4_6 *)new_effect)->unk_08))->unk_08 = (s32) (motion->z.v + 0xFF800000);
            ((S_801728B4_6 *)new_effect)->unk_BB = 0;
            effect_sprite = ((S_801728B4_6 *)new_effect)->unk_0C;
            ((S_801728B4_6 *)new_effect)->unk_4A = (u16) action->facing;
            action_value = sprite->animation_resource;
            effect_sprite->scale_y = 0x1000;
            effect_sprite->scale_x = 0x1000;
            effect_sprite->animation_resource = action_value;
            sprite_flags = sprite->flags;
            effect_anim = 0x2D;
            effect_sprite->flags = sprite_flags;
            sprite_angle = sprite->clut;
            effect_sprite -> tpage_abr = 0 ; effect_sprite -> flags = ( u16 ) ( sprite_flags | 0xC ) ; effect_sprite -> clut = ( s16 ) ( sprite_angle - 0x80 ) ; effect_sprite -> color . word = (s32) sprite->color.word;
            select_sprite_entry(effect_sprite, effect_anim, 0);
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)&primary_actor_record->unk_A4.value + 2)) = (u16) ((((D800814A8FieldView_810AF0B4 *)primary_actor_record)->field_A6) - 1);
            advance_status_timers(action);
            action->pending_turn_updates = (u8) (((u8)action->pending_turn_updates) - 1);
            actor->unk_8C.address = &dispatch_monster_move_attack_spell;
            action->target_tile_y = 0;
            action->target_tile_x = 0;
            action->action_flags = (u16) (action->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
            return;
        }
    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags = (u16) (sprite->flags | 0x800);
            return;
        }
        sprite->flags = (u16) (sprite->flags & 0xF7FF);
        actor->action_phase.u = (u8) (actor->action_phase.u + 1);
    case 2:
        target = ((S_801728B4_0 *)actor)->unk_A0;
        if (target != NULL) {
            slot_or_effect = target;
            effect_sprite = ((S_801728B4_9 *)slot_or_effect)->unk_0C;
            if (effect_sprite->flags & 0xE000) {
                ((S_801728B4_9 *)slot_or_effect)->unk_BB = 0xFF;
                ((S_801728B4_0 *)actor)->unk_A0 = NULL;
            }
        }
        if ((sprite->unk_04 == 4 && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags = (u16) (sprite->flags | 0x800);
            actor->action_timer.u = 3U;
            actor->action_state_flags = (u16) (actor->action_state_flags | 0x80);
        }
        ticks_left = actor->action_timer.u - 1;
        actor->action_timer.u = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            actor->action_timer.u = 0U;
            sprite->flags = (u16) (sprite->flags & 0xF7FF);
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if ((*(M2C_UNK * *)&sprite->frameTable) != &maximum_frame_set_4) {
            sprite->frameTable = &maximum_frame_set_4;
            select_sprite_entry(sprite, maximum_frame_set_4[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + action->facing + 0x100) >> 9) & 7], 0);
        }
        if ((g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        sprite->flags = (u16) (sprite->flags & 0xF7FF);
        actor->unk_8C.address = &dispatch_monster_move_attack_spell;
        advance_status_timers(action);
        if ((s8) ((u8)action->pending_turn_updates) > 0) {
            action->pending_turn_updates = (u8) (((u8)action->pending_turn_updates) - 1);
        }
        action->target_tile_y = 0;
        action->target_tile_x = 0;
        action->action_flags = (u16) (action->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    default:
        return;
    }
}
