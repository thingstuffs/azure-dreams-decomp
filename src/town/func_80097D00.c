typedef signed int s32;

extern s32 D_800FE5C0[6];

// Store the new three-component value and its difference from the previous value.
void func_80095460(s32 *newValue)
{
    D_800FE5C0[3] = newValue[0] - D_800FE5C0[0];
    D_800FE5C0[4] = newValue[1] - D_800FE5C0[1];
    D_800FE5C0[5] = newValue[2] - D_800FE5C0[2];
    D_800FE5C0[0] = newValue[0];
    D_800FE5C0[1] = newValue[1];
    D_800FE5C0[2] = newValue[2];
}
