#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_delay_views.h"
#include "town/map.h"
#include "town/map/position.h"

typedef struct S_800A8B98_0 {
    void (*unk_00)(s32,  s32 *);
    u8 pad_04[0x78];
    s16 unk_7C;
    u8 pad_7E[0x28];
    s8 unk_A6;
} S_800A8B98_0;   /* arg0 in set_record_pointer_and_byte; pointer addresses record offset 0x10 */

   /* arg1 in set_record_pointer_and_byte */

/* Sets the record's pointer and state and copies its signed byte to the output's high half. */
void set_record_pointer_and_byte(void *record_data, void *placement, struct SpriteFrameState *unused_sprite) {
    DelayMotionZ *output = placement;

    ((S_800A8B98_0 *)((u8 *)record_data - 0x10))->unk_00 = &process_raised_position_pair;
    output->unk_08 = (s32) (((S_800A8B98_0 *)((u8 *)record_data - 0x10))->unk_A6 << 0x10);
    ((S_800A8B98_0 *)((u8 *)record_data - 0x10))->unk_7C = 5;
}
