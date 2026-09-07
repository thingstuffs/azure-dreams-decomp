typedef unsigned short u16;

extern u16 D_80019114;

void func_80016B08(void)
{
    D_80019114 = (D_80019114 + 1) & 7;
}
