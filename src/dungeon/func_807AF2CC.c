#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"


typedef struct S_807AF2CC_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_807AF2CC_0;   /* func_8003FC64(0) in func_800F6ACC */

/* Set the returned object's data pointer to update_dungeon_tile_boundary_state. */
void func_800F6ACC(void) {
    ((S_807AF2CC_0 *)(func_8003FC64(0)))->unk_10 = (void *)update_dungeon_tile_boundary_state;
}
