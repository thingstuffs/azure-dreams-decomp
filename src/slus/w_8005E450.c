#include "common.h"

/* If a0 is nonzero, calls func_8005D9DC(D_80079500.ptr); success (call returns 0) sets D_800794FC.v=1 and returns 1, otherwise sets D_800794FC.v=0 and returns 0. */
typedef struct S_80079500 {
    void *ptr;
    s32 pad[2];
} S_80079500;
extern S_80079500 D_80079500;

typedef struct S_800794FC {
    s32 v;
    s32 pad[2];
} S_800794FC;
extern S_800794FC D_800794FC;

extern s32 func_8005D9DC(void *arg);

s32 func_8005E450(s32 a0) {
    s32 v0;

    if (a0 != 0) {
        v0 = func_8005D9DC(D_80079500.ptr);
        if (v0 == 0) {
            D_800794FC.v = 1;
            return 1;
        }
    }
    D_800794FC.v = 0;
    return 0;
}
