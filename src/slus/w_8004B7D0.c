#include "common.h"

typedef struct { u32 v; } __attribute__((packed)) UA32;

extern void func_8004B634(void);
extern void func_8003F320(void);
extern void func_800253A0(void *a0, void *a1, s32 a2, void *a3);
extern UA32 D_80080B50;

/* Copies the 4-byte D_80080B50 global to a stack local (unaligned-safe block
 * move), runs func_8004B634()/func_8003F320(), then forwards arg0, NULL, 0,
 * and the stack copy to func_800253A0. */
void func_8004B7D0(void *a0)
{
    UA32 local10;
    *(UA32 *)&local10 = *(UA32 *)&D_80080B50;
    func_8004B634();
    func_8003F320();
    func_800253A0(a0, 0, 0, &local10);
}
