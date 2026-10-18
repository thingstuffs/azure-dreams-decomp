#include "common.h"

void func_80403E54();                       /* extern */
void func_80403F1C(void *, s32, s32);       /* extern */
void position_selected_entry_content();                       /* extern */
void func_804040C8();                       /* extern */

/* Absolute anchor for a table of 128-byte records; the two fields accessed here
 * are 8 bytes apart and sit just BEFORE this anchor address (negative offsets). */
extern s32 D_800A0000[];

void complete_pending_object_state(s32 *ptr) {
    s32 offset;

    func_80403F1C((u8 *)ptr + 0xB0, 0x80, 0x18);
    func_80403F1C((u8 *)ptr + 0x128, 0x2C, 0x14);

    offset = *ptr << 7;
    if (*(s32 *)((u8 *)D_800A0000 + offset - 0x2228) != 0) {
        position_selected_entry_content(ptr);

        offset = *ptr << 7;
        if (*(s32 *)((u8 *)D_800A0000 + offset - 0x2220) != 0) {
            func_804040C8(ptr);
            return;
        }
    } else {
        func_80403E54(ptr);
    }
}
