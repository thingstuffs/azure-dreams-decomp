#include "common.h"

extern void func_8001C108(void);
extern u8 D_8001786E[];
extern u8 D_8001914C[];
extern u8 D_8001EEA7[];
extern u8 D_8001F0AA[];

u8 *func_8001C14C(s32 arg0, s32 arg1, s32 arg2) {
    u8 *result;

    if (arg2 == 4) {
        return D_8001EEA7;
    }
    if (arg2 == 5) {
        return D_8001786E;
    }
    if (arg2 != 0) {
        result = D_8001914C;
    } else {
        func_8001C108();
        result = D_8001F0AA;
    }
    return result;
}
