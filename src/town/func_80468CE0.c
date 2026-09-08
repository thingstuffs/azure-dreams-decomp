typedef signed char s8;
typedef short s16;
typedef int s32;

typedef void (*Callback)();

extern void *D_80016000;

/* Invoke the callback and add two signed deltas to the current stats. */
void func_80019CE0(void *stat_deltas)
{
    void *first_stats;
    void *second_stats;

    (*(Callback *)((s8 *)*(void **)((s8 *)D_80016000 + 0x20) + 0x258))(1);

    first_stats = *(void **)((s8 *)D_80016000 + 0x1C);
    *(s32 *)((s8 *)first_stats + 4) += *(s16 *)((s8 *)stat_deltas + 0);
    second_stats = *(void **)((s8 *)D_80016000 + 0x1C);
    *(s32 *)((s8 *)second_stats + 8) += *(s16 *)((s8 *)stat_deltas + 2);
}
