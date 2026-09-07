#include "common.h"

extern void func_80056948(void);
extern void func_800584E4(void);
extern void func_8005ACDC(void);

typedef struct {
    s32 v;
    s32 pad[2];
} PaddedS32;

extern PaddedS32 D_800737A8;
extern PaddedS32 D_80073824;
extern PaddedS32 D_80085F98;

long long func_80058510(void)
{
    s32 active;

    active = D_80073824.v;
    if ((active != 0) && (D_80085F98.v == 0)) {
        D_80085F98.v = 1;
        func_800584E4();
        if (D_800737A8.v >= 11) {
            func_80056948();
            func_8005ACDC();
            D_800737A8.v = 0;
        }
        D_80085F98.v = 0;
        D_800737A8.v += 1;
    }
}
