#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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
    void *entry;
    void *child;
    void *data;

    table = D_80082660;
    index = arg0;
    object = table[index].object;
    if (object != 0) {
        value = D_800D5070[arg1];
        entry = object;
        data = (u8 *)object + 0x20;
        if (index == FIELD(data, s32, 0x60)) {
            if (index == 1) {
                kind = FIELD(entry, void *, 0x10);
                if (kind != D_800C3174 && kind != D_800C321C) {
                    FIELD(data, u16, 0x10) = value;
                    return;
                }
            }
            child = FIELD(data, void *, 0x80);
            FIELD(data, u16, 0x6E) = value;
            FIELD(data, u16, 0x72) = value;
            func_800C2E84(data, FIELD(entry, s32, 0xC),
                          FIELD(child, s32, 4));
        }
    }
}
