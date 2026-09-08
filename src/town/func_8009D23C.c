#include "common.h"

extern void func_80035208(void *arg0);
extern void func_80094984(void *arg0, void *arg1, s32 arg2);
extern void func_800988C8(void *arg0, s32 arg1, s32 arg2);
extern void func_80099754(s32 arg0);

extern u8 D_8006CADE[];
extern u8 D_800834B8[];
extern u8 D_800D0078[];

/* Set the block's 12-bit value and apply its header parameters. */
void func_8009A99C(s32 value)
{
    void *block;
    void *header;
    s32 header_param_0c;
    s32 header_param_08;

    block = D_800834B8;
    header = (s8 *)block - 0x20;
    header_param_08 = *(s32 *)((s8 *)header + 8);
    header_param_0c = *(s32 *)((s8 *)header + 0xC);
    func_80099754(header_param_08);
    *(s16 *)((s8 *)block + 0x10) = value & 0xFFF;
    func_80094984(D_800D0078, block, header_param_0c);
    func_800988C8(block, header_param_08, header_param_0c);
    func_80035208(D_8006CADE);
}
