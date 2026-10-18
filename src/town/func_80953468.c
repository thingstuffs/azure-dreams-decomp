#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/types3b_types.h"

typedef struct S_80020468_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80020468_1;   /* arg0 in propagate_linked_flag_to_record */

typedef struct S_80020468_2 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80020468_2;   /* ((S_80020468_1 *)arg0)->unk_04 in propagate_linked_flag_to_record */


   /* arg0 in propagate_linked_flag_to_record; pointer addresses record offset 0x2 */


/* Propagate bit 15 from the linked record to the record and global flags. */
void propagate_linked_flag_to_record(void *record) {
    if (((S_80020468_2 *)(((S_80020468_1 *)record)->unk_04))->unk_04 & 0x8000) {
        ((ObjectStatusPrefix16 *)((u8 *)record - 0x2))->unk_00 = (u16) (((ObjectStatusPrefix16 *)((u8 *)record - 0x2))->unk_00
            | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
