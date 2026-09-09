#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_801732A4_arg0.h"

typedef struct S_80173CEC_11 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80173CEC_11;   /* temp_v0_2 in func_80173CEC */

typedef struct S_80173CEC_12 {
    s32 unk_00;
    s32 unk_04;
} S_80173CEC_12;   /* ((S_80173CEC_11 *)temp_v0_2)->unk_08 in func_80173CEC */




typedef struct S_80173CEC_2 {
    u8 unk_00;
} S_80173CEC_2;   /* &D_801742E5 in func_80173CEC */

typedef struct S_80173CEC_3 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80173CEC_3;   /* temp_s0_3 in func_80173CEC */

typedef struct S_80173CEC_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80173CEC_4;   /* temp_a1 in func_80173CEC */

typedef struct S_80173CEC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80173CEC_5;   /* temp_v0_2 in func_80173CEC */


typedef struct S_80173CEC_7 {
    u8 pad_00[0x42E0];
    s16 unk_42E0;
} S_80173CEC_7;   /* temp_a1_2 in func_80173CEC */

typedef struct S_80173CEC_8 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80173CEC_8;   /* temp_a2 in func_80173CEC */

typedef struct S_80173CEC_9 {
    u8 pad_00[0xC];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
    s32 unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80173CEC_9;   /* temp_s0 in func_80173CEC */



/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80170858[];
void func_8003DB94();
s32 Control_CD();
void func_8003F540();
void *func_8003FC64();
void func_80041588();
int func_800445E0();
s32 func_8004491C();
s32 func_800498A0();
s32 func_80069EF8();
void func_8009A028();
void func_8009A3D0();
void func_800A18E8();
s32 func_800A504C();
s32 func_800A56E0();
s32 func_800ADC4C();
s32 func_800C77D0();
void func_80173904();
extern M2C_UNK D_8003E140;
extern s32 D_8006CD58;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_800DCEEC;
extern M2C_UNK D_800DCF5C;
extern M2C_UNK D_8014A000;
extern M2C_UNK D_801736AC;
extern M2C_UNK D_80173B94;
extern M2C_UNK D_801742CC;
extern s32 D_801742D4[];
extern s16 D_801742E0;
extern M2C_UNK D_801742E4;
extern M2C_UNK D_801742E5;
extern s32 D_801742E8;

/* Advance the actor effect sequence through rotation, color blending, and particle spawning. */
void func_80173CEC(Rec_func_801732A4_arg0 *state, Rec_D_800E3D7C *position, Rec_D_80082E80 *actor, void *model) {
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    s16 next_spawn;
    s16 next_trail;
    s16 spawn_count;
    s16 trail_count;
    s32 direction;
    s32 color;
    s32 variant_index;
    register s32 effect_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 fade_left;
    u16 elapsed;
    u16 fade_timer;
    s32 event_done;
    u8 phase;
    void *effect_model;
    S_80173CEC_4 *target_color;
    register S_80173CEC_7 *effect_globals ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register S_80173CEC_8 *effect_position ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    S_80173CEC_9 *effect_sprite;
    S_80173CEC_3 *scene_color;
    S_80173CEC_5 *effect;

    scene_color = &D_80083160;
    phase = state->unk_9B;
    if (phase >= 8U) {
        goto done;
    }
    (void)state_labels; goto *D_80170858[(u32)(phase)];
jt_c0:
    state->unk_9B = (u8) (state->unk_9B + 1);
    return;
jt_c1:
    func_80041588(&D_801742CC, &D_801742E4, 0);
    state->unk_A6 = 0;
    state->unk_9B = (u8) (state->unk_9B + 1);
    ((Rec_D_80082E80 *)model)->unk_8A = (u16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v;
    ((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v = (s32) (((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v & 0xFFFBFFFF);
jt_c2:
    direction = ((s32) (D_80083228 + (s16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x100) >> 9) & 7;
    if ((*(u8 *)&D_801742E4) == 0) {
        goto turn_model;
    }
    if (direction == 2) {
        goto start_effect;
    }
turn_model:
    if (direction == 2) {
        goto done;
    }
    ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v = (u16) (((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x200);
    return;
start_effect:
    func_80041588(&D_801742CC, &D_801742E4, 1);
    func_8003F540(0, D_8006CD58, 0x04000AD4, 0x05000CC4);
    Control_CD(0x15, func_800445E0(), NULL);
    (*(s8 *)&D_801742E5) = 0;
    Control_CD(0xFF, &D_8003E140, &D_801742E5);
    func_800C77D0(model - 0x20, position, 8, 0x300);
    state->unk_96 = 0x10U;
    state->unk_9B = (u8) (state->unk_9B + 1);
jt_c3:
    fade_timer = state->unk_96;
    fade_left = fade_timer - 1;
    state->unk_96 = fade_left;
    if ((fade_left << 0x10) > 0) {
        goto blend_color;
    }
    event_done = ((S_80173CEC_2 *)(&D_801742E5))->unk_00;
    state->unk_96 = fade_timer;
    if (event_done == 0) {
        goto done;
    }
    state->unk_9B = (u8) (state->unk_9B + 1);
    func_800A56E0(0x300);
    return;
blend_color:
    target_color = (*(void **)((u8 *)(&D_800DCEEC) + func_800498A0(model) * 4));
    scene_color->unk_A8 = (u8) (scene_color->unk_A8 + ((s32) (target_color->unk_00 - scene_color->unk_A8) / (s16) state->unk_96));
    scene_color->unk_A9 = (u8) (scene_color->unk_A9 + ((s32) (target_color->unk_01 - scene_color->unk_A9) / (s16) state->unk_96));
    scene_color->unk_AA = (u8) (scene_color->unk_AA + ((s32) (target_color->unk_02 - scene_color->unk_AA) / (s16) state->unk_96));
    return;
jt_c4:
    effect = func_8003FC64(0x12);
    if (effect == NULL) {
        goto done;
    }
    effect->unk_10 = &D_80173B94;
    func_8004491C(effect, &D_801736AC);
    color = 0x808080;
    ASM_KEEP(color);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    state->unk_AC = effect;
    effect_model = model;
    ((S_80173CEC_12 *)(((S_80173CEC_11 *)effect)->unk_08))->unk_00 = (s32) position->unk_00.at00_s32.v;
    ASM_KEEP(effect_model);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80173CEC_12 *)(((S_80173CEC_11 *)effect)->unk_08))->unk_04 = (s32) position->unk_04.at00_s32.v;
    effect_position = effect->unk_08;
    effect_value = position->unk_08.at00_s32.v;
    effect_globals = (void *) 0x80170000;
    effect_globals->unk_42E0 = -8;
    effect_position->unk_08 = effect_value;
    effect_sprite = effect->unk_0C;
    effect_sprite->unk_1E = 0x1000;
    effect_sprite->unk_1C = 0x1000;
    effect_sprite->unk_0C.s = color;
    variant_index = func_800498A0(effect_model, effect_globals, effect_position, color) - 1;
    effect_value = variant_index;
    ASM_KEEP(variant_index);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if ((variant_index << 0x10) >= 0) {
        goto set_animation;
    }
    effect_value = func_80069EF8() % 3;
set_animation:
    func_8003DB94(effect_sprite, D_801742D4[(s16) effect_value] + (s8 *) &D_8014A000, 0);
    actor->unk_14.at00_u16.v = (u16) (actor->unk_14.at00_u16.v | 0x80);
    spawn_count = 0;
    state->unk_96 = 0U;
    state->unk_9B = (u8) (state->unk_9B + 1);
spawn_particles:
    func_80173904(state, position, actor, model, func_80069EF8() & 0xFFF, 0);
    next_spawn = spawn_count + 1;
    spawn_count = next_spawn;
    if (next_spawn >= 8) {
        goto done;
    }
    goto spawn_particles;
jt_c5:
    elapsed = state->unk_96;
    state->unk_96 = (u16) (elapsed + 1);
    if ((s16) elapsed >= 0x1E) {
        goto check_animation;
    }
    trail_count = 0;
spawn_trail:
    func_80173904(state, position, actor, model, func_80069EF8() & 0xFFF, 0);
    next_trail = trail_count + 1;
    trail_count = next_trail;
    if (next_trail < 8) {
        goto spawn_trail;
    }
check_animation:
    effect_sprite = state->unk_AC;
    effect_sprite = effect_sprite->unk_0C.u;
    if (!(effect_sprite->unk_14 & 0xE000)) {
        goto check_movement;
    }
    state->unk_9B = (u8) (state->unk_9B + 1);
jt_c6:
check_movement:
    if (state->unk_9B != 6) {
        goto done;
    }
    if (func_800ADC4C(position, D_801742E8, D_801742E0, &D_800DCF5C) == 0) {
        goto done;
    }
    state->unk_96 = 0x10U;
    state->unk_9B = (u8) (state->unk_9B + 1);
    func_800A18E8(((Rec_D_80082E80 *)model)->unk_12.at01_u8.v, 3);
    func_8009A3D0(actor->unk_24, actor->unk_25, 0x300);
    func_8009A028(model);
    effect_sprite = model - 0x20;
    effect_sprite->unk_10 = (s32) (effect_sprite->unk_10 | 0x80000000);
    return;
jt_c7:
    ((Rec_D_80082E80 *)model)->unk_60.as_s32 = func_800A504C(actor, model);
done:
    return;
}
