#include "common.h"
#include "m2c_compat.h"

M2C_UNK TestEvent();                         /* extern */
extern s32 D_80028550;
extern s32 D_80028554;
extern s32 D_80028558;
extern s32 D_8002855C;

/* Tests the four card event handles. */
void func_800214A4(void) {
    TestEvent(D_80028550);
    TestEvent(D_80028554);
    TestEvent(D_80028558);
    TestEvent(D_8002855C);
}
