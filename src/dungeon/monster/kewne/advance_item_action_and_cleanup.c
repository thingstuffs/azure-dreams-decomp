#include "sdk/libc.h"
#include "shared/audio_commands.h"
#include "common.h"
#include "dungeon/monster/kewne.h"
#include "shared/object_node.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "slus.h"
extern s32 cd_cue_base[];
extern u8 animation_tick_scale;
extern u8 D_800DCF50;
extern s32 D_800DDAB8[];
extern u8 kewne_action_resume_address[];
extern u8 D_80175F40[];
extern u16 D_80175F6E;

extern void create_actor_linked_effect(void *sourceData);

/* Advance an item action through targeting, audio playback, and animation cleanup. */
/* Starts Kewne's targeted spell and linked effects, times optional CD audio playback, then restores
 * movement and status. */
void advance_item_action_and_cleanup(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor_arg) {
    ActorRecord *actor = actor_arg;
    s32 state;
    s32 action_value;
    u8 has_item;
    s16 sound_id;
    u8 * item_addr;
    s32 item_or_audio_base;
    s32 item_id;
    void *audio_base;
    s32 direction;
    s32 cd_param;
    s32 item_type;
    s32 item_index;
    s32 audio_index;
    void *resource;
    ObjectNodeHeader *target;

    state = body->action_phase.u;
    item_or_audio_base = 0;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
    switch (actor->action_flags & 0x3FFF) {
    case 7:
        item_or_audio_base = 1;
        /* fallthrough */
    case 3:
        item_addr = ((u8 *)actor + 0xE);
        break;
    case 6:
        item_or_audio_base = 1;
        /* fallthrough */
    case 2:
        item_addr = ((u8 *)actor + 0xB);
        break;
    case 5:
        item_or_audio_base = 1;
        /* fallthrough */
    case 1:
        item_addr = ((u8 *)actor + 8);
        break;
    default:
        item_addr = 0;
        break;
    }
    action_value = body->action_state_flags;
    has_item = item_or_audio_base;
    body->action_state_flags = action_value & 0xFF7F;
    state = *item_addr;
    if (has_item != 0) {
        state |= 0x80;
    }
    D_80175F6E = state;
    if (has_item != 0) {
        target = (ObjectNodeHeader *)primary_actor_record;
        actor->target = target;
        state = (s32)(target - 1)->sprite;
        actor->target_tile_x = ((ActorRecord *)state)->mp_value.parts.fraction;
        actor->target_tile_y = ((ActorRecord *)state)->mp_value.parts.whole;
    } else if (item_action_definitions[*item_addr].kind == 2) {
        target = actor->target;
        if (target != 0) {
            state = (s32)(target - 1)->sprite;
            actor->target_tile_x = ((ActorRecord *)state)->mp_value.parts.fraction;
            actor->target_tile_y = ((ActorRecord *)state)->mp_value.parts.whole;
        }
    } else {
        resource = scan_actor_along_heading(actor, sprite->tile_x,
                            sprite->tile_y, actor->facing, 0x10);
        actor->target = resource;
        actor->target_tile_x = abs(actor->target_tile_x);
        actor->target_tile_y = abs(actor->target_tile_y);
    }

    if (create_actor_spell_effect(actor, item_addr, item_or_audio_base, (u8 *)body + 0x98) == 0) {
        return;
    }
    if (item_or_audio_base != 0) {
        D_800DCF50 = *item_addr;
        actor->species |= 0x80;
    }
    direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
    select_sprite_entry(sprite, ((u8 *)sprite->frameTable)[direction], 2);
    sprite->flags |= 0x800;
    if (item_or_audio_base != 0 && !(actor->species & 0x80)) {
        create_linked_source_object(actor);
        create_linked_child_object(actor);
        body->action_phase.u++;
    } else {
        actor->species &= 0x7F;
        D_80175F6E &= 0xFF7F;
        create_actor_linked_effect(actor);
        body->action_phase.u++;
    }
    case 1:
    item_addr = (u8 *)(&D_80175F6E);
    if (*(u16 *)item_addr & 0x80) {
        if (get_cd_command_queue_depth() != 0) {
            return;
        }
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        {
            s32 slot;

            slot = (s16)resolve_alternate_spell_id(*(u16 *)item_addr & 0x7F);
            body->action_timer.s = D_80175F40[slot] - 0x10;
        }
        body->action_phase.u++;
        return;
    }
    action_value = body->action_phase.u;
    action_value += 2;
    body->action_phase.u = action_value;
    return;

    case 2:
    body->action_timer.u -= animation_tick_scale;
    if (body->action_timer.s < 3) {
        sprite->flags &= 0xF7FF;
    }
    if (body->action_timer.s > 0) {
        return;
    }
    item_id = D_80175F6E & 0x7F;
    audio_base = D_800DDAB8;
    audio_index = (s16)resolve_alternate_spell_id(item_id);
    sound_id = 0x1300;
    play_sound_if_enabled(sound_id);
    sound_set_cd_cue_parameters(0, cd_cue_base[0],
                  ((s32 *)(((audio_index << 17) >> 14) + audio_base))[0],
                  ((s32 *)(((audio_index << 17) >> 14) + audio_base))[1]);
    cd_param = read_stream_cue_start_offset();
    Control_CD(0x15, cd_param, 0);
    body->action_phase.u++;

    case 3:
    if (get_cd_command_queue_depth() != 0) {
        sprite->flags |= 0x800;
        return;
    }
    sprite->flags &= 0xF7FF;
    body->action_phase.u++;

    case 4:
    if (!(body->action_state_flags & 0x80)) {
        sprite->frame_ticks--;
    }

    if (!((sprite->unk_04 == 4 && (sprite->flags & 0x1000)) ||
          (sprite->flags & 0xE000))) {
        return;
    }
    body->action_state_flags |= 0x80;
    if (!(sprite->flags & 0xE000)) {
        return;
    }
    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    resource = kewne_direction_frames;
    if (sprite->frameTable != resource) {
        (sprite->frameTable) = resource;
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
        select_sprite_entry(sprite, kewne_direction_frames[direction], 0);
    }
    {
        if ((g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
    }
    body->unk_8C.address = kewne_action_resume_address;
    advance_status_timers(actor);
    actor->pending_turn_updates--;
    actor->action_flags &= 0x7FFF;
    body->action_state_flags &= 0xFFBF;
    actor->target_tile_y = 0;
    actor->target_tile_x = 0;
    play_sound_if_enabled(AUDIO_FADE_CD_FAST);
    }
}
