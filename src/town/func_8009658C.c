typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 D_800834B8;
extern void func_80094984(s32 a0, void *a1, s32 a2);

void func_80093CEC(s32 arg0) {
    s32 *p = &D_800834B8;
    func_80094984(arg0, p, *(s32 *)((u8 *)p - 0x14));
}
