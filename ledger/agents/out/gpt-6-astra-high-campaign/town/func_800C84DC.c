typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 D_80083780[];
extern s32 D_800D0428[];

/* Copy the global position to the output with an offset on the third component. */
void func_800C5C3C(s32 unused, void *position_out) {
    *(s32 *)position_out = D_80083780[0];
    *(s32 *)((u8 *)position_out + 4) = D_80083780[1];
    *(s32 *)((u8 *)position_out + 8) = D_80083780[2] + D_800D0428[0];
}
