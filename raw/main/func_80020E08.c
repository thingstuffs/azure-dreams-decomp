#include "common.h"

extern void func_804084DC(void *arg0);
extern void func_80406678(void *arg0);
extern void func_80407E50(void) __attribute__((noreturn));
extern void func_8040701C(void *arg0, s32 arg1);

void func_80020E08(void *arg0) {
    s32 temp_a1;

    func_804084DC((u8 *)arg0 - 0x20);
    temp_a1 = *(s32 *)arg0;
    if (temp_a1 == 0) {
        func_80406678(*(void **)((u8 *)arg0 + 0x14));
        func_80407E50();
    } else {
        func_8040701C(*(void **)((u8 *)arg0 + 0x14), temp_a1);
    }
}
