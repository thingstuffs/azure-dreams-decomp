#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BB894;

typedef struct Copy24 {
    s32 words[6];
} Copy24;

typedef struct S_800BB798_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800BB798_0;   /* arg0 in func_800BB798 */

typedef struct S_800BB798_1 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800BB798_1;   /* temp_s1 in func_800BB798 */

typedef struct S_800BB798_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} S_800BB798_2;   /* temp_v0 in func_800BB798 */

typedef struct S_800BB798_3 {
    u8 pad_00[0x48];
    s16 unk_48;
    s16 unk_4A;
} S_800BB798_3;   /* temp_v0_2 in func_800BB798 */

s32 func_800BB798(S_800BB798_0 *arg0, s16 arg1, s16 arg2) {
    s32 temp_a0;
    s32 temp_s0;
    s32 temp_s0_2;
    u8 *temp_s1;
    s32 temp_t0;
    s32 temp_v0_math;
    void *temp_v0;
    S_800BB798_3 *temp_v0_2;
    void *temp_v1;

    temp_s1 = D_80083160;
    temp_a0 = arg0->unk_10 + ((S_800BB798_1 *)temp_s1)->unk_C8;
    temp_s0 = arg0->unk_0C;
    temp_v0_math = func_80064584(temp_a0);
    temp_s0_2 = temp_s0 >> 0xC;
    temp_t0 = temp_s0_2 * temp_v0_math;
    arg0->unk_0C = temp_t0;
    temp_a0 = arg0->unk_10 + ((S_800BB798_1 *)temp_s1)->unk_C8;
    temp_v0_math = func_800644B8(temp_a0);
    
    
    temp_t0 = temp_s0_2 * temp_v0_math;
    arg0->unk_10 = temp_t0;
    temp_v0 = func_8003FD64(0x312, &D_80083498);
    if (temp_v0 != NULL) {
        temp_v1 = ((S_800BB798_2 *)temp_v0)->unk_08;
        ((S_800BB798_2 *)temp_v0)->unk_10 = &D_800BB894;
        *(Copy24 *)temp_v1 = *(Copy24 *)arg0;
        temp_v0_2 = temp_v0 + 0x20;
        temp_v0_2->unk_48 = arg1;
        temp_v0_2->unk_4A = arg2;
    }
    return 0;
}

/* MECHANISM: A held D_80083160 base in s1 plus destructive s0 and t0 live ranges
   reproduces the 0x28 frame and both multiply/call schedules.  Splitting each
   call argument and using one 24-byte aggregate copy yields the retail a3 hold
   and grouped v0/a0/a1/a2 loads/stores without load-delay nops. */
