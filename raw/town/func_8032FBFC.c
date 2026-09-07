#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*TownCallback)(void *, u8, s32);

extern void *D_80016000;
extern s32 D_8001C370;
extern s32 D_8001C374;

void func_8001A3FC(void) {
    s32 *entryBase;
    void *entry;
    u8 type;
    s32 index;
    s32 offset;

    do {
        entryBase = &D_8001C370;
    } while (0);
    index = FIELD(D_80016000, s32, 0x14);
    offset = index * 0x1C;
    ASM_SCHED_BARRIER();
    entry = (void *)(offset + *entryBase);
    do {
        type = FIELD(entry, volatile u8, 0);
    } while (0);
    D_8001C374 = FIELD(D_80016000, volatile s32, 0);
    FIELD((FIELD(entry, volatile u8, 0) * 0x10) +
              FIELD(entry, s32, 0x10),
          TownCallback, 4)(entry, type,
                           FIELD(D_80016000, volatile s32, 0));
}
