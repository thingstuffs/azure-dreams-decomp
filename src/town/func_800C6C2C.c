#include "common.h"

typedef struct {
    s8 val;
    u8 pad[7];
} Rec8;

extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);
extern void func_800C3C5C(void);
extern Rec8 D_80082660[];

void func_800C438C(void *arg0, s32 unused1, s32 arg2) {
    func_800C2E84(arg0, arg2, *(void **) ((u8 *) *(void **) ((u8 *) arg0 + 0x80) + 0x14));
    D_80082660[*(s32 *) ((u8 *) arg0 + 0x60)].val = 0;
    *(void **) ((u8 *) arg0 + 0x54) = (void *) func_800C3C5C;
    *(s16 *) ((u8 *) arg0 + 0x72) = 0;
}
