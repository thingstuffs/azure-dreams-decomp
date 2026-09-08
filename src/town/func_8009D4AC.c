#include "common.h"

extern void func_80094984(void *arg0, void *arg1, s32 arg2);
extern void func_80099754(s32 arg0);

extern u8 D_800834B8[];
extern u8 D_80097D2C[];
extern u8 D_8009ACFC[];
extern u8 D_800D0078[];
extern s32 D_800D0620;

/* Initializes the global object and resets its state pointers and flag. */
void func_8009AC0C(void)
{
    void *object;
    void *object_header;
    s32 init_value;

    object = D_800834B8;
    object_header = (u8 *)object - 0x20;
    init_value = *(s32 *)((u8 *)object_header + 0xC);
    func_80099754(*(s32 *)((u8 *)object_header + 8));
    func_80094984(D_800D0078, object, init_value);
    D_800D0620 = 0;
    *(void **)D_800834B8 = D_80097D2C;
    *(void **)((u8 *)object + 4) = D_8009ACFC;
}
