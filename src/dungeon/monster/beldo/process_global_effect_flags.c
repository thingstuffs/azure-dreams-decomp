#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

extern s32 enqueue_runtime_pool_script(void *input_data);                   /* extern */
extern M2C_UNK beldo_effect_pool_script;

typedef struct S_81254060_0 {
    u8 pad_00[0x6D];
    s8 unk_6D;
} S_81254060_0;   /* arg3 in process_global_effect_flags */

typedef struct S_81254060_1 {
    u8 pad_00[0x9B];
    s8 unk_9B;
} S_81254060_1;   /* arg0 in process_global_effect_flags */

/* Runs the global handler and clears both record flags when bit 21 is set. */
void process_global_effect_flags(S_81254060_1 *primary_record, s32 unused_1, s32 unused_2, S_81254060_0 *secondary_record) {
    if (((s32)g_game_work.pressed_buttons) & 0x200000) {
        enqueue_runtime_pool_script(&beldo_effect_pool_script);
        secondary_record->unk_6D = 0;
        primary_record->unk_9B = 0;
    }
}
