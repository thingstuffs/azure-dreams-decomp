#include "common.h"
#include "frontend/libcard/message.h"
void noop_release_notification(s32);                         /* extern */

typedef struct S_8002742C_0 {
    u8 pad_00[0xFC];
    s32 * unk_FC;
} S_8002742C_0;   /* arg0 in release_three_row_panel_text */

/* Pass the object's referenced value to func_8004E994. */
void release_three_row_panel_text(S_8002742C_0 *object) {
    noop_release_notification(*object->unk_FC);
}
