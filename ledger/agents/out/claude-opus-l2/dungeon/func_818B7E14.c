#include "common.h"

typedef struct DungeonRenderData {
    u8 pad00[0xC];
    u8 color_r;
    u8 color_g;
    u8 color_b;
    u8 pad0F[3];
    s16 f12;
    u16 f14;
    u8 pad16[4];
    s16 f1A;
    s16 f1C;
    s16 f1E;
} DungeonRenderData;

typedef struct DungeonObject {
    u8 pad00[8];
    s32 *data;
    DungeonRenderData *render;
    void *update;
    u8 pad14[0xC];
    void *owner;
    u8 pad24[0xC];
    s16 f30;
    u8 pad32[2];
    u16 f34;
} DungeonObject;

typedef struct DungeonSource {
    s32 word[6];
} DungeonSource;

extern void *func_8003FC64(s32);
extern void func_8003DB94(DungeonRenderData *, void *, s32);
extern s32 rand(void);
extern void func_8004491C(DungeonObject *, void *);

extern u8 D_8002553C[12];
extern u8 D_80025EE4[12];
extern u8 D_80045C34[12];

/* Spawn a 0x212 effect object owned by `owner`, give it a random 12-bit spin and copy the source transform into it. */
s32 func_818B7E14(void *owner, DungeonSource *source)
{
    s32 random;
    s32 adjusted;
    DungeonObject *obj;
    DungeonRenderData *render;
    u8 *sub;
    DungeonSource *dst;
    s32 copy0;
    s32 copy0_2;
    s32 copy1;
    s32 copy1_2;
    s32 copy2;
    s32 copy3;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        sub = (u8 *)obj + 0x20;
        obj->update = D_8002553C;
        obj->owner = owner;
        *(s16 *)(sub + 0x10) = 0;
        *(u16 *)(sub + 0x14) = *(u16 *)((u8 *)owner + 0x12);
        render = obj->render;
        render->color_b = 0x80;
        render->color_g = 0x80;
        render->color_r = 0x80;
        render->f12 = 0x7E00;
        render->f14 |= 0x100;
        func_8003DB94(render, D_80025EE4, 0);
        random = rand();
        adjusted = random;
        if (random < 0) {
            adjusted = random + 0xFFF;
        }
        render->f1A = random - ((adjusted >> 12) << 12);
        render->f1E = 0x400;
        render->f1C = 0x400;
        func_8004491C(obj, D_80045C34);
        dst = (DungeonSource *)obj->data;

        *dst = *source;
        return obj;
    }
    return 0;
}
