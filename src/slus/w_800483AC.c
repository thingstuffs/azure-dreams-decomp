#include "common.h"

typedef struct { s16 x, y, w, h; } RECT;

/* Real symbol is a RECT (8 bytes); padded here to force %hi/%lo (not $gp)
 * addressing, matching the target's lui/addiu address construction. */
typedef struct { s16 x, y, w, h; s32 pad; } S_800483AC_rect;

extern void *alloc_gpu_scratch_ring(s32 a0);
extern void bzero(void *ptr, s32 len);
extern int LoadImage(RECT *rect, void *p);
extern int upload_vram_row_and_cache(s32 a0, s32 a1, s32 a2, s32 a3);
extern void DrawSync(s32 a0);

extern S_800483AC_rect D_800710D4;
extern S_800483AC_rect D_800710DC;

/* Uploads a zeroed buffer to the selected rectangle, submits two transfers, and waits for drawing. */
void clear_alternate_texture_regions(s16 use_alt_rect)
{
    void *clear_buf;

    clear_buf = alloc_gpu_scratch_ring(0x2000);
    bzero(clear_buf, 0x2000);

    if (use_alt_rect) {
        LoadImage((RECT *)&D_800710DC, clear_buf);
        upload_vram_row_and_cache((s32)clear_buf, 0x7A40, 1, 2);
        upload_vram_row_and_cache((s32)clear_buf, 0x79C0, 1, 2);
    } else {
        LoadImage((RECT *)&D_800710D4, clear_buf);
        upload_vram_row_and_cache((s32)clear_buf, 0x7A41, 1, 2);
        upload_vram_row_and_cache((s32)clear_buf, 0x79C1, 1, 2);
    }
    DrawSync(0);
}
