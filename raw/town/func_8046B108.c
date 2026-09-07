#include "common.h"

extern u8 *D_8001E950;
extern void func_8001E578(s32);

void func_8001C108(void) {
    D_8001E950[0] = 2;
    D_8001E950[5] = 2;
    D_8001E950[1] = 2;
    func_8001E578(0xA2);
}
