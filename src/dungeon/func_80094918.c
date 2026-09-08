#include "common.h"

extern void *D_800E3D7C;
extern s32 D_800E296C;

extern void func_8009A028(void *arg0);

/* Mark and process entries without flag 0x4000, then set the global update flag. */
void func_8009A078(void)
{
    void *entry;
    void *node;
    void *next_entry;

    entry = D_800E3D7C;
    do {
        node = *(void **)((u8 *)entry + 0x5C);
        next_entry = (u8 *)node + 0x20;
        if (!(*(s32 *)((u8 *)entry + 0x14) & 0x4000)) {
            node = (u8 *)entry - 0x20;
            *(u16 *)((u8 *)node + 0x1E) = (u16)(*(u16 *)((u8 *)node + 0x1E) | 0x1000);
            func_8009A028(entry);
        }
        entry = next_entry;
    } while (entry != D_800E3D7C);

    D_800E296C = D_800E296C | 0x10000000;
}
