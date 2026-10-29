#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"

/* extern */

typedef struct S_80124F6C_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
} S_80124F6C_0;   /* arg0 in enter_catalog_detail_input */

/* Initialize the state fields before calling reset_catalog_scroll_indicators. */
void enter_catalog_detail_input(S_80124F6C_0 *state) {
    state->unk_0A = 8;
    state->unk_04 = 0;
    state->unk_06 = 0;
    reset_catalog_scroll_indicators(state);
}
