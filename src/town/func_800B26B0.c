#include "common.h"

extern u8 D_800891F8[0x29];
extern void build_reverse_indexed_chain(s32, void *, s32);

typedef struct CopyData {
    u32 words[10];
    u8 tail;
} CopyData;

/* Passes a local copy of D_800891F8 to build_reverse_indexed_chain for the target. */
void link_item_menu_object_entries(s32 target)
{
    CopyData data_copy;

    __builtin_memcpy(&data_copy, D_800891F8, 0x29);
    build_reverse_indexed_chain(target, &data_copy, 0x28);
}
