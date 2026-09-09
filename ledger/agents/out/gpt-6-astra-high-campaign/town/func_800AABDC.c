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

/* Clears and flags a handled object, or clamps the town index and selects a record. */
void func_800A833C(void *object, void *check_context, void *record_holder)
{
    u8 *state_byte;

    if (func_8009CFE0(object, check_context) != 0) {
        state_byte = *(u8 **)((u8 *)object + 0x98);
        if (state_byte != 0) {
            *state_byte = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    if (D_800D0E44 < 0) {
        D_800D0E44 = 0;
    } else if (D_800D0E44 >= 21) {
        D_800D0E44 = 20;
    }
    *(TownRecord **)((u8 *)record_holder + 8) = &D_800F8A70[D_800D0E40[1]];
}
