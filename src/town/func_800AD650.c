#include "common.h"

extern s16 D_80100D80;
extern s16 D_80100D82;
extern void func_8009539C(void *arg);

typedef struct {
    s32 unk0[3];
    s32 x;
    s32 y;
} Object;

/* Applies the global offsets scaled by 64 to the object and updates it. */
void func_800AADB0(void *unused_first, void *unused_second, Object *object) {
    object->x += D_80100D80 << 6;
    object->y += D_80100D82 << 6;
    func_8009539C(object);
}
