#include "common.h"

extern void func_8001E578(s32 id);
extern u8 *D_8001E950;

/* Dispatch event 0x402 when the state byte is nonzero. */
s32 func_8001BF58(void) {
    if (D_8001E950[1] == 0) {
        return 0;
    }
    func_8001E578(0x402);
    return 1;
}
