#include "common.h"
#define F(p,t,o) (*(t)((u8 *)(p)+(o)))
extern s16 D_80083228; extern s32 D_80045340, D_80083498, D_801714B0, D_80174C5C; extern void *D_80174CDC[3];
extern void *func_8003FD64(); extern void func_8004491C(); extern void func_80047784(); extern void func_8009A028(); extern void func_8009A3D0(); extern void func_800A9C18();

/* Create and initialize an object at the supplied coordinates and store it globally. */
void func_80171594(u8 x, u8 y, s32 z) {
    register s32 saved_z ASM_REG("$16") = z;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 saved_x ASM_REG("$20") = x;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u8 saved_y ASM_REG("$21") = y;   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *object, *state ASM_REG("$19"), *position ASM_REG("$17"), *sprite ASM_REG("$16");
    s32 tile_mask;
    u8 tile_x, tile_y;
    register void *call_object ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */

    ASM_KEEP4_NV(saved_z, saved_x, saved_y, saved_z);   /* MATCH pin: retail schedule: same instructions, different order without it */
    object = func_8003FD64(0x112, &D_80083498);
    call_object = object;
    if (object != 0) {
        register s32 z_offset ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

        state = object + 0x20;
        F(state, s8*, 0x13) = 0x15;
        F(object, s32**, 0x10) = &D_801714B0;
        func_8004491C(call_object, &D_80045340);
        call_object = object;
        z_offset = saved_z - 0x18;
        position = F(object, void**, 8);
        F(position, s16*, 0xA) = z_offset;
        sprite = F(object, void**, 0xC);
        F(sprite, s32**, 0x2C) = &D_80174C5C;
        F(sprite, u8*, 0x24) = saved_x;
        F(sprite, u8*, 0x25) = saved_y;
        F(sprite, s16*, 6) = -4;
        func_800A9C18(call_object, position, sprite, 0);
        F(state, s16*, 0x2A) = 0x200;
        func_80047784(sprite, ((u8 *)F(sprite, s32**, 0x2C))[((D_80083228 + 0x300) >> 9) & 7], 0);
        F(sprite, s16*, 0x1E) = 0x1800;
        F(sprite, s16*, 0x1C) = 0x1800;
        F(position, u16*, 2) -= 0x10;
        F(position, u16*, 6) -= 0x10;
        tile_x = F(sprite, u8*, 0x24);
        tile_y = F(sprite, u8*, 0x25);
        tile_mask = 0x3000;
        if (F(state, s32*, 0x1C) & 0x2000)
            tile_mask = 0x300;
        func_8009A3D0(tile_x, tile_y, tile_mask);
        func_8009A028(state);
        D_80174CDC[0] = object;
        F(object, s32**, 0x10) = (s32 *)((s32)F(object, s32**, 0x10) | 0x80000000);
    }
}
