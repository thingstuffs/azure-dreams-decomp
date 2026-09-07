typedef unsigned char u8;
typedef int s32;

extern s32 D_80018014[];
extern u8 *D_8001E950;

s32 func_8001B374(void)
{
    return D_80018014[D_8001E950[3]];
}
