/* Relink of matched dungeon/func_812542E4; every changed retail word is a paired relocation. */
#define D_80174710 D_8016E710
#include "common.h"
#include "shared/record_ptrs.h"

extern void func_8016DA48(void);
extern void func_80099FDC(void *);

extern u8 *D_8016E710;

/* Clear the state flag, run the shared update, and process both occupied object slots. */
void func_8016DAE4(void)
{
    s16 slot;
    void *object;
    u8 *state;

    slot = 0;
    state = D_8016E710 + 0x20;
    *(u16 *)(state + 0x46) &= 0x7FFF;
    func_8016DA48();
    do {
        object = *(void **)(((u8 *)D_800E3D7C) + 0xAC + slot * 4);
        if (object != 0) {
            func_80099FDC((u8 *)object - 0x20);
        }
        slot++;
    } while (slot < 2);
}
