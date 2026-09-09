#include "common.h"

typedef struct {
    u8 bytes[0x20];
} __attribute__((packed)) Copy32;

extern void Control_CD(s32, void *, s32);
extern void func_8003F320(void);
extern void func_8003F6D4(s32, void *, s32 *, s32);

extern u8 D_8001F584;
extern u8 *D_80083478;
extern Copy32 D_800DDC9C;
extern Copy32 D_8014A000;

/* Loads an indexed resource and copies two 32-byte blocks and a trailing byte to globals. */
void func_800194C4(s16 resource_index)
{
    s32 load_result;
    u8 *resource_data;

    resource_data = (u8 *)&D_8014A000;
    func_8003F6D4(1, resource_data, &load_result, resource_index + 0x3F5E);
    Control_CD(6, &load_result, 0);
    func_8003F320();
    *(Copy32 *)D_80083478 = D_8014A000;
    D_800DDC9C = *(Copy32 *)(resource_data + 0x20);
    D_8001F584 = resource_data[0x40];
}

/* MECHANISM: Packed 32-byte assignments express both retail unaligned copies.
   Mixing one direct D_8014A000 copy with a held full-address local creates the retail
   s1 high-page and s0 full-address roles, 0x28 frame, and 3+3+2 copy-register chunks. */
