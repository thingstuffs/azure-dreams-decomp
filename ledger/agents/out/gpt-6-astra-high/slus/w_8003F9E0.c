#include "common.h"

/* struct describing one draw-entry: word handle/flag at 0, two halfword coords at 4/6, pad to 0xC */
typedef struct S_8003F9E0 {
    s32 f0;
    u16 f4;
    u16 f6;
    s32 f8;
} S_8003F9E0;

extern s32 func_8003F80C(s32 a0, s32 a1, s32 a2, s32 a3);

/* Dispatch draw entries until an entry with a zero handle is reached. */
void func_8003F9E0(S_8003F9E0 *entries) {
    S_8003F9E0 *entry = entries;

    while (entry->f0) {
        func_8003F80C(entry->f0, entry->f4, entry->f6, 0);
        entry++;
    }
}
