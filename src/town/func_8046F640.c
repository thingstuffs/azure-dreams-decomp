#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK *func_8001628C();
extern s32 func_80017E98(s32, M2C_UNK);
extern M2C_UNK func_80019880(void);
extern s32 func_80019A04();
extern M2C_UNK *func_80019ABC();
extern s32 func_8001A7F8();

extern M2C_UNK D_8001A94C;
extern M2C_UNK D_8001B1F8;
extern M2C_UNK D_8001B63C;
extern M2C_UNK D_80020E5C;

M2C_UNK *func_80016640(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u8 *page_v0;
    M2C_UNK *var_s0;

    if (func_80017E98(arg0, arg1) != 0) {
#ifdef NON_MATCHING
        return &D_8001B63C;
#else
        page_v0 = (u8 *)0x80020000;
        ASM_KEEP(page_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        return (M2C_UNK *)(page_v0 - 0x49C4);
#endif
    }
    var_s0 = func_80019ABC(&D_8001A94C, &D_8001B1F8, arg0, arg2);
    if (func_8001A7F8() >= 5) {
        func_80019880();
#ifdef NON_MATCHING
        var_s0 = &D_80020E5C;
#else
        page_v0 = (u8 *)0x80020000;
        ASM_KEEP(page_v0);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        var_s0 = (M2C_UNK *)(page_v0 + 0xE5C);
#endif
    }
    if (func_80019A04(&D_8001A94C, arg0, arg2) != 0) {
        var_s0 = func_8001628C(arg0, arg1, arg2);
    }
    return var_s0;
}
