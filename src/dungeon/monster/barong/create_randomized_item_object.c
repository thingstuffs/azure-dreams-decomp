#include "slus/data.h"
#include "shared/object_node.h"
#include "dungeon/monster/barong.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "dungeon/data.h"

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
    BarongItemDescriptor arg;
} DungeonObjectArg;







typedef struct {
    ObjectNodeHeader header;
    TossedItemMotionBody work;
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

extern s32 select_random_replacement_item(BarongItemDescriptor *selection, u8 *context);

extern DungeonGroup item_category_groups[];

extern DirectionVector barong_direction_vectors[];

/* Creates a dungeon entity with the supplied position, direction, and object data. */
void create_randomized_item_object(ActorRecord *owner, ObjectPosition *source_pos, SpriteFrameState *unused,
                   DungeonObjectArg *object)
{
    Entity *entity;
    TossedItemMotionBody *work;
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

    entity->header.update_callback = update_motion_and_terrain_collision;
    register_node(&entity->header, project_sprite_chain);

    render = entity->header.sprite;
    render->flags &= 0xFFF3;
    work = &entity->work;
    work->owner = owner;
    work->arg = object->arg;
    select_random_replacement_item(&work->arg, object);
    object->arg.index = 0;
    object->arg.group = 0;

    position = entity->header.position;
    position->x.w.i = source_pos->x.w.i;
    position->y.w.i = source_pos->y.w.i;
    position->z.w.i = source_pos->z.w.i - 0x20;

    work->velocity_x = barong_direction_vectors[(object->mode >> 9) & 7].x << 18;
    work->velocity_y = barong_direction_vectors[(object->mode >> 9) & 7].y << 18;
    work->velocity_z = 0xFFF80000;
    work->acceleration_z = 0x14900;
    work->direction.u = (object->mode >> 9) & 7;

    render = entity->header.sprite;
    render->scale_y = 0x1000;
    render->scale_x = 0x1000;
    render->depth_bias = barong_direction_vectors[(object->mode >> 9) & 7].y * 6;

    owner->unk_A0.parts.high = 0x4D;
    work->cell_x.s = (s16)source_pos->x.w.i / 0x40;
    work->cell_y.s = (s16)source_pos->y.w.i / 0x40;

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
