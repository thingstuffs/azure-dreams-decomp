#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "dungeon/effect/screen.h"
#include "dungeon/item/effect.h"
#include "engine/node.h"
#include "dungeon/item_callbacks_api.h"
#include "dungeon/item/return_magic_sprite_data.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct EntityFields {
    ObjectNodeHeader header;
    ActorRecord actor;
} EntityFields;

/* Creates and configures an entity, copies source fields, and links it to the source. */
void *create_linked_actor_fade_effect(EntityFields *source) {
    ObjectNodeHeader *entity;
    ObjectPosition *source_fields;
    ObjectPosition *entity_fields;
    SpriteFrameState *config;
    ReturnMagicAscentBody *fade;
    ActorRecord *source_actor;
    u16 size;

    entity = allocate_list_node(2, &source->header.next);
    if (entity != NULL) {
        unlink_node(&source->header);
        retire_tracked_effect_by_id(&source->header);
        entity->update_callback = update_return_magic_ascent;
        register_node(entity, project_sprite_chain);

        source_fields = source->header.position;
        entity_fields = entity->position;
        entity_fields->x.w.i = source_fields->x.w.i;
        entity_fields->y.w.i = source_fields->y.w.i;
        entity_fields->z.w.i = source_fields->z.w.i;

        config = entity->sprite;
        config->tpage_abr = 0x20;
        config->source = return_magic_sprite_data;
        size = 0x1000;
        config->scale_y = size;
        config->color.word = 0x808080;
        config->scale_x = size;
        source_actor = &source->actor;
        config->flags |= 0xC;
        fade = NODE_BODY(entity);
        fade->counter = 0x10;
        fade->owner = source_actor;
        source_actor->flags14 |= 0x100000;
    }
    return entity;
}
