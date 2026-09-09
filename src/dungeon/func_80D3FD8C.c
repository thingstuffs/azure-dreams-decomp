#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8017558C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    s16 unk_94;
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
    u8 unk_B0;
    u8 unk_B1;
    s8 unk_B2;
    s8 unk_B3;
    s8 unk_B4;
    u8 pad_B5[0x1];
    u16 unk_B6;
    u16 unk_B8;
    u16 unk_BA;
} S_8017558C_0;   /* arg0 in func_8017558C */




typedef struct S_8017558C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 * unk_0C;
    u8 * unk_10;
} S_8017558C_4;   /* temp_v0_3 in func_8017558C */

typedef struct S_8017558C_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    void * unk_44;
} S_8017558C_5;   /* temp_v0_4 in func_8017558C */

typedef struct S_8017558C_6 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8017558C_6;   /* temp_a0 in func_8017558C */

typedef struct S_8017558C_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017558C_7;   /* temp_v1_2 in func_8017558C */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800E296C[3];
extern u8 D_800E2438[];
extern s16 D_80083228[5];
extern u8 D_80170A84[];
extern s32 D_80045C34[3];
extern u8 D_800E2440[];
extern u8 D_800E2448[];
extern u8 D_800E23E0[];
extern u8 D_800E2488[];
extern u8 D_80171A80[];
extern s32 D_8008346C[];
extern void *D_801708A0[];
void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();               /* extern */
M2C_UNK func_8009D8A4();                            /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800BCB04();                   /* extern */
M2C_UNK func_801708B8();      /* extern */
M2C_UNK func_80174C64(); /* extern */

