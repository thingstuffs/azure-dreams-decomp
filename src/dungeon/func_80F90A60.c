/* Relink of matched dungeon/func_80F8AA60; every changed retail word is a paired relocation. */
#define D_80170868 D_8016A868
#define D_80170874 D_8016A874
#define D_80174688 D_8016E688
#define D_80174ACC D_8016EACC
#define D_80174B14 D_8016EB14
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

#define U8_AT(p, n)  (*(u8 *)((u8 *)(p) + (n)))
#define S8_AT(p, n)  (*(s8 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))

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
extern u8 D_8016EACC[];
extern u8 D_8016EB14[];

/* Updates a timed effect sequence and restores the actor animation when it finishes. */
void update_actor_timed_visual_slot_f(void *state_input, void *motion_input, void *animation_input, void *actor_input) {
    void *motion = motion_input;
    u16 spawn_offset[3];
    Record10 effect_values_1c = D_8016A868.values;
    Record10 effect_values_1e = D_8016A874.values;
    s32 active_state = 1;
    s32 state;
    u16 animation_flags;
    s16 timer;
    void *effect_object;
    void *spawned_data;
    s32 effect_data;
    s32 next_state;

    U16_AT(state_input, 0xA0)--;
    state = U8_AT(state_input, 0x9B);

    switch (state) {
    case 0:
        animation_flags = U16_AT(animation_input, 0x14);
        if (animation_flags & 0x8000) {
            effect_data = S32_AT(actor_input, 0x60);
            if (effect_data != 0) {
                func_800C8150((EntityRec *)effect_data, 0x10, 0x10);
                U8_AT(state_input, 0x9B) = 2;
            } else {
                U8_AT(state_input, 0x9B) = 2;
            }
            return;
        }

        if (!(animation_flags & 0x6000)) {
            return;
        }

        if (func_8003DE58(S32_AT(animation_input, 8), animation_input, spawn_offset, 0) == 0) {
            spawn_offset[2] = 0;
            spawn_offset[1] = 0;
            spawn_offset[0] = 0;
        }

        effect_object = func_8003FD64(0x201, ((u8 *)(&scene_object_list_anchor)));
        if (effect_object != NULL) {
            func_8004491C(effect_object, D_8016E688);
            PTR_AT(effect_object, 0x10) = func_8016E5E0;
            spawned_data = (u8 *)effect_object + 0x20;
            S16_AT(spawned_data, 0x0C) = U16_AT(motion, 2) + spawn_offset[0];
            S16_AT(spawned_data, 0x0E) = U16_AT(motion, 6) + spawn_offset[1];
            S16_AT(spawned_data, 0x10) = U16_AT(motion, 0xA) + spawn_offset[2];
            S32_AT(spawned_data, 0x58) = 0x80;
            S16_AT(spawned_data, 0x48) = active_state;
        }
        play_sound_if_enabled(0x815);
        {

            next_state = U8_AT(state_input, 0x9B);
            state = 0x1E;
            S16_AT(state_input, 0x96) = state;
        }
        U8_AT(state_input, 0x9B) = next_state + 1;
        return;
    case 1:
        effect_data = S32_AT(actor_input, 0x60);
        if (effect_data != 0) {
            timer = S16_AT(state_input, 0x96);
            if (timer >= 0x12) {
                effect_object = (u8 *)(long)effect_data - 0x20;
                if (timer < 0x17) {
                    U16_AT(PTR_AT(effect_object, 0x0C), 0x1C) = effect_values_1c.value[timer - 0x12];
                    U16_AT(PTR_AT(effect_object, 0x0C), 0x1E) = effect_values_1e.value[S16_AT(state_input, 0x96)
                        - 0x12];
                }
            }
        }

        if (S16_AT(state_input, 0x96) == 0x14) {
            effect_data = S32_AT(actor_input, 0x60);
            if (effect_data != 0) {
                func_800C8150((EntityRec *)effect_data, 0x10, 0x10);
            }
        }

        timer = U16_AT(state_input, 0x96) - 1;
        S16_AT(state_input, 0x96) = timer;
        if (timer > 0) {
            return;
        }

        PTR_AT(animation_input, 0x2C) = D_8016EB14;
        func_80047784(animation_input,
            D_8016EB14[((g_game_work.view.camera_rotation.parts.viewAngle + S16_AT(actor_input, 0x2A) + 0x100) >> 9) & 7],
            0);
        next_state = U8_AT(state_input, 0x9B);
        U8_AT(state_input, 0x9B) = next_state + 1;
        return;
    case 2:
        if (U16_AT(animation_input, 0x14) & 0xE000) {

            S32_AT(motion, 0x10) = 0;
            S32_AT(motion, 0x0C) = 0;
            func_800AD594(actor_input, 0x800);
            PTR_AT(animation_input, 0x2C) = D_8016EACC;
            func_80047784(animation_input,
                D_8016EACC[((g_game_work.view.camera_rotation.parts.viewAngle + S16_AT(actor_input, 0x2A) + 0x100) >> 9) & 7],
                0);
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            func_800A4ACC(actor_input);
            U8_AT(actor_input, 0x6D) = 0;
            U16_AT(actor_input, 0x46) &= 0x7FFF;
            PTR_AT(state_input, 0x8C) = func_8016B138;
        }
        break;
    }
}

