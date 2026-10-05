#include "common.h"

extern void func_804084DC(void *ptr);
extern void func_80406678(void *ptr);
extern void func_8040701C(void *ptr, s32 value);

void func_80407E08(void *ptr) {
    s32 value;

    func_804084DC((u8 *)ptr - 0x20);
    value = *(s32 *)ptr;
    if (value == 0) {
        func_80406678(*(void **)((u8 *)ptr + 0x14));
        return;
    } else {
        func_8040701C(*(void **)((u8 *)ptr + 0x14), value);
    }
}
