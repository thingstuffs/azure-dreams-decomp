#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80174800_arg0.h"

typedef struct S_80174B20_13 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174B20_13;   /* temp_v0_2 in func_80174B20 */

typedef struct S_80174B20_14 {
    u8 pad_00[0x60];
    void * unk_60;
} S_80174B20_14;   /* arg3 in func_80174B20 */

typedef struct S_80174B20_15 {
    s32 unk_00;
    s32 unk_04;
} S_80174B20_15;   /* ((S_80174B20_13 *)temp_v0_2)->unk_08 in func_80174B20 */

typedef struct S_80174B20_16 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174B20_16;   /* ((S_80174B20_14 *)arg3)->unk_60 in func_80174B20 */


typedef struct S_80174B20_0_pre {
    u16 unk_00;
} S_80174B20_0_pre;   /* the 0x2 bytes before arg0 in func_80174B20, addressed as arg0[-1] */


typedef struct S_80174B20_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80174B20_1;   /* arg3 in func_80174B20 */

typedef struct S_80174B20_2 {
    u8 unk_00;
} S_80174B20_2;   /* &D_8017521D in func_80174B20 */

typedef struct S_80174B20_3 {
    u8 pad_00[0xA8];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80174B20_3;   /* temp_s0_base in func_80174B20 */

typedef struct S_80174B20_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80174B20_4;   /* temp_a1 in func_80174B20 */

typedef struct S_80174B20_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80174B20_5;   /* temp_v0_2 in func_80174B20 */


typedef struct S_80174B20_7 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
    u8 pad_14A4[0x3D74];
    s16 unk_5218;
} S_80174B20_7;   /* temp_a1_base in func_80174B20 */

typedef struct S_80174B20_8 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174B20_8;   /* temp_a2 in func_80174B20 */

typedef struct S_80174B20_9 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
    s32 unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80174B20_9;   /* temp_s0 in func_80174B20 */


typedef struct S_80174B20_11_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174B20_11_pre;   /* the 0x14 bytes before temp_v1_3 in func_80174B20, addressed as temp_v1_3[-1] */

typedef struct S_80174B20_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174B20_11;   /* temp_v1_3 in func_80174B20 */

typedef struct S_80174B20_12 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174B20_12;   /* temp_a0_2 in func_80174B20 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_801708B8[];
void func_8003DB94();     /* extern */
s32 Control_CD(); /* extern */
void func_8003F540(); /* extern */
void *func_8003FC64();                       /* extern */
void func_80041588(); /* extern */
int func_800445E0();                           /* extern */
s32 func_8004491C();           /* extern */
void func_80047738();              /* extern */
s32 func_800498A0();  /* extern */
s32 func_80069EF8();                          /* extern */
void func_8009A028();                      /* extern */
void func_8009A3D0();             /* extern */
void func_800A18E8();                 /* extern */
s32 func_800A504C();                /* extern */
s32 func_800A56E0();                     /* extern */
s32 func_800ADC4C();     /* extern */
s32 func_800C77D0(); /* extern */
void func_80174800(); /* extern */
extern M2C_UNK D_8003E140;
extern s32 D_8006CD58;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern void *D_800DCEEC[];
extern M2C_UNK D_800DCF5C;
extern u8 D_8014A000[];
extern M2C_UNK D_80174574;
extern M2C_UNK D_801749F4;
extern M2C_UNK D_801751F8;
extern s32 D_80175200[];
extern s16 D_80175218;
extern M2C_UNK D_8017521C;
extern M2C_UNK D_8017521D;
extern s32 D_80175220;

/* Advances the actor replacement sequence, including its visual effects and cleanup. */
void func_80174B20(void *state, Rec_D_800E3D7C *position, Rec_D_80082E80 *entity, void *actor) {
    static void *const phase_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8 };
    s32 tint;
    S_80174B20_7 *globals_base;
    S_80174B20_12 *effect_pool;
    s32 global_flags;
    u16 active_count;
    s16 next_ray;
    s16 ray_index;
    s32 direction;
    s32 effect_ready;
    s32 color_index;
    s32 random_value;
    s32 style_index;
    s16 style;
    s32 position_z;
    register void *call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u16 fade_ticks;
    u16 finish_ticks;
    u16 previous_ticks;
    u8 phase;
    S_80174B20_4 *target_color;
    S_80174B20_8 *effect_position;
    S_80174B20_3 *scene_color;
    S_80174B20_9 *sprite;
    S_80174B20_5 *effect;
    void *new_actor;
    void *replacement;

    scene_color = &D_80083160;
    phase = ((Rec_func_80174800_arg0 *)state)->unk_9B;
    if (phase >= 9U) {
        goto done;
    }
    (void)phase_labels; goto *D_801708B8[(u32)(phase)];
