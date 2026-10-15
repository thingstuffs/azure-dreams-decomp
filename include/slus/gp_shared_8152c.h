#ifndef SLUS_GP_SHARED_8152C_H
#define SLUS_GP_SHARED_8152C_H

/* Present C interface; historical filename and TU boundary remain inferred. */
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

#include "common.h"

/* Regular (>8B) globals accessed via %hi/%lo. */
extern unsigned char D_80016000[0x10];
extern unsigned char D_80023000[0x10];

/* <=8B global -> $gp small-data store (as -G8 sees size<=8 for this symbol
   in this TU, so the store to it is gp-relative). */
extern void *D_8008152C;

extern void *uploadImageTiles(void *a0, unsigned short a1, int a2, int a3, void *a4);

/* Uploads image tiles from fixed global buffers and stores the result in D_8008152C. */

#include "common.h"

/* S_80016000: opaque >8B blob (16 bytes) whose address is passed around by
   this wave's siblings; no fields are dereferenced inside THIS function
   (field accesses happen inside the callees, not decompiled in this wave). */
extern u8 D_80016000[0x10];

/* S_8008152C: <=8B global (gp-relative store in THIS TU) that simply holds
   a pointer value published by the sibling wrappers. */
extern void *D_8008152C;

extern void func_80046F88(void *a0);
extern void func_80047054(void *a0, u16 a1, u16 a2, u16 a3);

/* Advances the effect state, applies a fixed effect, and publishes the state pointer. */

void *func_80047D44(int resource_id);
void func_80047DF0(void);
void advanceEffectState(void);

#endif
