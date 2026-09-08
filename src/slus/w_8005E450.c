#include "common.h"

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

/* If enabled, checks the stored pointer and records and returns whether the check succeeded. */
s32 func_8005E450(s32 enabled) {
    s32 check_result;

    if (enabled != 0) {
        check_result = func_8005D9DC(D_80079500.ptr);
        if (check_result == 0) {
            D_800794FC.v = 1;
            return 1;
        }
    }
    D_800794FC.v = 0;
    return 0;
}
