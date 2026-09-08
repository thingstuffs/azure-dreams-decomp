#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} SourcePosition;

typedef struct {
    u8 pad0[0x2A];
    u16 mode;
    u8 pad2C[0x1C];
    u8 copied[4];
} DungeonObjectArg;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} EntityPosition;

typedef struct {
    u8 pad0[6];
    s16 height;
    s32 result;
    u8 red;
    u8 green;
    u8 blue;
    u8 padF[5];
    u16 flags;
    u8 pad16[6];
    u16 scale_y;
    u16 scale_x;
} EntityRender;

typedef struct {
    u8 pad0[0x24];
    u16 mode;
    u8 pad26[6];
    u8 entry;
    u8 group;
    u8 pad2E[6];
    void *owner;
    u8 pad38[0x18];
    s8 x_cell;
    s8 y_cell;
    u8 pad52[2];
    s32 x;
    s32 y;
    s32 z;
    u8 pad60[8];
    s32 scale;
} EntityWork;

typedef struct {
    u8 pad0[8];
    EntityPosition *position;
    EntityRender *render;
    void *callback;
    u8 pad14[0xC];
    EntityWork work;
} Entity;

typedef struct {
    u8 pad0[2];
    s16 height;
} DungeonEntry;

typedef struct {
    u8 active;
    u8 pad1[11];
    DungeonEntry *entries;
    u8 pad10[4];
} DungeonGroup;

typedef struct {
    s16 x;
    s16 y;
} DirectionVector;

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

extern Entity *func_8003FC64(s32);
extern void func_8004491C(Entity *, void *);
extern void func_801745B4(void *, DungeonObjectArg *, EntityRender *);

extern s32 D_80045340;
extern DungeonGroup D_80073414[];
extern s32 D_8007361C[256];
extern s32 D_801747F0;
extern DirectionVector D_801755E0[];

void func_80174D98(void *arg0, SourcePosition *arg1, void *arg2,
                   DungeonObjectArg *arg3)
{
    Entity *entity;
    EntityWork *work;
    EntityRender *render;
    EntityPosition *position;
    DungeonGroup *groups;
    DungeonGroup *group;
    s32 *results;
    s32 cell;
    PackedWord *copy_src;
    PackedWord *copy_dst;
    u32 copied_word;

    entity = func_8003FC64(0x12);
    if (entity == 0) {
        return;
    }

    entity->callback = &D_801747F0;
    func_8004491C(entity, &D_80045340);

    copy_dst = (PackedWord *)((u8 *)entity + 0x4C);
    ASM_USE(copy_dst);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    render = entity->render;
    render->flags &= 0xFFF3;
    work = &entity->work;
    copy_src = (PackedWord *)&arg3->copied[0];
    work->owner = arg0;
    copied_word = copy_src->value;
    copy_dst->value = copied_word;
    func_801745B4(copy_dst, arg3, render);
    arg3->copied[0] = 0;
    arg3->copied[1] = 0;

    position = entity->position;
    position->x = arg1->x;
    position->y = arg1->y;
    position->z = arg1->z - 0x20;

    work->x = D_801755E0[(arg3->mode >> 9) & 7].x << 18;
    work->y = D_801755E0[(arg3->mode >> 9) & 7].y << 18;
    work->z = 0xFFF80000;
    work->scale = 0x14900;
    work->mode = (arg3->mode >> 9) & 7;

    render = entity->render;
    render->scale_x = 0x1000;
    render->scale_y = 0x1000;
    render->height = D_801755E0[(arg3->mode >> 9) & 7].y * 6;

    *(u16 *)((u8 *)arg0 + 0xA2) = 0x4D;
    work->x_cell = (s16)arg1->x / 0x40;
    work->y_cell = (s16)arg1->y / 0x40;

    results = D_8007361C;
    groups = D_80073414;
    render->blue = 0x80;
    render->green = 0x80;
    render->red = 0x80;

    group = &groups[work->group];
    if (group->active == 0) {
        cell = work->entry * 5;
    } else {
        cell = work->entry * 3;
    }
    render->result = results[group->entries[cell].height];
}
