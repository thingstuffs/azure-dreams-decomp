#include "common.h"

extern void func_804025B8(void *arg0, void *arg1, s32 arg2);
extern void func_804025F8(s32 arg0, s32 arg1, s32 arg2);

static __inline__ void store_first_coord(
    s32 *record,
    void *arg0,
    u32 tripled
) {
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 8) =
        (s16)((s32)(tripled << 1) - (*(s32 *)((u8 *)arg0 + 0x18) / 2) + 0xA2);
}

static __inline__ void call_second(s32 second, s32 first, s32 third)
{
    func_804025F8(first, second, third);
}

static __inline__ void store_second_coord(s32 *record, void *arg0, s32 arg3)
{
    *(volatile s16 *)((u8 *)*(void **)((u8 *)record + 4) + 0xA) =
        (s16)((arg3 * 0x11) - (*(s32 *)((u8 *)arg0 + 0x1C) / 2) + 0x7A);
}

void func_8001B670(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u32 tripled;
    s32 first;
    s32 *source;
    u32 held_arg4;
    void *position;
    void *record;

    tripled = (u32)arg1 * 3U;
    record = *(s32 **)((u8 *)arg0 + 0x6A0);
    position = (u8 *)arg0 + 0x12C;
    store_first_coord((s32 *)record, arg0, tripled);
    store_second_coord((s32 *)record, arg0, arg3);
    held_arg4 = (u32)arg4;
    held_arg4 = (held_arg4 + (u32)arg3) - (u32)arg3;
    func_804025B8(arg0, position, arg2);
    *(s32 *)record = (s32)(unsigned long)position;
    source = *(s32 **)((u8 *)arg0 + arg3 * 4 + 0x68C);
    first = *source;
    func_804025F8(first, (s32)held_arg4, arg2);
}
