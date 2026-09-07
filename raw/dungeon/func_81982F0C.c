#include "common.h"

typedef struct {
    u8 pad0[8];
    void *dst;
    void *sprite;
    void (*callback)(void);
} Object;

extern Object *func_8003FC64(s32);
extern void func_8004491C(Object *, void *);
extern s32 rand(void);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_800245F8(void);
extern u8 D_80045340[];
extern u8 D_80026AB0[];

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void *func_8002470C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 count)
{
    Object *obj = 0;
    s16 base_angle = (s16)arg3;
    s32 iterations = count;

    while (iterations > 0) {
        obj = func_8003FC64(0x202);
        if (obj != 0) {
            s32 angle;
            s32 final_angle;
            void *dst;
            void *sprite;
            u8 *extra;

            obj->callback = func_800245F8;
            func_8004491C(obj, D_80045340);
            dst = obj->dst;
            FIELD(dst, s16, 2) = (s16)arg0;
            FIELD(dst, s16, 6) = (s16)arg1;
            FIELD(dst, s16, 0xA) = (s16)(arg2 + 0x10);

            angle = (s16)((rand() & 0x7FF) - 0x400);
            angle -= 0x800;
            final_angle = base_angle + angle;
            FIELD(dst, s32, 0xC) = func_80064584(final_angle) << 6;
            FIELD(dst, s32, 0x10) = func_800644B8(final_angle) << 6;
            FIELD(dst, s32, 0x14) =
                (rand() & 0x1FFFF) - 0x10000;

            sprite = obj->sprite;
            FIELD(sprite, s16, 0x1E) = 0x1000;
            FIELD(sprite, s16, 0x1C) = 0x1000;
            FIELD(sprite, s32, 0xC) = 0x808080;
            func_8003DB94(sprite, D_80026AB0, rand() & 7);

            extra = (u8 *)obj + 0x20;
            FIELD(extra, s16, 0x30) = (s16)((rand() & 7) + 0x10);
            FIELD(extra, s16, 0x36) = (s16)arg3;
        }
        iterations--;
    }
    return obj;
}
