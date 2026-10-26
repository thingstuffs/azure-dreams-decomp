#include "dungeon/effect/motion.h"
/* Relink of matched dungeon/func_80F8AA60; every changed retail word is a paired relocation. */
#define D_80170868 D_8016A868
#define D_80170874 D_8016A874
#define D_80174688 D_8016E688
#define D_80174ACC timed_visual_slot_f_return_frames
#define D_80174B14 timed_visual_slot_f_wait_frames
#define create_cylindrical_effect func_8016E5E0
#include "modules/dungeon_ovl_fa7000.h"
#include "dungeon/actor/timed_visual_slot_f.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern void func_8016B138(void *, void *, void *, void *);

#ifndef NULL
#define NULL ((void *)0)
#endif


typedef struct {
    u16 value[5];
} Record10;

extern s32 func_8003DE58();
extern u32 func_800C8150(EntityRec *, s16, s16);

/* Retail stores each five-halfword record in a word-aligned 12-byte slot.
 * Keep the local copies at ten bytes; the storage wrapper owns the two zero
 * tail bytes that genuine ASPSX does not add implicitly at section end. */
typedef struct {
    Record10 values;
} __attribute__((aligned(4))) ParameterRecord5;
extern const ParameterRecord5 D_8016A868;
extern const ParameterRecord5 D_8016A874;
extern u8 D_8016E688[];
extern u8 timed_visual_slot_f_return_frames[];
extern u8 timed_visual_slot_f_wait_frames[];

/* Updates a timed effect sequence and restores the actor animation when it finishes. */
void update_actor_timed_visual_slot_f(ActorRecord *state_input, ObjectPosition *motion_input, SpriteFrameState *animation_input, ActorRecord *actor_input) {
    ObjectPosition *motion = motion_input;
    u16 spawn_offset[3];
    Record10 effect_values_1c = D_8016A868.values;
    Record10 effect_values_1e = D_8016A874.values;
    s32 active_state = 1;
    s32 state;
    u16 animation_flags;
    s16 timer;
    ObjectNodeHeader *effect_object;
    CylindricalEffectWork *spawned_data;
    void *effect_data;
    s32 next_state;

    state_input->unk_A0.parts.low--;
    state = state_input->action_phase;

    switch (state) {
    case 0:
        animation_flags = animation_input->flags;
        if (animation_flags & 0x8000) {
            effect_data = actor_input->target;
            if (effect_data != 0) {
                func_800C8150((EntityRec *)effect_data, 0x10, 0x10);
                state_input->action_phase = 2;
            } else {
                state_input->action_phase = 2;
            }
            return;
        }

        if (!(animation_flags & 0x6000)) {
            return;
        }

        if (func_8003DE58((s32)animation_input->source, animation_input, spawn_offset, 0) == 0) {
            spawn_offset[2] = 0;
            spawn_offset[1] = 0;
            spawn_offset[0] = 0;
        }

        effect_object = func_8003FD64(0x201, &scene_object_list_anchor.next);
        if (effect_object != NULL) {
            func_8004491C(effect_object, D_8016E688);
            effect_object->update_callback = func_8016E5E0;
            spawned_data = (CylindricalEffectWork *)(effect_object + 1);
            spawned_data->origin_x = (u16)motion->x.w.i + spawn_offset[0];
            spawned_data->origin_y = (u16)motion->y.w.i + spawn_offset[1];
            spawned_data->origin_z = (u16)motion->z.w.i + spawn_offset[2];
            spawned_data->shade = 0x80;
            spawned_data->timer.s = active_state;
        }
        play_sound_if_enabled(0x815);
        {

            next_state = state_input->action_phase;
            state = 0x1E;
            state_input->action_timer = state;
        }
        state_input->action_phase = next_state + 1;
        return;
    case 1:
        effect_data = actor_input->target;
        if (effect_data != 0) {
            timer = ((s16)state_input->action_timer);
            if (timer >= 0x12) {
                effect_object = (ObjectNodeHeader *)((u8 *)(long)effect_data - 0x20);
                if (timer < 0x17) {
                    effect_object->sprite->scale_x = effect_values_1c.value[timer - 0x12];
                    effect_object->sprite->scale_y = effect_values_1e.value[((s16)state_input->action_timer)
                        - 0x12];
                }
            }
        }

        if (((s16)state_input->action_timer) == 0x14) {
            effect_data = actor_input->target;
            if (effect_data != 0) {
                func_800C8150((EntityRec *)effect_data, 0x10, 0x10);
            }
        }

        timer = state_input->action_timer - 1;
        state_input->action_timer = timer;
        if (timer > 0) {
            return;
        }

        animation_input->frameTable = timed_visual_slot_f_wait_frames;
        func_80047784(animation_input,
            timed_visual_slot_f_wait_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor_input->facing + 0x100) >> 9) & 7],
            0);
        next_state = state_input->action_phase;
        state_input->action_phase = next_state + 1;
        return;
    case 2:
        if (animation_input->flags & 0xE000) {

            motion->velocity_y = 0;
            motion->velocity_x = 0;
            func_800AD594(actor_input, 0x800);
            animation_input->frameTable = timed_visual_slot_f_return_frames;
            func_80047784(animation_input,
                timed_visual_slot_f_return_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor_input->facing + 0x100) >> 9) & 7],
                0);
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            func_800A4ACC(actor_input);
            actor_input->pending_turn_updates = 0;
            actor_input->action_flags &= 0x7FFF;
            state_input->unk_8C.address = func_8016B138;
        }
        break;
    }
}

