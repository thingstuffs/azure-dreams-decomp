#include "common.h"
#include "m2c_compat.h"

void clear_entity_record_fields();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098104;

typedef struct S_80098C04_0 {
    u8 pad_00[0x4];
    s32 * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80098C04_0;   /* arg0 in set_handler_counter_and_clear_flag */

/* Assign the state table, clear the global flag, set the counter to 12, and initialize the target. */
void set_handler_counter_and_clear_flag(S_80098C04_0 *state, s32 target) {
    state->unk_04 = &D_80098104;
    D_80082668 = 0;
    state->unk_0A = 0xC;
    clear_entity_record_fields(target);
}
