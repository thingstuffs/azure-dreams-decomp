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
extern s32 cd_cue_base[];
extern u8 animation_tick_scale;
extern u8 D_800DCF50;
extern s32 D_800DDAB8[];
extern u8 kewne_action_resume_address[];
extern u8 D_80175F40[];
extern u16 D_80175F6E;

extern s32 Control_CD();
extern void sound_set_cd_cue_parameters(int value_0, int value_1, int value_2, int value_3);
extern s32 read_stream_cue_start_offset(void);
extern s16 resolve_alternate_spell_id(s32 tile_index);
extern void *create_actor_spell_effect(void *actor, void *record_data, s16 mode, void *context);
extern void create_actor_linked_effect(void *sourceData);
extern void create_linked_source_object(void *source);
extern void create_linked_child_object(void *parent);

typedef struct S_80173560_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
} S_80173560_0;   /* arg0 in advance_item_action_and_cleanup */

typedef struct S_80173560_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 u; s8 s; } unk_72;   /* accessed as both */
    union { u8 u; s8 s; } unk_73;   /* accessed as both */
} S_80173560_1;   /* arg3 in advance_item_action_and_cleanup */

typedef struct S_80173560_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173560_3;   /* inner in advance_item_action_and_cleanup */


/* Advance an item action through targeting, audio playback, and animation cleanup. */
/* Starts Kewne's targeted spell and linked effects, times optional CD audio playback, then restores
 * movement and status. */
void advance_item_action_and_cleanup(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor_arg) {
    void *actor = actor_arg;
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
    void *target;

    state = ((S_80173560_0 *)action)->unk_9B.n;
    item_or_audio_base = 0;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
    switch (((S_80173560_1 *)actor)->unk_46 & 0x3FFF) {
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
    action_value = ((S_80173560_0 *)action)->unk_98;
    has_item = item_or_audio_base;
    ((S_80173560_0 *)action)->unk_98 = action_value & 0xFF7F;
    state = *item_addr;
    if (has_item != 0) {
        state |= 0x80;
    }
    D_80175F6E = state;
    if (has_item != 0) {
        target = primary_actor_record;
        ((S_80173560_1 *)actor)->unk_60 = target;
        state = (s32)((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
        ((S_80173560_1 *)actor)->unk_72.u = ((S_80173560_3 *)state)->unk_24;
        ((S_80173560_1 *)actor)->unk_73.u = ((S_80173560_3 *)state)->unk_25;
    } else if (item_action_definitions[*item_addr].kind == 2) {
        target = ((S_80173560_1 *)actor)->unk_60;
        if (target != 0) {
            state = (s32)((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
            ((S_80173560_1 *)actor)->unk_72.u = ((S_80173560_3 *)state)->unk_24;
            ((S_80173560_1 *)actor)->unk_73.u = ((S_80173560_3 *)state)->unk_25;
        }
    } else {
        resource = scan_actor_along_heading(actor, sprite->tile_x,
                            sprite->tile_y, ((S_80173560_1 *)actor)->unk_2A, 0x10);
        ((S_80173560_1 *)actor)->unk_60 = resource;
        ((S_80173560_1 *)actor)->unk_72.u = abs(((S_80173560_1 *)actor)->unk_72.s);
        ((S_80173560_1 *)actor)->unk_73.u = abs(((S_80173560_1 *)actor)->unk_73.s);
    }

    if (create_actor_spell_effect(actor, (void *)item_addr, item_or_audio_base, (u8 *)action + 0x98) == 0) {
        return;
    }
    if (item_or_audio_base != 0) {
        D_800DCF50 = *item_addr;
        ((S_80173560_1 *)actor)->unk_13 |= 0x80;
    }
    direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173560_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
    select_sprite_entry(sprite, ((u8 *)sprite->frameTable)[direction], 2);
    sprite->flags |= 0x800;
    if (item_or_audio_base != 0 && !(((S_80173560_1 *)actor)->unk_13 & 0x80)) {
        create_linked_source_object(actor);
        create_linked_child_object(actor);
        ((S_80173560_0 *)action)->unk_9B.n++;
    } else {
        ((S_80173560_1 *)actor)->unk_13 &= 0x7F;
        D_80175F6E &= 0xFF7F;
        create_actor_linked_effect(actor);
        ((S_80173560_0 *)action)->unk_9B.n++;
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
            ((S_80173560_0 *)action)->unk_96.s = D_80175F40[slot] - 0x10;
        }
        ((S_80173560_0 *)action)->unk_9B.n++;
        return;
    }
    action_value = ((S_80173560_0 *)action)->unk_9B.v;
    action_value += 2;
    ((S_80173560_0 *)action)->unk_9B.n = action_value;
    return;

    case 2:
    ((S_80173560_0 *)action)->unk_96.u -= animation_tick_scale;
    if (((S_80173560_0 *)action)->unk_96.s < 3) {
        sprite->flags &= 0xF7FF;
    }
    if (((S_80173560_0 *)action)->unk_96.s > 0) {
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
    ((S_80173560_0 *)action)->unk_9B.n++;

    case 3:
    if (get_cd_command_queue_depth() != 0) {
        sprite->flags |= 0x800;
        return;
    }
    sprite->flags &= 0xF7FF;
    ((S_80173560_0 *)action)->unk_9B.n++;

    case 4:
    if (!(((S_80173560_0 *)action)->unk_98 & 0x80)) {
        sprite->frame_ticks--;
    }

    if (!((sprite->unk_04 == 4 && (sprite->flags & 0x1000)) ||
          (sprite->flags & 0xE000))) {
        return;
    }
    ((S_80173560_0 *)action)->unk_98 |= 0x80;
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
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173560_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
        select_sprite_entry(sprite, kewne_direction_frames[direction], 0);
    }
    {
        if ((g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
    }
    ((S_80173560_0 *)action)->unk_8C = kewne_action_resume_address;
    advance_status_timers(actor);
    ((S_80173560_1 *)actor)->unk_6D--;
    ((S_80173560_1 *)actor)->unk_46 &= 0x7FFF;
    ((S_80173560_0 *)action)->unk_98 &= 0xFFBF;
    ((S_80173560_1 *)actor)->unk_73.u = 0;
    ((S_80173560_1 *)actor)->unk_72.u = 0;
    play_sound_if_enabled(AUDIO_FADE_CD_FAST);
    }
}
