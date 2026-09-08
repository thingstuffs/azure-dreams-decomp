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

extern volatile s32 D_80012090[];
extern s16 D_8001F6F8[];
extern DungeonGroup D_80073414[];

/* Build cumulative item weights for each dungeon group. */
void func_8001E994(void)
{
    s32 total_weight;
    s32 group_index;
    s32 two;
    s32 item_weight;
    s32 item_offset;
    s32 item_index;
    s32 weight_bits;
    u16 item_flags;
    s16 *group_total;
    u8 *group;
    u8 *group_copy;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *table_base;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    total_weight = 0;
    group_index = 1;
    two = 2;
    ASM_KEEP(total_weight);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    table_base = (u8 *)D_8001F6F8;
    ASM_KEEP(table_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    group_total = (s16 *)(table_base + 2);
    table_base = (u8 *)D_80073414;
    ASM_KEEP(table_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    group = table_base + 0x14;
    do {
        ASM_KEEP(group);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        item_index = 1;
        if (item_index < (s32)*(u8 *)(group + 2)) {
            group_copy = group;
            item_offset = 0x14;
            do {
                ASM_KEEP(item_offset);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                item_flags =
                    *(u16 *)(item_offset + *(volatile s32 *)(group + 0xC));
                if (item_flags & 0x10) {
                    goto next_item;
                }
                if (!(item_flags & 0x40)) {
                    goto add_item;
                }
                {
                    volatile s32 *state_page;

                    state_page = (volatile s32 *)0x80010000;
                    if (*(volatile s32 *)((u8 *)state_page + 0x2090) !=
                        two) {
                        goto next_item;
                    }
                }
add_item:
                    weight_bits =
                        *(u16 *)(item_offset + *(s32 *)(group_copy + 0xC)) & 0x3000;
                    if (weight_bits < 0) {
                        weight_bits += 0xFFF;
                    }
                    weight_bits >>= 0xC;
                    {
                        register s32 weight_class ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        weight_class = weight_bits & 3;
                        item_weight = 0x80;
                        if (weight_class != 0) {
                            s32 one;

                            one = 1;
                            ASM_KEEP(one);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                            item_weight = 0x55;
                            if (weight_class != one) {
                                item_weight = one;
                                if (weight_class == two) {
                                    item_weight = 0x20;
                                }
                            }
                        }
                        total_weight += item_weight;
                    }
next_item:
                item_offset += 0x14;
            } while (++item_index < (s32)*(u8 *)(group + 2));
            ASM_KEEP(item_index);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        }
        *group_total = total_weight;
        group_total++;
        group_index++;
        group += 0x14;
    } while (group_index < 0x13);
    {
        s16 *totals;
        s32 tail_offset;

        totals = D_8001F6F8;
        ASM_KEEP(totals);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        tail_offset = group_index << 1;
        *(s16 *)(tail_offset + (s32)totals) = total_weight;
    }
}

/* MECHANISM: Frameless leaf keeps raw group/offset lifetimes at loop seams;
   volatile entries reload and scoped page/one values remove preheader holds,
   while guarded pins encode retail's nine stable loop-register roles. */
