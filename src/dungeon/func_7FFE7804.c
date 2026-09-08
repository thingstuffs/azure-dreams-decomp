/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

s32 func_7006DC5C();                             /* extern */
s32 func_7006DD28();                             /* extern */
extern s32 D_80086AD8;


typedef struct S_7FFE7804_0_pre {
    u16 unk_00;
} S_7FFE7804_0_pre;   /* the 0x2 bytes before arg0 in func_7FFE7804, addressed as arg0[-1] */

typedef struct S_7FFE7804_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xF];
    union { s16 s; u16 u; } unk_1E;   /* accessed as both */
    s16 unk_20;
    u8 pad_22[0x6];
    u16 unk_28;
    s16 unk_2A;
    u8 pad_2C[0xC];
    u16 unk_38;
    u16 unk_3A;
} S_7FFE7804_0;   /* arg0 in func_7FFE7804 */

typedef struct S_7FFE7804_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_7FFE7804_1;   /* arg1 in func_7FFE7804 */

typedef struct S_7FFE7804_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_7FFE7804_2;   /* arg2 in func_7FFE7804 */

/* Advance the effect around its center, fade its color, and flag it when its lifetime ends. */
void func_7FFE7804(void *effect, void *position, void *color) {
    s32 life_left;
    u16 next_angle;
    u16 angle;

    angle = ((S_7FFE7804_0 *)effect)->unk_28;
    next_angle = angle + 0xC8;
    ((S_7FFE7804_0 *)effect)->unk_28 = next_angle;
    if ((s16) next_angle >= 0x1001) {
        ((S_7FFE7804_0 *)effect)->unk_28 = (u16) (angle - 0xF38);
    }
    ((S_7FFE7804_1 *)position)->unk_02 = (s16) (((S_7FFE7804_0 *)effect)->unk_38 + ((s32) (((S_7FFE7804_0 *)effect)->unk_2A * func_7006DD28((s16) ((S_7FFE7804_0 *)effect)->unk_28)) >> 0xC));
    ((S_7FFE7804_1 *)position)->unk_06 = (s16) (((S_7FFE7804_0 *)effect)->unk_3A + ((s32) (((S_7FFE7804_0 *)effect)->unk_2A * func_7006DC5C((s16) ((S_7FFE7804_0 *)effect)->unk_28)) >> 0xC));
    ((S_7FFE7804_2 *)color)->unk_0C = (s8) ((s32) (((S_7FFE7804_0 *)effect)->unk_0C * ((S_7FFE7804_0 *)effect)->unk_1E.s) / (s16) ((S_7FFE7804_0 *)effect)->unk_20);
    ((S_7FFE7804_2 *)color)->unk_0D = (s8) ((s32) (((S_7FFE7804_0 *)effect)->unk_0D * ((S_7FFE7804_0 *)effect)->unk_1E.s) / (s16) ((S_7FFE7804_0 *)effect)->unk_20);
    ((S_7FFE7804_2 *)color)->unk_0E = (s8) ((s32) (((S_7FFE7804_0 *)effect)->unk_0E * ((S_7FFE7804_0 *)effect)->unk_1E.s) / (s16) ((S_7FFE7804_0 *)effect)->unk_20);
    life_left = ((S_7FFE7804_0 *)effect)->unk_1E.u - 1;
    ((S_7FFE7804_0 *)effect)->unk_1E.s = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + (-2))) = (u16) (((S_7FFE7804_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_80086AD8 |= 0x8000;
    }
}
