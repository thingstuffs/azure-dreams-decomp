#include "common.h"

#include "common.h"

typedef s32 (*Callback)(void *, s32, s32);

typedef struct Entry {
    u8 pad0[8];
    s32 arg1;
    s32 arg2;
    u8 pad10[0xE];
    u16 flags;
    u8 data[1];
} Entry;

extern s32 func_80045310(s32);
extern Entry *D_80083160[];
extern Callback D_80083360[0x20];
extern Entry *D_800833E0[0x20];

void func_800402F4(void)
{
    Callback *callback;
    Callback fn;
    register s32 i ASM_REG("$18");
    Entry **entryp;
    Entry *entry;
    s32 result;

    i = 0;
    callback = D_80083360;
    entryp = D_800833E0;
    ASM_KEEP(i);
loop:
    fn = *callback;
    if (fn != 0) {
        entry = *entryp;
        if (entry != 0) {
            if (!(entry->flags & 0x800)) {
                fn(entry->data, entry->arg1, entry->arg2);
                result = func_80045310(*(s32 *)((u8 *)D_80083160[0] + 0x8D0));
                ASM_KEEP(result);
                callback++;
                if (result == 0) {
                    i++;
                    goto next;
                }
                goto done;
            }
        } else {
            *callback = 0;
        }
    }
    callback++;
    i++;
next:
    entryp++;
    if (i < 0x20) {
        goto loop;
    }
done:
    return;
}
