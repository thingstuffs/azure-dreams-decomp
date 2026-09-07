#include "common.h"

typedef struct {
    u8 pad_00[0x18];
    s16 unk_18;
} UnkStruct;

extern void func_800160C0(void);
extern void func_80018A64(u32);
extern void func_80018ADC(s32);
extern s32 func_80018B5C(s32);
extern s16 D_80018CFA[5];

s32 func_800167E8(UnkStruct *arg0) {
    s32 status;

    func_800160C0();
    if (func_80018B5C(arg0->unk_18) != 0) {
        status = func_80018B5C(D_80018CFA[0]);
    } else {
        status = 0;
    }

    if (status != 0) {
        func_80018ADC(0x5BC);
    } else {
        func_80018A64(0x5BC);
    }
    func_80018A64(0x5BD);
    return status;
}
