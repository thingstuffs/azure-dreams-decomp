#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_8004B248();                      /* extern */
s32 func_800B677C();                             /* extern */
M2C_UNK func_800B691C(); /* extern */
s32 func_800B6990();                 /* extern */
void func_800B6AE8();                               /* extern */
extern M2C_UNK D_8004CAA0;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_800B6754;

typedef struct S_800B6A0C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800B6A0C_0;   /* var_s0 in func_800B6A0C */

typedef struct S_800B6A0C_1 {
    u8 pad_00[0x94];
    s32 unk_94;
    s32 unk_98;
} S_800B6A0C_1;   /* temp_s1 in func_800B6A0C */

void *func_800B6A0C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3, s32 arg4) {
    S_800B6A0C_1 *temp_s1;
    void *var_s0;

    var_s0 = func_8003FC64(0);
    temp_s1 = var_s0 + 0x20;
    if (var_s0 != NULL) {
        if (func_800B6990(temp_s1, 0x18) != 0) {
            ((S_800B6A0C_0 *)var_s0)->unk_0C = (void *) (var_s0 + 0xA8);
            temp_s1->unk_94 = func_800B677C(temp_s1->unk_98);
            func_800B691C(temp_s1, arg0, arg1, arg2, arg3, arg4);
            ((S_800B6A0C_0 *)var_s0)->unk_10 = &D_800B6754;
            func_8004491C(var_s0, &D_8004CAA0);
            return var_s0;
        }
        func_8004B248(var_s0 + 0xBC);
        ((S_800B6A0C_0 *)var_s0)->unk_1E = (u16) (((S_800B6A0C_0 *)var_s0)->unk_1E | 0x8000);
        var_s0 = NULL;
        D_800814A0 = (s32) (D_800814A0 | 0x8000);
    }
    return var_s0;
}
/* MECHANISM: Four incoming args stay live into the six-arg initializer, producing the retail
   s2/s4/s5/s3 holds while the allocation and its +0x20 base occupy s0/s1.
   Discarding the tail helper result returns s0; one shared fallthrough return removes the
   extra jump and its +1-word branch-displacement cascade after the direct global RMW. */
