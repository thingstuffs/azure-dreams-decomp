#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BBA98_0 {
    u16 unk_00;
    u8 pad_02[0x48];
    s16 unk_4A;
    u8 pad_4C[0x2];
    union { s16 s; u16 u; } unk_4E;   /* accessed as both */
} S_800BBA98_0;   /* temp_a3 in func_800BBA98; pointer addresses record offset 0x2 */


typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    u16 f14;
} State;

typedef struct {
    u8 pad0[0xC];
    s32 fc;
    s16 f10;
    s16 f12;
    u16 f14;
} Arg2State;

void func_800478B8();
s32 rand(void);
extern s32 D_800814A0[3];

/* Updates the effect's motion and fade state, then refreshes its display. */
void func_800BBA98(void *effect, void *motion_data, void *display_data) {
    s16 ticks_left;
    s16 phase_value;
    s32 random_drop;
    s32 x_velocity;
    s32 height;
    void *effect_data;
    State *motion;
    s32 x_decay;
    void *fade_step;
    register void *display;

    effect_data = effect;
    motion = (State *)motion_data;
    display = display_data;
    phase_value = ((S_800BBA98_0 *)((u8 *)effect_data - 0x2))->unk_4E.s;
    if (phase_value == 0) {
        goto advance_motion;
    }
    if (phase_value == 1) {
        goto fade_motion;
    }
    goto update_display;
advance_motion:
    motion->f0 += (motion->fc / (s16) ((S_800BBA98_0 *)((u8 *)effect_data - 0x2))->unk_4A);
    motion->f4 += (motion->f10 / (s16) ((S_800BBA98_0 *)((u8 *)effect_data - 0x2))->unk_4A);
    ticks_left = (u16) ((S_800BBA98_0 *)((u8 *)effect_data - 0x2))->unk_4A - 1;
    ((S_800BBA98_0 *)((u8 *)effect_data - 0x2))->unk_4A = ticks_left;
    phase_value = 0x60;
    if ((ticks_left << 0x10) <= 0) {
        ((Arg2State *)display)->f10 = phase_value;
        ((Arg2State *)display)->f14 |= 0xC;
        ((S_800BBA98_0 *)((u8 *)effect_data - 0x2))->unk_4E.u += 1;
        goto update_display;
    }
    goto update_display;
fade_motion:
    motion->f0 += motion->fc;
    motion->f4 += motion->f10;
    x_velocity = motion->fc;
    x_decay = x_velocity >> 1;
    motion->fc = x_velocity - x_decay;
    motion->f10 -= (motion->f10 >> 1);
    fade_step = (void *)0xFFEFEFF0;
    ((Arg2State *)display)->fc += (s32)fade_step;
    if ((u8) ((Arg2State *)display)->fc < 0x11U) {
        ((S_800BBA98_0 *)((u8 *)effect_data - 0x2))->unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    random_drop = (rand() & 7) << 0xF;
    height = motion->f8;
    height -= random_drop;
    motion->f8 = height;
    func_800478B8(display);
    return;
update_display:
    random_drop = (rand() & 7) << 0xF;
    height = motion->f8;
    height -= random_drop;
    motion->f8 = height;
    func_800478B8(display);
}
