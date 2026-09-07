#include "common.h"

extern s16 D_80084808[8];
extern s16 D_8008480A[8];
extern s16 D_8008480C[8];

/* Selects a player-stat halfword by index: 2->D_80084808[0], 1->D_8008480A[0], 4->D_8008480C[0], else 0 */
s32 func_80053E90(s32 arg0) {
    s32 v0;
    if (arg0 == 2) {
        goto L_case2;
    }
    if (arg0 >= 3) {
        goto L_ge3;
    }
    if (arg0 == 1) {
        goto L_case1;
    }
    v0 = 0;
    goto L_end;
L_ge3:
    if (arg0 != 4) {
        v0 = 0;
        goto L_end;
    }
    v0 = D_8008480C[0];
    goto L_end;
L_case1:
    v0 = D_8008480A[0];
    goto L_end;
L_case2:
    v0 = D_80084808[0];
L_end:
    return v0;
}
