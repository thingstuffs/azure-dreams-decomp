#include "common.h"

typedef struct S_800C4D80_0 {
    u8 pad_00[0x10];
    u16 unk_10;
    u8 pad_12[0x4E];
    s32 unk_60;
    u8 pad_64[0xA];
    u16 unk_6E;
    u8 pad_70[0x2];
    u16 unk_72;
    u8 pad_74[0xC];
    void * unk_80;
} S_800C4D80_0;   /* data in func_800C4D80 */

typedef struct S_800C4D80_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    void * unk_10;
} S_800C4D80_1;   /* entry in func_800C4D80 */

typedef struct S_800C4D80_2 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C4D80_2;   /* child in func_800C4D80 */



typedef struct {
    s32 unused;
    void *object;
} TownEntry;

extern TownEntry D_80082660[];
extern u8 D_800C3174[];
extern u8 D_800C321C[];
extern u16 D_800D5070[];

extern void func_800C2E84(void *, s32, s32);

/* Apply a table value to the matching town object and refresh its child state. */
void func_800C4D80(s8 object_slot, s8 value_index)
{
    TownEntry *table;
    s32 object_index;
    void *object_kind;
    u16 lookup_value;
    void *object;
    S_800C4D80_1 *entry;
    S_800C4D80_2 *child;
    S_800C4D80_0 *object_data;

    table = D_80082660;
    object_index = object_slot;
    object = table[object_index].object;
    if (object != 0) {
        lookup_value = D_800D5070[value_index];
        entry = object;
        object_data = (u8 *)object + 0x20;
        if (object_index == object_data->unk_60) {
            if (object_index == 1) {
                object_kind = entry->unk_10;
                if (object_kind != D_800C3174 && object_kind != D_800C321C) {
                    object_data->unk_10 = lookup_value;
                    return;
                }
            }
            child = object_data->unk_80;
            object_data->unk_6E = lookup_value;
            object_data->unk_72 = lookup_value;
            func_800C2E84(object_data, entry->unk_0C,
                          child->unk_04);
        }
    }
}
