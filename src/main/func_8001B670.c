#include "common.h"

extern void func_804025B8(void *arg0, void *arg1, s32 arg2);
extern void func_804025F8(s32 arg0, s32 arg1, s32 arg2);

static __inline__ void store_first_coord(
    s32 *record,
    void *object,
    u32 column_tripled
) {
    *(s16 *)((u8 *)*(void **)((u8 *)record + 4) + 8) =
        (s16)((s32)(column_tripled << 1) - (*(s32 *)((u8 *)object + 0x18) / 2) + 0xA2);
}

static __inline__ void call_second(s32 value, s32 row_value, s32 mode)
{
    func_804025F8(row_value, value, mode);
}

static __inline__ void store_second_coord(s32 *record, void *object, s32 row)
{
    *(volatile s16 *)((u8 *)*(void **)((u8 *)record + 4) + 0xA) =
        (s16)((row * 0x11) - (*(s32 *)((u8 *)object + 0x1C) / 2) + 0x7A);
}

/* Positions the object's record and updates the selected row. */
void func_8001B670(void *object, s32 column, s32 mode, s32 row, s32 value)
{
    u32 column_tripled;
    s32 row_value;
    s32 *row_data;
    u32 saved_value;
    void *position;
    void *record;

    column_tripled = (u32)column * 3U;
    record = *(s32 **)((u8 *)object + 0x6A0);
    position = (u8 *)object + 0x12C;
    store_first_coord((s32 *)record, object, column_tripled);
    store_second_coord((s32 *)record, object, row);
    saved_value = (u32)value;
    saved_value = (saved_value + (u32)row) - (u32)row;
    func_804025B8(object, position, mode);
    *(s32 *)record = (s32)(unsigned long)position;
    row_data = *(s32 **)((u8 *)object + row * 4 + 0x68C);
    row_value = *row_data;
    func_804025F8(row_value, (s32)saved_value, mode);
}
