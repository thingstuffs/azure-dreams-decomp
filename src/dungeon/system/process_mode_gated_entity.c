#include "shared/object_flags.h"
#include "shared/runtime_dispatch.h"
#include "common.h"


typedef s32 (*Func)(s32, s32);

typedef struct S_80025480_0_pre {
    u16 unk_00;
} S_80025480_0_pre;   /* the 0x2 bytes before arg0 in process_mode_gated_entity, addressed as arg0[-1] */


typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
} Entity;

extern void advance_paired_object_sequence(Entity *);
extern Func D_800294A8[];
extern struct { s32 v; s32 pad[2]; } D_800814A0;

/* Process an entity and set entity and global flags when the mode or callback permits. */
void process_mode_gated_entity(Entity *entity) {
    if (entity) {
        advance_paired_object_sequence(entity);
        if (runtime_dispatch_state.mode == 1 || D_800294A8[entity->field_18](entity->field_0, entity->field_10)) {
            ((S_80025480_0_pre *)entity)[-1].unk_00 |= 0x8000;
            D_800814A0.v |= OBJECT_REMOVE_PENDING;
        }
    }
}
