#include "common.h"

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0xE];
    u8 x;
    u8 y;
} Entry;

extern u8 D_800E3D40[];
extern u8 D_800DF870[];

extern s32 func_800A6D30(void);
extern void func_800A6508(void);
extern void func_800A56E0(s32);
extern void func_800C8DB0(void *, s32, s32);
extern void func_800C5E5C(s32, s32, s32, void *, s32);
extern void func_800CDD58(void);
extern void func_800CDDF8(void);

s32 func_800CDD0C(void *arg0)
{
    s32 result;
    register s32 remainder ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 random ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 range;
    s32 amount;
    Entry *entry;

    if (D_800E3D40[0] != 0) {
        goto main_path;
    }
    random = func_800A6D30() & 0xFFFF;
    range = *(u8 *)((u8 *)arg0 + 3);
    if (range == 0) {
        goto main_path;
    }
    result = range;
    ASM_USE(range);   /* MATCH pin: retail delay-slot fill depends on it */
    remainder = random % result;
    ASM_USE(remainder);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_800CDD58();
    return remainder;

main_path:
    result = 0;
    ASM_KEEP(result);   /* MATCH pin: retail basic-block layout depends on it */

    if (result < 0x30) {
        amount = 0x20;
        if (D_800E3D40[0] != 0) {
            amount = 0x400;
        }
        func_800C8DB0(arg0, amount, 0x10);

        entry = *(Entry **)((u8 *)arg0 - 0x14);
        if (!(entry->flags & 0x8000)) {
            func_800C5E5C((entry->x << 6) | 0x20,
                          (entry->y << 6) | 0x20,
                          *(s16 *)((u8 *)arg0 + 0x88), D_800DF870, 0);
            func_800A56E0(0x70A);
            func_800CDDF8();
            return 1;
        }
        return 1;
    }

    if (*(u8 *)((u8 *)arg0 + 0x13) == 0) {
        func_800A6508();
    }
    return 1;
}
