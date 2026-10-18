#include "common.h"
#include "shared/slus_callbacks.h"
#ifndef NULL
#define NULL 0
#endif
#define F(e,t,o) (*(t)((s8 *)(e)+(o)))
extern void * func_8003FD64(s32 flags, void **list_head);
extern s32 func_8004491C(void *entry, s32 registration_id);
extern s32 get_item_category_value(u8 *item);
extern void create_tracked_effect(void *, s32, s32, s32);

/* Create a sprite object with the supplied position and default color and scale. */
void *create_item_render_object(s32 parent, s32 sprite_source, s16 x, s32 y, s16 z) {
    void *object;
    void *sprite;
    void *position;

    object = func_8003FD64(0x12, (void *)parent);
    if (object != NULL) {
        position = F(object, void **, 8);
        sprite = F(object, void **, 0xC);
        F(position, s16 *, 2) = x;
        F(position, s16 *, 6) = y;
        F(position, s16 *, 0xA) = z;
        func_8004491C(object, func_80045340);
        F(sprite, u8 *, 0xE) = 0x80;
        F(sprite, u8 *, 0xD) = 0x80;
        F(sprite, u8 *, 0xC) = 0x80;
        F(sprite, s16 *, 0x1E) = 0x1000;
        F(sprite, s16 *, 0x1C) = 0x1000;
        F(sprite, s32 *, 8) = get_item_category_value((void *)sprite_source);
        create_tracked_effect(object, 0, 0, 0);
    }
    return object;
}
