#include "common.h"
void func_80018BD0(s32);                     /* extern */

/* Processes IDs 0xFB7 and 0xFB8, then returns zero. */
s32 process_ids_zero(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    return 0;
}
