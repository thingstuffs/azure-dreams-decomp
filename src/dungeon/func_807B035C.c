#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} DungeonState;

extern void *D_800FBE1C;
extern s8 D_800DCF4D;
extern DungeonState D_80083460;
extern u16 D_80013714;

void func_807B035C(void) {
    *((s8 *)D_800FBE1C + 0xD8) = 1;
    D_800DCF4D = -1;
    D_80083460.fieldA++;
    D_80013714 |= 8;
}
