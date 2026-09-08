#include "common.h"

extern u8 D_80408D40[][2];
extern s32 D_80408D44[];

extern void func_8004DDBC(void *arg0, s32 arg1, s32 *arg2);

/* Updates two object slots using the selected slot mapping and values. */
void func_80020160(u8 *object) {
    s32 slot;
    s32 slot_offset;
    u8 (*slot_map)[2];
    s32 *values;
    u8 mapped_slot;
    s32 *slot_data;
    s32 *value_dst;
    s32 mapped_value;
    s32 **slot_entries;
    s32 map_index;

    slot = 0;
    slot_map = D_80408D40;
    values = D_80408D44;
    slot_offset = 0;
    do {
        mapped_slot = slot_map[*(s32 *)(object + 0x24)][slot];
        slot_data = *(s32 **)(*(u8 **)(object + 0x60) + mapped_slot * 4 + 8);
        if (*slot_data != 0) {
            func_8004DDBC(object + (mapped_slot * 0xC + 4),
                          *(s32 *)((u8 *)D_80408D44 + 8 + slot_offset), slot_data);
        }
        mapped_slot = slot_map[*(s32 *)(object + 0x24)][slot];
        *(*(s32 **)((u8 *)*(s32 **)(slot_offset + *(s32 *)(object + 0x60)) + 4)) =
            values[mapped_slot];

        do {
            slot_entries = (s32 **)(slot_offset + *(s32 *)(object + 0x60));
            map_index = *(s32 *)(object + 0x24);
        } while (0);
        mapped_slot = slot_map[map_index][slot];
        value_dst = *(s32 * volatile *)((u8 *)slot_entries[2] + 4);
        mapped_value = *(volatile s32 *)&values[mapped_slot];
        if (mapped_value != 0) {
            slot += 1;
        } else {
            slot += 1;
        }
        *value_dst = mapped_value;
        slot_offset += 4;
    } while (slot < 2);
}
