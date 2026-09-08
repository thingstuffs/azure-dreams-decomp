#include "common.h"

extern s32 func_8009CFE0(void *, void *);
extern void func_80033D08(void *arg0);
extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];

/* Clear object status and set flags on a successful check, or run the fallback. */
void func_800A7B14(void *object, void *check_data, void *fallback_data)
{
    u8 *status_byte;

    if (func_8009CFE0(object, check_data) != 0) {
        status_byte = *(u8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    } else {
        func_800478B8(fallback_data);
    }
}
