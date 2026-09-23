#include "common.h"
#include "m2c_compat.h"



s32 func_8003BD84();                        /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */

typedef struct {
    s32 pad[3];
    s32 first;
    s32 second;
} FuncData;

/* Add a directional step to the vector and scale it down if it exceeds the length limit. */
void func_80094F58(s16 angle, s32 max_length, FuncData *vector) {
    s32 first_step;
    s32 second_step;
    s32 length;

    first_step = func_800644B8(angle) << 6;
    second_step = func_80064584(angle) << 6;
    vector->first += first_step;
    vector->second += second_step;
    length = func_8003BD84(vector->first, vector->second);
    if (max_length < length) {
        vector->first = vector->first / ((length + 0xFFF) / 0x1000) * (max_length / 0x1000);
        vector->second = vector->second / ((length + 0xFFF) / 0x1000) * (max_length / 0x1000);
    }
}
