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

/* Decode a packed ID or relative offset, synchronize, and dispatch the resolved values. */
void func_80041284(void *packed_data)
{
    s32 id_or_base;
    s32 target_time;
    register s32 offset_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 id_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    DrawSync(0);
    id_or_base = *(s32 *)packed_data & 0x7FFFFF;
    if (id_or_base == 0) {
        offset_base = D_8008148C.field_0;
        id_or_base = offset_base;
        target_time = id_or_base + ((*(volatile u32 *)packed_data & 0xFF800000) >> 12);
        D_80081480.field_0 = id_or_base;
    } else {
        id_base = D_8008148C.field_0;
        id_or_base = id_or_base | 0x80000000;
        target_time = id_base;
        D_80081480.field_0 = target_time;
    }
    func_8003E4FC(6, packed_data, 0);
    func_8003F320();
    func_80041344(id_or_base, target_time);
}
