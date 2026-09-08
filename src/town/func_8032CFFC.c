#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_80019D44();
extern M2C_UNK func_80019DFC();
extern M2C_UNK D_8001BB7C;
extern M2C_UNK D_8001C358;
extern u8 D_8001E891;

/* Process the selected entry and return its result or the override pointer. */
s32 func_800177FC(s32 context, s32 unused, M2C_UNK entry_id) {
    M2C_UNK entry_result;

    entry_result = func_80019DFC(&D_8001BB7C, &D_8001C358, context, entry_id);
    return func_80019D44(&D_8001BB7C, context, entry_id) != 0
        ? (s32)&D_8001E891
        : entry_result;
}
