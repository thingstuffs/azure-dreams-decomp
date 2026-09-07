#include "common.h"

#include "common.h"

s32 func_8003F5D4();                                /* extern */
extern s32 D_80084758;
extern s32 D_8008475C;
extern s32 D_80084760;
extern s32 D_80084764;

void func_800558FC(s32 arg0) {
    s32 temp_s0;
    s32 temp_v1;

    temp_v1 = func_8003F5D4();
    temp_s0 = arg0 & 0xFFFF;
    switch (temp_s0) {                              /* irregular */
    case 17:
        D_80084758 = temp_v1;
        return;
    case 18:
        D_8008475C = temp_v1;
        return;
    case 20:
        D_80084760 = temp_v1;
        return;
    case 24:
        D_80084764 = temp_v1;
        return;
    }
}
