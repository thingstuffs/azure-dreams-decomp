#include "common.h"

typedef struct {
    s16 value;
    s16 first;
    s16 second;
    s16 unused;
} Entry;

extern Entry D_800E3CD8[4];

s16 func_800A4474(s16 arg0, s16 arg1) {
    s32 i;
    s16 value;

    for (i = 0; i < 4; i++) {
        value = D_800E3CD8[i].value;
        if (value < 2) {
            return 0;
        }
        if ((arg0 == D_800E3CD8[i].first) &&
            (arg1 == D_800E3CD8[i].second)) {
            return value;
        }
    }
    return 0;
}
