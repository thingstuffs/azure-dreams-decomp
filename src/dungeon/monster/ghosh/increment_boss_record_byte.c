#include "common.h"
#include "m2c_compat.h"
#include "dungeon/monster/ghosh.h"

typedef struct S_80173DF0_0 {
    u8 pad_00[0x360C];
    u8 unk_360C;
} S_80173DF0_0;

/* Increment the byte counter in the record at the given base-relative offset. */
void increment_boss_record_byte(s32 record_offset) {
    S_80173DF0_0 *record;

    record = (void *)0x80010000 + record_offset;
    record->unk_360C = (u8) (record->unk_360C + 1);
}
