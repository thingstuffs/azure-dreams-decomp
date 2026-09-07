#include "common.h"

s32 func_80017A54();         /* extern */
void *func_80017B0C();       /* extern */
extern s32 D_80018968;
extern s32 D_80019104;
extern s32 D_800197D0;
extern s32 D_80019397;

/* Looks up an entry and substitutes special results for codes 0x2D and 0x2F. */
void *func_80016118(void *input, s32 unused_1, s32 input_code, s32 unused_3) {
    void *lookup_input;
    s32 code;
    void *result;

    lookup_input = input;
    code = input_code;
    {
        void *lookup_data = &D_80018968;

        result = func_80017B0C(lookup_data, &D_80019104, lookup_input, code);
        if (code == 0x2D) {
            if (func_80017A54(lookup_data, lookup_input, 0x2D) != 0) {
                return &D_800197D0;
            }
        }
    }
    if (code == 0x2F) {
        if (func_80017A54(&D_80018968, lookup_input, 0x2F) != 0) {
            return &D_80019397;
        }
    }
    return result;
}
