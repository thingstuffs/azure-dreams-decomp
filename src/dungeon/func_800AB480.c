#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8006658C();                 /* extern */
M2C_UNK func_800666F4();                      /* extern */

typedef struct S_800B0BE0_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    u8 pad_10[0x4];
    s8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x4];
    u8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x6];
    s8 unk_24;
    s8 unk_25;
} S_800B0BE0_0;   /* arg3 in func_800B0BE0 */

typedef struct S_800B0BE0_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
} S_800B0BE0_1;   /* arg1 in func_800B0BE0 */

typedef struct S_800B0BE0_2 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
} S_800B0BE0_2;   /* *arg2 in func_800B0BE0 */

typedef struct S_800B0BE0_3 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800B0BE0_3;   /* temp_v1 in func_800B0BE0 */

typedef struct S_800B0BE0_4 {
    u8 pad_00[0x9];
    u8 unk_09;
    u8 pad_0A[0x1];
    u8 unk_0B;
} S_800B0BE0_4;   /* temp_v1_2 in func_800B0BE0 */

typedef struct S_800B0BE0_5 {
    s8 unk_00;
} S_800B0BE0_5;   /* temp_v1_3 in func_800B0BE0 */

void *func_800B0BE0(s32 arg0, S_800B0BE0_1 *arg1, void **arg2, void *arg3) {
    s32 call_arg0;
    u32 tail_value;
    s8 temp_v0_2;
    s8 temp_v0_4;
    u8 temp_v0;
    u8 temp_v0_3;
    S_800B0BE0_3 *temp_v1;
    S_800B0BE0_4 *temp_v1_2;
    void *temp_v1_3;
    u16 temp_v1_4;

    ((S_800B0BE0_0 *)arg3)->unk_04 = (s32) arg1->unk_0C;
    func_800666F4(arg3);
    ((S_800B0BE0_0 *)arg3)->unk_0E = (u16) ((S_800B0BE0_2 *)(*arg2))->unk_06;
    temp_v1_4 = arg1->unk_10;
    if (temp_v1_4 != 0) {
        tail_value = temp_v1_4 + (((S_800B0BE0_2 *)(*arg2))->unk_04 & 0xFF9F);
    } else {
        tail_value = ((S_800B0BE0_2 *)(*arg2))->unk_04;
    }
    ((S_800B0BE0_0 *)arg3)->unk_16 = (u16) tail_value;
    temp_v0 = ((S_800B0BE0_2 *)(*arg2))->unk_08;
    ((S_800B0BE0_0 *)arg3)->unk_1C = temp_v0;
    ((S_800B0BE0_0 *)arg3)->unk_0C = temp_v0;
    temp_v1 = *arg2;
    temp_v0_2 = (temp_v1->unk_08 + temp_v1->unk_0A) - 1;
    ((S_800B0BE0_0 *)arg3)->unk_24 = temp_v0_2;
    ((S_800B0BE0_0 *)arg3)->unk_14 = temp_v0_2;
    temp_v0_3 = ((S_800B0BE0_2 *)(*arg2))->unk_09;
    ((S_800B0BE0_0 *)arg3)->unk_15 = temp_v0_3;
    ((S_800B0BE0_0 *)arg3)->unk_0D = temp_v0_3;
    temp_v1_2 = *arg2;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    call_arg0 = arg0;
    
    temp_v0_4 = (temp_v1_2->unk_09 + temp_v1_2->unk_0B) - 1;
    ((S_800B0BE0_0 *)arg3)->unk_25 = temp_v0_4;
    ((S_800B0BE0_0 *)arg3)->unk_1D = temp_v0_4;
    func_8006658C(call_arg0, arg3);
    temp_v1_3 = *arg2;
    arg3 += 0x28;
    if (((S_800B0BE0_5 *)temp_v1_3)->unk_00 < 0) {
        *arg2 = NULL;
    } else {
        *arg2 = temp_v1_3 + 0xC;
    }
    return arg3;
}

/* MECHANISM: Four live arguments naturally force the retail 0x28 frame and s3/s0/s2/s1 roles.
   A tied v0 tail-slot pin carries the masked size sum into the first dispatcher jump.
   The second dispatcher is noreturn; a scoped barrier holds its a0 setup in the retail load slot. */
