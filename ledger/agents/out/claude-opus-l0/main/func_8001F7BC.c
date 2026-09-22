#include "common.h"

extern void func_804045C8(void *, s32);
extern void func_80404668(void *);
extern void func_80405A00(s32, s32);

void func_804067BC(void *arg0) {
    s32 var_s1;

    var_s1 = 0;
    while (1) {
        if (var_s1 == *(s32 *)((u8 *)arg0 + 0x2C)) {
            func_804045C8(*(void **)((u8 *)arg0 + var_s1 * 4 + 0xC), 1);
        } else {
            func_80404668(*(void **)((u8 *)arg0 + var_s1 * 4 + 0xC));
        }
        var_s1++;
        if (var_s1 >= 5) {
            break;
        }
    }
    func_80405A00(*(s32 *)((u8 *)arg0 + 4), *(s32 *)((u8 *)arg0 + 0x2C));
}
