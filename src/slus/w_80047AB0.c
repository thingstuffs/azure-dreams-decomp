#include "common.h"

extern int func_8004713C(s32 a0, u16 a1, s32 a2);
extern int func_80047AA4(int a0);
extern int func_8003F80C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void DrawSync(s32 a0);
extern int func_80047200(s32 a0, s32 a1, s32 a2);
extern int func_80046F88(void *a0);
extern int func_80047054(void *a0, u16 a1, u16 a2, u16 a3);

/* Uploads image tiles and palettes, updates the object's texture references, and returns the object. */
void *uploadImageTiles(void *object, u16 texture_page, s32 clut_id, s32 alternate_page, s32 image_addr)
{
    s32 palette_addr;

    func_8004713C(image_addr, texture_page, 4);
    palette_addr = func_80047AA4(image_addr);
    func_8003F80C(palette_addr, clut_id, 0x10, 2);
    DrawSync(0);
    func_80047200(palette_addr, 0x10, 0);
    func_8003F80C(palette_addr, clut_id - 0x80, 0x10, 2);
    func_80046F88(object);
    func_80047054(object, texture_page, clut_id, alternate_page);
    return object;
}
