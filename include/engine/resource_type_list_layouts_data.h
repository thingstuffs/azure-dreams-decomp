#ifndef ENGINE_RESOURCE_TYPE_LIST_LAYOUTS_DATA_H
#define ENGINE_RESOURCE_TYPE_LIST_LAYOUTS_DATA_H

#include "common.h"

/* The loader uses the data pointer and count at +0/+4; list relocation uses
 * the second count at +6 and four word-scaled offsets at +8 through +E. */
typedef struct ResourceTypeListLayout {
    s32 *data;
    u16 packed_chunk_count;
    u16 relocation_count;
    u16 off8;
    u16 offA;
    u16 offC;
    u16 offE;
} ResourceTypeListLayout;

extern ResourceTypeListLayout *resource_type_list_layouts[];

#endif
