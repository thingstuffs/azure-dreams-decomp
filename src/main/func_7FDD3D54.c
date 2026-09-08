#include "common.h"

typedef struct MainValue {
    u8 pad0[0xC];
    s16 type;
    u8 padE[8];
    s16 flags;
} MainValue;

extern u16 D_8008B368[];
extern u16 D_8008B36A[];
extern u16 D_8008B36C[];
extern s32 D_800814A0[];
extern void func_7008ACFC(void);

/* Sets output fields from the value's type and propagates its high flag bit. */
void func_7FDD3D54(MainValue **value_slot, u8 *output, MainValue *value)
{
    value = *value_slot;
    if (value->type == 0 && (value->flags & 2) != 0) {
        *(u16 *)(output + 2) = D_8008B36A[0];
        func_7008ACFC();
        return;
    }
    *(u16 *)(output + 2) = D_8008B368[0];
    *(u16 *)(output + 6) = D_8008B36C[value->type];
    if ((value->flags & 0x8000) != 0) {
        *(u16 *)((u8 *)value_slot - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
