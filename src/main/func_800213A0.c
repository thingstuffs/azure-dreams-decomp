#include "common.h"

typedef struct { u8 pad[0x10]; void *callback; u8 pad14[0x2C]; void *first, *second; } Owner;
extern s32 initCardBackgroundObject(s32, s32);
extern void *initCardSlotObject(s32);
extern void func_80400948(void);
extern u8 D_804081AC[];
void func_804083A0(u8 *work) {
    Owner *owner = (Owner *)(work - 0x20);
    *(s32 *)(work + 0x20) = initCardBackgroundObject((s32)owner, (s32)(work + 0xC));
    *(void **)(work + 0x24) = initCardSlotObject((s32)owner);
    func_80400948();
    owner->callback = D_804081AC;
}
