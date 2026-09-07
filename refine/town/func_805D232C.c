#include "common.h"

extern void *func_80016250(void *);

extern s32 D_8001967C[3];
extern void *D_80019698[3];
extern u8 D_8001A730[9];
extern u8 D_8001AAEC[9];
extern u8 D_8001DE58[9];

/* Returns data selected by kind and the current global index. */
void *func_8001632C(s32 unused_0, s32 unused_1, s32 data_kind) {
    void *data = 0;

    if (data_kind == 8) {
        data = func_80016250(D_80019698[D_8001967C[0]]);
    } else if (data_kind == 6) {
        data = D_8001A730;
    } else if (data_kind == 1) {
        if (D_8001967C[0] != 3) {
            data = D_8001DE58;
        } else {
            data = D_8001AAEC;
        }
    }

    return data;
}
