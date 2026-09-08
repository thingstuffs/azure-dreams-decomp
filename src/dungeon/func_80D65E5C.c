#include "common.h"

extern s32 rand(void);

/* Returns a random sample below limit, or zero when limit is zero. */
s32 func_8017165C(s32 limit) {
    s32 sample;

    sample = 0;
    if (limit != 0) {
        if (limit < 5) {
            do {
                sample = (rand() & 0xC) >> 2;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x11) {
            do {
                sample = (rand() & 0xF0) >> 4;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x41) {
            do {
                sample = (rand() & 0xFC) >> 2;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x101) {
            do {
                sample = (rand() & 0xFF0) >> 4;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x1001) {
            do {
                sample = rand() & 0xFFF;
            } while (sample >= limit);
            return sample;
        }
        do {
            sample = rand() & 0xFFFF;
        } while (sample >= limit);
    }

    return sample;
}
