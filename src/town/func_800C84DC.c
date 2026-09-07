typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 D_80083780[];
extern s32 D_800D0428[];

void func_800C5C3C(s32 arg0, void *arg1) {
    *(s32 *)arg1 = D_80083780[0];
    *(s32 *)((u8 *)arg1 + 4) = D_80083780[1];
    *(s32 *)((u8 *)arg1 + 8) = D_80083780[2] + D_800D0428[0];
}
