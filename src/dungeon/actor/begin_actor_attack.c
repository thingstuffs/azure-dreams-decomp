#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/system.h"

typedef struct {
    u8 pad00[0x8C];
    s32 field8C;
    u8 pad90[8];
    u16 field98;
    s8 field9A;
    s8 field9B;
    u8 pad9C[0xA];
    s16 fieldA6;
} Entity;

typedef struct {
    u8 pad00[0x1C];
    s32 field1C;
    u8 pad20[0xA];
    s16 field2A;
    u8 pad2C[0x30];
    s32 field5C;
} Actor;

typedef struct {
    u16 field0;
    u16 field2;
    u8 pad04[8];
    Actor *field0C;
} DungeonState;

extern void prepare_directional_attack(Actor *, s32, s16, s32, s32);
extern s32 generate_random_value(void);
extern void process_unflagged_linked_entries_alt(u32);
extern void append_packed_action_record(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte);

/* Reset the entity state and initialize the active dungeon actor. */
s32 begin_actor_attack(Entity *entity, s32 unused, s32 action_param, Actor *actor) {

    entity->field98 |= 0x2000;
    prepare_directional_attack(actor, action_param, actor->field2A, 1, 0);
    if (actor->field1C & 0x400) {
        actor->field2A = (u16)actor->field2A + (generate_random_value() & 0xE00);
    }
    entity->field9A = 0x37;
    entity->field9B = 0;
    entity->field8C = 0;
    g_dungeon_status.active_actor = actor;
    entity->fieldA6 = 0;
    process_unflagged_linked_entries_alt(actor->field5C);
    append_packed_action_record(actor, 0x18, 0, 0);
    if (check_action_available_without_nearby_actor() != 0) {
        g_dungeon_status.flags |= 0x80;
    }
    return 0;
}
