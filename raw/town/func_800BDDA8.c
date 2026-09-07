#include "common.h"

extern s32 func_8009CFE0(void);
extern void func_8008F134(void *arg0);
extern void func_80033D08(void *arg0);
extern s32 D_800814A0;

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

void func_800BB508(void *arg0) {
    if (func_8009CFE0() != 0) {
        func_8008F134(arg0);
        if (FIELD(arg0, s8 **, 0x98) != 0) {
            *FIELD(arg0, s8 **, 0x98) = 0;
        }
        func_80033D08(arg0);
        FIELD(arg0, u16 *, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
