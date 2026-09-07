typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct {
    s32 values[3];
} ValueTable;

typedef s32 (*Callback)(u32);

extern void *D_80016000[];
extern ValueTable D_80019158;

s32 func_80468280(void)
{
    ValueTable table = D_80019158;
    void *callbacks = *(void **)((u8 *)D_80016000[0] + 0x20);
    Callback callback = *(Callback *)((u8 *)callbacks + 0x2D4);

    return table.values[callback(0)];
}
