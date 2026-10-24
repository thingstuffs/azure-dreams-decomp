#include "common.h"
#include "shared/item_menu.h"

extern u8 D_800891F8[0x29];
extern ItemMenuPart *build_reverse_indexed_chain(ItemMenuPart **parts, u8 *indices, s32 index_limit);

typedef struct CopyData {
    u32 words[10];
    u8 tail;
} CopyData;

/* Links the parts listed in a local copy of D_800891F8 into the draw chain and returns its head. */
ItemMenuPart *link_item_menu_object_entries(ItemMenuPart **parts)
{
    CopyData data_copy;

    __builtin_memcpy(&data_copy, D_800891F8, 0x29);
    return build_reverse_indexed_chain(parts, (u8 *)&data_copy, 0x28);
}
