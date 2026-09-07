#include "common.h"

typedef struct {
    s32 active;
    void *object;
} ObjectSlot;

typedef struct {
    void *value;
} PointerField;

typedef struct {
    s32 value;
} WordField;

extern s32 D_800C3174;
extern s32 D_800C3438;
extern ObjectSlot D_80082660[];

void func_800C3050(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 new_var;

    ((PointerField *)((u8 *)arg0 - 0x10))->value = &D_800C3174;
    ((PointerField *)((u8 *)arg0 + 0x50))->value = &D_800C3438;
    ((WordField *)((u8 *)arg0 + 0x60))->value = arg1;
    ((WordField *)((u8 *)arg0 + 0x58))->value = arg2;
    ((WordField *)((u8 *)arg0 + 0x5C))->value = arg3;
    ((WordField *)((u8 *)arg0 + 0x7C))->value = arg4;
    new_var = ((WordField *)((u8 *)arg0 + 0x60))->value;
    ((WordField *)((u8 *)arg0 + 0x80))->value = arg5;
    D_80082660[new_var].object = (u8 *)arg0 - 0x20;
}
