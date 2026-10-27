#include "common.h"
#include "town/scene/collection.h"

extern void *func_800374FC(s32, void *);
extern void func_8003BC18(void *, void *);
extern u8 menu_entry_draw_callback_address[];

typedef struct FourWords {
    s32 word[4];
} FourWords;

/* Allocate a record, install its callback, and copy three data blocks. */
void create_record_with_three_data_blocks(void *callback, void *data_blocks) {
    u8 *record;
    FourWords *src_block;
    FourWords *dst_block;
    FourWords *src_end;

    record = func_800374FC(1, &scene_object_factory_data);
    dst_block = (FourWords *)(record + 0x20);
    if (record != 0) {
        src_block = data_blocks;
        src_end = src_block + 3;
        do {
            *dst_block++ = *src_block++;
        } while (src_block != src_end);
        *(void **)(record + 0x10) = callback;
        func_8003BC18(record, menu_entry_draw_callback_address);
    }
}
