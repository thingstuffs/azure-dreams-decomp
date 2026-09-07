#include "common.h"

typedef struct {
    u8 pad_00[0x44];
    u32 *data;
    u8 enabled;
    s16 data_index;
    u8 pad_4c[0x18];
    volatile u16 frame;
    s16 table_offset;
} FuncInput;

typedef struct {
    u8 pad_00[8];
    u32 value_08;
    u32 value_0c;
} FuncOutput;

extern s32 func_80037534(FuncInput *arg0);
extern void func_80036C7C(u32 *arg0, u32 *arg1, void *arg2);

extern u32 D_8006A958[3];
extern u32 D_8006A964[3];
extern u32 D_8006A970[3];
extern u32 D_8006A97C[128];
extern u32 D_80082B50[6];
extern u32 D_80082B60[6];
extern u32 D_80082B70[6];

void func_80036F24(FuncInput *arg0, s32 arg1, FuncOutput *arg2) {
    u8 flags;
    u32 *data;

    if (func_80037534(arg0) != 0) {
        return;
    }

    func_80036C7C(arg0->data + 3, D_8006A958, D_80082B50);
    func_80036C7C(arg0->data + 3, D_8006A964, D_80082B60);
    func_80036C7C(arg0->data + 3, D_8006A970, D_80082B70);

    data = arg0->data;
    flags = ((u8 *)data + arg0->data_index)[0x4C];
    if ((flags & 0x80) != 0) {
        arg0->frame++;
        if ((arg0->frame & 1) != 0) {
            arg2->value_0c = 0xC0C0C0;
        } else {
            arg2->value_0c = 0;
        }
    } else {
        arg2->value_0c = 0xC0C0C0;
    }

    arg2->value_08 = D_8006A97C[(flags & 0x7F) + arg0->table_offset];
}
