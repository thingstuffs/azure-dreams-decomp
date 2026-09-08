#include "common.h"

/* S_80081480 / S_8008148C: >8B structs forced to hi/lo addressing (only
 * field_0 @ offset 0 accessed here); matches the layout used in the
 * already-matched siblings func_80041AB0 / func_80043CD0. */
struct S_80081480_80041284 { s32 field_0; s8 pad[8]; };
struct S_8008148C_80041284 { s32 field_0; s8 pad[8]; };

extern struct S_80081480_80041284 D_80081480;
extern struct S_8008148C_80041284 D_8008148C;

extern void DrawSync(int a0);
extern s32 func_8003E4FC(s32 a0, void *a1, s32 a2);
extern void func_8003F320(void);
extern void func_80041344(s32 a0, s32 a1);

/* Reads a packed word from *a0: bits [22:0] are an id, bit 31 is a "valid"
 * flag, and bits [30:23] are an offset. If the id field is nonzero, this is
 * treated as an explicit id (ORed with 0x80000000) and the base time is taken
 * directly from D_8008148C.field_0. Otherwise the base time is D_8008148C's
 * field_0 plus the offset field (shifted down). Either way the computed base
 * time is stashed into D_80081480.field_0, then the callback is registered
 * (func_8003E4FC), synced (func_8003F320), and func_80041344 is invoked with
 * the id/base-time pair. */
void func_80041284(void *a0)
{
    s32 s0;
    s32 s1;
    register s32 t0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 t1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    DrawSync(0);
    s0 = *(s32 *)a0 & 0x7FFFFF;
    if (s0 == 0) {
        t0 = D_8008148C.field_0;
        s0 = t0;
        s1 = s0 + ((*(volatile u32 *)a0 & 0xFF800000) >> 12);
        D_80081480.field_0 = s0;
    } else {
        t1 = D_8008148C.field_0;
        s0 = s0 | 0x80000000;
        s1 = t1;
        D_80081480.field_0 = s1;
    }
    func_8003E4FC(6, a0, 0);
    func_8003F320();
    func_80041344(s0, s1);
}
