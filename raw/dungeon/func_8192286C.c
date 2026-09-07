#include "common.h"

s32 func_80069EF8(void);
s32 func_80024184(void) __attribute__((noreturn));

s32 func_8192286C(s32 limit) {
    register s32 result ASM_REG("$2");
    s32 value;

    if (limit < 0) {
        limit = 0;
    }

    value = 0;
    if (limit != 0) {
        if (limit < 5) {
            do {
                value = (func_80069EF8() & 0xC) >> 2;
            } while (value >= limit);
            result = value;
            ASM_KEEP(result);
            func_80024184();
        }
        if (limit < 0x11) {
            do {
                value = (func_80069EF8() & 0xF0) >> 4;
            } while (value >= limit);
            result = value;
            ASM_KEEP(result);
            func_80024184();
        }
        if (limit < 0x41) {
            do {
                value = (func_80069EF8() & 0xFC) >> 2;
            } while (value >= limit);
            result = value;
            ASM_KEEP(result);
            func_80024184();
        }
        if (limit < 0x101) {
            do {
                value = (func_80069EF8() & 0xFF0) >> 4;
            } while (value >= limit);
            result = value;
            ASM_KEEP(result);
            func_80024184();
        }
        if (limit < 0x1001) {
            do {
                value = func_80069EF8() & 0xFFF;
            } while (value >= limit);
            result = value;
            ASM_KEEP(result);
            func_80024184();
        }
        do {
            value = func_80069EF8() & 0xFFFF;
        } while (value >= limit);
    }
    return value;
}
