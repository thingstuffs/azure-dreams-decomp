#include "common.h"

/* Pass the data at offset 0x20 to func_80026B18. */
void func_80026FF8(s32 base_addr) {
    func_80026B18(base_addr + 0x20);
}
