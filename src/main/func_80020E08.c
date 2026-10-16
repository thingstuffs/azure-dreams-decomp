#include "common.h"

extern void memoryProcessHandlesAndMarkObject(void *ptr);
extern void func_80406678(void *ptr);
extern void func_8040701C(void *ptr, s32 value);

void cardBootClearMenuState(void *ptr) {
    s32 value;

    memoryProcessHandlesAndMarkObject((u8 *)ptr - 0x20);
    value = *(s32 *)ptr;
    if (value == 0) {
        func_80406678(*(void **)((u8 *)ptr + 0x14));
        return;
    } else {
        func_8040701C(*(void **)((u8 *)ptr + 0x14), value);
    }
}
