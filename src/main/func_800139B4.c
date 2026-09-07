#include "common.h"

extern void func_8004CBFC(void *arg0, s32 arg1, s32 *arg2);
extern u8 D_80028068[];
extern s32 D_8002806C[];
extern s32 D_80028074[];

void func_800269B4(u8 *arg0)
{
    s32 i;
    u8 *iter;
    u8 *id_table;
    s32 *value_table;
    s32 *weight;

    i = 0;
    id_table = D_80028068;
    value_table = D_8002806C;
    iter = arg0;
    weight = D_80028074;
    do {
        u32 id_address;
        u32 id_address2;
        u32 entry_address;
        u8 *outer;
        u8 *outer2;
        u8 id;
        u8 id2;
        s32 selector;
        s32 selector2;
        s32 record_offset;
        s32 *destination;
        s32 *destination2;
        s32 *entry;
        s32 value;
        s32 value2;

        selector = *(s32 *)(arg0 + 0x24) * 2;
        id_address = (u32)selector;
        id_address += (u32)(unsigned long)id_table;
        id_address += (u32)i;
        id = *(u8 *)(unsigned long)id_address;
        entry_address = (u32)(unsigned long)arg0;
        entry_address += (u32)(id * 4);
        entry = *(s32 **)(unsigned long)(entry_address + 0x68);
        if (*entry != 0) {
            record_offset = id * 12;
            record_offset += 4;
            func_8004CBFC(arg0 + record_offset, *weight, entry);
        }

        selector = *(s32 *)(arg0 + 0x24) * 2;
        outer = *(u8 **)(iter + 0x60);
        id_address = (u32)selector;
        id_address += (u32)(unsigned long)id_table;
        id_address += (u32)i;
        id = *(u8 *)(unsigned long)id_address;
        destination = *(s32 **)(outer + 4);
        value = value_table[id];
        *destination = value;

        selector2 = *(s32 *)(arg0 + 0x24) * 2;
        outer2 = *(u8 **)(iter + 0x68);
        id_address2 = (u32)selector2;
        id_address2 += (u32)(unsigned long)id_table;
        id_address2 += (u32)i;
        id2 = *(u8 *)(unsigned long)id_address2;
        destination2 = *(s32 **)(outer2 + 4);
        value2 = value_table[id2];
        weight++;
        i++;
        *destination2 = value2;
        iter += 4;
    } while (i < 2);
}
