#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
extern M2C_UNK D_800248BC;
extern M2C_UNK D_80025238;
extern s8 D_8002745C[];

typedef struct S_8195FB34_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8195FB34_0;   /* temp_v0_3 in func_8195FB34 */

typedef struct S_8195FB34_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195FB34_1;   /* temp_v0_4 in func_8195FB34 */

typedef struct S_8195FB34_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_8195FB34_2;   /* temp_a0 in func_8195FB34 */

typedef struct S_8195FB34_3 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x46];
    s16 unk_4C;
} S_8195FB34_3;   /* temp_v1 in func_8195FB34 */

void func_8195FB34(s16 arg0, s16 arg1, s16 arg2) {
    s16 var_a1;
    s16 var_v1;
    s16 temp_v0;
    s16 temp_v0_2;
    s32 var_v0;
    s8 *base;
    s8 *row;
    void *call_arg;
    void *callback;
    S_8195FB34_2 *temp_a0;
    void *temp_v0_3;
    S_8195FB34_1 *temp_v0_4;
    S_8195FB34_3 *temp_v1;

    var_a1 = 0;
    base = D_8002745C;
    do {
        var_v1 = 0;
        row = (s8 *)(((s32) (var_a1 << 0x10) >> 0xC) + (u32)base);
loop_2:
        var_v0 = var_v1 << 0x10;
        *(s16 *)((var_v0 >> 0xF) + (u32)row) = 0;
        temp_v0_2 = var_v1 + 1;
        var_v1 = temp_v0_2;
        if (temp_v0_2 < 8) {
            goto loop_2;
        }
        temp_v0 = var_a1 + 1;
        var_a1 = temp_v0;
    } while (temp_v0 < 8);
    temp_v0_3 = func_8003FC64(0x202);
    if (temp_v0_3 != NULL) {
        call_arg = temp_v0_3;
        
        callback = &D_800248BC;
        
        ((S_8195FB34_0 *)temp_v0_3)->unk_10 = callback;
        func_8004491C(call_arg, &D_80025238);
        temp_v0_4 = ((S_8195FB34_0 *)temp_v0_3)->unk_08;
        temp_v0_4->unk_02 = arg0;
        temp_v0_4->unk_06 = arg1;
        temp_v0_4->unk_0A = arg2;
        temp_a0 = ((S_8195FB34_0 *)temp_v0_3)->unk_0C;
        temp_a0->unk_1E = 0x2000;
        temp_a0->unk_1C = 0x2000;
        temp_a0->unk_0C = 0x808080;
        temp_v1 = temp_v0_3 + 0x20;
        temp_a0->unk_10 = 0x20;
        ((S_8195FB34_0 *)temp_v0_3)->unk_20 = 0xF8F82CC0;
        temp_v1->unk_04 = 0x13D;
        temp_a0->unk_08 = temp_v1;
        temp_v1->unk_4C = 0x10;
    }
}

/* MECHANISM: The one-argument allocator ABI releases a1/a2 for retail's loop roles.
   Initializing the inner counter inside the outer body fixes the save/init schedule.
   Integer-form offset-plus-base sums preserve both retail addu operand orders. */