/* Update the actor action sequence, including its effect, animations, and position restoration. */
void func_8017558C(void *action, Rec_D_800E3D7C *position, Rec_D_80082E80 *sprite, Rec_D_800E3D7C *actor) {
    static void *const phase_labels[] = { &&phase_start, &&phase_wait, &&phase_windup, &&phase_active, &&phase_restore, &&phase_finish };
    s16 height_delta;
    s16 height;
    s16 view_dir;
    s32 *effect_sprite;
    u16 timer;
    u16 finish_timer;
    u16 effect_timer;
    u16 start_timer;
    u16 windup_timer;
    u16 restore_timer;
    u16 saved_angle;
    u16 pause_timer;
    u8 phase;
    s32 restore_phase;
    s32 next_phase;
    void *effect;
    S_8017558C_5 *effect_state;
    S_8017558C_7 *effect_position;

    s32 global_flags;

    phase = ((S_8017558C_0 *)action)->unk_9B;
    if (phase >= 6) {
        goto done;
    }
    (void)phase_labels; goto *D_801708A0[(u32)(phase)];
phase_start:
    if (!(sprite->unk_14.at00_u16.v & 0x8000)) {
        goto adjust_height;
    }
    {
        s32 finish_phase;
        do {
            func_8009D8A4();
        } while (0);
        finish_phase = 5;
        global_flags = D_800E296C[0];
        ((S_8017558C_0 *)action)->unk_96 = finish_phase;
        D_800E296C[0] = global_flags | 0x800000;
        ((S_8017558C_0 *)action)->unk_9B = finish_phase;
    }
    sprite->unk_14.at00_u16.v = (u16) (sprite->unk_14.at00_u16.v | 0x6000);
    goto done;
adjust_height:
    position->unk_14.as_s32 = 0;
    position->unk_10.at00_s32.v = 0;
    position->unk_0C.as_s32 = 0;
    height_delta = func_800BCB04(position->unk_00.at02_u16.v, position->unk_04.at02_u16.v, (s16) (actor->unk_88.as_u16 - 0x20));
    height = actor->unk_88.as_u16;
    height_delta -= height;
    if (((S_8017558C_0 *)action)->unk_92.s >= height_delta) {
        goto clamp_height;
    }
    ((S_8017558C_0 *)action)->unk_92.u = ((S_8017558C_0 *)action)->unk_92.u + 0xC;
    if (height_delta >= (s16) ((S_8017558C_0 *)action)->unk_92.u) {
        goto check_height;
    }
clamp_height:
    ((S_8017558C_0 *)action)->unk_92.u = (u16) height_delta;
check_height:
    if (((S_8017558C_0 *)action)->unk_92.s != 0) {
        goto update_effect;
    }
    sprite->unk_2C.as_pu8 = D_800E2438;
    func_80047784(sprite, D_800E2438[((s32) (*D_80083228 + actor->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x800);
    ((S_8017558C_0 *)action)->unk_96 = 2U;
    ((S_8017558C_0 *)action)->unk_9B = (u8) (((S_8017558C_0 *)action)->unk_9B + 1);
    sprite->unk_06.as_s16 = 6;
    ((S_8017558C_0 *)action)->unk_A6 = (u16) actor->unk_2A.as_s16;
update_effect:
    effect_timer = ((S_8017558C_0 *)action)->unk_96 + 1;
    ((S_8017558C_0 *)action)->unk_96 = effect_timer;
    if ((s16) effect_timer != 1) {
        goto done;
    }
    effect = func_8003FD64(0x12, action - 0x20);
    if (effect == NULL) {
        goto done;
    }
    ((S_8017558C_0 *)action)->unk_AC = effect;
    ((S_8017558C_4 *)effect)->unk_10 = D_80170A84;
    func_8004491C(effect, D_80045C34);
    effect_state = effect + 0x20;
    effect_state->unk_38 = 5;
    effect_state->unk_40 = action;
    effect_state->unk_44 = position;
    effect_sprite = ((S_8017558C_4 *)effect)->unk_0C;
    ((S_8017558C_6 *)effect_sprite)->unk_10 = 0x40;
    ((S_8017558C_6 *)effect_sprite)->unk_14 = (u16) (((S_8017558C_6 *)effect_sprite)->unk_14 | 0xC);
    effect_position = ((S_8017558C_4 *)effect)->unk_08;
    effect_position->unk_02 = (u16) position->unk_00.at02_u16.v;
    effect_position->unk_06 = (u16) position->unk_04.at02_u16.v;
    effect_position->unk_0A = (u16) actor->unk_88.as_u16;
    effect_sprite = ((S_8017558C_4 *)effect)->unk_0C;
    ((S_8017558C_6 *)effect_sprite)->unk_1E = 0xA00;
    ((S_8017558C_6 *)effect_sprite)->unk_1C = 0xA00;
    ((S_8017558C_6 *)effect_sprite)->unk_0E = 0;
    ((S_8017558C_6 *)effect_sprite)->unk_0D = 0;
    ((S_8017558C_6 *)effect_sprite)->unk_0C = 0;
    ((S_8017558C_6 *)effect_sprite)->unk_08 = D_800E2488;
    goto done;
phase_wait:
    start_timer = ((S_8017558C_0 *)action)->unk_96 - 1;
    ((S_8017558C_0 *)action)->unk_96 = start_timer;
    if ((start_timer << 0x10) <= 0) {
        goto start_windup;
    }
    if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
start_windup:
    sprite->unk_2C.as_pu8 = D_800E2440;
    func_80047784(sprite, D_800E2440[((s32) (*D_80083228 + actor->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    ((S_8017558C_0 *)action)->unk_96 = 3U;
    ((S_8017558C_0 *)action)->unk_9B = (u8) (((S_8017558C_0 *)action)->unk_9B + 1);
    ((S_8017558C_0 *)action)->unk_B6 = (u16) position->unk_00.at02_u16.v;
    ((S_8017558C_0 *)action)->unk_B8 = (u16) position->unk_04.at02_u16.v;
    ((S_8017558C_0 *)action)->unk_BA = (u16) actor->unk_88.as_u16;
    goto done;
phase_windup:
    windup_timer = ((S_8017558C_0 *)action)->unk_96 - 1;
    ((S_8017558C_0 *)action)->unk_96 = windup_timer;
    if ((windup_timer << 0x10) > 0) {
        goto done;
    }
    next_phase = ((S_8017558C_0 *)action)->unk_9B;
    ((S_8017558C_0 *)action)->unk_96 = 0x1EU;
    ((S_8017558C_0 *)action)->unk_A8 = 0;
    ((S_8017558C_0 *)action)->unk_B1 = 0U;
    ((S_8017558C_0 *)action)->unk_B2 = 0;
    ((S_8017558C_0 *)action)->unk_B4 = 0;
    ((S_8017558C_0 *)action)->unk_B3 = 0;
    next_phase += 1;
    ((S_8017558C_0 *)action)->unk_9B = next_phase;
    goto done;
phase_active:
    func_80174C64(action, position, sprite, actor);
    goto done;
phase_restore:
    restore_phase = ((S_8017558C_0 *)action)->unk_B1;
    if (restore_phase == 1) {
        goto wait_pause;
    }
    if ((s32) restore_phase >= 2) {
        goto check_restore_end;
    }
    if (restore_phase == 0) {
        goto restore_position;
    }
    goto done;
check_restore_end:
    if (restore_phase == 2) {
        goto finish_restore;
    }
    goto done;
restore_position:
    restore_timer = ((S_8017558C_0 *)action)->unk_96 + 1;
    ((S_8017558C_0 *)action)->unk_96 = restore_timer;
    if ((s16) restore_timer != 1) {
        goto wait_restore;
    }
    position->unk_00.at02_u16.v = (u16) ((S_8017558C_0 *)action)->unk_B6;
    position->unk_04.at02_u16.v = (u16) ((S_8017558C_0 *)action)->unk_B8;
    actor->unk_88.as_u16 = (u16) ((S_8017558C_0 *)action)->unk_BA;
    saved_angle = ((S_8017558C_0 *)action)->unk_A6;
    actor->unk_2A.as_s16 = (s16) saved_angle;
    view_dir = ((s32) (*D_80083228 + (s16) saved_angle + 0x100) >> 9) & 7;
    func_80047738(sprite, sprite->unk_2C.as_pu8[view_dir], sprite->unk_04.as_s8);
    ((S_8017558C_0 *)action)->unk_94 = view_dir;
wait_restore:
    if ((s16) ((S_8017558C_0 *)action)->unk_96 < 0x10) {
        goto done;
    }
    ((S_8017558C_0 *)action)->unk_96 = 0U;
    ((S_8017558C_0 *)action)->unk_B1 = (u8) (((S_8017558C_0 *)action)->unk_B1 + 1);
    sprite->unk_14.at00_u16.v = (u16) (sprite->unk_14.at00_u16.v & 0x9F7F);
    goto done;
wait_pause:
    pause_timer = ((S_8017558C_0 *)action)->unk_96;
    ((S_8017558C_0 *)action)->unk_96 = (u16) (pause_timer + 1);
    if ((s16) pause_timer < 4) {
        goto done;
    }
    ((S_8017558C_0 *)action)->unk_96 = 0U;
    ((S_8017558C_0 *)action)->unk_B1 = (u8) (((S_8017558C_0 *)action)->unk_B1 + 1);
    sprite->unk_2C.as_pu8 = D_800E2448;
    func_80047784(sprite, D_800E2448[((s32) (*D_80083228 + actor->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    sprite->unk_14.at00_u16.v = (u16) (sprite->unk_14.at00_u16.v & 0x9F7F);
    func_800A56E0(0x801);
    goto done;
finish_restore:
    if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    position->unk_14.as_s32 = 0;
    position->unk_10.at00_s32.v = 0;
    position->unk_0C.as_s32 = 0;
    func_800A2B04(position, sprite->unk_24, sprite->unk_25);
    actor->unk_1C.as_s32 = (s32) (actor->unk_1C.as_s32 | 0x40000);
    ((S_8017558C_0 *)action)->unk_98 = (u16) (((S_8017558C_0 *)action)->unk_98 | 8);
    if (sprite->unk_2C.as_pu8 == D_800E23E0) {
        goto done;
    }
    sprite->unk_2C.as_pu8 = D_800E23E0;
    func_80047784(sprite, D_800E23E0[((s32) (*D_80083228 + actor->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    ((S_8017558C_0 *)action)->unk_96 = 5U;
    ((S_8017558C_0 *)action)->unk_9B = (u8) (((S_8017558C_0 *)action)->unk_9B + 1);
    if (((S_8017558C_0 *)action)->unk_B0 != 0) {
        goto done;
    }
    func_801708B8(action, position, sprite);
    goto done;
phase_finish:
    finish_timer = ((S_8017558C_0 *)action)->unk_96;
    ((S_8017558C_0 *)action)->unk_96 = (u16) (finish_timer - 1);
    if ((finish_timer << 0x10) > 0) {
        goto done;
    }
    sprite->unk_06.as_s16 = 0;
    func_800AD594(actor, 0x1000);
    ((S_8017558C_0 *)action)->unk_8C = D_80171A80;
    *D_8008346C = 0;
    actor->unk_44.at02_u16.v = (u16) (actor->unk_44.at02_u16.v & 0x7FFF);
done:
    return;
}
