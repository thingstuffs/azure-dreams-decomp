#include "common.h"

typedef struct {
    s32 word[6];
} CopyBlock;

typedef struct {
    u8 pad00[0x0C];
    s32 color;
    u8 pad10[0x0C];
    u16 scale_x;
    u16 scale_y;
} RenderPart;

typedef struct {
    u8 pad00[8];
    CopyBlock *copy_dst;
    RenderPart *part;
    void *callback;
    u8 pad14[0x12];
    u16 kind;
} Object;

extern Object *func_8003FC64(s32 type);
extern void func_8004491C(Object *object, void *init);
extern void func_8003DB94(RenderPart *part, void *data, s32 index);

extern u8 D_80045340[16];
extern u8 D_800B21B8[16];
extern u8 D_800DEC70[16];

/* Creates an object from the source block and initializes its render part. */
void func_800B2230(CopyBlock *source)
{
    Object *object;
    RenderPart *part;

    object = func_8003FC64(0x212);
    if (object != 0) {
        object->callback = D_800B21B8;
        func_8004491C(object, D_80045340);
        *object->copy_dst = *source;

        part = object->part;
        part->color = 0x00808080;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        func_8003DB94(part, D_800DEC70, 0);
        object->kind = 0x20;
    }
}
