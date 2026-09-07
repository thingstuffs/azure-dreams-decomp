#include "common.h"

#include "common.h"

extern void func_8003C0C8(void *arg0, void *arg1);
extern u32 D_80083160[];

void func_8003C3B4(void *arg0, void *arg1, void *arg2) {
    u8 *global;
    s32 value;
    void (*callback)(void) = *(void (**)(void))arg0;

    global = D_80083160;
    if (callback != 0) {
        callback();
        if ((*(u16 *)((u8 *)arg0 - 2) & 0x8000) != 0) {
            return;
        }
    }

    func_8003C0C8(arg0, arg2);
    value = *(u32 *)(global + 8) & 0x10;
    if (value != 0) {
        value = 5;
    } else {
        value = 0x10;
    }
    *(u16 *)((u8 *)arg1 + 0xA) = value;
}
