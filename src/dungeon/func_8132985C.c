#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"

extern s32 D_80174CD8[3];

extern void func_8009FAC4(void);
extern void func_80173ED0(void);
extern void func_80099FDC(void *);

/* Dungeon teardown: clear the on-screen/status flag bits, run both shutdown hooks, and release the two objects held in the actor table. */
void func_8017105C(void) {
    s32 i;
    void *object;
    u8 *ptr;
    u16 *flags = ((u16 *)&D_80013714);

    ptr = (u8 *)(D_80174CD8[0] + 0x20);
    *(u16 *)(ptr + 0x46) &= 0x7FFF;
    D_800E296C &= 0xF7FFFFFF;
    flags[0] &= 0xFFF6;
    func_8009FAC4();
    func_80173ED0();

    i = 0;
    do {
        object = *(void **)(((u8 *)D_800E3D7C) + 0xAC + i * 4);
        if (object != 0) {
            func_80099FDC((u8 *)object - 0x20);
        }
        i++;
    } while (i < 2);
}
