#include "common.h"

extern void func_800263C0(void);
extern s32 D_800265B8[];

void func_80026410(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x38) != 0) {
        *(s32 **)((u8 *)arg0 - 0x10) = &D_800265B8[0];
        return;
    }
    func_800263C0();
}
