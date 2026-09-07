#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK func_800250B4();
extern void *func_80025350();
extern M2C_UNK func_800253C0();
extern s32 func_80026168();
extern s32 func_80026A64();
extern s32 func_8002845C();
extern void *func_8003FC64();
extern s32 func_8004A330();
extern M2C_UNK func_800DBF38();
extern s32 D_80029498;
extern s32 D_800814A0;
extern u8 D_80082E6A;


typedef struct S_80025198_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025198_0;   /* temp_v0 in func_80025198 */

typedef struct S_80025198_1_pre {
    u16 unk_00;
} S_80025198_1_pre;   /* the 0x2 bytes before temp_s2 in func_80025198, addressed as temp_s2[-1] */

typedef struct S_80025198_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} S_80025198_1;   /* temp_s2 in func_80025198 */

typedef struct S_80025198_2 {
    u8 unk_00;
    u8 unk_01;
} S_80025198_2;   /* temp_a1 in func_80025198 */

typedef struct S_80025198_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80025198_3;   /* temp_s0 in func_80025198 */

typedef struct S_80025198_4 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025198_4;   /* var_v1 in func_80025198 */

typedef struct S_80025198_5 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80025198_5;   /* temp_s5 in func_80025198 */

void *func_80025198(s32 arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4) {
    s32 *temp_s0;
    register s32 temp_a0 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    s32 var_a0;
    void *temp_a1;
    void *temp_s2;
    s32 *temp_s5;
    void *temp_v0;
    void *var_v1;

    temp_v0 = func_8003FC64(0);
    if (temp_v0 != NULL) {
        temp_a1 = arg3;
        temp_s2 = temp_v0 + 0x20;
        ((S_80025198_0 *)temp_v0)->unk_20 = arg0;
        ((S_80025198_1 *)temp_s2)->unk_10 = arg1;
        ((S_80025198_1 *)temp_s2)->unk_14 = (s32) ((S_80025198_2 *)temp_a1)->unk_01;
        ((S_80025198_1 *)temp_s2)->unk_18 = arg2;
        ((S_80025198_1 *)temp_s2)->unk_1C = (s32) ((S_80025198_2 *)temp_a1)->unk_00;
        func_800250B4(temp_s2, temp_a1, arg4);
        (*(s32 *)((u8 *)temp_v0 + (0x10))) = 0;
        temp_a0 = 8;
        if (D_80082E6A != 1) {
            func_800DBF38();
            temp_a0 = 8;
        }
        temp_s0 = &D_80029498;
        ((S_80025198_1 *)temp_s2)->unk_2C = func_8004A330(temp_a0, 0xEC, 0x64, 0xEC, 0x64, 0x50, 1, D_80029498);
        ((S_80025198_1 *)temp_s2)->unk_30 = func_8004A330(4, 0xEC, 0x64, 0xEC, 0x74, 0x50, 1, ((S_80025198_3 *)temp_s0)->unk_04);
        ((S_80025198_1 *)temp_s2)->unk_34 = func_8004A330(0x10, 0xEC, 0x64, 0xEC, 0x84, 0x50, 1, ((S_80025198_3 *)temp_s0)->unk_08);
        ((S_80025198_1 *)temp_s2)->unk_20 = func_80026168(temp_v0, ((S_80025198_1 *)temp_s2)->unk_14, ((S_80025198_1 *)temp_s2)->unk_04);
        ((S_80025198_1 *)temp_s2)->unk_24 = func_8002845C(temp_v0, ((S_80025198_1 *)temp_s2)->unk_14);
        ((S_80025198_1 *)temp_s2)->unk_28 = func_80026A64(temp_v0, ((S_80025198_1 *)temp_s2)->unk_14, ((S_80025198_1 *)temp_s2)->unk_04);
        temp_s5 = (s32 *) 0x80080000;
        var_a0 = 0;
        var_v1 = temp_s2;
loop_4:
        var_a0 += 1;
        if (((S_80025198_4 *)var_v1)->unk_20 != 0) {
            goto nonzero;
        }
        func_800253C0(temp_s2);
        ((S_80025198_1_pre *)temp_s2)[-1].unk_00 = (u16) (((S_80025198_1_pre *)temp_s2)[-1].unk_00 | 0x8000);
        temp_v0 = NULL;
        ((S_80025198_5 *)temp_s5)->unk_14A0 |= 0x8000;
        goto end;
nonzero:
        var_v1 += 4;
        if (var_a0 < 3) {
            goto loop_4;
        }
    }
end:
    return temp_v0;
}
