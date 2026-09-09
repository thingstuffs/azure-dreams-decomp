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

/* Selects a lookup result or a fallback based on the input checks. */
M2C_UNK *func_80016640(s32 selector, M2C_UNK check_value, M2C_UNK lookup_value) {
    u8 *data_page;
    M2C_UNK *result;

    if (func_80017E98(selector, check_value) != 0) {
#ifdef NON_MATCHING
        return &D_8001B63C;
#else
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        return (M2C_UNK *)(data_page - 0x49C4);
#endif
    }
    result = func_80019ABC(&D_8001A94C, &D_8001B1F8, selector, lookup_value);
    if (func_8001A7F8() >= 5) {
        func_80019880();
#ifdef NON_MATCHING
        result = &D_80020E5C;
#else
        data_page = (u8 *)0x80020000;
        ASM_KEEP(data_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        result = (M2C_UNK *)(data_page + 0xE5C);
#endif
    }
    if (func_80019A04(&D_8001A94C, selector, lookup_value) != 0) {
        result = func_8001628C(selector, check_value, lookup_value);
    }
    return result;
}
