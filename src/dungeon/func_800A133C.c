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

extern s32 func_800A6A6C();
extern DungeonGroup D_80073414[];

typedef struct {
    u8 pad[0x5720];
    u8 data[1];
} RamPage;


typedef struct S_800A6A9C_0 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 pad_03[0x9];
    DungeonItem * unk_0C;
} S_800A6A9C_0;   /* var_a2 in func_800A6A9C */

/* Restores item flag 0x400 across the item category table from the RAM bitmap, then calls func_800A6A6C. */
void func_800A6A9C(void)
{
    u8 *group;
    s32 bitmap_byte;
    s32 item_index;
    s32 item_offset;
    s32 group_index;
    s32 bitmap_offset;
    s32 clear_flag_mask;
    RamPage *ram_page;
    s16 *item_flags;
    s16 *marked_flags;

    group_index = 0;
    clear_flag_mask = -0x401;
    ram_page = (RamPage *)0x80010000;
    group = (u8 *)D_80073414;
    do {
        ASM_KEEP(group);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        item_index = 0;
        if (((S_800A6A9C_0 *)group)->unk_02 != 0) {
            bitmap_offset = group_index * 8;
            item_offset = 0;
            do {
                item_flags = (s16 *)(item_offset +
                    (s32)((S_800A6A9C_0 *)group)->unk_0C);
                *item_flags = *item_flags & clear_flag_mask;
                bitmap_byte = item_index / 8;
                if (((s32)*(u8 *)(bitmap_offset + bitmap_byte + (s32)ram_page + 0x5720) >>
                     (item_index & 7)) & 1) {
                    marked_flags = (s16 *)(item_offset +
                        (s32)((S_800A6A9C_0 *)group)->unk_0C);
                    *marked_flags |= 0x400;
                }
                item_offset += 0x14;
            } while (++item_index < (s32)((S_800A6A9C_0 *)group)->unk_02);
        }
        group_index += 1;
        group += sizeof(DungeonGroup);
    } while (group_index < 0x13);
    func_800A6A6C();
}

/* MECHANISM: The 0x18 frame has only the $ra save; explicit clear_flag_mask/page locals
   fix preheader order, and preincrement loads count before the inner increment.
   Loop-top ASM_KEEP holds the unrebased group base, yielding v0-high/a2-low
   split addressing with +2/+0xC fields; index-first RAM arithmetic fixes addu. */
