#include "common.h"
#include "m2c_compat.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */
extern s8 town_action_reset_byte;
extern void D_80098104();

typedef struct S_80098C04_0 {
    u8 pad_00[0x4];
    void (*unk_04)();
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80098C04_0;   /* arg0 in set_handler_counter_and_clear_flag */

/* Assign the state table, clear the global flag, set the counter to 12, and initialize the target. */
void set_handler_counter_and_clear_flag(S_80098C04_0 *state, s32 target) {
    state->unk_04 = &D_80098104;
    town_action_reset_byte = 0;
    state->unk_0A = 0xC;
    clear_entity_record_fields((struct EntityRec *)(target));
}
