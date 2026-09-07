#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B835C(); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800A5828;
extern M2C_UNK D_800DD854;
extern M2C_UNK D_800DD860;

typedef struct S_800A5A18_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800A5A18_0;   /* temp_v0 in func_800A5A18 */

typedef struct S_800A5A18_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_800A5A18_1;   /* temp_v1 in func_800A5A18 */

typedef struct S_800A5A18_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x5E];
    s16 unk_66;
} S_800A5A18_2;   /* temp_v1_2 in func_800A5A18 */

void *func_800A5A18(s32 arg0, s32 arg1) {
    s32 stack_args[2];
    void *temp_v0;
    S_800A5A18_1 *temp_v1;
    S_800A5A18_2 *temp_v1_2;

    temp_v0 = func_8003FD64(0x212, &D_80083498);
    if (temp_v0 != NULL) {
        ((S_800A5A18_0 *)temp_v0)->unk_10 = &D_800A5828;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = ((S_800A5A18_0 *)temp_v0)->unk_0C;
        ((S_800A5A18_0 *)temp_v0)->unk_08 = arg0;
        temp_v1->unk_08 = &D_800DD854;
        temp_v1->unk_1E = 0x1000;
        temp_v1->unk_1C = 0x1000;
        temp_v1_2 = temp_v0 + 0x20;
        temp_v1_2->unk_04 = arg1;
        temp_v1_2->unk_66 = 4;
        stack_args[0] = 0x01800340;
        stack_args[1] = 0x400040;
        func_800B835C(&D_800DD860, stack_args, 1, 0);
        func_800A56E0(0x60F);
    }
    return temp_v0;
}

/* MECHANISM: Model the callee workspace as one escaping s32[2] stack record,
   fixing the sp+0x10/sp+0x14 identity, constant stores, and argument pointer.
   Long-lived args/result naturally produce the 0x28 frame and s1/s2/s0 saves. */
