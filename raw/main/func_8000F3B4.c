#include "common.h"

extern void func_80022300(void *arg0, void *arg1, s32 arg2);
extern void func_8002233C(s32 arg0, s32 arg1, s32 arg2);

static __inline__ u32 calculate_first(
    void *arg0,
    s32 arg1
)
{
    u32 first;

    first = (u32)arg1 * 4U;
    first -= (u32)(*(s32 *)((u8 *)arg0 + 0x18) / 2);
    return first + 0xA2;
}

void func_800223B4(void *arg0, s32 arg1, s32 arg2, s32 arg3, volatile s32 arg4)
{
    register void *base ASM_REG("$17") = arg0;
    register s32 *record ASM_REG("$18");
    void *position;
    u32 first;
    s32 saved_arg4;

    first = calculate_first(base, arg1);
    position = (u8 *)base + 0xE4;
    record = *(s32 **)((u8 *)base + 0x8E4);
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 8) = (s16)first;
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 0xA) =
        (s16)((arg3 * 0x11) - (*(s32 *)((u8 *)base + 0x1C) / 2) + 0x7A);
    saved_arg4 = arg4;
    func_80022300(base, position, arg2);
    record[0] = (s32)(unsigned long)position;
    func_8002233C(
        *(s32 *)*(s32 **)((u8 *)base + arg3 * 4 + 0x8CC),
        saved_arg4,
        arg2);
}
