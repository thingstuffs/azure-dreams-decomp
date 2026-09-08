#include "common.h"
#include "m2c_compat.h"

extern u8 D_800D4258[];

typedef struct S_800C17A0_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_800C17A0_0;   /* base in func_800C17A0 */

/* town_seq_reserve: reserve the town sequence pair. */
void func_800C17A0(s16 sequence_effect, s16 sequence_id) {
    u8 *reserved_sound;

    reserved_sound = D_800D4258;
    ((S_800C17A0_0 *)reserved_sound)->unk_04 = sequence_effect;
    ((S_800C17A0_0 *)reserved_sound)->unk_06 = sequence_id;
}
