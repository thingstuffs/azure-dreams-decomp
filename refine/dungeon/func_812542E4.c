#include "common.h"

extern void func_80173A48(void);
extern void func_80099FDC(void *);

extern u8 *D_80174710;
extern u8 *D_800E3D7C;

/* Clear the state flag, run the shared update, and process both occupied object slots. */
void func_812542E4(void)
{
    s16 slot;
    void *object;
    u8 *state;

    slot = 0;
    state = D_80174710 + 0x20;
    *(u16 *)(state + 0x46) &= 0x7FFF;
    func_80173A48();
    do {
        object = *(void **)(D_800E3D7C + 0xAC + slot * 4);
        if (object != 0) {
            func_80099FDC((u8 *)object - 0x20);
        }
        slot++;
    } while (slot < 2);
}
