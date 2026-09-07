#include "common.h"

extern void func_804025B8(void *arg0, void *arg1, s32 arg2);
extern void func_804025F8(s32 arg0, s32 arg1, s32 arg2);

static __inline__ void store_first_coord(
    s32 *record,
    void *arg0,
    u32 tripled,
    s32 arg4
) {
    u32 first;

    first = (tripled << 1) + (u32)arg4;
    first -= (u32)arg4;
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 8) =
        (s16)((s32)first - (*(s32 *)((u8 *)arg0 + 0x18) / 2) + 0xA2);
}

void func_8001B670(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 *record;
    void *position;
    u32 tripled;

    tripled = (u32)arg1 * 3U;
    position = (u8 *)arg0 + 0x12C;
    record = *(s32 **)((u8 *)arg0 + 0x6A0);
    store_first_coord(record, arg0, tripled, arg4);
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 0xA) =
        (s16)((arg3 * 0x11) - (*(s32 *)((u8 *)arg0 + 0x1C) / 2) + 0x7A);
    func_804025B8(arg0, position, arg2);
    record[0] = (s32)(unsigned long)position;
    func_804025F8(
        *(s32 *)*(s32 **)((u8 *)arg0 + arg3 * 4 + 0x68C), arg4, arg2);
}
