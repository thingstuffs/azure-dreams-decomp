#include "common.h"

extern void func_80019DFC(void *, void *, s32, s32);
extern s32 D_8001B920;
extern u8 D_8001B924[];
extern u8 D_8001B944[];
extern s32 D_8001C354;

// Dispatches a value and code with state-selected data, setting the state for codes other than 0x2D.
void func_8001698C(s32 value, s32 unused, s32 code) {
    void *selectedData;

    if (D_8001B920 != 0) {
        selectedData = D_8001B944;
    } else {
        selectedData = D_8001B924;
    }
    if (code != 0x2D) {
        D_8001B920 = 1;
    }
    func_80019DFC(selectedData, &D_8001C354, value, code);
}
