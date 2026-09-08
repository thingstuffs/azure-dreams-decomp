#include "common.h"

extern void func_8004CBFC(void *arg0, s32 arg1, s32 *arg2);
extern u8 D_80028068[];
extern s32 D_8002806C[];
extern s32 D_80028074[];

/* Updates two selected records and writes their table values to paired destinations. */
void func_800269B4(u8 *state)
{
    s32 slot;
    u8 *slot_cursor;
    u8 *id_table;
    s32 *value_table;
    s32 *weight;

    slot = 0;
    id_table = D_80028068;
    value_table = D_8002806C;
    slot_cursor = state;
    weight = D_80028074;
    do {
        u32 id_address;
        u32 second_id_address;
        u32 entry_address;
        u8 *first_link;
        u8 *second_link;
        u8 id;
        u8 second_id;
        s32 table_offset;
        s32 second_table_offset;
        s32 record_offset;
        s32 *first_dest;
        s32 *second_dest;
        s32 *entry;
        s32 first_value;
        s32 second_value;

        table_offset = *(s32 *)(state + 0x24) * 2;
        id_address = (u32)table_offset;
        id_address += (u32)(unsigned long)id_table;
        id_address += (u32)slot;
        id = *(u8 *)(unsigned long)id_address;
        entry_address = (u32)(unsigned long)state;
        entry_address += (u32)(id * 4);
        entry = *(s32 **)(unsigned long)(entry_address + 0x68);
        if (*entry != 0) {
            record_offset = id * 12;
            record_offset += 4;
            func_8004CBFC(state + record_offset, *weight, entry);
        }

        table_offset = *(s32 *)(state + 0x24) * 2;
        first_link = *(u8 **)(slot_cursor + 0x60);
        id_address = (u32)table_offset;
        id_address += (u32)(unsigned long)id_table;
        id_address += (u32)slot;
        id = *(u8 *)(unsigned long)id_address;
        first_dest = *(s32 **)(first_link + 4);
        first_value = value_table[id];
        *first_dest = first_value;

        second_table_offset = *(s32 *)(state + 0x24) * 2;
        second_link = *(u8 **)(slot_cursor + 0x68);
        second_id_address = (u32)second_table_offset;
        second_id_address += (u32)(unsigned long)id_table;
        second_id_address += (u32)slot;
        second_id = *(u8 *)(unsigned long)second_id_address;
        second_dest = *(s32 **)(second_link + 4);
        second_value = value_table[second_id];
        weight++;
        slot++;
        *second_dest = second_value;
        slot_cursor += 4;
    } while (slot < 2);
}
