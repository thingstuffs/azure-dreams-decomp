#include "common.h"

extern void *func_80016250(void *);

extern s32 D_8001967C[3];
extern void *D_80019698[3];
extern u8 D_8001A730[9];
extern u8 D_8001AAEC[9];
extern u8 D_8001DE58[9];

void *func_8001632C(s32 arg0, s32 arg1, s32 arg2) {
    void *result = 0;

    if (arg2 == 8) {
        result = func_80016250(D_80019698[D_8001967C[0]]);
    } else if (arg2 == 6) {
        result = D_8001A730;
    } else if (arg2 == 1) {
        if (D_8001967C[0] != 3) {
            result = D_8001DE58;
        } else {
            result = D_8001AAEC;
        }
    }

    return result;
}
