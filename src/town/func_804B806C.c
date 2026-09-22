#include "common.h"
#include "m2c_compat.h"

s32 func_8001894C();
s32 func_80018044();
extern M2C_UNK D_80018B18;
extern M2C_UNK D_80018E38;
extern u8 D_8001C59A[16];

/* Look up the slot's record, falling back to the default table when the query fails. */
void *func_8001686C(s32 slot, M2C_UNK unused, M2C_UNK context) {
    if (func_8001894C(0x510) == 0) {
        return (void *)func_80018044(&D_80018B18, &D_80018E38, slot, context);
    }
    return D_8001C59A;
}
