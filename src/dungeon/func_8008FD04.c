#include "common.h"

extern s16 func_800B500C(s32, s32, s16);

typedef struct {
    u8 pad[3];
    u8 flags;
} DungeonEntry;

extern DungeonEntry D_800E3648[];

s32 func_80095464(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 result;
    s32 failed;

    result = func_800B500C(
        *((u8 *)arg2 + 0x24),
        *((u8 *)arg2 + 0x25),
        *(s16 *)((u8 *)arg3 + 0x88));
    *(s16 *)((u8 *)arg0 + 0x100) = result;

    if (result < 0) {
        failed = 1;
    } else {
        if (D_800E3648[result].flags & 0x80) {
            failed = 0;
        } else {
            *(s16 *)((u8 *)arg0 + 0x100) = -1;
            failed = 1;
        }
    }
    return failed;
}
