#include "common.h"

extern s16 D_80084808[8];
extern s16 D_8008480A[8];
extern s16 D_8008480C[8];

extern void func_80054D64(void);
extern void func_800552C8(void);

/* Sets a player-stat halfword by index: 2->D_80084808[0]=arg0, 1->D_8008480A[0]=arg0
   (also invokes func_800552C8), 4->D_8008480C[0]=arg0 (also invokes func_80054D64),
   else no-op. Mirrors the getter func_80053E90. */
void func_80053E20(s16 arg0, s32 arg1) {
    if (arg1 == 2) {
        goto L_case2;
    }
    if (arg1 >= 3) {
        goto L_ge3;
    }
    if (arg1 == 1) {
        goto L_case1;
    }
    goto L_end;
L_ge3:
    if (arg1 != 4) {
        goto L_end;
    }
    D_8008480C[0] = arg0;
    func_80054D64();
    goto L_end;
L_case1:
    D_8008480A[0] = arg0;
    func_800552C8();
    goto L_end;
L_case2:
    D_80084808[0] = arg0;
L_end:
    return;
}
