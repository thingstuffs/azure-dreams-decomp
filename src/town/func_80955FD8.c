#include "common.h"

typedef struct {
    u8 bytes[7];
} __attribute__((packed)) Copy7;

typedef struct {
    s16 state;
    s16 pad2;
    u8 *text;
    u16 *value;
    u8 *status;
} Entry;

extern Copy7 D_80020198;
extern volatile s32 D_800814A0;
extern void func_800537D0(s32 value, s32 mode, void *dst);

/* Format an inactive entry's value in units of 30 and propagate its status flag. */
void func_80022FD8(Entry *entry)
{
    s16 raw_value;
    s16 whole_units;
    s16 unit_remainder;
    u8 *text;
    u8 *status;
    volatile s32 *global_flags;

    status = entry->status;
    raw_value = *entry->value;
    if (entry->state != 0) {
        return;
    }

    if (raw_value >= 30000) {
        u8 *overflow_text;

        overflow_text = entry->text;
        *(Copy7 *)(overflow_text + 1) = D_80020198;
    } else {
        whole_units = raw_value / 30;
        func_800537D0(whole_units, 4, entry->text);
        unit_remainder = raw_value % 30;
        func_800537D0((unit_remainder * 100) / 30, 2, entry->text + 5);
    }

    text = entry->text;
    if (text[5] == 0x20) {
        text[5] = 0x30;
    }
    global_flags = &D_800814A0;
    if (*(u16 *)(status + 0x3A) & 0x8000) {
        *(volatile u16 *)((u8 *)entry - 2) |= 0x8000;
        *global_flags |= 0x8000;
    }
}
