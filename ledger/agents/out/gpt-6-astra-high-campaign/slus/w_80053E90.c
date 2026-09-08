#include "common.h"

extern s16 D_80084808[8];
extern s16 D_8008480A[8];
extern s16 D_8008480C[8];

/* Returns the player stat selected by index 1, 2, or 4, or zero for other indices. */
s32 func_80053E90(s32 stat_index) {
    s32 stat_value;
    if (stat_index == 2) {
        goto L_case2;
    }
    if (stat_index >= 3) {
        goto L_ge3;
    }
    if (stat_index == 1) {
        goto L_case1;
    }
    stat_value = 0;
    goto L_end;
L_ge3:
    if (stat_index != 4) {
        stat_value = 0;
        goto L_end;
    }
    stat_value = D_8008480C[0];
    goto L_end;
L_case1:
    stat_value = D_8008480A[0];
    goto L_end;
L_case2:
    stat_value = D_80084808[0];
L_end:
    return stat_value;
}
