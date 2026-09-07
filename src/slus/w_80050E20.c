#include "common.h"

typedef struct {
    u8 pad_00[0x1E];
    u16 unk1E;
} S_80050E20_target;

typedef struct {
    u8 pad_00[0x1C];
    s32 unk1C;
    u8 pad_20[(0x28 - 0x1C) - 4];
    s32 unk28;
    u8 pad_2C[(0xA0 - 0x28) - 4];
    S_80050E20_target *unkA0;
} S_80050E20_sub;

typedef struct S_80050E20 {
    u8 pad_00[0x1E];
    u16 unk1E;
    u8 pad_20[(0x20 - 0x1E) - 2];
    S_80050E20_sub unk20;
} S_80050E20;

typedef struct {
    s32 val;
    s32 pad[2];
} S_800814A0;

extern void func_8004FE78(s32 a0);
extern void func_8004B248(s32 *a0);
extern s32 D_80080B98;
extern S_800814A0 D_800814A0;

void func_80050E20(S_80050E20 *a0)
{
    S_80050E20_sub *s0 = &a0->unk20;
    s32 global_flags;
    u16 object_flags;

    func_8004FE78(s0->unk28);
    s0->unk28 = 0;
    D_80080B98 = s0->unk1C;
    func_8004B248((s32 *)(((u8 *)a0) + 0x8C));
    s0->unkA0->unk1E |= 0x8000;
    global_flags = D_800814A0.val;
    object_flags = a0->unk1E;
    *(s32 *)0x800814A0 = global_flags | 0x8000;
    a0->unk1E = object_flags | 0x8000;
}
