#include "common.h"

#include "common.h"

typedef struct {
    u8 pad00[6];
    s16 unk06;
    u8 pad08[0x14 - 0x8];
    u16 unk14;
} Entry80044C54;

extern void RotTransPers(void *a0, void *a1, void *a2, void *a3);
extern void func_80044D24(void *a0, Entry80044C54 *a1, s32 a2);
extern s32 func_80045310(u32 a0);
extern void *D_80083160[3];

s32 func_80044C54(u8 *arg0, void *arg1, Entry80044C54 *arg2)
{
    u8 *pos = arg0;
    void *coord = arg1;
    Entry80044C54 *entry = arg2;
    u8 *scratch = (u8 *)0x1F800000;
    void *next;

    for (;;) {
        if (!(entry->unk14 & 0x80)) {
            *(u16 *)(scratch + 0x70) = *(u16 *)((u8 *)coord + 2);
            *(u16 *)(scratch + 0x72) = *(u16 *)((u8 *)coord + 6);
            *(u16 *)(scratch + 0x74) = *(u16 *)((u8 *)coord + 0xA);
            RotTransPers(scratch + 0x70, scratch, scratch + 0x90, scratch + 0x94);
            func_80044D24(pos, entry, entry->unk06);
            if (func_80045310(*(u32 *)((u8 *)D_80083160[0] + 0x8D0))) {
                return 0;
            }
        }

        next = *(void **)(pos - 8);
        if (next == 0) {
            return 0;
        }
        pos = (u8 *)next + 0x20;
        coord = *(void **)((u8 *)next + 8);
        entry = *(Entry80044C54 **)((u8 *)next + 0xC);
    }
}
