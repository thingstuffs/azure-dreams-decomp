#include "common.h"
#include "shared/object_links.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "frontend/settings.h"

typedef struct S_7FDD3AE0_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_7FDD3AE0_1;   /* arg0 in propagate_record_high_bit */

typedef struct S_7FDD3AE0_2 {
    u8 pad_00[0x16];
    s16 unk_16;
} S_7FDD3AE0_2;   /* ((S_7FDD3AE0_1 *)arg0)->unk_04 in propagate_record_high_bit */

/* Propagates the linked record high flag to the record and global flags. */
void propagate_record_high_bit(void *record) {
    if (((S_7FDD3AE0_2 *)(((S_7FDD3AE0_1 *)record)->unk_04))->unk_16 & 0x8000) {
        ((ObjectStatusPrefix16 *)((u8 *)record - 0x2))->flags = (u16) (((ObjectStatusPrefix16 *)((u8 *)record - 0x2))->flags
            | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
