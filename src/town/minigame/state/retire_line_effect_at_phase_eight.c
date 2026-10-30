#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/minigame/state.h"

typedef struct S_80022454_2 {
    u8 pad_00[0x36];
    s16 unk_36;
} S_80022454_2;   /* owner body reached through RetiringLineEffectObject::linked_object */

/* Set record and global flags when the linked object has state 8. */
void retire_line_effect_at_phase_eight(RetiringLineEffectObject *record) {
    if (((S_80022454_2 *)(record->linked_object))->unk_36 == 8) {
        ((ObjectStatusPrefix16 *)((u8 *)record - 0x2))->flags = (u16) (((ObjectStatusPrefix16 *)((u8 *)record - 0x2))->flags
            | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
