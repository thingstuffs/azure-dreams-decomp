#include "common.h"

extern s32 D_8001B218[];

void func_80018198(void);
void func_8001844C(s32 arg0);
void func_8001A418(s32 arg0);

/* Process flagged type 0x18 entries, displaying messages and invoking their handlers. */
void func_800181DC(void) {
    u8 *entry;
    u8 *type_ptr;
    u8 entry_code;

    entry = (u8 *)D_8001B218;
    entry_code = entry[1];
    type_ptr = entry + 1;
    if (entry_code == 0) {
        return;
    }

    do {
        if ((entry_code == 0x18) && (type_ptr[2] & 0x20)) {
            entry_code = entry[0];
            if (entry_code == 0x20) {
                func_80018198();
            } else {
                if (entry_code == 0x1C) {
                    func_8001A418(0xD);
                } else if (entry_code == 0x1D) {
                    func_8001A418(0xE);
                }
                func_8001A418(entry[0] + 0x1497);
                func_8001A418(0x14C9);
                func_8001844C(entry[0]);
            }
        }
        type_ptr += 4;
        entry_code = type_ptr[0];
        entry += 4;
    } while (entry_code != 0);
}
