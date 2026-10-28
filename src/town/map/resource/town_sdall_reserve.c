#include "common.h"
#include "m2c_compat.h"

extern u8 town_pending_sound[];

typedef struct S_800C1770_0 {
    s16 unk_00;
} S_800C1770_0;   /* D_800D4258 in town_sdall_reserve */

typedef struct S_800C1770_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} S_800C1770_1;

/* town_sdall_reserve: reserve the four town sound effect and sequence values. */
void town_sdall_reserve(s16 effect_id, s16 sound_id, s16 sequence_effect, s16 sequence_id) {
    S_800C1770_1 *reserved_sound;

    ((S_800C1770_0 *)town_pending_sound)->unk_00 = effect_id;
    reserved_sound = (S_800C1770_1 *)town_pending_sound;
    reserved_sound->unk_02 = sound_id;
    reserved_sound->unk_04 = sequence_effect;
    reserved_sound->unk_06 = sequence_id;
}
