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

void func_8186EDA8(DungeonState *arg0, S_8186EDA8_0 *arg1, DungeonEffect *arg2) {
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s32 var_a0;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 effect_x;
    u16 effect_y;
    u8 effect_c;
    u8 effect_d;
    u8 effect_e;
    u8 temp_v1_3;
    DungeonEffect *effect = arg2;
    u16 *flag_page = (u16 *)0x80020000;
    s32 first_angle = arg0->angle;

    ASM_USE_NV(flag_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    
    arg1->unk_00 = (s32) (arg0->base0 + (arg0->count * func_800644B8((flag_page[0x2984] = 1, first_angle)) * 0x10));
    arg1->unk_04 = (s32) (arg0->base1 + (arg0->count * func_80064584(arg0->angle) * 0x10));
    func_800478B8(effect);
    temp_v1 = arg0->state;
    if (temp_v1 == 1) {
        goto case_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto case_0;
        }
        func_80024874();
        return;
    }
    if (temp_v1 == 2) {
        goto case_2;
    }
    if (temp_v1 == 3) {
        goto case_3;
    }
    func_80024874();
    return;

case_0:
            temp_v0 = ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_04 - 1;
            ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_04 = temp_v0;
            if ((temp_v0 << 0x10) <= 0) {
                u16 state_plus_one = ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_02.s + 1;
                ASM_TAILSLOT_PIN(state_plus_one);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                func_80024770();
                return;
            }
            goto block_41;

case_1:
            temp_v1_4 = (u16) ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0E - ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_10;
            ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0E = temp_v1_4;
            if (temp_v1_4 < 0) {
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0E = (s16) (temp_v1_4 + 0x1000);
            }
            if ((s16) ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_10 < 0x7F8) {
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_10 = (u16) (((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_10 + 8);
            }
            temp_v1_5 = ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0C;
            if (temp_v1_5 >= 0x41) {
                if (temp_v1_5 >= 0x65) {
                    s32 tail_arg = 3;
                    ASM_TAILSLOT_PIN(tail_arg);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    func_80024710(tail_arg);
                    return;
                }
                var_a0 = 2;
                if (temp_v1_5 < 0x47) {
                    var_a0 = 1;
                    if (temp_v1_5 >= 0x33) {
                        var_a0 = 2;
                    }
                }
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0C = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0C - var_a0);
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
            ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_04 = 0x28U;
            ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_02.u = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_02.u + 1);
            func_80024874();
            return;

case_2:
            temp_v1_2 = (u16) ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0E - ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_10;
            ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0E = temp_v1_2;
            if (temp_v1_2 < 0) {
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0E = (s16) (temp_v1_2 + 0x1000);
            }
            if ((s16) ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_10 < 0x100) {
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_10 = (u16) (((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_10 + 8);
            }
            temp_v1_5 = ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0C;
            if (temp_v1_5 >= 0x1B) {
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_0C = (s16) (temp_v1_5 - 1);
            }
            temp_v1_3 = effect->c;
            if (temp_v1_3 >= 2U) {
                effect->c = (u8) (temp_v1_3 - 2);
                effect->d -= 2;
                effect->e -= 2;
            }
            if (effect->c == 0) {
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_04 = 0U;
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_02.u = (s16) ((u16) ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_02.u + 1);
            }
            effect->x1C -= 0x14;
            effect->y1E += 0xC8;
            func_80024874();
            return;

case_3:
            temp_v0_2 = ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_04 - 1;
            ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_04 = temp_v0_2;
            if ((temp_v0_2 << 0x10) <= 0) {
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
                D_800814A0[0] |= 0x8000;
            }
block_41:
            if (effect->flags14 & 0x8000) {
                ((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_8186EDA8_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
                D_800814A0[0] |= 0x8000;
            }
            return;

}
