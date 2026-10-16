#define func_80173A48 func_80166A48
#define dungeonClearEntryFlagAndLinkOwner func_80098DDC
#define D_800E3D7C D_800E397C
#define D_80174710 D_80167710
/* Relink of matched dungeon/dungeonProcessGlobalEffectSlots at file 0x12742E4; imports and data use paired retail relocations. */
#include "common.h"
#include "shared/record_ptrs.h"

extern void func_80166A48(void);
extern void func_80098DDC(void *);

extern u8 *D_80167710;

/* Clear the state flag, run the shared update, and process both occupied object slots. */
void func_80166AE4(void)
{
    s16 slot;
    void *object;
    u8 *state;

    slot = 0;
    state = D_80167710 + 0x20;
    *(u16 *)(state + 0x46) &= 0x7FFF;
    func_80166A48();
    do {
        object = *(void **)(((u8 *)D_800E397C) + 0xAC + slot * 4);
        if (object != 0) {
            func_80098DDC((u8 *)object - 0x20);
        }
        slot++;
    } while (slot < 2);
}
