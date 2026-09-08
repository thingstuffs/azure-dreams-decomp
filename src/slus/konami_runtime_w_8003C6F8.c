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

/* Stores data in the selected entry, activates its pointers, and applies a mode-specific flag. */
void func_8003C6F8(void *data, s32 entry_index)
{
    Func8003C6F8Entry *entry;
    Func8003C6F8Entry *entries;
    void *paired_data;

    entries = D_8006B200;
    entry_index *= 8;
    entry = (Func8003C6F8Entry *)((u8 *)entries + entry_index);
    paired_data = entry->field_4;
    entry->field_0 = data;
    D_80081460 = data;
    *(void **)0x80080A8C = paired_data;
    func_80041284(data);

    if (D_80082E6A[0] == 2) {
        *(s8 *)0x800DCF4D = -2;
    }
}
