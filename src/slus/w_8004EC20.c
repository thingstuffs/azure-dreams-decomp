#include "common.h"

typedef struct S_8004EC20 {
    u8 pad00[4];
    s32 idx;       /* 0x4: index into D_80071654 callback table */
    u8 b8;         /* 0x8 */
    u8 b9;         /* 0x9 */
} S_8004EC20;

extern s32 func_8004EBDC(void);
extern void func_80044618(s32);

extern s32 (*D_80071654[])(void *);

/* If both flags are set, wait for readiness and return the selected callback's result; otherwise return zero. */
s32 func_8004EC20(S_8004EC20 *dispatch) {
    s32 result = 0;

    if (dispatch->b8 != 0) {
        if (dispatch->b9 != 0) {
            while (func_8004EBDC() == 0) {
                func_80044618(2);
            }
            result = D_80071654[dispatch->idx]((void *)((u8 *)dispatch - 0x20));
        }
    }
    return result;
}
