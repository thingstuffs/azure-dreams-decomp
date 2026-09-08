#include "common.h"

extern s32 func_8004A618(void *arg0);
extern s8 D_800D1074[];
extern s32 D_800D1080[];

/* Classifies listed entry types by two value thresholds, returning 3 for unlisted types. */
s32 func_800A9A38(u8 *entry) {
    s32 type_index;
    s32 entry_value;

    if (D_800D1074[0] != -1) {
        type_index = 0;
        do {
            if (D_800D1074[type_index] == entry[1]) {
                entry_value = func_8004A618(entry);
                if (entry_value < D_800D1080[0]) {
                    return 0;
                }
                if (entry_value < D_800D1080[1]) {
                    return 1;
                }
                return 2;
            }
            type_index++;
        } while (D_800D1074[type_index] != -1);
    }

    return 3;
}
