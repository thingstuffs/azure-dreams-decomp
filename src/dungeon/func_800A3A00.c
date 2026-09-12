#include "common.h"

typedef struct S_800A9160_0 {
    u8 pad_00[0x5720];
    u8 unk_5720;
} S_800A9160_0;   /* temp_t1 + (var_v0 >> 3) + (s32)ram in func_800A9160 */

typedef struct S_800A9160_1 {
    u8 pad_00[0x5720];
    u8 unk_5720;
} S_800A9160_1;   /* temp_a0 in func_800A9160 */



typedef struct {
    u16 flags;
    u8 pad02[0x12];
} DungeonCell;

typedef struct {
    u8 pad00[2];
    u8 count;
    u8 pad03[9];
    DungeonCell *cells;
    u8 pad10[4];
} DungeonGroup;

typedef struct {
    u8 pad00[0x5720];
    u8 bits[1];
} RamPage;

extern DungeonGroup D_80073414[];

/* Packs item flag 0x400 into a RAM bitset for each item category. */
void func_800A9160(void)
{
    DungeonGroup *item_category;
    DungeonGroup *cell_group;
    s32 group_bits_offset;
    s32 set_index;
    s32 bit_index;
    s32 cell_index;
    u8 *cell_offset;
    s32 group_index;
    s32 clear_index;
    s32 one;
    S_800A9160_1 *bit_byte;
    RamPage *ram;

    group_index = 0;
    ram = (RamPage *)0x80010000;
    item_category = D_80073414;
    do {
        cell_index = 0;
        if (item_category->count != 0) {
            group_bits_offset = group_index * 8;
            cell_group = item_category;
            cell_offset = 0;
            do {
                if (!(cell_index & 7)) {
                    clear_index = cell_index;
                    if (cell_index < 0) {
                        clear_index = cell_index + 7;
                    }
                    ((S_800A9160_0 *)(group_bits_offset + (clear_index >> 3) + (s32)ram))->unk_5720 = 0;
                }
                if (*(u16 *)(cell_offset + (s32)cell_group->cells) & 0x400) {
                    set_index = cell_index;
                    if (cell_index < 0) {
                        set_index = cell_index + 7;
                    }
                    bit_byte = group_bits_offset + (set_index >> 3) + (s32)ram;
                    bit_index = cell_index & 7;
                    one = 1;
                    ASM_KEEP(one);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    bit_byte->unk_5720 =
                        bit_byte->unk_5720 |
                        (one << bit_index);
                }
                cell_offset += sizeof(DungeonCell);
            } while (++cell_index < (s32)cell_group->count);
        }
        group_index += 1;
        item_category += 1;
    } while (group_index < 0x13);
}

/* MECHANISM: Frameless leaf; typed 20-byte groups recover the two local do-loops
   and the outer +20 delay-slot stride. Held current/inner group roles plus an
   index-first 0x80010000 RAM address reproduce t2/t0 and the 0x5720 accesses.
   A preincrement condition emits count-load before index increment and closes. */
