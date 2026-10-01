#include "common.h"

extern void func_800241D4(void *, s32);
extern void func_80024224(void *, s32);
extern void func_80024274(void *);
extern void func_80024F3C(s32, s32, s32);

void func_800250E8(void *arg0)
{
    s32 index;

    for (index = 0; index < 5; index++) {
        if (index == *(s32 *)((u8 *)arg0 + 0x2C)) {
            func_80024224(((void **)arg0)[index + 1], 1);
        } else if (index == *(s32 *)((u8 *)arg0 + 0x28)) {
            func_800241D4(((void **)arg0)[index + 1], 1);
        } else {
            func_80024274(((void **)arg0)[index + 1]);
        }
    }

    func_80024F3C(
        *(s32 *)((u8 *)arg0 + 0x1C),
        *(s32 *)((u8 *)arg0 + 0x28),
        *(s32 *)((u8 *)arg0 + 0x44)
        );
}
