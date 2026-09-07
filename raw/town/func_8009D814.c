#include "common.h"

extern void func_80094984(void *arg0, void *arg1, s32 arg2);
extern void func_8009AE88(void *arg0, s32 arg1, s32 arg2);
extern u8 D_800D0078[];
extern void *D_8009AFF4[];

typedef struct {
    s32 unk0;
    void **unk4;
    u16 unk8;
    u16 unkA;
} Struct8009D814;

void func_8009AF74(Struct8009D814 *arg0, s32 arg1, s32 arg2) {
    s16 temp;

    temp = arg0->unkA - 1;
    arg0->unkA = temp;
    if (temp <= 0) {
        func_80094984(D_800D0078, arg0, arg2);
        arg0->unk4 = D_8009AFF4;
    }
    func_8009AE88(arg0, arg1, arg2);
}
