#include "common.h"

typedef struct {
    s32 words[3];
} TownRecord;

extern s32 func_8009CFE0(void *arg0, void *arg1);
extern void func_80033D08(void *arg0);

extern s32 D_800814A0[3];
extern s32 D_800D0E44;
extern s32 D_800D0E40[3];
extern TownRecord D_800F8A70[];

void func_800A833C(void *arg0, void *arg1, void *arg2)
{
    u8 *field98;

    if (func_8009CFE0(arg0, arg1) != 0) {
        field98 = *(u8 **)((u8 *)arg0 + 0x98);
        if (field98 != 0) {
            *field98 = 0;
        }
        func_80033D08(arg0);
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    if (D_800D0E44 < 0) {
        D_800D0E44 = 0;
    } else if (D_800D0E44 >= 21) {
        D_800D0E44 = 20;
    }
    *(TownRecord **)((u8 *)arg2 + 8) = &D_800F8A70[D_800D0E40[1]];
}
