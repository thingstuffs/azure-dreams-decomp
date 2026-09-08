#include "common.h"

extern u8 D_800E3D40[];

extern s32 func_800C8CD8(void *arg0, s32 arg1, s32 arg2);
extern void func_800A6508(void);
extern void func_800C5BBC(s32, s32, s32, s32, s32, s32);
extern void func_800A56E0(s32);

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0xE];
    u8 x;
    u8 y;
} Entry;

s32 func_800CC2A8(void *arg0) {
    s32 amount = 0x40;
    Entry *entry;

    if (D_800E3D40[0] != 0) {
        amount = 0x400;
    }
    if (func_800C8CD8(arg0, amount, 0x10) == 0) {
        if (*(u8 *)((u8 *)arg0 + 0x13) == 0) {
            func_800A6508();
            return 1;
        }
        return 1;
    }
    entry = *(Entry **)((u8 *)arg0 - 0x14);
    if (!(entry->flags & 0x8000)) {
        func_800C5BBC((entry->x << 6) | 0x20,
                      (entry->y << 6) | 0x20,
                      *(s16 *)((u8 *)arg0 + 0x88), 0x802020, 0x20, 0);
        func_800A56E0(0x611);
    }
    return 1;
}
