/* Selector 72, retail file [0x19DED8C, 0x19DEEB0); complete callable clone. */
#include "common.h"

extern s32 rand(void);

/* Returns a uniform random sample in [0, limit) by rejection: the rand() bits are masked down to the
 * smallest bit range that covers limit, and the draw repeats while it is out of range.  Zero when limit is zero. */
s32 func_8002458C(s32 limit) {
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
