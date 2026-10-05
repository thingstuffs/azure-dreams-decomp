#include "common.h"

extern void func_804045C8(void *, s32);
extern void func_80404668(void *);
extern void func_80405A00(s32, s32);

void func_804067BC(void *ptr) {
    s32 i;

    i = 0;
    while (1) {
        if (i == *(s32 *)((u8 *)ptr + 0x2C)) {
            func_804045C8(*(void **)((u8 *)ptr + i * 4 + 0xC), 1);
        } else {
            func_80404668(*(void **)((u8 *)ptr + i * 4 + 0xC));
        }
        i++;
        if (i >= 5) {
            break;
        }
    }
    func_80405A00(*(s32 *)((u8 *)ptr + 4), *(s32 *)((u8 *)ptr + 0x2C));
}
