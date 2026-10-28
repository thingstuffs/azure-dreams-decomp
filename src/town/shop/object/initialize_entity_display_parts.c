#include "common.h"
#include "shared/gpu_packets.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template16;


extern Template16 display_block_defaults;
extern DisplayPositionWords display_vector_defaults;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} EntityPart;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
} EntityVector;

typedef struct {
    s32 unk0;
    EntityPart *unk4;
    EntityVector *unk8;
} Entity;

/* Initialize an entity and its part and vector storage from default templates. */
void initialize_entity_display_parts(Entity *entity, Template16 *part, EntityVector *vector) {
    Template16 *part_template = &display_block_defaults;
    DisplayPositionWords *vector_template = &display_vector_defaults;
    s32 *vector_word;

    part->unk0 = part_template->unk0;
    vector_word = &vector_template->unk0;
    part->unk4 = part_template->unk4;
    part->unk8 = part_template->unk8;
    part->unkC = part_template->unkC;

    vector->unk0 = *vector_word;
    vector->unk4 = vector_template->unk4;
    ((DisplayPositionWords *)vector)->unk8 = vector_template->unk8;

    entity->unk4 = (EntityPart *)part;
    entity->unk8 = vector;
    entity->unk0 = 0;

    entity->unk4->unk0 = 0;
    entity->unk4->unk1 = 0;
    entity->unk4->unk2 = 0;
    entity->unk4->unk8 = 0;
    entity->unk4->unkA = 0;
    entity->unk4->unkC = 0x200;
    entity->unk4->unk6 = 0x1000;
    entity->unk8->unk8 = 0x30;
    entity->unk4->unkF = 4;
}
