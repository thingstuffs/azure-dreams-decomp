#include "common.h"

extern void func_80018A64(s32);
extern void func_80018ADC(s32);
extern s32 D_80019178[];

/* Apply the fixed operation codes and clear the first D_80019178 entry. */
void func_8051EA54(void) {
    func_80018A64(0x5A5);
    func_80018ADC(0x5C2);
    func_80018ADC(0x5BF);
    func_80018ADC(0x5C0);
    D_80019178[0] = 0;
}
