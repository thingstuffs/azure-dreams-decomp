#include "common.h"

extern void *D_8008ACDC[];
extern void *D_8008EAC8[];
extern u32 D_8008346C[];
extern s32 func_800A1C58(void *arg0, void *arg1);

/* Selects the target's table from flags and clears global state when the update returns zero. */
void func_800924F0(void *target, void *unused, void *flag_data, void *source) {
    void *table;
    if (!(*(s32 *)((u8 *)source + 0x1C) & 0x100000)) {
        if (*(u16 *)((u8 *)flag_data + 0x14) & 0xE000) {
            table = D_8008ACDC;
        } else {
            return;
        }
    } else {
        table = D_8008EAC8;
    }

    *(void **)((u8 *)target + 0x8C) = table;
    if ((func_800A1C58(source, target) << 16) == 0) {
        D_8008346C[0] = 0;
    }
}
