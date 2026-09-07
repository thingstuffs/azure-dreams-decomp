#include "common.h"
#include "m2c_compat.h"

typedef struct S_81868B84_0_pre {
    u16 unk_00;
} S_81868B84_0_pre;   /* the 0x2 bytes before arg0 in func_81868B84, addressed as arg0[-1] */

typedef struct S_81868B84_0 {
    u16 unk_00;
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    void * unk_0C;
    u8 unk_10;
} S_81868B84_0;   /* arg0 in func_81868B84 */

typedef struct S_81868B84_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81868B84_1;   /* temp_v0 in func_81868B84 */

typedef struct S_81868B84_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
} S_81868B84_2;   /* arg1 in func_81868B84 */

typedef struct S_81868B84_3 {
    u8 pad_00[0x16];
    s8 unk_16;
} S_81868B84_3;   /* ((S_81868B84_0 *)arg0)->unk_0C in func_81868B84 */


M2C_UNK func_80024264();
extern void func_8002465C(void) __attribute__((noreturn));
extern void func_80024660(void) __attribute__((noreturn));
s32 func_800644B8();
s32 func_80064584();
s32 func_800A45D8();
extern s32 D_800814A0[];

/* Animate three expanding, rotating points through growth, fade, and completion. */
void func_81868B84(void *effect, void *position) {
    s32 radial_product;
    s32 fade_angle;
    s32 grow_angle;
    s32 fade_point;
    s32 grow_point;
    s32 fade_angle_fixed;
    register s32 grow_angle_fixed ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */
    s32 finish_state;
    u16 angular_speed;
    void *effect_data;
    s16 state;

    effect_data = ((S_81868B84_0 *)effect)->unk_0C;
    ((S_81868B84_1 *)effect_data)->unk_14 = (u16) (((S_81868B84_1 *)effect_data)->unk_14 + 1);
    ((S_81868B84_0 *)effect)->unk_02.s = (u16) (((S_81868B84_0 *)effect)->unk_02.s + 1);
    state = *(s16 *)effect;
    if (state == 1) {
        goto state1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state0;
        }
        ((S_81868B84_0 *)effect)->unk_00 = 3;
        func_80024660();
        return;
    }
    if (state == 2) {
        goto state2;
    }
    finish_state = 3;
    ASM_KEEP(finish_state);   /* MATCH pin: retail delay-slot contents depend on it */
    if (state == finish_state) {
        goto state3;
    }
    ((S_81868B84_0 *)effect)->unk_00 = 3;
    func_80024660();
    return;

state0:
        ((S_81868B84_2 *)position)->unk_0A = (u16) (((S_81868B84_2 *)position)->unk_0A - 4);
        func_80024264(((S_81868B84_0 *)effect)->unk_0C, position, ((S_81868B84_0 *)effect)->unk_10);
        if (((S_81868B84_0 *)effect)->unk_02.u < 8) {
            return;
        }
        {
            s32 next_state;
            next_state = ((S_81868B84_0 *)effect)->unk_00 + 1;
            ((S_81868B84_0 *)effect)->unk_02.s = 0U;
            ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_8002465C();
        }
        return;
