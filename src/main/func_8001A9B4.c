#include "common.h"

extern s32 D_804094EC[];
extern s32 D_804000F4;
extern s32 D_80408AA0[2];
extern s8 D_80409290[];

s32 func_8007BF80();
s32 func_8007BF50();
s32 func_8007CAB8();
s32 func_8007CAC8();

/* Collects entries matching the selected search path and returns their count. */
s32 func_8001A9B4(void) {
    s32 search_path[8];
    s32 *path_prefix;
    s8 *entry;
    s32 entry_count;

    entry_count = 0;
    entry = D_80409290;
    path_prefix = &D_80408AA0[0];
    if (D_804094EC[0] != 0) {
        path_prefix = &D_80408AA0[0] + 1;
    }
    func_8007BF80(&search_path, *path_prefix);
    func_8007BF50(&search_path, &D_804000F4);
    if (func_8007CAB8(&search_path, entry) != 0) {
        do {
            entry_count += 1;
            entry += 0x28;
        } while (func_8007CAC8(entry) == entry);
    }
    return entry_count;
}
