#include "common.h"

/* Regular (>8B) globals accessed via %hi/%lo. */
extern unsigned char D_80016000[0x10];
extern unsigned char D_80023000[0x10];

/* <=8B global -> $gp small-data STORE, but its address-of must stay %hi/%lo. */
extern void *D_8008152C;

extern void func_800479D4(void *a0, void *a1, unsigned short a2);
extern void func_8003F320(void);
extern void *func_80047AB0(void *a0, unsigned short a1, int a2, int a3, void *a4);

/* Loads image data by resource ID, uploads its tiles, and returns the global object slot. */
void *func_80047D44(int resource_id)
{
    func_800479D4(&D_80016000, &D_80023000, (unsigned short)resource_id);
    func_8003F320();
    D_8008152C = func_80047AB0(&D_80016000, 0xB, 0x7900, 0xD, &D_80023000);
    return &D_8008152C;
}