state1:
        grow_point = 0;
        grow_angle_fixed = grow_point;
        ((S_81868B84_0 *)effect)->unk_06 = (u16) (((S_81868B84_0 *)effect)->unk_06 + 6);
        angular_speed = ((S_81868B84_0 *)effect)->unk_0A + 0x10;
        ((S_81868B84_0 *)effect)->unk_0A = angular_speed;
        ((S_81868B84_0 *)effect)->unk_08 = (u16) (((S_81868B84_0 *)effect)->unk_08 + angular_speed);
        do {
            grow_angle = grow_angle_fixed >> 0x10;
            radial_product = (func_800644B8((s16) ((S_81868B84_0 *)effect)->unk_08 + grow_angle) >> 4) * (s16) ((S_81868B84_0 *)effect)->unk_06;
            ((S_81868B84_2 *)position)->unk_02 = (u16) (((S_81868B84_2 *)position)->unk_0E + (radial_product >> 8));
            radial_product = (func_80064584((s16) ((S_81868B84_0 *)effect)->unk_08 + grow_angle) >> 4) * (s16) ((S_81868B84_0 *)effect)->unk_06;
            ((S_81868B84_2 *)position)->unk_06 = (u16) (((S_81868B84_2 *)position)->unk_12 + (radial_product >> 8));
            if ((func_800A45D8(((S_81868B84_2 *)position)->unk_02, ((S_81868B84_2 *)position)->unk_06, (s16) ((S_81868B84_2 *)position)->unk_0A, radial_product) << 0x10) == 0) {
                func_80024264(((S_81868B84_0 *)effect)->unk_0C, position, ((S_81868B84_0 *)effect)->unk_10);
            }
            grow_angle_fixed += 0x05550000;
            grow_point += 1;
        } while (grow_point < 3);
        if (((S_81868B84_0 *)effect)->unk_02.u < 0x20) {
            return;
        }
        {
            s32 next_state;
            next_state = ((S_81868B84_0 *)effect)->unk_00 + 1;
            ((S_81868B84_0 *)effect)->unk_02.s = 0U;
            ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_8002465C();
        }
        return;
state2:
        fade_point = 0;
        fade_angle_fixed = fade_point;
        ((S_81868B84_0 *)effect)->unk_06 = (u16) (((S_81868B84_0 *)effect)->unk_06 + 6);
        ((S_81868B84_0 *)effect)->unk_08 = (u16) (((S_81868B84_0 *)effect)->unk_08 + ((S_81868B84_0 *)effect)->unk_0A);
        do {
            fade_angle = fade_angle_fixed >> 0x10;
            radial_product = (func_800644B8((s16) ((S_81868B84_0 *)effect)->unk_08 + fade_angle) >> 4) * (s16) ((S_81868B84_0 *)effect)->unk_06;
            ((S_81868B84_2 *)position)->unk_02 = (u16) (((S_81868B84_2 *)position)->unk_0E + (radial_product >> 8));
            radial_product = (func_80064584((s16) ((S_81868B84_0 *)effect)->unk_08 + fade_angle) >> 4) * (s16) ((S_81868B84_0 *)effect)->unk_06;
            ((S_81868B84_2 *)position)->unk_06 = (u16) (((S_81868B84_2 *)position)->unk_12 + (radial_product >> 8));
            if ((func_800A45D8(((S_81868B84_2 *)position)->unk_02, ((S_81868B84_2 *)position)->unk_06, (s16) ((S_81868B84_2 *)position)->unk_0A, radial_product) << 0x10) == 0) {
                func_80024264(((S_81868B84_0 *)effect)->unk_0C, position, ((S_81868B84_0 *)effect)->unk_10);
            }
            fade_angle_fixed += 0x05550000;
            fade_point += 1;
        } while (fade_point < 3);
        ((S_81868B84_0 *)effect)->unk_10 = (u8) (((S_81868B84_0 *)effect)->unk_10 - 8);
        if (((S_81868B84_0 *)effect)->unk_02.u < 8) {
            return;
        }
        {
            s32 next_state;
            next_state = ((S_81868B84_0 *)effect)->unk_00 + 1;
            ((S_81868B84_0 *)effect)->unk_02.s = 0U;
            ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_8002465C();
        }
        return;
state3:
        ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
        ((S_81868B84_3 *)(((S_81868B84_0 *)effect)->unk_0C))->unk_16 = 1;
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_81868B84_0_pre *)effect)[-1].unk_00 | 0x8000);
        {
            s32 *global_flags;
            global_flags = D_800814A0;
            global_flags[0] |= 0x8000;
        }
        ((S_81868B84_0 *)effect)->unk_00 = (u16) ((s32 (*)(void)) func_80024660)();
}
