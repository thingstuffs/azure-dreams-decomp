#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

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

extern s32 select_sprite_entry(void *, u8, s32);
extern void prepare_directional_attack(void *, void *, s16, s32, s32);
extern s32 get_actor_height_difference(s32, void *);
extern s32 probe_directional_neighbor(void *, u8, u8, s16);
extern s32 try_claim_dungeon_action_slot(void *);
extern s32 check_entity_interaction_compatibility(void *, s32);
extern void apply_camera_offset_and_select_target(void *, s32, s32, s32);

/* Validates the actor's direction and state, then initializes its action and animation. */
s32 validate_direction_and_initialize_action(Arg0 *action_state, s32 action_id, SpriteFrameState *sprite, Arg3 *actor) {
    DungeonGlobalStatus *flags_base;
    u8 *direction_frames;
    u16 flags;
    s32 target_angle;
    s32 result;

    actor->field_71 &= 0x7F;
    flags_base = &g_dungeon_status;
    result = 0;
    if (flags_base->flags & 0x2000) {
        return -1;
    }

    target_angle = probe_directional_neighbor(actor, sprite->tile_x, sprite->tile_y, actor->field_2a);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return result;
    }

    flags = flags_base->flags;
    if (flags & 0x2000) {
        return -1;
    }
    if ((actor->field_46 & 0x8000) == 0 && (flags & 8) != 0) {
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

    action_state->field_9b = 0;
    action_state->field_8c = 0;
    if (action_state->field_98 & 0x8000) {
        action_state->field_9a = 0x17;
        if (actor->field_1c & 0x1000) {
            action_state->field_98 |= 0x4000;
        } else {
            action_state->field_98 &= 0xBFFF;
        }
        action_state->field_ac = actor->field_03;
        actor->field_03 = 0xFF;
        actor->field_84 = 0x7E;
        actor->field_85 = 8;
    } else {
        action_state->field_9a = 0x11;
        actor->field_84 = 0x7C;
        actor->field_85 = 8;
    }

    direction_frames = killer_direction_frames;
    sprite->frameTable = direction_frames;
    select_sprite_entry(sprite, direction_frames[(((s32)g_game_work.view.camera_rotation.parts.viewAngle + actor->field_2a + 0x100) >> 9) & 7], 0);
    actor->field_6d--;
    prepare_directional_attack(actor, sprite, actor->field_2a, 1, 0);
    if ((action_state->field_98 & 0x8000) == 0) {
        actor->field_1c &= 0xFEFFFFFF;
    }
    return result;
}
