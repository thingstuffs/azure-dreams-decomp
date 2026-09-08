typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 D_800834B8;
extern void func_80094984(s32 a0, void *a1, s32 a2);

/* Calls func_80094984 with the input value and global context. */
void func_80093CEC(s32 value) {
    s32 *context = &D_800834B8;
    func_80094984(value, context, *(s32 *)((u8 *)context - 0x14));
}
