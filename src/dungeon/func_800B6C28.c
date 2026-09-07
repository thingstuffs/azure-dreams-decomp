typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

extern s32 D_800814A0[4];

void func_800BC388(void *arg0)
{
    void *ptr = *(void **)arg0;
    if ((*(u16 *)((u8 *)ptr + 0x1E) & 0x8000) || (*(*(s32 **)((u8 *)arg0 + 4)) == 0))
    {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
