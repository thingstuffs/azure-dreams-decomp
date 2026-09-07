#include "common.h"

typedef struct {
    u8 bytes[0x20];
} __attribute__((packed)) Copy32;

extern void func_8003E4FC(s32, void *, s32);
extern void func_8003F320(void);
extern void func_8003F6D4(s32, void *, s32 *, s32);

extern u8 D_8001F584;
extern u8 *D_80083478;
extern Copy32 D_800DDC9C;
extern Copy32 D_8014A000;

void func_800194C4(s16 arg0)
{
    s32 local;
    u8 *src;

    src = (u8 *)&D_8014A000;
    func_8003F6D4(1, src, &local, arg0 + 0x3F5E);
    func_8003E4FC(6, &local, 0);
    func_8003F320();
    *(Copy32 *)D_80083478 = D_8014A000;
    D_800DDC9C = *(Copy32 *)(src + 0x20);
    D_8001F584 = src[0x40];
}

/* MECHANISM: Packed 32-byte assignments express both retail unaligned copies.
   Mixing one direct D_8014A000 copy with a held full-address local creates the retail
   s1 high-page and s0 full-address roles, 0x28 frame, and 3+3+2 copy-register chunks. */
