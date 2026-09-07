#include "common.h"

s8 *func_800B1484(s8 *arg0) {
    if (*arg0 >= 0) {
        arg0 += 0xC;
        while (*arg0 >= 0) {
            arg0 += 0xC;
        }
    }
    return arg0;
}
