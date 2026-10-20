#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct CopyFields {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[2];
    u16 fieldA;
} CopyFields;

typedef struct ConfigFields {
    u8 pad0[8];
    void * field8;
    u32 fieldC;
    u16 field10;
    u16 field12;
    u16 field14;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
} ConfigFields;

typedef struct TailFields {
    u8 pad0[0x14];
    u32 field14;
    u8 pad18[0x34];
    u16 field4C;
    u8 pad4E[0x1A];
    u32 field68;
} TailFields;

typedef struct EntityFields {
    u8 pad0[8];
    CopyFields *field8;
    ConfigFields *fieldC;
    void *field10;
    u8 pad14[0xC];
    TailFields tail;
} EntityFields;

extern u8 D_800C0404[];
extern u8 D_800DF4A4[];

extern EntityFields *allocate_list_node(s32, EntityFields *);
extern void unlink_node(EntityFields *);
extern void retire_tracked_effect_by_id(EntityFields *);
extern void register_node(EntityFields *, void *);

/* Creates and configures an entity, copies source fields, and links it to the source. */
void *create_linked_actor_fade_effect(EntityFields *source) {
    EntityFields *entity;
    CopyFields *source_fields;
    CopyFields *entity_fields;
    SpriteFrameState *config;
    TailFields *entity_tail;
    TailFields *source_tail;
    u16 size;

    entity = allocate_list_node(2, source);
    if (entity != NULL) {
        unlink_node(source);
        retire_tracked_effect_by_id(source);
        entity->field10 = D_800C0404;
        register_node(entity, project_sprite_chain);

        source_fields = source->field8;
        entity_fields = entity->field8;
        entity_fields->field2 = source_fields->field2;
        entity_fields->field6 = source_fields->field6;
        entity_fields->fieldA = source_fields->fieldA;

        config = entity->fieldC;
        config->tpage_abr = 0x20;
        config->source = D_800DF4A4;
        size = 0x1000;
        config->scale_y = size;
        config->color.word = 0x808080;
        config->scale_x = size;
        source_tail = &source->tail;
        config->flags |= 0xC;
        entity_tail = &entity->tail;
        entity_tail->field4C = 0x10;
        entity_tail->field68 = source_tail;
        source_tail->field14 |= 0x100000;
    }
    return entity;
}
