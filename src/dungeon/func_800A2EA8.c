#include "common.h"
#ifndef NULL
#define NULL 0
#endif
#define F(e,t,o) (*(t)((s8 *)(e)+(o)))
extern u8 D_80045340[];
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A7A38(void *);
extern void func_800BC26C(void *, s32, s32, s32);

/* Create a sprite object with the supplied position and default color and scale. */
void *func_800A8608(s32 parent, s32 sprite_source, s16 x, s32 y, volatile s32 z) {
    s32 z_value = z;
    void *object;
    void *sprite;
    void *position;

    object = func_8003FD64(0x12, (void *)parent);
    if (object != NULL) {
        position = F(object, void **, 8);
        sprite = F(object, void **, 0xC);
        F(position, s16 *, 2) = x;
        F(position, s16 *, 6) = y;
        F(position, s16 *, 0xA) = (s16)z_value;
        func_8004491C(object, D_80045340);
        F(sprite, u8 *, 0xE) = 0x80;
        F(sprite, u8 *, 0xD) = 0x80;
        F(sprite, u8 *, 0xC) = 0x80;
        F(sprite, s16 *, 0x1E) = 0x1000;
        F(sprite, s16 *, 0x1C) = 0x1000;
        F(sprite, s32 *, 8) = func_800A7A38((void *)sprite_source);
        func_800BC26C(object, 0, 0, 0);
    }
    return object;
}
