typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct {
    s32 values[3];
} ValueTable;

typedef s32 (*Callback)(u32);

extern void *D_80016000[];
extern ValueTable D_80019158;

// Returns the table value selected by the callback invoked with zero.
s32 func_80468280(void)
{
    ValueTable valueTable = D_80019158;
    void *callbackTable = *(void **)((u8 *)D_80016000[0] + 0x20);
    Callback getValueIndex = *(Callback *)((u8 *)callbackTable + 0x2D4);

    return valueTable.values[getValueIndex(0)];
}
