#include "common.h"

typedef struct {
    s32 unk0;
    void *unk4;
} Entry;

extern Entry D_80082660[];
extern s32 D_80082A38[];

extern s32 func_800C2B6C(s32, void *);

void func_800C4BE0(s32 arg0, void *arg1) {
    s32 *dst = D_80082A38;
    void *entry;

    if (arg0 != 0) {
        entry = D_80082660[arg0].unk4;
        if (entry != 0) {
            dst[0x12] = func_800C2B6C(*(s16 *)((u8 *)entry + 0x8E), arg1);
        }
    }
}
