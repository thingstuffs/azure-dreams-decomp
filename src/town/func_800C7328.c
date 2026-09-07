#include "common.h"

typedef struct {
    u8 active;
    u8 unk1;
    u8 variant;
    u8 unk3[5];
} TownSlot;

extern TownSlot D_80082660[];
extern u16 D_800D5070[];
extern void func_800C41D4(void *);

void func_800C4A88(void *arg0)
{
    TownSlot *slot;
    register void *child ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    u8 raw_variant;
    register u8 variant ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    slot = &D_80082660[*(s32 *)((u8 *)arg0 + 0x60)];
    raw_variant = slot->variant;
    slot->active = 0;
    do {
        child = *(void **)((u8 *)arg0 + 0x98);
    } while (0);
    variant = raw_variant & 3;
    if (child != 0) {
        ASM_USE(raw_variant);   /* MATCH pin: load-bearing for the whole function shape */
        *(u8 *)((u8 *)child + 4) = variant;
    }
    *(u16 *)((u8 *)arg0 + 0x6E) = D_800D5070[variant];
    func_800C41D4(arg0);
}

/* MECHANISM: The proven 0x18 frame/CFG holds child in $a3 and raw_variant in $v0.
   Pinning only the masked variant live range to $v1 moves its andi into the branch
   delay slot and reuses $v1 for both the child store and u16 table lookup. */
