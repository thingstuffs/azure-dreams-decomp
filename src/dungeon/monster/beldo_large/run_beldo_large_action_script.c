#include "shared/entity.h"
#include "common.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "dungeon/item.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/actor/state.h"
#include "dungeon/system.h"
#include "dungeon/data.h"
#include "dungeon/monster/beldo_large_frames.h"
#include "dungeon/monster/beldo_large_data.h"

#define SEQUENCE_INDEX_ADVANCE(index, base) ((index) += (s32)(base))
#define SEQUENCE_INDEX_BYTE(index, base) (*(u8 *)(index))

/* BYTES: retail stores single bytes (sb) at +0xAA, +0xAF and +0xB0; ActorRecord declares a halfword and two scratch unions there until those fields are settled (R16) */
/* The ring script sets script_active at startup. The form transition sets phase 1
 * before the script advances it to 2. Both bytes belong to this actor. */
typedef struct BeldoScriptTail {
    u8 pad_AC[3];
    s8 script_active;
    s8 transition_phase;
} BeldoScriptTail;

extern void advance_multi_form_ring_phase(void);
extern void advance_secondary_object_state(void);
extern void func_80170838(void);

extern u8 D_80173A60[];
extern u8 D_80173A88[];
extern u8 D_80173AF8;

/* Interprets timed direction commands, relative script jumps, and form changes while updating actor status
 * and MP. */
