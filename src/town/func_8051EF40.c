#include "common.h"

typedef struct {
    u8 pad_00[0x18];
    s16 unk_18;
} UnkStruct;

extern void func_800160C0(UnkStruct *);
extern void func_800160D4(void);
extern void func_80018A64(s32);
extern void func_80018ADC(s32);
extern s32 func_80018B5C(s32);
extern s16 D_80018CFA[5];

s32 func_80016740(UnkStruct *arg0) {
    s32 status;
    s32 result;

    func_800160C0(arg0);
    if (func_80018B5C(arg0->unk_18) != 0) {
        status = func_80018B5C(D_80018CFA[0]);
    } else {
        status = 0;
    }

    if (status != 0) {
        func_80018ADC(0x5BC);
        return status;
    }

    if (func_80018B5C(0x1068) != 0) {
        func_800160D4();
        result = 1;
    } else {
        func_80018A64(0x5BC);
        func_80018A64(0x5BE);
        func_80018A64(0x5C5);
        ASM_KEEP(status);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        result = status;
    }
    return result;
}
