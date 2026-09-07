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

void func_800C4D80(s8 arg0, s8 arg1)
{
    TownEntry *table;
    s32 index;
    void *kind;
    u16 value;
    void *object;
    S_800C4D80_1 *entry;
    S_800C4D80_2 *child;
    S_800C4D80_0 *data;

    table = D_80082660;
    index = arg0;
    object = table[index].object;
    if (object != 0) {
        value = D_800D5070[arg1];
        entry = object;
        data = (u8 *)object + 0x20;
        if (index == data->unk_60) {
            if (index == 1) {
                kind = entry->unk_10;
                if (kind != D_800C3174 && kind != D_800C321C) {
                    data->unk_10 = value;
                    return;
                }
            }
            child = data->unk_80;
            data->unk_6E = value;
            data->unk_72 = value;
            func_800C2E84(data, entry->unk_0C,
                          child->unk_04);
        }
    }
}
