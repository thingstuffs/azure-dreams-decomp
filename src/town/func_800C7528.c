#include "common.h"

typedef struct {
    s32 unk0;
    void *unk4;
} Entry;

extern Entry D_80082660[];
extern s32 D_80082A38[];
extern u8 D_800C3174[];
extern u8 D_800C321C[];

extern s32 func_800C2B6C(s32, void *);
extern void func_800C4D00(s32, void *);

void func_800C4C88(s32 arg0) {
    s32 *dst = D_80082A38;
    void *entry;
    u8 *data;

    if (arg0 != 0) {
        entry = D_80082660[arg0].unk4;
        if (entry != 0) {
            data = (u8 *)entry + 0x20;
            if (arg0 == 1) {
                void *kind = *(void **)((u8 *)entry + 0x10);

                if (kind != D_800C3174 && kind != D_800C321C) {
                    func_800C4D00(*(u16 *)(data + 0x10) << 16, data);
                    return;
                }
            }
            dst[0x12] = func_800C2B6C(*(volatile s16 *)(data + 0x72), data);
        }
    }
}
