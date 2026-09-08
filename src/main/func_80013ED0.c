#include "common.h"

extern s32 func_8004B4A8(void *arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_80026FB4(void *arg0);
extern void bzero(void *arg0, s32 arg1);
extern void func_80026DF0(void *arg0, s32 arg1);
extern s32 func_80026DC8(void *arg0);
extern void func_80026E90(void *arg0, s32 arg1);

extern u8 D_8002B850[];
extern u8 D_80027DD0[];
extern u8 D_80026AE4[];

/* Creates or resets the shared object and initializes its data and callbacks. */
void *func_80026ED0(s32 init_value, s32 stored_value)
{
    void *object;
    void *data;

    object = D_8002B850;
    data = (u8 *)object + 0x20;
    if (func_8004B4A8(object) == 0) {
        object = func_8003FE78(0, object, 0x45);
        func_8004491C(object, D_80027DD0);
    } else {
        func_80026FB4(object);
        *(u16 *)((u8 *)object + 0x1E) &= 0x7FFF;
        bzero(data, 0xF0);
    }
    func_80026DF0(data, 4);
    *(void **)((u8 *)object + 0xC) = (u8 *)data + 0x50;
    *(s32 *)((u8 *)data + 0x5C) = func_80026DC8((u8 *)data + 0x60);
    *(s32 *)((u8 *)data + 0x24) = stored_value;
    func_80026E90(data, init_value);
    *(void **)((u8 *)object + 0x10) = D_80026AE4;
    return object;
}
