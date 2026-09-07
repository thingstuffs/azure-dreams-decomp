#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80099FDC();                      /* extern */
M2C_UNK func_8009A21C();             /* extern */
s8 func_8009FB34();                           /* extern */
M2C_UNK func_800A2B04();              /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D2E9C;
extern M2C_UNK D_800D3140;
extern M2C_UNK D_800D36D0;
extern M2C_UNK D_800DEF08;

typedef struct S_800D2CB4_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0x2];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
} S_800D2CB4_0;   /* var_s2 in func_800D2CB4 */

typedef struct S_800D2CB4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800D2CB4_1;   /* temp_v0 in func_800D2CB4 */

typedef struct S_800D2CB4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D2CB4_2;   /* temp_s1 in func_800D2CB4 */

typedef struct S_800D2CB4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800D2CB4_3;   /* temp_s0 in func_800D2CB4 */

void *func_800D2CB4(s16 arg0, u8 arg1, u8 arg2, s16 arg3) {
    M2C_UNK var_a2;
    s16 hold_arg0;
    S_800D2CB4_3 *temp_s0;
    S_800D2CB4_2 *temp_s1;
    void *temp_v0;
    S_800D2CB4_0 *var_s2;
    register u8 hold_arg1 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 hold_arg3;
    register u8 hold_arg2 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 kind;
    u8 call_x;
    u8 call_y;

    hold_arg0 = arg0;
    var_s2 = NULL;
    hold_arg1 = arg1;
    hold_arg3 = arg3;
    hold_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s2 = temp_v0 + 0x20;
        var_s2->unk_13 = 0x34;
        kind = (s16) hold_arg0;
        if (kind == 1) {
            var_s2->unk_14 = (s32) (var_s2->unk_14 | 0x2000);
            var_s2->unk_1C = (s32) (var_s2->unk_1C | 0x2000);
        }
        func_8004491C(temp_v0, &D_800D36D0);
        temp_s1 = ((S_800D2CB4_1 *)temp_v0)->unk_08;
        temp_s1->unk_0A = hold_arg3;
        temp_s0 = ((S_800D2CB4_1 *)temp_v0)->unk_0C;
        temp_s0->unk_24 = hold_arg1;
        temp_s0->unk_25 = hold_arg2;
        func_8003DB94(temp_s0, &D_800DEF08, 0);
        temp_s0->unk_12 = 0x7E02;
        temp_s0->unk_1C = 0x1800;
        temp_s0->unk_1E = 0x2000;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        temp_s0->unk_10 = (u16) (temp_s0->unk_10 | 0x20);
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
        ((S_800D2CB4_1 *)temp_v0)->unk_10 = &D_800D2E9C;
        var_s2->unk_8C = &D_800D3140;
        temp_s0->unk_26 = func_8009FB34(temp_s0->unk_24, temp_s0->unk_25);
        func_800A2B04(temp_s1, temp_s0->unk_24, temp_s0->unk_25);
        var_s2->unk_88 = func_800BCB04(temp_s1->unk_02, temp_s1->unk_06, temp_s1->unk_0A);
        temp_s0->unk_0C = 0x808080;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x8000);
        func_80099FDC(temp_v0);
        call_x = temp_s0->unk_24;
        call_y = temp_s0->unk_25;
        var_a2 = 0x3000;
        if (var_s2->unk_1C & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A21C(call_x, call_y, var_a2);
        var_s2->unk_9A = 0xE;
        var_s2->unk_9C = -1;
        var_s2->unk_9E = 0;
        var_s2->unk_1C = (s32) (var_s2->unk_1C | 0x40000200);
    }
    return var_s2;
}

/* MECHANISM: The 0x30 frame comes from the exact s0/s2/s6/s4/s5/s3/s1 hold set,
   with s0 deliberately reused for the later object pointer after arg0 dies.
   Preloaded call bytes remove the +1 displacement cascade; a v0 compare temp
   preserves retail's sll/sra/v1 sequence and closes the final four words. */
