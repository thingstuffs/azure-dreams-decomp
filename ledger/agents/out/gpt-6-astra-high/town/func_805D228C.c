#include "common.h"

extern void func_800193E0(s32);
extern void *func_80016250(void *);

extern s32 D_8001967C[3];
extern void *D_80019688[3];
extern u8 D_8001A730[9];
extern u8 D_8001AAEC[9];
extern u8 D_8001DE58[9];

/* Returns data for the request type and current selection. */
void *func_8001628C(s32 unused_0, s32 unused_1, s32 request_type) {
    void *result = 0;

    if (request_type == 8) {
        func_800193E0(0x1479);
        result = func_80016250(D_80019688[D_8001967C[0]]);
    } else if (request_type == 6) {
        result = D_8001A730;
    } else if (request_type == 1) {
        if (D_8001967C[0] != 3) {
            result = D_8001DE58;
        } else {
            result = D_8001AAEC;
        }
    }

    return result;
}
