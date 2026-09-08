#include "common.h"

typedef struct {
    s32 words[10];
} Data40;

extern Data40 D_800170FC;
extern u8 D_8001632C[];
extern void func_80018FC8(Data40 *, u8 *, s32, s32);

/* Pass a local copy of the global data and the shared byte table to func_80018FC8. */
void func_804762B8(s32 first_value, s32 unused, s32 second_value)
{
    Data40 data_copy;

    data_copy = D_800170FC;
    func_80018FC8(&data_copy, D_8001632C, first_value, second_value);
}
