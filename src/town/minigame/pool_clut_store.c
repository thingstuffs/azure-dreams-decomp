#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern void StoreImage(void *data_ptr_a, void *data_ptr_b);
extern void DrawSync(s32 value);
extern void MoveImage(void *data_ptr, s32 value_a, s32 value_b);
extern u8 pool_palette_rect_2[];
extern u8 pool_palette_rect[];
extern u8 pool_palette_backup[];
/* pool_clut_store: Store the pool CLUT and update its transfer region. */
void pool_clut_store(void)
{
    StoreImage(pool_palette_rect_2, pool_palette_backup);
    DrawSync(0);
    MoveImage(pool_palette_rect, 0x60, 0x1FA);
}
