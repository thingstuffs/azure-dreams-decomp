#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/minigame/state.h"

   /* the 0x2 bytes before arg0 in update_tile_row_position, addressed as arg0[-1] */


typedef struct S_80021028_1 {
    u8 pad_00[0x4];
    u16 unk_04;
    s16 unk_06;
} S_80021028_1;


/* Updates the object's derived value and propagates the linked data's 0x8000 flag. */
void update_tile_row_position(void *object_arg) {
    SceneTileObject *object = object_arg;
    ObjectStatusPrefix16 *object_view = object_arg;
    S_80021028_1 *objectData;

    objectData = object->linked;
    object->y.s = (s16) ((objectData->unk_06 * 0xC) + 0x1E);
    if (objectData->unk_04 & 0x8000) {
        object_view[-1].flags = (u16) (object_view[-1].flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
