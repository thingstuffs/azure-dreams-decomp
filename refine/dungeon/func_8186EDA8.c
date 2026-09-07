#include "common.h"
#include "m2c_compat.h"

typedef struct S_8186EDA8_0 {
    s32 unk_00;
    s32 unk_04;
} S_8186EDA8_0;   /* arg1 in func_8186EDA8 */

typedef struct S_8186EDA8_1 {
    u16 unk_00;
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u16 unk_04;
    u8 pad_06[0x6];
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
} S_8186EDA8_1;   /* arg0 in func_8186EDA8; pointer addresses record offset 0x2 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_80025308[];
extern s32 D_800814A0[];
extern void func_80024710() __attribute__((noreturn));
void func_80024770() __attribute__((noreturn));      /* extern */
void func_80024874(void) __attribute__((noreturn));  /* extern */
s32 func_800644B8(s16);                          /* extern */
s32 func_80064584(s16);                          /* extern */
void func_800478B8(void *);                       /* extern */

typedef struct {
    s16 state;
    u16 timer;
    u8 pad4[6];
    s16 count;
    s16 angle;
    u16 angle2;
    u8 pad10[0x3C];
    s32 base0;
    s32 base1;
} DungeonState;

typedef struct {
    u8 pad0[0xC];
    u8 c;
    u8 d;
    u8 e;
    u8 padF[5];
    u16 flags14;
    u8 pad16[6];
    u16 x1C;
    u16 y1E;
} DungeonEffect;

/* Updates a rotating dungeon effect through delay, contraction, fade, and completion. */
void func_8186EDA8(DungeonState *anim, S_8186EDA8_0 *position, DungeonEffect *input_effect) {
    s16 phase;
    s16 fade_angle;
    s16 shrink_angle;
    s16 radius;
    s32 radius_step;
    u16 delay_timer;
    u16 finish_timer;
    u16 effect_x;
    u16 effect_y;
    u8 effect_c;
    u8 effect_d;
    u8 effect_e;
    u8 fade_level;
    DungeonEffect *effect = input_effect;
    u16 *flag_page = (u16 *)0x80020000;
    s32 first_angle = anim->angle;

    ASM_USE_NV(flag_page);   /* MATCH pin: keeps a statement from moving across a call/branch */

    position->unk_00 = (s32) (anim->base0 + (anim->count * func_800644B8((flag_page[0x2984] = 1, first_angle)) * 0x10));
    position->unk_04 = (s32) (anim->base1 + (anim->count * func_80064584(anim->angle) * 0x10));
    func_800478B8(effect);
    phase = anim->state;
    if (phase == 1) {
        goto case_1;
    }
    if (phase < 2) {
        if (phase == 0) {
    goto case_0;
        }
        func_80024874();
        return;
    }
    if (phase == 2) {
        goto case_2;
    }
    if (phase == 3) {
        goto case_3;
    }
    func_80024874();
    return;

case_0:
    delay_timer = ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 - 1;
    ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 = delay_timer;
    if ((delay_timer << 0x10) <= 0) {
        u16 next_state = ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_02.s + 1;
        ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail delay-slot fill depends on it */
        func_80024770();
        return;
    }
    goto check_effect_done;

case_1:
    shrink_angle = (u16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E - ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10;
    ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E = shrink_angle;
    if (shrink_angle < 0) {
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E = (s16) (shrink_angle + 0x1000);
    }
    if ((s16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 < 0x7F8) {
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 = (u16) (((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 + 8);
    }
    radius = ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C;
    if (radius >= 0x41) {
        if (radius >= 0x65) {
            s32 tail_arg = 3;
            ASM_TAILSLOT_PIN(tail_arg);   /* MATCH pin: load-bearing for the whole function shape */
            func_80024710(tail_arg);
            return;
        }
        radius_step = 2;
        if (radius < 0x47) {
            radius_step = 1;
            if (radius >= 0x33) {
                radius_step = 2;
            }
        }
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C - radius_step);
        effect_x = ((volatile DungeonEffect *)effect)->x1C;
        effect_c = ((volatile DungeonEffect *)effect)->c;
        effect_x -= 0x46;
        ((volatile DungeonEffect *)effect)->x1C = effect_x;
        effect_y = ((volatile DungeonEffect *)effect)->y1E;
        effect_c += 4;
        ((volatile DungeonEffect *)effect)->c = effect_c;
        effect_e = ((volatile DungeonEffect *)effect)->e;
        effect_y -= 0x46;
        ((volatile DungeonEffect *)effect)->y1E = effect_y;
        effect_d = ((volatile DungeonEffect *)effect)->d;
        effect_e += 4;
        ((volatile DungeonEffect *)effect)->e = effect_e;
        effect->d = effect_d + 4;
        func_80024874();
        return;
    }
    ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 = 0x28U;
    ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_02.u = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_02.u + 1);
    func_80024874();
    return;

case_2:
    fade_angle = (u16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E - ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10;
    ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E = fade_angle;
    if (fade_angle < 0) {
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0E = (s16) (fade_angle + 0x1000);
    }
    if ((s16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 < 0x100) {
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 = (u16) (((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_10 + 8);
    }
    radius = ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C;
    if (radius >= 0x1B) {
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_0C = (s16) (radius - 1);
    }
    fade_level = effect->c;
    if (fade_level >= 2U) {
        effect->c = (u8) (fade_level - 2);
        effect->d -= 2;
        effect->e -= 2;
    }
    if (effect->c == 0) {
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 = 0U;
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_02.u = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_02.u + 1);
    }
    effect->x1C -= 0x14;
    effect->y1E += 0xC8;
    func_80024874();
    return;

case_3:
    finish_timer = ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 - 1;
    ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_04 = finish_timer;
    if ((finish_timer << 0x10) <= 0) {
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_00 = (u16) (((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
check_effect_done:
    if (effect->flags14 & 0x8000) {
        ((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_00 = (u16) (((S_8186EDA8_1 *)((u8 *)anim - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
    return;

}
