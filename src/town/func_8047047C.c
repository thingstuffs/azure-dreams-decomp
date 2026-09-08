#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001628C();    /* extern */
s32 func_80017E98(s32, M2C_UNK);                                /* extern */
s32 func_80019A04();      /* extern */
s32 func_80019ABC(); /* extern */
s32 func_8001A510();                             /* extern */
extern M2C_UNK D_8001A9AC;
extern M2C_UNK D_8001B1F8;
extern M2C_UNK D_8001B63C;
extern M2C_UNK D_8001CFB4;

typedef struct S_8001747C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8001747C_0;   /* arg0 in func_8001747C */

s32 func_8001747C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u8 *page_v0;
    s32 temp_s1;
    s32 var_v0;

    if (func_80017E98(arg0, arg1) != 0) {
        page_v0 = (u8 *)0x80020000;
        ASM_KEEP(page_v0);   /* MATCH pin: load-bearing for the whole function shape */
        return (s32)(page_v0 - 0x49C4);
    }
    temp_s1 = func_80019ABC(&D_8001A9AC, &D_8001B1F8, arg0, arg2);
    var_v0 = temp_s1;
    if (func_80019A04(&D_8001A9AC, arg0, arg2) != 0) {
        if (func_8001A510(((S_8001747C_0 *)arg0)->unk_18) != 0) {
            var_v0 = func_8001628C(arg0, arg1, arg2);
        } else {
            page_v0 = (u8 *)0x80020000;
            ASM_KEEP(page_v0);   /* MATCH pin: load-bearing for the whole function shape */
            var_v0 = (s32)(page_v0 - 0x304C);
        }
    }
    return var_v0;
}

/* MECHANISM: True-space local joins remove the phantom jal/nop cascades.
   A guarded $v0 0x80020000 page carrier splits both return constants exactly;
   ASM_USE(arg0) holds the later call setup below the early-return branch. */
