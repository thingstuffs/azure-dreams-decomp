#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/dungeon_delay_views.h"

typedef struct S_80097D08_0 {
    void (*unk_00)();
    u8 pad_04[0x78];
    s16 unk_7C;
    u8 pad_7E[0x28];
    s8 unk_A6;
} S_80097D08_0;   /* arg0 in set_motion_handler_and_copy_signed_byte; pointer addresses record offset 0x10 */

   /* arg1 in set_motion_handler_and_copy_signed_byte */


extern void D_80097C50(void *object, s32 target);

/* Set the record pointer and state, and copy its signed byte to the output in 16.16 format. */
void set_motion_handler_and_copy_signed_byte(void *record_data, void *placement, struct SpriteFrameState *unused_sprite) {
    DelayMotionZ *output = placement;

    ((S_80097D08_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80097C50;
    output->unk_08 = (s32) (((S_80097D08_0 *)((u8 *)record_data - 0x10))->unk_A6 << 0x10);
    ((S_80097D08_0 *)((u8 *)record_data - 0x10))->unk_7C = 5;
}
