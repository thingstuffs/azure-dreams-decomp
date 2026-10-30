#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "dungeon/effect/particle.h"

/* Sparse views for fields not covered by the existing record types. */




typedef struct {
    u8 pad_00[0xC];
    s32 field_0C;
    s32 field_10;
    s32 field_14;
} TransformFieldView_81336BB4;




extern void beldo_large_action_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
extern s16 encounter_blink_update_flag[];
extern u8 beldo_large_frame_set_2[];

extern void initialize_timed_motion_step(s32, s32, void *);
extern void select_sprite_entry(void *, u8, s32);
extern void play_sound_if_enabled(s32);
extern void create_eight_part_textured_ribbon(void *, void *, void *, void *);
extern void create_player_centered_sequence_effect(void *, void *, void *); /* Unprototyped: retail call passes more arguments than the callee reads */

/* Advances a timed actor sequence, updating effects and directional animation before clearing completion flags. */
void advance_timed_actor_effect_sequence(ActorRecord *sequence, ObjectPosition *transform, SpriteFrameState *sprite_arg, ActorRecord *actor_arg) {
    u8 state;
    s32 anim_mode;
    u8 *anim_table;
    u8 *current_anim_table;
    ActorRecord *effect_actor;
    u16 timer;
    u16 next_timer;
    s16 old_timer;
    s32 direction;
    SpriteFrameState *sprite = sprite_arg;
    ActorRecord *actor = actor_arg;
    state = sequence->action_phase.u;
    switch (state) {
    case 0:
        create_layered_sprite_pulse(transform);
        sequence->action_timer.s = 5;
        sequence->action_phase.s = sequence->action_phase.u + 1;
        play_sound_if_enabled(0x703);
        encounter_blink_update_flag[0] = 0;
        return;

    case 1:
        timer = sequence->action_timer.u - 1;
        sequence->action_timer.s = timer;
        if ((timer << 0x10) > 0 && !( sprite->flags & 0xE000)) {
            return;
        }
        state = sequence->action_phase.u;
        sequence->action_timer.s = 0;
        sequence->action_phase.s = state + 1;
        return;

    case 2:
        timer = sequence->action_timer.u + 1;
        sequence->action_timer.s = timer;
        if ((s16)timer == 1) {
            create_eight_part_textured_ribbon(sequence, transform, sprite, ((u8 *)(&view_reference_entity)));
        }
        if (sequence->action_timer.s == 2) {
            effect_actor = primary_actor_record;
            ((PlayerRecord *)effect_actor)->unk_10C |= 1;
            effect_actor->movement_facing = ((u16)effect_actor->facing) + 0x800;
            initialize_timed_motion_step(6, 0xC, effect_actor);
            play_sound_if_enabled(0x601);
            create_player_centered_sequence_effect(sequence, transform, sprite);
        }
        if (sequence->action_timer.s == 0xB) {
            state = sequence->action_phase.u;
            sequence->action_timer.s = 0;
            sequence->action_phase.s = state + 1;
            return;
        }
        return;

    case 3:
        if (!( sprite->flags & 0xE000)) {
            return;
        }
        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, sprite->tile_x, sprite->tile_y);
        anim_mode = sequence->unk_AC.byte;
        switch (anim_mode) {
        case 0:
            current_anim_table = sprite->frameTable;
            anim_table = beldo_large_frame_set_2;
            break;
        case 1:
            current_anim_table = sprite->frameTable;
            anim_table = beldo_large_frame_set_2 + 0x8;
            break;
        case 2:
            current_anim_table = sprite->frameTable;
            anim_table = beldo_large_frame_set_2 + 0x10;
            break;
        case 3:
            current_anim_table = sprite->frameTable;
            anim_table = beldo_large_frame_set_2 + 0x18;
            break;
        default:
            state = sequence->action_phase.u;
            sequence->action_timer.s = 0;
            sequence->action_phase.s = state + 1;
            return;
        }
        if (current_anim_table != anim_table) {
            sprite->frameTable = anim_table;
            direction = ((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, *(u8 *)((u32)direction + (unsigned long)anim_table), 0);
        }
        goto advance;

    case 4:
        old_timer = sequence->action_timer.u;
        next_timer = old_timer + 1;
        sequence->action_timer.s = next_timer;
        if (old_timer < 0x50) {
            return;
        }
advance:
        state = sequence->action_phase.u;
        sequence->action_timer.s = 0;
        sequence->action_phase.s = state + 1;
        return;

    case 5:
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        sequence->unk_8C.address = beldo_large_action_resume_address;
        g_dungeon_status.active_actor = 0;
        actor->action_flags &= 0x7FFF;

        return;
    default:
        return;
    }
}
