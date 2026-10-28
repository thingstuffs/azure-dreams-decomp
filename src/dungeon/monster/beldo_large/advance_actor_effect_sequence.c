#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"

#define SEQUENCE_INDEX_ADVANCE(index, base) ((index) += (s32)(base))
#define SEQUENCE_INDEX_BYTE(index, base) (*(u8 *)(index))

typedef struct Entity Entity;
typedef struct Aux Aux;

struct Entity {
    u8 pad00[0x2A];
    s16 angle;
    u8 pad2C[0x1A];
    u16 flags46;
    u8 pad48[0x4E];
    u16 timer;
    u8 pad98[3];
    u8 state;
    u8 pad9C[0xE];
    s8 direction;
    u8 padAB;
    u8 animation;
    u8 padAD[2];
    s8 fieldAF;
    s8 fieldB0;
};

struct Aux {
    u8 pad00[4];
    s8 field04;
    u8 pad05[0xF];
    u16 flags14;
    u8 pad16[0xE];
    u8 x24;
    u8 y25;
    u8 pad26[6];
    u8 *sequence;
};

struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void play_sound_if_enabled(s32);
extern void update_actor_status_and_mp(Entity *);
extern void advance_actor_movement_step(u8 *movement_in, ObjectPosition *action_ctx, u8 *position, u8 *actor);
extern void complete_actor_facing_action(Entity *, ObjectPosition *, Aux *, Entity *);
extern void start_actor_directional_action(Entity *, ObjectPosition *, SpriteFrameState *, Entity *);
extern void advance_multi_form_ring_phase(void);
extern void advance_secondary_object_state(void);
extern void func_80170838(void);

extern u8 beldo_large_frame_set_2[];
extern u8 beldo_large_frame_set_5[];
extern u8 beldo_large_frame_set_1[];
extern u8 beldo_large_frame_set_3[];
extern u8 D_80173A60[];
extern u8 D_80173A88[];
extern u8 D_80173AF8;
extern u8 *encounter_script_cursor;
extern s16 beldo_script_timer;

/* Advances the entity action script and updates its animation, facing, and timed events. */
/* Interprets timed direction commands, relative script jumps, and form changes while updating actor status
 * and MP. */
s32 advance_actor_effect_sequence_2(Entity *entity, ObjectPosition *action_value, SpriteFrameState *aux)
{
    s32 angle_out[2];
    Entity *actor;
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
        entity->fieldAF = 0;
    } else {
        duration = script[0];
        timer = (u16)(beldo_script_timer + 1);
        beldo_script_timer = (s16)timer;
        if (duration < (s16)timer) {
            encounter_script_cursor = script + 2;
            beldo_script_timer = 0;
        }
        old_flags = actor->flags46;
        actor->angle = (s16)((command & 7) << 9);
        actor->flags46 = (u16)(old_flags | 0x8000);
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
            actor->angle = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
            complete_actor_facing_action(entity, action_value, aux, actor);
            return 0;

        case 0x10:
            animation = entity->animation;
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
                (*(u8 **)((u8 *)aux + 0x2C)) = sequence;
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
            }
            break;

        case 0xF8:
            state = entity->state;
            switch (state) {
            case 0:
            {
                s16 *angle_base;

                if (entity->animation != 0) {
                    break;
                }
                old_sequence = aux->frameTable;
                start_sequence = D_80173A88;
                if (old_sequence == start_sequence) {
                    break;
                }
                angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                (*(u8 **)((u8 *)aux + 0x2C)) = start_sequence;
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, start_sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, start_sequence), aux->unk_04);
                entity->state++;
                entity->timer = 0;
                break;
            }
            case 1:
            {
                s16 *angle_base;

                timer = (u16)(entity->timer + 1);
                entity->timer = timer;
                if ((s16)timer < 0x28) {
                    break;
                }
                entity->animation = 2;
                angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                sequence = ((*(u8 **)((u8 *)aux + 0x2C)) = beldo_large_frame_set_1);
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
                entity->state++;
                break;
            }
            }
            break;

        case 0xE0:
            event_state = entity->state;
            switch (event_state) {
            case 0:
            {
                s16 *angle_base;
                u8 *event_sequence;

                if (entity->animation != 2) {
                    break;
                }
                event_sequence = D_80173A60;
                if (aux->frameTable == event_sequence) {
                    break;
                }
                angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                (*(u8 **)((u8 *)aux + 0x2C)) = event_sequence;
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, event_sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, event_sequence), aux->unk_04);
                entity->state++;
                entity->timer = 0;
                break;
            }
            case 1:
            {
                s16 *angle_base;

                timer = (u16)(entity->timer + 1);
                entity->timer = timer;
                if ((s16)timer == 0x1A) {
                    advance_secondary_object_state();
                    advance_multi_form_ring_phase();
                    D_80173AF8 = event_state;
                    func_80170838();
                }
                if ((s16)entity->timer == 0x24) {
                    play_sound_if_enabled(0x819);
                }
                if ((s16)entity->timer < 0x2C) {
                    break;
                }
                entity->animation = 3;
                angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                sequence = ((*(u8 **)((u8 *)aux + 0x2C)) = beldo_large_frame_set_3);
                sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                SEQUENCE_INDEX_ADVANCE(sequence_index, sequence);
                select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, sequence), 0);
                entity->state++;
                break;
            }
            }
            break;

        case 0xD8:
            state = entity->state;
            next_phase = 1;
            switch (state) {
            case 0:
                entity->state = next_phase;
                entity->timer = 0;
                entity->direction = 0;
            case 1:
                actor->angle = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
                timer = (u16)(entity->timer + 1);
                entity->timer = timer;
                if (timer & 1) {
                    entity->direction = -1;
                } else {
                    entity->direction = 1;
                }
                break;
            }
            break;

        case 0xC8:
            state = entity->state;
            switch (state) {
            case 0:
                actor->angle = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
                entity->state++;
                entity->timer = 0;
                entity->direction = 0;
                entity->fieldB0 = 2;
                break;
            case 1:
            {
                s16 *angle_base;
                u8 *idle_sequence;

                timer = (u16)(entity->timer + 1);
                entity->timer = timer;
                if ((s16)timer >= 4) {
                    entity->timer = 0;
                    entity->state = (u8)(entity->state + 1);
                    actor->angle = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
                    idle_sequence = beldo_large_frame_set_2;
                    angle_base = &g_game_work.view.camera_rotation.parts.viewAngle;
                    entity->animation = 0;
                    (*(u8 **)((u8 *)aux + 0x2C)) = idle_sequence;
                    sequence_index = ((*angle_base + actor->angle + 0x100) >> 9) & 7;
                    SEQUENCE_INDEX_ADVANCE(sequence_index, idle_sequence);
                    select_sprite_entry(aux, SEQUENCE_INDEX_BYTE(sequence_index, idle_sequence), 0);
                }
            }
            case 2:
                actor->angle = get_rounded_facing_and_rounding_flag(aux->tile_x, aux->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, angle_out);
                break;
            }
            break;
        }
    }

    update_actor_status_and_mp(actor);
    return 0;
}
