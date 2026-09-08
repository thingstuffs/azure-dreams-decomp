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

/* Returns a handler result or a fixed fallback address based on the object checks. */
s32 func_8001747C(s32 object, M2C_UNK request, M2C_UNK context) {
    u8 *page_base;
    s32 default_result;
    s32 result;

    if (func_80017E98(object, request) != 0) {
        page_base = (u8 *)0x80020000;
        ASM_KEEP(page_base);
        return (s32)(page_base - 0x49C4);
    }
    default_result = func_80019ABC(&D_8001A9AC, &D_8001B1F8, object, context);
    result = default_result;
    if (func_80019A04(&D_8001A9AC, object, context) != 0) {
        if (func_8001A510(((S_8001747C_0 *)object)->unk_18) != 0) {
            result = func_8001628C(object, request, context);
        } else {
            page_base = (u8 *)0x80020000;
            ASM_KEEP(page_base);
            result = (s32)(page_base - 0x304C);
        }
    }
    return result;
}
