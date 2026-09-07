#include "common.h"

s32 func_80096E9C(s32 *x, s32 *y) {
    s32 side[2];
    s32 distance[4];
    register volatile s32 *page ASM_REG("$6");
    register volatile s32 *state ASM_REG("$7");
    s32 result;
    s32 first;
    s32 vertical;

    page = (volatile s32 *)0x80100000;
    ASM_KEEP(page);
    first = *(volatile s32 *)((s8 *)page - 0x1AE0);
    ASM_SCHED_BARRIER();
    result = 0;
    if (first != 0x80000000) {
        vertical = 2;
        state = (volatile s32 *)((s8 *)page - 0x1AE0);
        ASM_KEEP_NV(state);
        do {
            distance[0] = *x - state[0];
            if (distance[0] > 0) {
                distance[1] = state[1] - *x;
                if (distance[1] > 0) {
                    distance[2] = *y - state[2];
                    if (distance[2] > 0) {
                        distance[3] = state[3] - *y;
                        if (distance[3] > 0) {
                            if (distance[1] < distance[0]) {
                                distance[0] = distance[1];
                                side[0] = 1;
                            } else {
                                side[0] = 0;
                            }
                            if (distance[2] > distance[3]) {
                                distance[2] = distance[3];
                                side[1] = 3;
                            } else {
                                side[1] = vertical;
                            }
                            if (distance[0] > distance[2]) {
                                if (side[1] == vertical) {
                                    result |= 0x100;
                                    *y = state[2];
                                } else {
                                    result |= 0x1000;
                                    *y = state[3];
                                }
                            } else if (side[0] == 0) {
                                result |= 1;
                                *x = state[0];
                            } else {
                                result |= 0x10;
                                *x = state[1];
                            }
                        }
                    }
                }
            }
            state += 4;
        } while (state[0] != 0x80000000);
    }
    return result;
}
