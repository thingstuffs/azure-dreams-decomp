#include "common.h"

/* Regular (>8B) globals accessed via %hi/%lo. */
extern unsigned char D_80119000[0x10];
extern unsigned char D_80126000[0x10];

/* <=8B global -> $gp small-data STORE, while address-of stays %hi/%lo. */
extern void *D_80081528;

extern void func_800479D4(void *a0, void *a1, unsigned short a2);
extern void func_8003F320(void);
extern void *func_80047AB0(void *a0, unsigned short a1, int a2, int a3, void *a4);

/* Loads image data by resource ID, uploads its tiles, and returns the global object slot. */
void *func_80047E78(int resource_id)
{
    func_800479D4(&D_80119000, &D_80126000, (unsigned short)resource_id);
    func_8003F320();
    D_80081528 = func_80047AB0(&D_80119000, 5, 0x7F80, 0xF, &D_80126000);
    return &D_80081528;
}
