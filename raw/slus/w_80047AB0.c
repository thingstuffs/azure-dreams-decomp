#include "common.h"

extern int func_8004713C(s32 a0, u16 a1, s32 a2);
extern int func_80047AA4(int a0);
extern int func_8003F80C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void DrawSync(s32 a0);
extern int func_80047200(s32 a0, s32 a1, s32 a2);
extern int func_80046F88(void *a0);
extern int func_80047054(void *a0, u16 a1, u16 a2, u16 a3);

/* Streams N image tiles (func_8004713C) into a scratch VRAM buffer
 * (func_80047AA4(a4) = a4+0x8000), DMAs/draws it twice (func_8003F80C /
 * func_80047200), then finalises the target object (func_80046F88 /
 * func_80047054) before returning the object pointer unchanged. */
void *uploadImageTiles(void *a0, u16 a1, s32 a2, s32 a3, s32 a4)
{
    s32 addr;

    func_8004713C(a4, a1, 4);
    addr = func_80047AA4(a4);
    func_8003F80C(addr, a2, 0x10, 2);
    DrawSync(0);
    func_80047200(addr, 0x10, 0);
    func_8003F80C(addr, a2 - 0x80, 0x10, 2);
    func_80046F88(a0);
    func_80047054(a0, a1, a2, a3);
    return a0;
}
