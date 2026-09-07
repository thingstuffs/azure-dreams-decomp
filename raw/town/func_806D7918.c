#include "common.h"

s32 func_80017A54();         /* extern */
void *func_80017B0C();       /* extern */
extern s32 D_80018968;
extern s32 D_80019104;
extern s32 D_800197D0;
extern s32 D_80019397;

void *func_80016118(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *s1;
    s32 s0;
    void *s3;

    s1 = arg0;
    s0 = arg2;
    {
        void *s2 = &D_80018968;

        s3 = func_80017B0C(s2, &D_80019104, s1, s0);
        if (s0 == 0x2D) {
            if (func_80017A54(s2, s1, 0x2D) != 0) {
                return &D_800197D0;
            }
        }
    }
    if (s0 == 0x2F) {
        if (func_80017A54(&D_80018968, s1, 0x2F) != 0) {
            return &D_80019397;
        }
    }
    return s3;
}
