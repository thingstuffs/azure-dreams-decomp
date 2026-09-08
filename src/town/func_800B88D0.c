#include "common.h"

extern void func_8004E5A0(void *a0, s32 a1, void *a2);
extern u8 *func_8004E69C(u8 *arg0);

/* Builds and processes a short encoded sequence in the output buffer. */
void *func_800B6030(void *source, u8 *outputBuffer) {
    u8 *payload;

    payload = outputBuffer + 1;
    outputBuffer[0] = 0x20;
    func_8004E5A0(source, 2, payload);
    outputBuffer[3] = 0xA;
    outputBuffer[4] = 0x6F;
    outputBuffer[5] = 0;
    func_8004E69C(payload);
    return outputBuffer;
}
