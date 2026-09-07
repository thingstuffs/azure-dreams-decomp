#include "common.h"
#include "m2c_compat.h"

M2C_UNK *func_80016E00();                        /* extern */
s32 func_800178A8();             /* extern */
M2C_UNK *func_80017960(); /* extern */
s32 func_8001868C();                         /* extern */
s32 func_80018868();                /* extern */
M2C_UNK func_800188E8();       /* extern */
extern M2C_UNK D_800189BC;
extern M2C_UNK D_80018B94;
extern M2C_UNK D_8001A04A;

/* Selects a request result and conditionally advances a three-state cursor. */
M2C_UNK *func_806D4430(s32 entry_id, s32 unused, s32 request_id) {
    M2C_UNK *result;
    s32 cursor;

    result = func_80016E00(request_id);
    if (result != NULL) {
        return result;
    }
    result = func_80017960(&D_800189BC, &D_80018B94, entry_id, request_id);
    cursor = func_80018868(0x990, 2);
    if (func_8001868C(0x997) == 0) {
        cursor++;
        if (cursor == 3) {
            cursor = 0;
        }
        func_800188E8(0x990, cursor, 2);
    }
    if ((request_id == 0xB) && (func_800178A8(&D_800189BC, entry_id, 0xB) != 0)) {
        result = &D_8001A04A;
    }
    return result;
}
