typedef signed int s32;

extern s32 D_800FE5C0[6];

void func_80095460(s32 *arg0)
{
    do { D_800FE5C0[3] = arg0[0] - D_800FE5C0[0]; } while (0);
    D_800FE5C0[4] = arg0[1] - D_800FE5C0[1];
    D_800FE5C0[5] = arg0[2] - D_800FE5C0[2];
    D_800FE5C0[0] = arg0[0];
    D_800FE5C0[1] = arg0[1];
    D_800FE5C0[2] = arg0[2];
}
