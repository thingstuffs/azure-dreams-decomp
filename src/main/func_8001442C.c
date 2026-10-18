#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E994();                         /* extern */

typedef struct S_8002742C_0 {
    u8 pad_00[0xFC];
    s32 * unk_FC;
} S_8002742C_0;   /* arg0 in release_three_row_panel_text */

/* Pass the object's referenced value to func_8004E994. */
void release_three_row_panel_text(S_8002742C_0 *object) {
    func_8004E994(*object->unk_FC);
}
