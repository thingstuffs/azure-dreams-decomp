#include "common.h"

extern s16 D_80084808[8];
extern s16 D_8008480A[8];
extern s16 D_8008480C[8];

extern void func_80054D64(void);
extern void func_800552C8(void);

/* Sets the indexed player stat and invokes its update routine when needed. */
void func_80053E20(s16 value, s32 stat_index) {
    if (stat_index == 2) {
        goto L_case2;
    }
    if (stat_index >= 3) {
        goto L_ge3;
    }
    if (stat_index == 1) {
        goto L_case1;
    }
    goto L_end;
L_ge3:
    if (stat_index != 4) {
        goto L_end;
    }
    D_8008480C[0] = value;
    func_80054D64();
    goto L_end;
L_case1:
    D_8008480A[0] = value;
    func_800552C8();
    goto L_end;
L_case2:
    D_80084808[0] = value;
L_end:
    return;
}
