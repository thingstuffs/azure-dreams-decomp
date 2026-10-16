/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

typedef struct {
    void *callback0;
    void *callback4;
    u8 pad08[2];
    s16 timer;
    u8 pad0C[4];
    s16 id;
    u8 pad12[0x24];
    s16 x;
    s16 y;
} Entity;

extern void townClearEntityRecordFields(s32 record);
extern void townCallTheHandlerSelectsNonzeroEntry(void *entries, void *record, s32 handler_param);

extern Entity D_800834B8;
extern s32 D_80097D2C[3];
extern s32 D_8009A81C;
extern u8 D_800D0090[];

void func_8009A8EC(s32 entity_id, s32 x, s32 y) {
    Entity *entity = &D_800834B8;
    s32 *context = (s32 *)((u8 *)entity - 0x20);
    s32 context_value = context[3];

    townClearEntityRecordFields(context[2]);
    townCallTheHandlerSelectsNonzeroEntry(D_800D0090, entity, context_value);
    D_800834B8.callback0 = D_80097D2C;
    entity->callback4 = &D_8009A81C;
    entity->id = entity_id & 0xFFF;
    entity->x = x;
    entity->y = y;
    entity->timer = 0x10;
}
