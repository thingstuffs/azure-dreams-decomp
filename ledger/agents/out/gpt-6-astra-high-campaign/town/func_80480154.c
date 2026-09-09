#include "common.h"

extern void *D_80016000;
extern s32 D_800189BC[];
extern s32 D_80019548[];
extern void func_80016540(s32, s32);

/* Call func_80016540, then copy the table entry selected by the current index. */
void func_80480154(s32 first_input, s32 second_input)
{
    func_80016540(first_input, second_input);
    D_80019548[0] = D_800189BC[*(s32 *)((u8 *)D_80016000 + 8)];
}
