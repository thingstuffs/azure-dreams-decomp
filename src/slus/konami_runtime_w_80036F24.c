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

/* Updates three data tables and selects an output value and flashing intensity. */
void func_80036F24(FuncInput *input, s32 unused, FuncOutput *output) {
    u8 flags;
    u32 *data;

    if (func_80037534(input) != 0) {
        return;
    }

    func_80036C7C(input->data + 3, D_8006A958, D_80082B50);
    func_80036C7C(input->data + 3, D_8006A964, D_80082B60);
    func_80036C7C(input->data + 3, D_8006A970, D_80082B70);

    data = input->data;
    flags = ((u8 *)data + input->data_index)[0x4C];
    if ((flags & 0x80) != 0) {
        input->frame++;
        if ((input->frame & 1) != 0) {
            output->value_0c = 0xC0C0C0;
        } else {
            output->value_0c = 0;
        }
    } else {
        output->value_0c = 0xC0C0C0;
    }

    output->value_08 = D_8006A97C[(flags & 0x7F) + input->table_offset];
}
