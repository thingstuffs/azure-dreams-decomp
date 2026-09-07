#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void *func_80174A00(void *arg0, u16 arg1, u16 arg2, s16 arg3) {
    void *head = arg0;

    arg0 = (void *)(FIELD(arg0, s32, 0x5C) + 0x20);
    while (arg0 != head) {
        void *data = FIELD(arg0, void *, -0x14);
        void *result = arg0 - 0x20;
        s16 value;

        if ((FIELD(data, u8, 0x24) == arg1) &&
            (FIELD(data, u8, 0x25) == arg2) &&
            (value = FIELD(arg0, s16, 0x88), value <= arg3 + 0x20) &&
            (value >= arg3 - 0x20) &&
            ((u32)(FIELD(arg0, u8, 0x13) - 0x33) < 4)) {
            return result;
        }
        arg0 = (void *)(FIELD(arg0, s32, 0x5C) + 0x20);
    }
    return NULL;
}
