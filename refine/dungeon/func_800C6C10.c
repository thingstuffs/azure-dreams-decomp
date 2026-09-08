#include "common.h"

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern s16 D_8006CCD8[], D_8006CCE8[];
extern s32 func_8009B390();
extern void func_8009CE1C();
extern s16 func_800B500C();
extern s16 func_800A70E4();
extern void func_800CCC20();
extern u8 D_800E3648[], D_800E3548[];
extern u8 *D_800E3D7C[];
extern u32 D_800814A0[3];

/* Advance the effect, process collisions, and mark it finished when its steps run out. */
void func_800CC370(void *effect)
{
    s32 target;
    s16 entry_index;

    U16(effect, 0) += D_8006CCD8[U8(effect, 6)];
    U16(effect, 2) += D_8006CCE8[U8(effect, 6)];
    target = func_8009B390(U16(effect, 0), U16(effect, 2), S16(effect, 4));
    if (target) {
        func_8009CE1C(target, 6, U8(D_800E3D7C[0], 0x11), 9,
                      (s16)(U8(effect, 6) << 9), 0, 3);
    }
    entry_index = func_800B500C(S16(effect, 0), S16(effect, 2), S16(effect, 4));
    if (entry_index >= 0) {
        if (D_800E3648[entry_index * 4] == 7) {
            func_800CCC20(0, entry_index);
        } else {
            U32(D_800E3648, entry_index * 4) = 0;
        }
    }
    entry_index = func_800A70E4(S16(effect, 0), S16(effect, 2), S16(effect, 4));
    if (entry_index >= 0) {
        U32(D_800E3548, entry_index * 4) = 0;
    }
    U8(effect, 7)--;
    if (!U8(effect, 7)) {
        U16(effect, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
