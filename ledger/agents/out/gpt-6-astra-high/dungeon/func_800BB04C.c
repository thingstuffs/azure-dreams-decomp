#include "common.h"

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
    void * volatile field8;
    volatile u32 fieldC;
    volatile u16 field10;
    u16 field12;
    volatile u16 field14;
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

extern u8 D_80045340[];
extern u8 D_800C0404[];
extern u8 D_800DF4A4[];

extern EntityFields *func_8003FD64(s32, EntityFields *);
extern void func_80044A50(EntityFields *);
extern void func_800BC318(EntityFields *);
extern void func_8004491C(EntityFields *, void *);

/* Creates and configures an entity, copies source fields, and links it to the source. */
void *func_800C07AC(EntityFields *source) {
    EntityFields *entity;
    CopyFields *source_fields;
    CopyFields *entity_fields;
    ConfigFields *config;
    TailFields *entity_tail;
    TailFields *source_tail;
    register u16 config_flags ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u16 size;

    entity = func_8003FD64(2, source);
    if (entity != NULL) {
        func_80044A50(source);
        func_800BC318(source);
        entity->field10 = D_800C0404;
        func_8004491C(entity, D_80045340);

        source_fields = source->field8;
        entity_fields = entity->field8;
        entity_fields->field2 = source_fields->field2;
        entity_fields->field6 = source_fields->field6;
        entity_fields->fieldA = source_fields->fieldA;

        config = entity->fieldC;
        config->field10 = 0x20;
        config->field8 = D_800DF4A4;
        size = 0x1000;
        config->field1E = size;
        config->field1C = size;
        source_tail = &source->tail;
        config_flags = config->field14;
        config->fieldC = 0x808080;
        config->field14 = config_flags | 0xC;
        entity_tail = &entity->tail;
        entity_tail->field4C = 0x10;
        entity_tail->field68 = source_tail;
        source_tail->field14 |= 0x100000;
    }
    return entity;
}
