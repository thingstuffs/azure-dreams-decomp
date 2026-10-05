#include "common.h"
#include "shared/slus_callbacks.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} SourcePosition;

typedef struct {
    u8 index;
    u8 group;
    u8 param;
    u8 flags;
} DungeonArg;

typedef struct {
    u8 pad0[0x2A];
    u16 mode;
    u8 pad2C[0x1C];
    DungeonArg arg;
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
    DungeonArg arg;
    u8 pad30[4];
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

extern Entity *func_8003FC64(s32);
extern void func_8004491C(Entity *, void *);
extern s32 func_801745B4(DungeonArg *selection, u8 *context);

extern DungeonGroup D_80073414[];
extern s32 D_8007361C[256];
extern s32 D_801747F0;
extern DirectionVector D_801755E0[];

/* Creates a dungeon entity with the supplied position, direction, and object data. */
void func_80174D98(void *owner, SourcePosition *source_pos, void *unused,
                   DungeonObjectArg *object)
{
    Entity *entity;
    EntityWork *work;
    EntityRender *render;
    EntityPosition *position;
    DungeonGroup *item_category_table;
    DungeonGroup *item_category;
    s32 *results;
    s32 entry_index;

    entity = func_8003FC64(0x12);
    if (entity == 0) {
        return;
    }

    entity->callback = &D_801747F0;
    func_8004491C(entity, func_80045340);

    render = entity->render;
    render->flags &= 0xFFF3;
    work = &entity->work;
    work->owner = owner;
    work->arg = object->arg;
    func_801745B4(&work->arg, object);
    object->arg.index = 0;
    object->arg.group = 0;

    position = entity->position;
    position->x = source_pos->x;
    position->y = source_pos->y;
    position->z = source_pos->z - 0x20;

    work->x = D_801755E0[(object->mode >> 9) & 7].x << 18;
    work->y = D_801755E0[(object->mode >> 9) & 7].y << 18;
    work->z = 0xFFF80000;
    work->scale = 0x14900;
    work->mode = (object->mode >> 9) & 7;

    render = entity->render;
    render->scale_x = 0x1000;
    render->scale_y = 0x1000;
    render->height = D_801755E0[(object->mode >> 9) & 7].y * 6;

    *(u16 *)((u8 *)owner + 0xA2) = 0x4D;
    work->x_cell = (s16)source_pos->x / 0x40;
    work->y_cell = (s16)source_pos->y / 0x40;

    results = D_8007361C;
    item_category_table = D_80073414;
    render->blue = 0x80;
    render->green = 0x80;
    render->red = 0x80;

    item_category = &item_category_table[work->arg.group];
    if (item_category->active == 0) {
        entry_index = work->arg.index * 5;
    } else {
        entry_index = work->arg.index * 3;
    }
    render->result = results[item_category->entries[entry_index].height];
}
