typedef signed char s8;
typedef short s16;
typedef int s32;

typedef void (*Callback)();

extern void *D_80016000;

void func_80019CE0(void *arg0)
{
    void *stats0;
    void *stats1;

    (*(Callback *)((s8 *)*(void **)((s8 *)D_80016000 + 0x20) + 0x258))(1);

    stats0 = *(void **)((s8 *)D_80016000 + 0x1C);
    *(s32 *)((s8 *)stats0 + 4) += *(s16 *)((s8 *)arg0 + 0);
    stats1 = *(void **)((s8 *)D_80016000 + 0x1C);
    *(s32 *)((s8 *)stats1 + 8) += *(s16 *)((s8 *)arg0 + 2);
}
