#include "common.h"

extern void func_80093D48(void *arg0, s32 arg1, s32 arg2);
extern void func_80094984(void *arg0, void *arg1, s32 arg2);
extern void func_80099754(s32 arg0);

extern u8 D_800834B8[];
extern u8 D_800D0078[];

// Processes D_800834B8 using the parameters stored in its preceding header.
void func_8009AC8C(void) {
    void *dataBuffer;
    void *bufferHeader;
    s32 headerValue0C;
    s32 headerValue08;

    dataBuffer = D_800834B8;
    bufferHeader = (s8 *)dataBuffer - 0x20;
    headerValue08 = *(s32 *)((s8 *)bufferHeader + 8);
    headerValue0C = *(s32 *)((s8 *)bufferHeader + 0xC);
    func_80099754(headerValue08);
    func_80094984(D_800D0078, dataBuffer, headerValue0C);
    func_80093D48(dataBuffer, headerValue08, headerValue0C);
}
