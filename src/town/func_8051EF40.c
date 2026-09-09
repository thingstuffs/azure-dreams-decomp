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

/* Initializes the object and selects follow-up actions from status checks. */
s32 func_80016740(UnkStruct *object) {
    s32 status;
    s32 result;

    func_800160C0(object);
    if (func_80018B5C(object->unk_18) != 0) {
        status = func_80018B5C(D_80018CFA[0]);
    } else {
        status = 0;
    }

    if (status != 0) {
        func_80018ADC(0x5BC);
        do {
            return status;
        } while (0);
    }

    if (func_80018B5C(0x1068) != 0) {
        func_800160D4();
        result = 1;
    } else {
        func_80018A64(0x5BC);
        func_80018A64(0x5BE);
        func_80018A64(0x5C5);
        result = status;
    }
    return result;
}
