#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "slus/data.h"

typedef struct { s16 x, y, w, h; } RECT;

/* Uploads a VRAM strip and records its source and width in the cache. */
void upload_vram_row_and_cache(s32 src_addr, s32 vram_addr, s32 block_count, s32 skip_flags)
{
    s32 slot;
    s32 flags;
    s32 width_blocks;
    s32 *cache;

    flags = skip_flags;
    width_blocks = block_count;
    slot = (vram_addr - 0x7000) >> 6;
    if (!(flags & 1)) {
        RECT rect;
        rect.x = ((slot & 0x40) << 1) + ((vram_addr & 0x3F) << 4);
        rect.y = (slot & 0x3F) + 0x1C0;
        rect.w = width_blocks << 4;
        rect.h = 1;
        LoadImage(&rect, (void *)src_addr);
    }
    if (!(flags & 2)) {
        vram_row_upload_cache[slot] = (src_addr & 0xFFFFFF) | (width_blocks << 24);
    }
    if (slot < 0x40 && width_blocks >= 0x11) {
        cache = vram_row_upload_cache;
        cache[slot + 0x40] = 0;
    }
}
