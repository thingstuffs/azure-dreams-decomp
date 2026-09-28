#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80403E54();                       /* extern */
M2C_UNK func_80403F1C();       /* extern */
M2C_UNK func_80403F7C();                       /* extern */
M2C_UNK func_804040C8();                       /* extern */

/* Absolute anchor for a table of 128-byte records; the two fields accessed here
 * are 8 bytes apart and sit just BEFORE this anchor address (negative offsets). */
extern s32 D_800A0000[];
__asm__(".set D_800A0000, 0x800A0000");

/* Initializes a record's buffers and dispatches its state-specific handler. */
void func_80404178(s32 *record) {
    s32 record_index;

    func_80403F1C((u8 *)record + 0xB0, 0x80, 0x18);
    func_80403F1C((u8 *)record + 0x128, 0x2C, 0x14);

    record_index = *record << 7;
    if (*(s32 *)((u8 *)D_800A0000 + record_index - 0x2228) != 0) {
        func_80403F7C(record);

        record_index = *record << 7;
        if (*(s32 *)((u8 *)D_800A0000 + record_index - 0x2220) != 0) {
            func_804040C8(record);
            return;
        }
    } else {
        func_80403E54(record);
    }
}
