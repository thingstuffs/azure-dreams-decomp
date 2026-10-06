#include "common.h"
#include "m2c_compat.h"
typedef struct S_800491F4 S_800491F4;

S_800491F4 *func_800491F4(S_800491F4 **, u8 *, s32);  /* extern */
extern u8 D_800294E8;

/* Calls func_800491F4 with the context, shared data, and value 13. */
void func_80025D74(S_800491F4 **context) {
    func_800491F4(context, &D_800294E8, 13);
}