jt_c0:
    ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
    return;
jt_c1:
    func_80041588(&D_801751F8, &D_8017521C, 0);
    ((Rec_func_80174800_arg0 *)state)->unk_B0 = 0;
    ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
    ((S_80174B20_1 *)actor)->unk_8A = (u16) ((S_80174B20_1 *)actor)->unk_2A;
    ((S_80174B20_1 *)actor)->unk_1C = (s32) (((S_80174B20_1 *)actor)->unk_1C & 0xFFFBFFFF);
jt_c2:
    direction = ((s32) (D_80083228 + (s16) ((S_80174B20_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
    if ((*(u8 *)&D_8017521C) == 0) {
        goto turn_actor;
    }
    if (direction == 2) {
        goto start_effect;
    }
turn_actor:
    if (direction == 2) {
        goto done;
    }
    ((S_80174B20_1 *)actor)->unk_2A = (u16) (((S_80174B20_1 *)actor)->unk_2A + 0x200);
    return;
start_effect:
    func_80041588(&D_801751F8, &D_8017521C, 1);
    func_8003F540(0, D_8006CD58, 0x04000AD4, 0x05000CC4);
    Control_CD(0x15, func_800445E0(), NULL);
    (*(s8 *)&D_8017521D) = 0;
    Control_CD(0xFF, &D_8003E140, &D_8017521D);
    func_800C77D0(actor - 0x20, position, 8, 0x300);
    ((Rec_func_80174800_arg0 *)state)->unk_96 = 0x10U;
    ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
jt_c3:
    previous_ticks = ((Rec_func_80174800_arg0 *)state)->unk_96;
    fade_ticks = previous_ticks - 1;
    ((Rec_func_80174800_arg0 *)state)->unk_96 = fade_ticks;
    if ((fade_ticks << 0x10) > 0) {
        goto fade_color;
    }
    effect_ready = ((S_80174B20_2 *)(&D_8017521D))->unk_00;
    ((Rec_func_80174800_arg0 *)state)->unk_96 = previous_ticks;
    if (effect_ready == 0) {
        goto done;
    }
    ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
    func_800A56E0(0x300);
    return;
fade_color:
    color_index = func_800498A0(actor);
    target_color = D_800DCEEC[color_index];
    scene_color->unk_A8 = (u8) (scene_color->unk_A8 + ((s32) (target_color->unk_00 - scene_color->unk_A8) / (s16) ((Rec_func_80174800_arg0 *)state)->unk_96));
    scene_color->unk_A9 = (u8) (scene_color->unk_A9 + ((s32) (target_color->unk_01 - scene_color->unk_A9) / (s16) ((Rec_func_80174800_arg0 *)state)->unk_96));
    scene_color->unk_AA = (u8) (scene_color->unk_AA + ((s32) (target_color->unk_02 - scene_color->unk_AA) / (s16) ((Rec_func_80174800_arg0 *)state)->unk_96));
    return;
jt_c4:
    effect = func_8003FC64(0x12);
    if (effect == NULL) {
        goto done;
    }
    effect->unk_10 = &D_801749F4;
    func_8004491C(effect, &D_80174574);
    tint = 0x808080;
    call_arg = actor;
    ((Rec_func_80174800_arg0 *)state)->unk_AC = effect;
    ((S_80174B20_15 *)(((S_80174B20_13 *)effect)->unk_08))->unk_00 = (s32) position->unk_00.at00_s32.v;
    ((S_80174B20_15 *)(((S_80174B20_13 *)effect)->unk_08))->unk_04 = (s32) position->unk_04.at00_s32.v;
    effect_position = effect->unk_08;
    globals_base = (void *)0x80170000;
    ASM_KEEP(tint);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    position_z = position->unk_08.at00_s32.v;
    globals_base->unk_5218 = -4;
    effect_position->unk_08 = position_z;
    sprite = effect->unk_0C;
    sprite->unk_1E = 0x1000;
    sprite->unk_1C = 0x1000;
    ASM_KEEP(tint);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    sprite->unk_0C.s = tint;
    style_index = func_800498A0(call_arg, globals_base, effect_position, tint) - 1;
    style = style_index;
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    call_arg = sprite;
    if ((style_index << 0x10) >= 0) {
        goto set_animation;
    }
    random_value = func_80069EF8(call_arg);
    style = random_value % 3;
    do {
        call_arg = sprite;
    } while (0);
set_animation:
    func_8003DB94(call_arg, &D_8014A000[(*(s32 *)((u8 *)D_80175200 + (s16) style * 4))], 0);
    entity->unk_14.at00_u16.v = (u16) (entity->unk_14.at00_u16.v | 0x80);
    ray_index = 1;
    ((Rec_func_80174800_arg0 *)state)->unk_96 = 0U;
    ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
spawn_rays:
    func_80174800(state, position, entity, (s16) (ray_index << 0xA));
    next_ray = ray_index + 1;
    ray_index = next_ray;
    if (next_ray < 8) {
        goto spawn_rays;
    }
    return;
jt_c5:
    sprite = ((Rec_func_80174800_arg0 *)state)->unk_AC;
    sprite = sprite->unk_0C.u;
    if (!(sprite->unk_14 & 0xE000)) {
        goto check_motion;
    }
    ((Rec_func_80174800_arg0 *)state)->unk_96 = 0x10U;
    ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
    func_800A18E8(((S_80174B20_1 *)actor)->unk_13, 3);
    func_8009A3D0(entity->unk_24, entity->unk_25, 0x300);
    func_8009A028(actor);
    sprite = actor - 0x20;
    sprite->unk_10 = (s32) (sprite->unk_10 | 0x80000000);
jt_c6:
check_motion:
    if (((Rec_func_80174800_arg0 *)state)->unk_9B != 6) {
        goto done;
    }
    if (func_800ADC4C(position, D_80175220, D_80175218, &D_800DCF5C) == 0) {
        goto done;
    }
    ((Rec_func_80174800_arg0 *)state)->unk_96 = 0x10U;
    ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
    func_800A18E8(((S_80174B20_1 *)actor)->unk_13, 3);
    func_8009A3D0(entity->unk_24, entity->unk_25, 0x300);
    func_8009A028(actor);
    sprite = actor - 0x20;
    sprite->unk_10 = (s32) (sprite->unk_10 | 0x80000000);
    return;
jt_c7:
    new_actor = func_800A504C(entity, actor);
    ((S_80174B20_1 *)actor)->unk_60 = new_actor;
    if (new_actor == NULL) {
        goto done;
    }
    ((Rec_func_80174800_arg0 *)state)->unk_96 = 0x10U;
    ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
    ((S_80174B20_16 *)(((S_80174B20_14 *)actor)->unk_60))->unk_2A = (u16) ((S_80174B20_1 *)actor)->unk_2A;
    replacement = ((S_80174B20_1 *)actor)->unk_60;
    sprite = ((S_80174B20_11_pre *)replacement)[-1].unk_00;
    func_80047738(sprite, sprite->unk_2C[((s32) (D_80083228 + (s16) ((S_80174B20_11 *)replacement)->unk_2A + 0x100) >> 9) & 7], sprite->unk_04);
    sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFFE);
jt_c8:
    finish_ticks = ((Rec_func_80174800_arg0 *)state)->unk_96 - 1;
    ((Rec_func_80174800_arg0 *)state)->unk_96 = finish_ticks;
    if ((finish_ticks << 0x10) > 0) {
        goto done;
    }
    globals_base = (void *)0x80080000;
    effect_pool = &D_80083460;
    ((S_80174B20_16 *)(((S_80174B20_14 *)actor)->unk_60))->unk_2A = (u16) ((S_80174B20_1 *)actor)->unk_8A;
    ((S_80174B20_0_pre *)state)[-1].unk_00 = (u16) (((S_80174B20_0_pre *)state)[-1].unk_00 | 0x8000);
    global_flags = globals_base->unk_14A0;
    active_count = effect_pool->unk_0A;
    globals_base->unk_14A0 = global_flags | 0x8000;
    effect_pool->unk_0A = active_count - 1;
    ((S_80174B20_1 *)actor)->unk_6D = 0;
done:
    return;
}
