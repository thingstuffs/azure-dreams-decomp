#include "common.h"

typedef struct {
    u8 pad_00[0x18];
    s16 unk_18;
} UnkStruct;

extern void func_800160C0(UnkStruct *);
extern void func_80018A64(s32);
extern void func_80018ADC(s32);
extern s32 func_80018B5C(s32);
extern s16 D_80018CFA[5];

/* Update the object and select the action for 0x5BC from the combined status checks. */
s32 func_80016650(UnkStruct *object) {
    s32 status;

    func_800160C0(object);
    if (func_80018B5C(object->unk_18) != 0) {
        status = func_80018B5C(D_80018CFA[0]);
    } else {
        status = 0;
    }

    if (status != 0) {
        func_80018ADC(0x5BC);
    } else {
        func_80018A64(0x5BC);
    }
    return status;
}
