#include "common.h"
#include "m2c_compat.h"

s32 func_80016D98();                         /* extern */
M2C_UNK func_80017960(); /* extern */
extern M2C_UNK D_800189A4;
extern M2C_UNK D_80018B94;

/* Submit the request with the shared data when its flag is clear. */
void func_806D4204(s32 request_id, M2C_UNK unused, M2C_UNK flag_id) {
    if (func_80016D98(flag_id) == 0) {
        func_80017960(&D_800189A4, &D_80018B94, request_id, flag_id);
    }
}
