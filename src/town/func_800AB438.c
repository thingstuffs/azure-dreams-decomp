#include "common.h"
#include "shared/dungeon_delay_views.h"

typedef struct S_800A8B98_0 {
    s32 * unk_00;
    u8 pad_04[0x78];
    s16 unk_7C;
    u8 pad_7E[0x28];
    s8 unk_A6;
} S_800A8B98_0;   /* arg0 in set_record_pointer_and_byte; pointer addresses record offset 0x10 */

   /* arg1 in set_record_pointer_and_byte */
void process_raised_position_pair(s32 unused_arg, s32 *position);

/* Sets the record's pointer and state and copies its signed byte to the output's high half. */
void set_record_pointer_and_byte(void *record_data, DelayMotionZ *output) {
    ((S_800A8B98_0 *)((u8 *)record_data - 0x10))->unk_00 = &process_raised_position_pair;
    output->unk_08 = (s32) (((S_800A8B98_0 *)((u8 *)record_data - 0x10))->unk_A6 << 0x10);
    ((S_800A8B98_0 *)((u8 *)record_data - 0x10))->unk_7C = 5;
}
