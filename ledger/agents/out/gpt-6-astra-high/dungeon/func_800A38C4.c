#include "common.h"

typedef struct {
    u16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[2];
    u8 count;
    u8 pad3[9];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern DungeonGroup D_80073414[];

/* Marks eligible items in selected groups and records them in the item bitset. */
void func_800A9024(s32 group_bit) {
    DungeonGroup *group;
    s32 item_index;
    register s32 item_offset ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s32 group_index;
    s32 byte_index_bias;
    s32 group_bitset_offset;
    u32 ram_base;
    s32 bit_mask;
    s32 bit_index;
    u16 *item_flags;
    u16 flags;
    void *bitset_base;

    group_index = 0;
    ram_base = 0x80010000;
    bit_mask = 1;
    group = D_80073414;
    do {
        ASM_KEEP(group);   /* MATCH pin: load-bearing for the whole function shape */
        if (((s32)*((u8 *)group + 1) >> group_bit) & 1) {
            item_index = 0;
            if (group->count != 0) {
                group_bitset_offset = group_index * 8;
                item_offset = 0;
                do {
                    item_flags = (u16 *)(item_offset + (s32)group->entries);
                    flags = *item_flags;
                    if (!(flags & 0x200)) {
                        *item_flags = flags | 0x400;
                        byte_index_bias = item_index;
                        if (item_index < 0) {
                            byte_index_bias = item_index + 7;
                        }
                        bitset_base = (void *)(group_bitset_offset + (byte_index_bias >> 3) + ram_base);
                        bit_index = item_index & 7;
                        *((u8 *) bitset_base + 0x5720) = (u8) (*((u8 *) bitset_base + 0x5720) | (bit_mask << bit_index));
                    }
                    item_offset += sizeof(DungeonItem);
                } while (++item_index < (s32)group->count);
            }
        }
        group_index += 1;
        group += 1;
    } while (group_index < 0x13);
}
