#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

extern void func_8009FAC4(void);
extern void func_8016ECFC(void);
extern void func_80099FDC(void *);

extern s32 D_80083460;
extern u16 D_80013714[];
extern s32 D_80175D50;
extern s32 D_800E3D7C;

void func_8016ED98(void)
{
    s32 i;
    s32 value;
    void *object;
    u8 *state;

    object = (void *)(D_80175D50 + 0x20);
    state = (u8 *)&D_80083460;
    FIELD(state, u16, 0xA) = FIELD(state, u16, 0xA) - 1;
    FIELD(object, u16, 0x46) &= 0x7FFF;
    D_80013714[0] &= 0xFFF6;
    func_8009FAC4();
    func_8016ECFC();
    i = 0;
    do {
        value = FIELD(D_800E3D7C + i * 4, s32, 0xAC);
        if (value != 0) {
            func_80099FDC((void *)(value - 0x20));
        }
        i++;
    } while (i < 2);
}
