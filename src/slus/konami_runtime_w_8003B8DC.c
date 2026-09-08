#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_800B2244();                         /* extern */
extern s32 D_8001029C;

/* Process the global value repeatedly until it becomes zero. */
void func_8003B8DC(void) {
    if (D_8001029C != 0) {
        do {
            func_800B2244(*(s32 *)0x8001029C);
        } while (*(s32 *)0x8001029C != 0);
    }
}
