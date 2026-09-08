#include "common.h"

typedef struct {
    u8 pad_00[0x18];
    s16 unk_18;
} UnkStruct;

extern void func_800160C0(UnkStruct *);
extern void func_80018A64(u32);
extern void func_80018ADC(s32);
extern s32 func_80018B5C(s32);
extern s16 D_80018CFA[5];

/* Processes an entry and applies updates based on its status and the global status. */
s32 func_800167E8(UnkStruct *entry) {
    s32 status;

    func_800160C0(entry);
    if (func_80018B5C(entry->unk_18) != 0) {
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
