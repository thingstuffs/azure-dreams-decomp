typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef int s32;

extern void *func_8003FC64(s32 size);
extern void func_8004491C(void *object, void *data);
extern s16 D_80080B04;
extern void *D_80081508;
extern s32 D_800D1824;

void func_800D1648(void)
{
    void *object;

    object = func_8003FC64(0);
    func_8004491C(object, &D_800D1824);
    do {
        D_80081508 = ((u8 *)object) + 0x20;
        *((s8 *)(((u8 *)object) + 0x20)) = 0;
        D_80080B04 = 0;
    } while (0);
}
