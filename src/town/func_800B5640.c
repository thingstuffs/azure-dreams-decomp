typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern void func_800B2D00(s32 a0, void *a1, s32 a2);

void func_800B2DA0(s32 arg0, void **arg1) {
    void *temp_a1;

    temp_a1 = *arg1;
    func_800B2D00(arg0, (u8 *)temp_a1 + 0x1C, *(s32 *)((u8 *)temp_a1 + 0x3C));
}
