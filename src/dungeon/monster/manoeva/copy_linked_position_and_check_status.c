#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_801745F0_3 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_801745F0_3;   /* arg0 in copy_linked_position_and_check_status */

   /* ((S_801745F0_3 *)arg0)->unk_1C in copy_linked_position_and_check_status */

   /* arg1 in copy_linked_position_and_check_status */

typedef struct S_801745F0_2 {
    u16 unk_00;
} S_801745F0_2;   /* arg0 in copy_linked_position_and_check_status; pointer addresses record offset 0x2 */

void advance_sprite_animation_and_textures();                      /* extern */

/* Copy three object fields and set object and global flags from the processed status. */
void copy_linked_position_and_check_status(void *object, MovingPosition *dest, SpriteFrameState *status) {
    dest->x = (u16) ((MovingPosition *)(((S_801745F0_3 *)object)->unk_1C))->x;
    dest->y = (u16) ((MovingPosition *)(((S_801745F0_3 *)object)->unk_1C))->y;
    dest->z = (u16) ((MovingPosition *)(((S_801745F0_3 *)object)->unk_1C))->z;
    advance_sprite_animation_and_textures(status);
    if (status->flags & 0x6000) {
        ((S_801745F0_2 *)((u8 *)object - 0x2))->unk_00 = (u16) (((S_801745F0_2 *)((u8 *)object - 0x2))->unk_00
            | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
