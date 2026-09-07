#include "common.h"

#include "common.h"

typedef struct {
    u8 unk_00[0x0C];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F[0x0D];
    u16 unk_1C;
} Func8003C520Data;

extern void func_80033D08(void *arg0);
extern u32 D_800814A0;

void func_8003C520(void *arg0, void *arg1, Func8003C520Data *arg2) {
    s32 value_e = arg2->unk_0E;
    s32 value_1c = arg2->unk_1C;

    value_e -= 0x10;
    value_1c -= 0x200;
    arg2->unk_1C = value_1c;
    if (value_e < 0) {
        value_e = 0;
    }

    arg2->unk_0E = value_e;
    arg2->unk_0D = value_e;
    arg2->unk_0C = value_e;
    if (*(s16 *)&arg2->unk_1C > 0) {
        return;
    }

    func_80033D08(arg0);
    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
    D_800814A0 |= 0x8000;
}
