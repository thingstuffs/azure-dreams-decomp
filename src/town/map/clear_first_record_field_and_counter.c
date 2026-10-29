#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/map.h"

extern s16 tile_key_pair_count;
extern s32 tile_coordinate_records;

typedef struct S_800AC454_0 {
    u8 pad_00[0x20];
    s8 unk_20;
} S_800AC454_0;

/* Selects record zero, stores its field address, and clears the field and global counter. */
void clear_first_record_field_and_counter(void) {
    void *record;

    record = allocate_flagged_object_node(0);
    tile_coordinate_records = record + 0x20;
    ((S_800AC454_0 *)record)->unk_20 = 0;
    tile_key_pair_count = 0;
}
