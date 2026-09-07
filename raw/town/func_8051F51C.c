#include "common.h"

#define FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern s8 D_80016000[];
extern s32 D_80018FE0;
extern s32 *D_8001917C;
extern s32 D_8001C328;
extern s32 D_8001C7C4;

extern s32 func_80018B5C(s32);
extern void func_80018ADC(s32);

void func_80016D1C(void) {
    D_8001917C = &D_80018FE0;
    if (func_80018B5C(0x5C2) != 0) {
        if (func_80018B5C(0x5BF) != 0) {
            FIELD(FIELD(FIELD(&D_80016000, void **, 0), void **, 0x1C), s32 **, 0x40) = &D_8001C328;
        } else {
            FIELD(FIELD(FIELD(&D_80016000, void **, 0), void **, 0x1C), s32 **, 0x40) = &D_8001C7C4;
        }
        func_80018ADC(0x5C2);
        return;
    }
    func_80018ADC(0x5C4);
}
