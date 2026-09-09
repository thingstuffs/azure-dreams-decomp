#include "common.h"

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
extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80047784();
extern void func_800A4ACC();
extern void func_800A56E0();
extern void func_800AD594();
extern void func_800C8150();

extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80083498[];
extern Record10 D_80170868;
extern Record10 D_80170874;
extern u8 D_80171138[];
extern u8 D_801745E0[];
extern u8 D_80174688[];
extern u8 D_80174ACC[];
extern u8 D_80174B14[];

/* Updates a timed effect sequence and restores the actor animation when it finishes. */
void func_80174260(void *state_input, void *motion_input, void *animation_input, void *actor_input) {
    void *state_data = state_input;
    void *motion = motion_input;
    void *animation = animation_input;
    void *actor = actor_input;
    u16 spawn_offset[3];
    Record10 effect_values_1c = D_80170868;
    Record10 effect_values_1e = D_80170874;
    s32 active_state = 1;
    s32 state;
    u16 animation_flags;
    s16 timer;
    void *effect_object;
    void *spawned_data;
    s32 effect_data;
    s32 next_state;

    ASM_KEEP(state_data);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(animation);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    U16_AT(state_data, 0xA0)--;
    state = U8_AT(state_data, 0x9B);

    if (state == active_state) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    animation_flags = U16_AT(animation, 0x14);
    if (animation_flags & 0x8000) {
        effect_data = S32_AT(actor, 0x60);
        if (effect_data != 0) {
            func_800C8150(effect_data, 0x10, 0x10);
        }
        U8_AT(state_data, 0x9B) = 2;
        return;
    }

    if (!(animation_flags & 0x6000)) {
        goto end;
    }

    if (func_8003DE58(S32_AT(animation, 8), animation, spawn_offset, 0) == 0) {
        spawn_offset[2] = 0;
        spawn_offset[1] = 0;
        spawn_offset[0] = 0;
    }

    effect_object = func_8003FD64(0x201, D_80083498);
    if (effect_object != NULL) {
        func_8004491C(effect_object, D_80174688);
        PTR_AT(effect_object, 0x10) = D_801745E0;
        spawned_data = (u8 *)effect_object + 0x20;
        S16_AT(spawned_data, 0x0C) = U16_AT(motion, 2) + spawn_offset[0];
        S16_AT(spawned_data, 0x0E) = U16_AT(motion, 6) + spawn_offset[1];
        S16_AT(spawned_data, 0x10) = U16_AT(motion, 0xA) + spawn_offset[2];
        S32_AT(spawned_data, 0x58) = 0x80;
        S16_AT(spawned_data, 0x48) = active_state;
    }
    func_800A56E0(0x815);
    {
        register s32 duration ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        next_state = U8_AT(state_data, 0x9B);
        duration = 0x1E;
        S16_AT(state_data, 0x96) = duration;
    }
    goto advance_state;
state_one:
    effect_data = S32_AT(actor, 0x60);
    if (effect_data != 0) {
        timer = S16_AT(state_data, 0x96);
        if (timer >= 0x12) {
            effect_object = (u8 *)(long)effect_data - 0x20;
            if (timer < 0x17) {
                U16_AT(PTR_AT(effect_object, 0x0C), 0x1C) = effect_values_1c.value[timer - 0x12];
                U16_AT(PTR_AT(effect_object, 0x0C), 0x1E) = effect_values_1e.value[S16_AT(state_data, 0x96) - 0x12];
            }
        }
    }

    if (S16_AT(state_data, 0x96) == 0x14) {
        effect_data = S32_AT(actor, 0x60);
        if (effect_data != 0) {
            func_800C8150(effect_data, 0x10, 0x10);
        }
    }

    timer = U16_AT(state_data, 0x96) - 1;
    S16_AT(state_data, 0x96) = timer;
    if (timer > 0) {
        goto end;
    }

    PTR_AT(animation, 0x2C) = D_80174B14;
    func_80047784(animation,
        D_80174B14[((D_80083228 + S16_AT(actor, 0x2A) + 0x100) >> 9) & 7],
        0);
    next_state = U8_AT(state_data, 0x9B);
advance_state:
    U8_AT(state_data, 0x9B) = next_state + 1;
    return;
state_two:
    if (U16_AT(animation, 0x14) & 0xE000) {
        u16 *global_counts;

        S32_AT(motion, 0x10) = 0;
        S32_AT(motion, 0x0C) = 0;
        func_800AD594(actor, 0x800);
        PTR_AT(animation, 0x2C) = D_80174ACC;
        func_80047784(animation,
            D_80174ACC[((D_80083228 + S16_AT(actor, 0x2A) + 0x100) >> 9) & 7],
            0);
        global_counts = (u16 *)&D_80083460;
        global_counts[5]--;
        func_800A4ACC(actor);
        U8_AT(actor, 0x6D) = 0;
        U16_AT(actor, 0x46) &= 0x7FFF;
        PTR_AT(state_data, 0x8C) = D_80171138;
    }
end:
    return;
}
