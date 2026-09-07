#include "common.h"

typedef struct {
    s32 words[4];
} UnkStruct80476358;

extern UnkStruct80476358 D_80017124;
extern u8 D_800170D0[];
extern void func_80018FC8(UnkStruct80476358 *, u8 *, s32, s32);

void func_80476358(s32 arg0, s32 arg1, s32 arg2) {
    UnkStruct80476358 copy = D_80017124;

    func_80018FC8(&copy, D_800170D0, arg0, arg2);
}
