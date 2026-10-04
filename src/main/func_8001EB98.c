#include "common.h"

extern void func_804045C8(void *, s32);
extern void func_80404618(void *, s32);
extern void func_80404668(void *);
extern void func_80405A00(s32, s32);

void func_80405B98(void *ptr) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == *((s32 *)ptr + 0xB)) {
            func_80404618(((void **)ptr)[i + 1], 1);
        } else if (i == *((s32 *)ptr + 0xA)) {
            func_804045C8(((void **)ptr)[i + 1], 1);
        } else {
            func_80404668(((void **)ptr)[i + 1]);
        }
    }
    func_80405A00(*((s32 *)ptr + 7), *((s32 *)ptr + 0xA));
}
