#include "common.h"

extern void func_80022300(void *arg0, void *arg1, s32 arg2);
extern void func_8002233C(s32 arg0, s32 arg1, s32 arg2);

static __inline__ u32 calculate_x(
    void *context,
    s32 column
)
{
    u32 x;

    x = (u32)column * 4U;
    x -= (u32)(*(s32 *)((u8 *)context + 0x18) / 2);
    return x + 0xA2;
}

/* Positions the current record and updates the specified row. */
void func_800223B4(void *context, s32 column, s32 mode, s32 row, volatile s32 row_value)
{
    void *state = context;
    s32 *record;
    void *position;
    u32 x;
    s32 saved_row_value;

    x = calculate_x(state, column);
    position = (u8 *)state + 0xE4;
    record = *(s32 **)((u8 *)state + 0x8E4);
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 8) = (s16)x;
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 0xA) =
        (s16)((row * 0x11) - (*(s32 *)((u8 *)state + 0x1C) / 2) + 0x7A);
    saved_row_value = row_value;
    func_80022300(state, position, mode);
    record[0] = (s32)(unsigned long)position;
    func_8002233C(
        *(s32 *)*(s32 **)((u8 *)state + row * 4 + 0x8CC),
        saved_row_value,
        mode);
}
