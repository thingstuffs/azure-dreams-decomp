#include "common.h"

extern u8 *D_8001E950[];
extern u8 D_8001FD7A[];

u8 *func_8001CF1C(void) {
    D_8001E950[0][5] = 0;
    D_8001E950[0][1] = 2;
    return D_8001FD7A;
}
