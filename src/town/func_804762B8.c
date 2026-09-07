#include "common.h"

typedef struct {
    s32 words[10];
} Data40;

extern Data40 D_800170FC;
extern u8 D_8001632C[];
extern void func_80018FC8(Data40 *, u8 *, s32, s32);

void func_804762B8(s32 arg0, s32 arg1, s32 arg2)
{
    Data40 data;

    data = D_800170FC;
    func_80018FC8(&data, D_8001632C, arg0, arg2);
}
