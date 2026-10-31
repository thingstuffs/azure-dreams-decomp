#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/graphics.h"

typedef struct {
    u8 pad_00[0x84];
    u8 field_84;
    u8 field_85;
    u8 pad_86[0x06];
    s32 field_8c;
    u8 pad_90[0x08];
    u16 field_98;
    s8 field_9a;
    s8 field_9b;
    u8 pad_9c[0x10];
    u8 field_ac;
} Arg0;

typedef struct {
    u8 pad_00[0x03];
    u8 field_03;
    u8 pad_04[0x18];
    s32 field_1c;
    u8 pad_20[0x0a];
    s16 field_2a;
    u8 pad_2c[0x1a];
    u16 field_46;
    u8 pad_48[0x24];
    u8 field_6c;
    u8 field_6d;
    u8 pad_6e[0x03];
    u8 field_71;
    u8 pad_72[0x12];
    u8 field_84;
    u8 field_85;
} Arg3;

typedef struct {
    u8 pad_00[0x24];
    u8 field_24;
    u8 field_25;
    u8 pad_26[0x06];
    u8 *field_2c;
} Arg2;

#include "dungeon/monster/killer.h"
#include "dungeon/effect.h"

extern void prepare_directional_attack(void *, void *, s16, s32, s32);
extern s32 get_actor_height_difference(s32, void *);
extern s32 probe_directional_neighbor(void *, u8, u8, s16); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern s32 try_claim_dungeon_action_slot(void *);
extern s32 check_entity_interaction_compatibility(void *, s32);

/* Validates the actor's direction and state, then initializes its action and animation. */
s32 validate_direction_and_initialize_action(ActorRecord *action_state, ObjectPosition *action_id, SpriteFrameState *sprite, ActorRecord *actor) {
    DungeonGlobalStatus *flags_base;
    u8 *direction_frames;
    u16 flags;
    s32 target_angle;
    s32 result;

    actor->movement_queue_state &= 0x7F;
    flags_base = &g_dungeon_status;
    result = 0;
    if (flags_base->flags & 0x2000) {
        return -1;
    }

    target_angle = probe_directional_neighbor(actor, sprite->tile_x, sprite->tile_y, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return result;
    }

    flags = flags_base->flags;
    if (flags & 0x2000) {
        return -1;
    }
    if ((actor->action_flags & 0x8000) == 0 && (flags & 8) != 0) {
        return -1;
    }

    if ((u32)((0 - get_actor_height_difference(target_angle, actor) + 0x40) & 0xFFFF) >= 0x81U) {
        return result;
    }
    result = 1;
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_id, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    action_state->action_phase.s = 0;
    action_state->unk_8C.run = 0;
    if (action_state->action_state_flags & 0x8000) {
        action_state->action_id.s = 0x17;
        if (actor->flags1C & 0x1000) {
            action_state->action_state_flags |= 0x4000;
        } else {
            action_state->action_state_flags &= 0xBFFF;
        }
        action_state->unk_AC.byte = actor->unk_00[3];
        actor->unk_00[3] = 0xFF;
        actor->unk_84 = 0x7E;
        actor->unk_85 = 8;
    } else {
        action_state->action_id.s = 0x11;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 8;
    }

    direction_frames = killer_direction_frames;
    sprite->frameTable = direction_frames;
    select_sprite_entry(sprite, direction_frames[(((s32)g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
    actor->pending_turn_updates--;
    prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
    if ((action_state->action_state_flags & 0x8000) == 0) {
        actor->flags1C &= 0xFEFFFFFF;
    }
    return result;
}
