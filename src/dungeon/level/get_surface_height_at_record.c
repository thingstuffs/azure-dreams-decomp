#include "common.h"
#include "m2c_compat.h"

s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);                   /* extern */

typedef struct S_800BCAD0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BCAD0_0;   /* arg0 in get_surface_height_at_record */

/* Pass the record coordinates to sample_terrain_surface_height. */
s16 get_surface_height_at_record(S_800BCAD0_0 *record) {
    return sample_terrain_surface_height(record->unk_02, record->unk_06, record->unk_0A);
}
