#include "common.h"
#include "engine/graphics.h"
#include "engine/resource.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"

typedef struct { s16 x, y, w, h; } RECT;

/* Real symbol is a RECT (8 bytes); padded here to force %hi/%lo (not $gp)
 * addressing, matching the target's lui/addiu address construction. */
typedef struct { s16 x, y, w, h; s32 pad; } S_800483AC_rect;

extern S_800483AC_rect alternate_texture_clear_rect_0;
extern S_800483AC_rect alternate_texture_clear_rect_1;

/* Uploads a zeroed buffer to the selected rectangle, submits two transfers, and waits for drawing. */
void clear_alternate_texture_regions(s16 use_alt_rect)
{
    void *clear_buf;

    clear_buf = alloc_gpu_scratch_ring(0x2000);
    bzero(clear_buf, 0x2000);

    if (use_alt_rect) {
        LoadImage((RECT *)&alternate_texture_clear_rect_1, clear_buf);
        upload_vram_row_and_cache((s32)clear_buf, 0x7A40, 1, 2);
        upload_vram_row_and_cache((s32)clear_buf, 0x79C0, 1, 2);
    } else {
        LoadImage((RECT *)&alternate_texture_clear_rect_0, clear_buf);
        upload_vram_row_and_cache((s32)clear_buf, 0x7A41, 1, 2);
        upload_vram_row_and_cache((s32)clear_buf, 0x79C1, 1, 2);
    }
    DrawSync(0);
}
