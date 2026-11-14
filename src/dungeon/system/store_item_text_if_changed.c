#include "common.h"
#include "m2c_compat.h"
#include "dungeon/system.h"
#include "sdk/libc.h"

void install_mode_gated_callback();                         /* extern */
s32 get_work_value_third();                             /* extern */

typedef struct S_8002573C_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_8002573C_0;   /* arg0 in store_item_text_if_changed */

typedef struct S_8002573C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    s32 unk_28;
} S_8002573C_1;

/* Process changed text, then finalize its context. */
s32 store_item_text_if_changed(void *context) {
    s32 text;
    S_8002573C_1 *text_state;

    text_state = ((S_8002573C_0 *)context)->unk_14 + 0x20;
    text = get_work_value_third(text_state->unk_28);
    if (strcmp(text, context + 0x78) != 0) {
        store_unique_text_record(text, ((S_8002573C_0 *)context)->unk_0C, text_state->unk_1C);
    }
    install_mode_gated_callback(((S_8002573C_0 *)context)->unk_14);
    return 1;
}
