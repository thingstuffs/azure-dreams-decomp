#include "common.h"
#include "m2c_compat.h"

M2C_UNK TestEvent();                         /* extern */
extern s32 D_80028560;
extern s32 D_80028564;
extern s32 D_80028568;
extern s32 D_8002856C;
extern s32 D_800287E4;

void func_80021538(void) {
    D_800287E4 = 0;
    TestEvent(D_80028560);
    TestEvent(D_80028564);
    TestEvent(D_80028568);
    TestEvent(D_8002856C);
}
