#include "common.h"
#include "m2c_compat.h"

u8 *get_special_data_by_id(s32 id);
s32 func_800178A8();             /* extern */
s32 * func_80017960(void *, void *, s32, s32);
s32 func_8001868C();                         /* extern */
s32 func_80018868();                /* extern */
s32 func_800188E8(s32, s32, s32);
extern M2C_UNK D_800189BC;
extern M2C_UNK D_80018B94;
extern M2C_UNK D_8001A04A;

/* Selects a request result and conditionally advances a three-state cursor. */
s32 *select_request_conditionally_three_state(s32 entry_id, s32 unused, s32 request_id) {
    s32 *result;
    s32 cursor;

    result = get_special_data_by_id(request_id);
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
