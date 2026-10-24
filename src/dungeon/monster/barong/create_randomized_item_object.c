#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
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

extern void register_node(Entity *, void *);
extern s32 select_random_replacement_item(DungeonArg *selection, u8 *context);

extern DungeonGroup item_category_groups[];
extern s32 item_display_icon_words[256];
extern s32 D_801747F0;
extern DirectionVector barong_direction_vectors[];

/* Creates a dungeon entity with the supplied position, direction, and object data. */
void create_randomized_item_object(void *owner, SourcePosition *source_pos, void *unused,
                   DungeonObjectArg *object)
{
    Entity *entity;
    EntityWork *work;
    SpriteFrameState *render;
    ObjectPosition *position;
    DungeonGroup *item_category_table;
    DungeonGroup *item_category;
    s32 *results;
    s32 entry_index;

    entity = allocate_flagged_object_node(0x12);
    if (entity == 0) {
        return;
    }

    entity->callback = &D_801747F0;
    register_node(entity, project_sprite_chain);

    render = entity->render;
    render->flags &= 0xFFF3;
    work = &entity->work;
    work->owner = owner;
    work->arg = object->arg;
    select_random_replacement_item(&work->arg, object);
    object->arg.index = 0;
    object->arg.group = 0;

    position = entity->position;
    position->x.w.i = source_pos->x;
    position->y.w.i = source_pos->y;
    position->z.w.i = source_pos->z - 0x20;

    work->x = barong_direction_vectors[(object->mode >> 9) & 7].x << 18;
    work->y = barong_direction_vectors[(object->mode >> 9) & 7].y << 18;
    work->z = 0xFFF80000;
    work->scale = 0x14900;
    work->mode = (object->mode >> 9) & 7;

    render = entity->render;
    render->scale_y = 0x1000;
    render->scale_x = 0x1000;
    render->depth_bias = barong_direction_vectors[(object->mode >> 9) & 7].y * 6;

    *(u16 *)((u8 *)owner + 0xA2) = 0x4D;
    work->x_cell = (s16)source_pos->x / 0x40;
    work->y_cell = (s16)source_pos->y / 0x40;

    results = item_display_icon_words;
    item_category_table = item_category_groups;
    render->color.c.b = 0x80;
    render->color.c.g = 0x80;
    render->color.c.r = 0x80;

    item_category = &item_category_table[work->arg.group];
    if (item_category->active == 0) {
        entry_index = work->arg.index * 5;
    } else {
        entry_index = work->arg.index * 3;
    }
    render->source = results[item_category->entries[entry_index].height];
}
