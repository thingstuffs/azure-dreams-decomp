#include "common.h"

typedef struct {
    u32 unk0;
    void *unk4;
} Entry;

extern Entry D_80082660[];
extern s32 D_80082A38[64];

void func_800C4D20(s32 arg0) {
    s32 *dst = D_80082A38;
    void *entry;
    s16 *sub;

    if (arg0 != 0) {
        entry = D_80082660[arg0].unk4;
        if (entry != 0) {
            sub = *(s16 **)((u8 *)entry + 8);
            dst[0x13] = sub[1];
            dst[0x14] = sub[3];
            dst[0x15] = sub[5];
        }
    }
}
