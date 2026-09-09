#include "common.h"

typedef struct {
    u8 unk00[0xA];
    u16 unk0A;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern u16 D_800DDE84[];
extern u8 D_800E1035[];

extern void func_800A6480(void *arg0);
extern s32 func_800AD6FC(void *arg0, s32 arg1, s32 arg2);
extern void func_800A5F38(void *arg0, s32 arg1);
extern void func_80098B38(s32 arg0);
extern void func_800997FC(void *arg0);

/* Handle an item against a target using its type flags, decrementing the counter on fallback. */
s32 func_800BE4E8(void *target, s32 item) {
    u32 type_flags;

    if ((u32) target <= 0x9FFFFFFFU) {
        func_800A6480(target);
        type_flags = D_800DDE84[((u8 *) target)[0x13]];
        if (func_800AD6FC(target, (type_flags >> 2) & 3, 0) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
        func_80098B38(item);
    } else {
        func_800997FC(D_800E1035);
    }

    D_80083460.unk0A -= 1;
    return 1;
}
