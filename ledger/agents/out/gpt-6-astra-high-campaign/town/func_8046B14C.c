#include "common.h"

extern void func_8001C108(void);
extern u8 D_8001786E[];
extern u8 D_8001914C[];
extern u8 D_8001EEA7[];
extern u8 D_8001F0AA[];

/* Select data by mode, initializing the data for mode 0. */
u8 *func_8001C14C(s32 unused_0, s32 unused_1, s32 mode) {
    u8 *data;

    if (mode == 4) {
        return D_8001EEA7;
    }
    if (mode == 5) {
        return D_8001786E;
    }
    if (mode != 0) {
        data = D_8001914C;
    } else {
        func_8001C108();
        data = D_8001F0AA;
    }
    return data;
}
