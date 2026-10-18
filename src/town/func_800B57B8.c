#include "common.h"
void func_800B2E3C(s32);                         /* extern */

/* Calls func_800B2E3C with the input offset by 0x20. */
void forward_offset_to_record_loader(s32 base) {
    func_800B2E3C(base + 0x20);
}
