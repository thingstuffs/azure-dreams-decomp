#include "dungeon/system/project_and_queue_visible_shaded_quad.h"


s32 project_and_queue_visible_shaded_quad(s32 limit) {
    s16 result;
    s32 sample;

    if (limit < 0) {
        limit = 0;
    }

    sample = 0;
    if (limit != 0) {
        if (limit < 5) {
            do {
                sample = (func_80069EF8() & 0xC) >> 2;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x11) {
            do {
                sample = (func_80069EF8() & 0xF0) >> 4;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x41) {
            do {
                sample = (func_80069EF8() & 0xFC) >> 2;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x101) {
            do {
                sample = (func_80069EF8() & 0xFF0) >> 4;
            } while (sample >= limit);
            return sample;
        }
        if (limit < 0x1001) {
            do {
                sample = func_80069EF8() & 0xFFF;
            } while (sample >= limit);
            return sample;
        }
        do {
            sample = func_80069EF8() & 0xFFFF;
        } while (sample >= limit);
    }
    return sample;
}
