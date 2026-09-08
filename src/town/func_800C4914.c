#include "common.h"

typedef struct CallbackEntry CallbackEntry;
typedef void (*Callback)(CallbackEntry *);

struct CallbackEntry {
    Callback callback;
    u8 pad[20];
};

extern s32 func_8009CFE0(void);
extern s32 D_800814A0[3];
extern CallbackEntry D_800D4710[];

void func_800C2074(void *arg0)
{
    CallbackEntry *entry = D_800D4710;
    u8 *byte;

    if (func_8009CFE0() != 0) {
        byte = *(u8 **)((u8 *)arg0 + 0x98);
        if (byte != 0) {
            *byte = 0;
        }
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    while (entry->callback != 0) {
        entry->callback(entry);
        entry++;
    }
}
