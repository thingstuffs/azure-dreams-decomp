#include "common.h"

#include "common.h"

typedef struct {
    u8 unk00[0x44];
    u8 *base;
    u8 unk48[2];
    s16 index;
    u8 unk4c[0x18];
    volatile u16 counter;
    s16 table_index;
} Func37090Input;

typedef struct {
    u8 unk00[8];
    u32 table_value;
    u32 color;
} Func37090Output;

extern s32 func_80037534(Func37090Input *, void *, Func37090Output *);
extern void func_80036C7C(u8 *, u8 *, u8 *);

extern u32 D_8006A958[3];
extern u32 D_8006A964[3];
extern u32 D_8006A970[3];
extern u32 D_8006A97C[32];
extern u8 D_80082B50[16];
extern u8 D_80082B60[16];
extern u8 D_80082B70[16];

void func_80037090(Func37090Input *arg0, void *arg1, Func37090Output *arg2) {
    u8 value;

    if (func_80037534(arg0, arg1, arg2) != 0) {
        return;
    }

    func_80036C7C(arg0->base + 0xC, (u8 *)D_8006A958, D_80082B50);
    func_80036C7C(arg0->base + 0xC, (u8 *)D_8006A964, D_80082B60);
    func_80036C7C(arg0->base + 0xC, (u8 *)D_8006A970, D_80082B70);

    {
        u8 *base = arg0->base + 0x4C;
        s16 index = arg0->index;

        value = base[index];
    }
    if (value & 0x80) {
        arg0->counter++;
        if (arg0->counter & 1) {
            arg2->color = 0xC0C0C0;
        } else {
            arg2->color = 0;
        }
    } else {
        arg2->color = 0;
    }

    arg2->table_value = D_8006A97C[((value & 0x7F) + arg0->table_index)];
}
