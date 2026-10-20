#include "common.h"

/* S_80048500_elem: 8-byte element type indexed by a0 within a D_800710E4[a1] sub-array. */
typedef struct {
    s32 w0;
    s32 w1;
} S_80048500_elem;

/* Sized array (>8B) => forces %hi/%lo addressing (not $gp-relative). */
extern S_80048500_elem *palette_resource_descriptors[100];

/* S_80048500_target: struct pointed to by D_80081480.field_0; only the s16 field at
 * offset 0x18 is accessed here. */
typedef struct {
    s8 pad[0x18];
    s16 unk18;
} S_80048500_target;

/* S_80081480: >8B struct forced to hi/lo addressing; field_0 holds a pointer value. */
typedef struct {
    S_80048500_target *field_0;
    s32 pad4;
    s32 pad8;
} S_80081480;

extern S_80081480 gpu_scratch_write_pointer;

extern void file_load_com(void *arg);
extern void drain_cd_command_queue(void);
extern void DrawSync(s32 a0);
extern s32 copy_processed_vram_tile_backward(s32 a0);

/* Processes the selected element, waits for drawing, and redraws the target VRAM tile. */
s32 load_resource_and_mirror_palette(s32 elem_index, s32 array_index)
{
    s32 tile_index;

    file_load_com(&palette_resource_descriptors[array_index][elem_index]);
    drain_cd_command_queue();
    tile_index = gpu_scratch_write_pointer.field_0->unk18;
    DrawSync(0);
    return copy_processed_vram_tile_backward(tile_index);
}
