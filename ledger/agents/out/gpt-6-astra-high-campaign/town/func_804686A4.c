#include "common.h"

extern void func_8001E5F0(s32 arg0);
extern struct {
    u8 *ptr;
    u8 pad[8];
} D_8001E950;

/* Clear two state bytes and process five fixed identifiers. */
void func_800196A4(void) {
    D_8001E950.ptr[1] = 0;
    D_8001E950.ptr[6] = 0;
    func_8001E5F0(0x400);
    func_8001E5F0(0x401);
    func_8001E5F0(0x402);
    func_8001E5F0(0xA0);
    func_8001E5F0(0xA1);
}
