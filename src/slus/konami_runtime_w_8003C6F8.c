#include "common.h"

#include "common.h"

typedef struct {
    void *field_0;
    void *field_4;
} Func8003C6F8Entry;

extern Func8003C6F8Entry D_8006B200[];
extern void *D_80081460;
extern u8 D_80082E6A[];

extern void func_80041284(void *arg0);

void func_8003C6F8(void *arg0, s32 arg1)
{
    Func8003C6F8Entry *entry;
    Func8003C6F8Entry *base;
    void *field_4;

    base = D_8006B200;
    arg1 *= 8;
    entry = (Func8003C6F8Entry *)((u8 *)base + arg1);
    field_4 = entry->field_4;
    entry->field_0 = arg0;
    D_80081460 = arg0;
    *(void **)0x80080A8C = field_4;
    func_80041284(arg0);

    if (D_80082E6A[0] == 2) {
        *(s8 *)0x800DCF4D = -2;
    }
}
