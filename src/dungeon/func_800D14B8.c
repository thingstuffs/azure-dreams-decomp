#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D6C18_0_pre {
    u16 unk_00;
} S_800D6C18_0_pre;   /* the 0x2 bytes before arg0 in func_800D6C18, addressed as arg0[-1] */

typedef struct S_800D6C18_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u8 pad_18[0x3C];
    s16 unk_54;
    s16 unk_56;
} S_800D6C18_0;   /* arg0 in func_800D6C18 */

typedef struct S_800D6C18_1 {
    u8 pad_00[0x14];
    u32 unk_14;
} S_800D6C18_1;   /* temp_v1 in func_800D6C18 */

typedef struct S_800D6C18_2 {
    u8 pad_00[0x14];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_14;   /* overlapping accesses */
} S_800D6C18_2;   /* arg1 in func_800D6C18 */

typedef struct S_800D6C18_3 {
    u8 pad_00[0x44];
    s16 unk_44;
    u8 pad_46[0x6];
    s16 unk_4C;
} S_800D6C18_3;   /* var_a0 in func_800D6C18 */


M2C_UNK func_800D6AD4(); /* extern */
extern M2C_UNK D_800814A0;

void func_800D6C18(void *arg0, S_800D6C18_2 *arg1) {
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 var_s0;
    s32 var_s1;
    u32 temp_v0;
    S_800D6C18_1 *temp_v1;
    void *var_a0;
    s32 *global_base;

    temp_v1 = ((S_800D6C18_0 *)arg0)->unk_14;
    if (((S_800D6C18_0 *)arg0)->unk_0C >= 0xF) {
        temp_v0 = temp_v1->unk_14;
        arg1->unk_14.at00.v = (s32) (arg1->unk_14.at00.v + ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1));
    }
    temp_v0_2 = arg1->unk_14.at02.v + 0x10;
    ((S_800D6C18_0 *)arg0)->unk_56 = temp_v0_2;
    ((S_800D6C18_0 *)arg0)->unk_54 = temp_v0_2;
    if ((((S_800D6C18_0 *)arg0)->unk_0C < 0x13) && !((u16) ((S_800D6C18_0 *)arg0)->unk_0C & 1)) {
        var_s0 = 0;
        var_a0 = arg0;
        do {
            if (((S_800D6C18_3 *)var_a0)->unk_44 < 0) {
                ((S_800D6C18_3 *)var_a0)->unk_44 = (s16) ((u16) ((S_800D6C18_3 *)var_a0)->unk_44 + 1);
            }
            if (((S_800D6C18_3 *)var_a0)->unk_44 > 0) {
                ((S_800D6C18_3 *)var_a0)->unk_44 = (s16) ((u16) ((S_800D6C18_3 *)var_a0)->unk_44 - 1);
            }
            if (((S_800D6C18_3 *)var_a0)->unk_4C < 0) {
                ((S_800D6C18_3 *)var_a0)->unk_4C = (s16) ((u16) ((S_800D6C18_3 *)var_a0)->unk_4C + 1);
            }
            if (((S_800D6C18_3 *)var_a0)->unk_4C > 0) {
                ((S_800D6C18_3 *)var_a0)->unk_4C = (s16) ((u16) ((S_800D6C18_3 *)var_a0)->unk_4C - 1);
            }
            var_s0 += 1;
            var_a0 += 2;
        } while (var_s0 < 4);
    }
    if ((((S_800D6C18_0 *)arg0)->unk_0C == 0xF) && (((S_800D6C18_0 *)arg0)->unk_10 == 0)) {
        var_s0 = 0;
        var_s1 = 0;
        do {
            s32 delta;
            s32 color;

            color = 0xE0E0E0;
            /*A*/
            func_800D6AD4((void *)((s8 *)arg0 - 0x20), color, 0, 0, var_s1 >> 0x10, (s16) var_s0);
            delta = -0x40000;
            var_s1 += delta;
            ASM_KEEP(delta);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            var_s0 += 1;
        } while (var_s0 < 0x51);
    }
    temp_v0_3 = (u16) ((S_800D6C18_0 *)arg0)->unk_0C - 1;
    ((S_800D6C18_0 *)arg0)->unk_0C = temp_v0_3;
    global_base = (s32 *) 0x80080000;
    if ((temp_v0_3 << 0x10) <= 0) {
        ((S_800D6C18_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800D6C18_0_pre *)arg0)[-1].unk_00 | 0x8000);
        global_base[0x14A0 / 4] |= 0x8000;
    }
}
