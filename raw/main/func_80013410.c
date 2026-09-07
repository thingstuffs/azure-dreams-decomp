#include "common.h"

extern void func_800263C0(void);
extern void func_8002643C(void) __attribute__((noreturn));
extern s32 D_800265B8[];

void func_80026410(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x38) != 0) {
        *(s32 **)((u8 *)arg0 - 0x10) = &D_800265B8[0];
        func_8002643C();
    }
    func_800263C0();
}
