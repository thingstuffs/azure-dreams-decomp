#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

typedef struct {
    s32 word[6];
} Copy24;

typedef struct {
    u8 pad00[4];
    s32 word;
} Resource;

typedef struct {
    Resource *resource;
    s8 x;
    s8 y;
    u8 pad06[2];
    s32 resource_word;
    s32 color;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    s16 scale_y;
    s16 scale_x;
} Primitive;

typedef struct {
    u8 pad00[8];
    Copy24 *position;
    Primitive *primitive;
    u8 *callback;
} Object;

typedef struct {
    u8 pad00[0x48];
    s16 lifetime;
} Motion;

typedef struct {
    u8 pad00[0x48];
    u16 timer;
    s16 count;
} Self;

extern Object *func_8003FD64(s32, void *);
extern void func_8004491C(Object *, void *);
extern s32 rand(void);

extern u8 D_80045340[];
extern int D_800814A0[3];
extern u8 D_80083498[];
extern u8 D_800BBA98[];
extern Resource D_800F162C[];

void func_800BB894(Self *self, Copy24 *origin) {
    s32 count = self->count;

    if (count >= 0) {
        u8 *callback = D_800BBA98;
        Resource *resource;

        do {
            Object *object = func_8003FD64(0x312, D_80083498);

            if (object != NULL) {
                Primitive *primitive;

                object->callback = callback;
                func_8004491C(object, D_80045340);
                primitive = object->primitive;
                *object->position = *origin;

                object->position->word[0] +=
                    ((rand() % 255) - 0x80) * 0x40000;
                object->position->word[1] +=
                    ((rand() % 255) - 0x80) * 0x40000;

                primitive->scale_x = 0x1000;
                primitive->scale_y = 0x1000;
                object = (Object *)((u8 *)object + 0x20);
                if (origin->word[3] < 0) {
                    primitive->flags |= 1;
                }
                resource = D_800F162C;
                primitive->resource = resource;
                primitive->resource_word = resource->word;
                primitive->x = 0;
                primitive->y = 0;
                primitive->color = 0x808080;
                ((Motion *)object)->lifetime = 10;
            }
            count--;
        } while (count >= 0);
    }

    {
        u16 timer = self->timer - 1;

        self->timer = timer;
        if ((s16)timer <= 0) {
            FIELD(self, u16, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }
}
