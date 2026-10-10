#include "modules/dungeon_ovl_192a800.h"
#include "common.h"

extern s32 rand(void);

/* Returns a random value in [0, limit), or zero when limit is zero. Rejection sampling: the rand() bits are masked
 * to the smallest bit range that covers limit (2, 4, 6, 8, 12 or 16 bits) and redrawn until below limit. */
s32 func_80024590(s32 limit) {
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
