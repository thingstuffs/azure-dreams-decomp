#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"

typedef struct S_80022454_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80022454_1;   /* arg0 in retire_line_effect_at_phase_eight */

typedef struct S_80022454_2 {
    u8 pad_00[0x36];
    s16 unk_36;
} S_80022454_2;   /* ((S_80022454_1 *)arg0)->unk_04 in retire_line_effect_at_phase_eight */


   /* arg0 in retire_line_effect_at_phase_eight; pointer addresses record offset 0x2 */


/* Set record and global flags when the linked object has state 8. */
void retire_line_effect_at_phase_eight(void *record) {
    if (((S_80022454_2 *)(((S_80022454_1 *)record)->unk_04))->unk_36 == 8) {
        ((ObjectStatusPrefix16 *)((u8 *)record - 0x2))->unk_00 = (u16) (((ObjectStatusPrefix16 *)((u8 *)record - 0x2))->unk_00
            | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
