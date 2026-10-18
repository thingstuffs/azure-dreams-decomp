#include "common.h"

typedef struct S_8009EC3C_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_8009EC3C_0;   /* arg1 in clear_the_state_fields_initialize_handlers_mode */

typedef struct S_8009EC3C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009EC3C_1;   /* arg2 in clear_the_state_fields_initialize_handlers_mode */

typedef struct S_8009EC3C_2 {
    s32 * unk_00;
    u8 pad_04[0x5C];
    s32 * unk_60;
    u8 pad_64[0x18];
    s16 unk_7C;
} S_8009EC3C_2;   /* arg0 in clear_the_state_fields_initialize_handlers_mode; pointer addresses record offset 0x10 */
#include "modules/town_town_windows.h"
void invoke_entity_callback_and_follow_up(func_800A06C8_EntityLike *entity, s32 callback_id, s32 callback_data);
typedef struct S_8009ECF0_0 S_8009ECF0_0;
void run_both_updates_decrement_countdown_check_completion(S_8009ECF0_0 *state, s32 update_ctx, s32 update_data, s32 finish_ctx);

/* Clear the state fields and initialize the record handlers and mode. */
void clear_the_state_fields_initialize_handlers_mode(void *record_data, S_8009EC3C_0 *state, S_8009EC3C_1 *values) {
    state->unk_15 = 0;
    values->unk_0C = 0;
    values->unk_10 = 0;
    values->unk_14 = 0;
    ((S_8009EC3C_2 *)((u8 *)record_data - 0x10))->unk_60 = &run_both_updates_decrement_countdown_check_completion;
    ((S_8009EC3C_2 *)((u8 *)record_data - 0x10))->unk_7C = 7;
    ((S_8009EC3C_2 *)((u8 *)record_data - 0x10))->unk_00 = &invoke_entity_callback_and_follow_up;
}
