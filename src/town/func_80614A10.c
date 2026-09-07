typedef signed char s8;
typedef int s32;

typedef s32 Callback(s32);

extern void *D_80016000;

void func_80614A10(void)
{
    void *temp_a0;
    void *temp_v1;
    void *temp_v1_2;

    (*(Callback **)((s8 *)*(void **)((s8 *)D_80016000 + 0x20) + 0x244))(0);
    *(s32 *)((s8 *)*(void **)((s8 *)D_80016000 + 0x1C) + 0x38) = 0;
    temp_v1 = *(void **)((s8 *)D_80016000 + 0x1C);
    if (*(s32 *)temp_v1 == 0) {
        *(s32 *)((s8 *)temp_v1 + 0x38) = 1;
    }
    temp_v1_2 = *(void **)((s8 *)D_80016000 + 0x1C);
    if (*(s32 *)temp_v1_2 == 2) {
        *(s32 *)((s8 *)temp_v1_2 + 0x38) = 3;
    }
    temp_a0 = *(void **)((s8 *)D_80016000 + 0x1C);
    if (*(s32 *)temp_a0 == 1) {
        *(s32 *)((s8 *)temp_a0 + 0x38) = 2;
    }
}