s32 run_beldo_large_action_script(ActorRecord *entity, ObjectPosition *action_value, SpriteFrameState *aux)
{
    s32 angle_out[2];
    ActorRecord *actor;
    BeldoScriptTail *tail;
    u8 *script;
    s32 command;
    s32 command_byte;
    s32 animation;
    s32 next_phase;
    s32 opcode;
    s32 sequence_index;
    u8 *sequence;
    u8 *start_sequence;
    u8 *old_sequence;
    u8 *jump_script;
    s32 duration;
    s32 state;
    u16 timer;
    s32 event_state;
    u16 old_flags;

    actor = entity;
top:
    if (aux->flags & 0x40) {
        return 0;
    }
    script = encounter_script_cursor;
    command = script[1];
    command_byte = (u8) command;
    if (command_byte == 0) {
        tail = (BeldoScriptTail *)&entity->unk_AC;
        tail->script_active = 0;
    } else {
        duration = script[0];
        timer = (u16)(beldo_script_timer + 1);
        beldo_script_timer = (s16)timer;
        if (duration < (s16)timer) {
            encounter_script_cursor = script + 2;
            beldo_script_timer = 0;
        }
        old_flags = actor->action_flags;
        actor->facing = (s16)((command & 7) << 9);
        actor->action_flags = (u16)(old_flags | 0x8000);
        opcode = command_byte & 0xF8;
        switch (opcode) {
        case 0xD0:
            jump_script = encounter_script_cursor;
            beldo_script_timer = 0;
            jump_script += *(s8 *)jump_script * 2;
            encounter_script_cursor = jump_script;
            goto top;

        case 0x08:
            advance_actor_movement_step(entity, action_value, aux, actor);
            return 0;

        case 0xF0:
            start_actor_directional_action(entity, action_value, aux, actor);
            return 0;

        case 0xE8:
            actor->facing = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
            complete_actor_facing_action(entity, action_value, aux, actor);
            return 0;

        case 0x10:
            animation = entity->unk_AC.byte;
            switch (animation) {
            case 0:
                old_sequence = aux->frameTable;
                sequence = beldo_large_frame_set_2;
                break;
            case 1:
                old_sequence = aux->frameTable;
                sequence = beldo_large_frame_set_5;
                break;
            case 2:
                old_sequence = aux->frameTable;
                sequence = beldo_large_frame_set_1;
                break;
            case 3:
                old_sequence = aux->frameTable;
                sequence = beldo_large_frame_set_3;
                break;
            default:
                update_actor_status_and_mp(actor);
                return 0;
            }
            {
                s16 *angle_base;

                if (old_sequence == sequence) {
                    break;
                }
                angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                (*(u8 **)&aux->frameTable) = sequence;
                sequence_index = ((*angle_base + actor->facing + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
            }
            break;

        case 0xF8:
            state = entity->action_phase;
            switch (state) {
            case 0:
            {
                s16 *angle_base;

                if (entity->unk_AC.byte != 0) {
                    break;
                }
                old_sequence = aux->frameTable;
                start_sequence = D_80173A88;
                if (old_sequence == start_sequence) {
                    break;
                }
                angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                (*(u8 **)&aux->frameTable) = start_sequence;
                sequence_index = ((*angle_base + actor->facing + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, start_sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, start_sequence), aux->unk_04);
                entity->action_phase++;
                entity->action_timer = 0;
                break;
            }
            case 1:
            {
                s16 *angle_base;

                timer = (u16)(entity->action_timer + 1);
                entity->action_timer = timer;
                if ((s16)timer < 0x28) {
                    break;
                }
                entity->unk_AC.byte = 2;
                angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                sequence = ((*(u8 **)&aux->frameTable) = beldo_large_frame_set_1);
                sequence_index = ((*angle_base + actor->facing + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
                entity->action_phase++;
                break;
            }
            }
            break;

        case 0xE0:
            event_state = entity->action_phase;
            switch (event_state) {
            case 0:
            {
                s16 *angle_base;
                u8 *event_sequence;

                if (entity->unk_AC.byte != 2) {
                    break;
                }
                event_sequence = D_80173A60;
                if (aux->frameTable == event_sequence) {
                    break;
                }
                angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                (*(u8 **)&aux->frameTable) = event_sequence;
                sequence_index = ((*angle_base + actor->facing + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, event_sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, event_sequence), aux->unk_04);
                entity->action_phase++;
                entity->action_timer = 0;
                break;
            }
            case 1:
            {
                s16 *angle_base;

                timer = (u16)(entity->action_timer + 1);
                entity->action_timer = timer;
                if ((s16)timer == 0x1A) {
                    advance_secondary_object_state();
                    advance_multi_form_ring_phase();
                    D_80173AF8 = event_state;
                    func_80170838();
                }
                if (entity->action_timer == 0x24) {
                    play_sound_if_enabled(0x819);
                }
                if (entity->action_timer < 0x2C) {
                    break;
                }
                entity->unk_AC.byte = 3;
                angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                sequence = ((*(u8 **)&aux->frameTable) = beldo_large_frame_set_3);
                sequence_index = ((*angle_base + actor->facing + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
                entity->action_phase++;
                break;
            }
            }
            break;

        case 0xD8:
            state = entity->action_phase;
            next_phase = 1;
            switch (state) {
            case 0:
                entity->action_phase = next_phase;
                entity->action_timer = 0;
                *(s8 *)&entity->unk_AA = 0; /* BYTES: sb into the halfword at +0xAA */
            case 1:
                actor->facing = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
                timer = (u16)(entity->action_timer + 1);
                entity->action_timer = timer;
                if (timer & 1) {
                    *(s8 *)&entity->unk_AA = -1; /* BYTES: sb into the halfword at +0xAA */
                } else {
                    *(s8 *)&entity->unk_AA = 1; /* BYTES: sb into the halfword at +0xAA */
                }
                break;
            }
            break;

        case 0xC8:
            state = entity->action_phase;
            switch (state) {
            case 0:
                actor->facing = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
                entity->action_phase++;
                entity->action_timer = 0;
                *(s8 *)&entity->unk_AA = 0; /* BYTES: sb into the halfword at +0xAA */
                tail = (BeldoScriptTail *)&entity->unk_AC;
                tail->transition_phase = 2;
                break;
            case 1:
            {
                s16 *angle_base;
                u8 *idle_sequence;

                timer = (u16)(entity->action_timer + 1);
                entity->action_timer = timer;
                if ((s16)timer >= 4) {
                    entity->action_timer = 0;
                    entity->action_phase = (u8)(entity->action_phase + 1);
                    actor->facing = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
                    idle_sequence = beldo_large_frame_set_2;
                    angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                    entity->unk_AC.byte = 0;
                    (*(u8 **)&aux->frameTable) = idle_sequence;
                    sequence_index = ((*angle_base + actor->facing + 0x100) >> 9) & 7;
                    SEQUENCE_INDEX_ADVANCE(sequence_index, idle_sequence);
                    select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, idle_sequence), 0);
                }
            }
            case 2:
                actor->facing = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
                break;
            }
            break;
        }
    }

    update_actor_status_and_mp(actor);
    return 0;
}
