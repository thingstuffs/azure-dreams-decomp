#include "common.h"

extern void func_800241D4(void *object_addr, s32 enable_table);
extern void func_80024224(void *object, s32 value);
extern void func_80024274(void *object_addr);
extern void func_80024F3C(s32 object_addr, s32 value_7c, s32 value_80);

void func_800250E8(void *menu)
{
    s32 index;

    for (index = 0; index < 5; index++) {
        if (index == *(s32 *)((u8 *)menu + 0x2C)) {
            func_80024224(((void **)menu)[index + 1], 1);
        } else if (index == *(s32 *)((u8 *)menu + 0x28)) {
            func_800241D4(((void **)menu)[index + 1], 1);
        } else {
            func_80024274(((void **)menu)[index + 1]);
        }
    }

    func_80024F3C(
        *(s32 *)((u8 *)menu + 0x1C),
        *(s32 *)((u8 *)menu + 0x28),
        *(s32 *)((u8 *)menu + 0x44)
        );
}
