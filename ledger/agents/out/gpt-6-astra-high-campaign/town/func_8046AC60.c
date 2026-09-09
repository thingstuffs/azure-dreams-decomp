#include "common.h"

extern s32 func_8001A4F0(void);
extern s32 func_8001A58C(s32, s32, s32, s32);

/* Return the candidate if func_8001A58C succeeds, otherwise use func_8001A4F0. */
s32 func_8001BC60(s32 candidate, s32 first_value, s32 second_value, s32 third_value) {
    if (func_8001A58C(candidate, first_value, second_value, third_value) != 0) {
        return candidate;
    }
    return func_8001A4F0();
}
