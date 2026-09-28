#include "common.h"

s32 func_80017E98(void *, s32);
s32 func_80019A04();
s32 func_80019ABC();
s32 func_8001A510();

extern s32 D_8001A98C;
extern s32 D_8001B1F8;
extern s32 D_8001B6D0[1];
extern s32 D_8001F690;
extern s8 D_8001FB7F;

/* Selects a result for an object based on validation checks. */
s32 func_80016F64(void *object, s32 check_mode, s32 context) {
    s32 *data_table;
    s32 result;
    s32 status_or_base;

    status_or_base = func_80017E98(object, check_mode);
    if (status_or_base != 0) {
        if (func_8001A510(*(s16 *)((s8 *)object + 0x18)) == 0) {
            return &D_8001B6D0[0];
        }
    }

    data_table = (s32 *)&D_8001A98C;
    result = func_80019ABC(data_table, &D_8001B1F8, object, context);
    if (func_80019A04(data_table, object, context) != 0) {
        status_or_base = func_8001A510(*(s16 *)((s8 *)object + 0x18));
        if (status_or_base == 0) {
            result = &D_8001F690;
        } else {
            result = &D_8001FB7F;
        }
    }
    return result;
}
