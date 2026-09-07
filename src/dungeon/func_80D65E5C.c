#include "common.h"

extern s32 rand(void);

s32 func_8017165C(s32 arg0) {
    s32 value;

    value = 0;
    if (arg0 != 0) {
        if (arg0 < 5) {
            do {
                value = (rand() & 0xC) >> 2;
            } while (value >= arg0);
            return value;
        }
        if (arg0 < 0x11) {
            do {
                value = (rand() & 0xF0) >> 4;
            } while (value >= arg0);
            return value;
        }
        if (arg0 < 0x41) {
            do {
                value = (rand() & 0xFC) >> 2;
            } while (value >= arg0);
            return value;
        }
        if (arg0 < 0x101) {
            do {
                value = (rand() & 0xFF0) >> 4;
            } while (value >= arg0);
            return value;
        }
        if (arg0 < 0x1001) {
            do {
                value = rand() & 0xFFF;
            } while (value >= arg0);
            return value;
        }
        do {
            value = rand() & 0xFFFF;
        } while (value >= arg0);
    }

    return value;
}
