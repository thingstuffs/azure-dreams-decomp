#include "common.h"

#include "common.h"
#include "engine/item.h"

/* 20-byte item record; offset 0xC is the pointer this function shuffles. */
typedef struct S_8004AA78_Rec {
    u8 pad0[0xC];
    s32 ptr;
    u8 pad1[4];
} S_8004AA78_Rec;

/* 20-byte category-table entry: count @0x2, records pointer @0xC. */
typedef struct S_8004AA78_CategoryEntry {
    u8 pad0[2];
    u8 count;
    u8 pad1[9];
    S_8004AA78_Rec *records;
    u8 pad2[4];
} S_8004AA78_CategoryEntry;

/* Stack workspace: indices[0x40] then ptrs[] at +0x40 (matches retail lw offset). */
typedef struct S_8004AA78_Buf {
    u8 indices[0x40];
    s32 ptrs[0x40];
} S_8004AA78_Buf;

extern S_8004AA78_CategoryEntry itemCategoryTable[];

/* Shuffles nonzero item pointers among occupied records in a category. */
void shuffle_category_item_data(s32 category) {
    S_8004AA78_Buf shuffle;
    s32 ptr_count;
    s32 index;
    s32 record_count;
    S_8004AA78_Rec *records;
    S_8004AA78_Rec *record;
    u8 *packed_cursor;
    s32 item_ptr;

    ptr_count = 0;
    record_count = itemCategoryTable[category].count;
    records = itemCategoryTable[category].records;
    index = 0;
    if (record_count != 0) {
        record = records;
        packed_cursor = shuffle.indices;
        do {
            item_ptr = record->ptr;
            if (item_ptr != 0) {
                *(s32 *)(packed_cursor + 0x40) = item_ptr;
                packed_cursor += 4;
                ptr_count += 1;
            }
            index += 1;
            record += 1;
        } while (index < record_count);
    }

    index = 0;
    if (ptr_count > 0) {
        do {
            shuffle.indices[index] = (u8)index;
            index += 1;
        } while (index < ptr_count);
    }

    shuffle_byte_array(shuffle.indices, ptr_count);

    ptr_count = 0;
    index = 0;
    if (record_count != 0) {
                        /* Indexed form keeps base+0xC (avoids IV strength-reduce to &field). */
        S_8004AA78_Buf *shuffle_buf = &shuffle;
        do {
            item_ptr = records[index].ptr;
            if (item_ptr != 0) {
                item_ptr = shuffle_buf->ptrs[shuffle_buf->indices[ptr_count]];
                ptr_count += 1;
                records[index].ptr = item_ptr;
            }
            index += 1;
        } while (index < record_count);
    }
}
