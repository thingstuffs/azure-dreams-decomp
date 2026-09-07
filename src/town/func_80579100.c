#include "common.h"
#include "m2c_compat.h"

typedef struct S_80579100_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_80579100_0;   /* D_80016000 in func_80579100 */

typedef struct S_80579100_1 {
    u8 pad_00[0x35C0];
    s16 unk_35C0;
} S_80579100_1;   /* temp_a1 in func_80579100 */


M2C_UNK func_80017398();             /* extern */
extern S_80579100_0 *D_80016000;
extern M2C_UNK D_80017500;
extern s16 D_800175B4;
extern M2C_UNK *D_800175B8;

void func_80579100(void) {
    S_80579100_1 *temp_a1;
    s32 temp_v1;

    temp_a1 = D_80016000->unk_38;
    temp_v1 = temp_a1->unk_35C0;
    D_800175B8 = &D_80017500;
    if (temp_v1 < 0x1E) {
        temp_a1->unk_35C0 = 0x1E;
    }
    func_80017398(0x5D9, temp_a1);
    func_80017398(0x5DA);
    D_800175B4 = 0;
    func_80017398(0x5DB);
}

/* MECHANISM: A named s32 local orders the signed halfword read before the pointer store
   while preserving retail's single lh; the natural ABI yields a 0x18 ra-only frame.
   The cdk lineage schedules the final halfword store before jal with the literal in its slot. */
