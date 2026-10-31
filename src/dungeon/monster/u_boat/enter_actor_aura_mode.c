#include "shared/entity.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/system.h"
#include "dungeon/level.h"
#include "engine/node/allocation.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_80175BA8_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    void * unk_44;
} S_80175BA8_5;

extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);

extern u8 clipped_sprite_renderer_address[];
extern u8 uboat_aura_start_frames[];
extern u8 uboat_aura_later_frames[];
extern u8 uboat_aura_sprite_data[];
extern u8 D_80170CEC[];
#include "dungeon/monster/u_boat.h"
#include "engine/graphics.h"

/* Updates the actor's height offset, spawns an effect, and advances its animation phases. */
void enter_actor_aura_mode(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    void *allocation_head_address;
    ObjectNodeHeader **allocation_head;
    s16 target_offset;
    u16 next_offset;
    u16 phase_ticks;
    u16 first_delay;
    u16 second_delay;
    s32 phase;
    SpriteFrameState *effect_sprite;
    ObjectNodeHeader *effect;
    S_80175BA8_5 *effect_state;
    ObjectPosition *effect_position;

    phase = body->action_phase.u;
    switch (phase) {
    case 0:
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        target_offset = sample_terrain_surface_height(((u16) position->x.w.i), ((u16) position->y.w.i),
                                (s16)(actor->ground_height - 0x20))
        - actor->ground_height;
        if (body->unk_90.parts.high.s < target_offset) {
            next_offset = body->unk_90.parts.high.u + 0xC;
            body->unk_90.parts.high.u = next_offset;
            if (target_offset < (s16)next_offset) {
                body->unk_90.parts.high.s = target_offset;
            }
        } else {
            body->unk_90.parts.high.s = target_offset;
        }
        if (sprite->flags & 0x8000) {
            body->unk_90.parts.high.u = 0;
        }
        phase_ticks = body->action_timer.u + 1;
        body->action_timer.u = phase_ticks;
        if (((s16)phase_ticks == 1) || (sprite->flags & 0x8000)) {
            body->unk_B4.bytes[1] = 1;
            allocation_head_address = (u8 *)body - 0x20;
            allocation_head = allocation_head_address;
            effect = allocate_list_node(0x12,allocation_head);
            if (effect != NULL) {
                body->unk_AC.address = effect;
                effect->update_callback = D_80170CEC;
                register_node(effect, clipped_sprite_renderer_address);
                effect_state = (S_80175BA8_5 *)((u8 *)effect + 0x20);
                effect_state->unk_38 = 5;
                effect_state->unk_40 = body;
                effect_state->unk_44 = position;
                effect_sprite = effect->sprite;
                effect_sprite->tpage_abr = 0x40;
                effect_sprite->flags |= 0xC;
                effect_position = effect->position;
                effect_position->x.w.i = ((u16) position->x.w.i);
                effect_position->y.w.i = ((u16) position->y.w.i);
                effect_position->z.w.i = actor->ground_height;
                effect_sprite = effect->sprite;
                effect_sprite->scale_y = 0xA00;
                effect_sprite->scale_x = 0xA00;
                effect_sprite->color.c.b = 0;
                effect_sprite->color.c.g = 0;
                effect_sprite->color.c.r = 0;
                effect_sprite->source = uboat_aura_sprite_data;
            }
        }
        if (body->unk_90.parts.high.s == 0) {
            (sprite->frameTable) = uboat_aura_start_frames;
            select_sprite_entry(sprite,
                          uboat_aura_start_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                              >> 9) & 7],
                          0);
            body->action_timer.u = 2;
            body->action_phase.u++;
            if (!(sprite->flags & 0x8000)) {
                play_sound_if_enabled(0x800);
            }
        }
        if (!(sprite->flags & 0x8000)) {
            return;
        }

    case 1:
        first_delay = body->action_timer.u - 1;
        body->action_timer.u = first_delay;
        if (((first_delay << 0x10) <= 0) || (sprite->flags & 0xE000)) {
            (sprite->frameTable) = uboat_aura_later_frames;
            select_sprite_entry(sprite,
                          uboat_aura_later_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                              >> 9) & 7],
                          0);
            body->action_timer.u = 3;
            body->action_phase.u++;
        }
        if (!(sprite->flags & 0x8000)) {
            return;
        }
    case 2:
        second_delay = body->action_timer.u - 1;
        body->action_timer.u = second_delay;
        if (((second_delay << 0x10) <= 0) || (sprite->flags & 0x8000)) {
            body->action_timer.u = 0x1E;
            body->unk_A8.s = 0;
            body->unk_B0.bytes[1] = 0;
            body->unk_B0.bytes[2] = 0;
            body->unk_B4.bytes[0] = 0;
            body->unk_B0.bytes[3] = 0;
            body->action_phase.u++;
            body->action_state_flags &= 0xFFF7;
            sprite->depth_bias = 0;
            body->unk_8C.address = uboat_behavior_entry;
            g_dungeon_status.active_actor = 0;
            actor->action_flags &= 0x7FFF;
        }
        return;
    default:
        return;
    }
}
