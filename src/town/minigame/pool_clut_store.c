#include "shared/game_work.h"
#include "town/data.h"
#include "town/minigame/pool_palette_data.h"

extern void StoreImage(void *data_ptr_a, void *data_ptr_b);
extern void DrawSync(s32 value);
extern void MoveImage(void *data_ptr, s32 value_a, s32 value_b);
/* pool_clut_store: Store the pool CLUT and update its transfer region. */
void pool_clut_store(void)
{
    StoreImage(pool_palette_rect_2, pool_palette_backup);
    DrawSync(0);
    MoveImage(pool_palette_rect, 0x60, 0x1FA);
}
