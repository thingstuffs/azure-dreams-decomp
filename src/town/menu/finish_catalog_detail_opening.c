#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"

/* extern */

typedef struct S_80124F20_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
    s8 unk_0B;
} S_80124F20_0;   /* arg0 in finish_catalog_detail_opening */

/* Advance the counter and initialize state eight when the limit is reached. */
void finish_catalog_detail_opening(S_80124F20_0 *controller) {
    u16 next_count;

    next_count = controller->unk_04 + 1;
    controller->unk_04 = next_count;
    if ((s16) next_count == controller->unk_06) {
        controller->unk_0B = 0;
        controller->unk_0A = 8;
        controller->unk_06 = 0;
        controller->unk_04 = 0U;
        reset_catalog_scroll_indicators(controller);
    }
}
