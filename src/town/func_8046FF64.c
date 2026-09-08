#include "common.h"

s32 func_80017E98(void *, s32);
s32 func_80019A04();
s32 func_80019ABC();
s32 func_8001A510();

extern s32 D_8001A98C;
extern s32 D_8001B1F8;
extern s32 D_8001B6D0;
extern s32 D_8001F690;
extern s8 D_8001FB7F;

/* Selects a result for an object based on validation checks. */
s32 func_80016F64(void *object, s32 check_mode, s32 context) {
    register s32 *data_table ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 result;
    s32 status_or_base;

    status_or_base = func_80017E98(object, check_mode);
    data_table = (s32 *)0x80020000;
    if (status_or_base != 0) {
        if (func_8001A510(*(s16 *)((s8 *)object + 0x18)) == 0) {
            status_or_base = 0x80020000;
            ASM_KEEP(status_or_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            return status_or_base - 0x4930;
        }
    }

    data_table = (s32 *)((s8 *)data_table - 0x5674);
    result = func_80019ABC(data_table, &D_8001B1F8, object, context);
    if (func_80019A04(data_table, object, context) != 0) {
        status_or_base = func_8001A510(*(s16 *)((s8 *)object + 0x18));
        if (status_or_base == 0) {
            ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            status_or_base = 0x80020000;
            ASM_KEEP(status_or_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            result = status_or_base - 0x970;
        } else {
            status_or_base = 0x80020000;
            ASM_KEEP(status_or_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            result = status_or_base - 0x481;
        }
    }
    return result;
}
