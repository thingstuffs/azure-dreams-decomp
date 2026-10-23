#include "common.h"

/* Struct type for the entity pointed to by a0 in set_code_for_entity_mode.
   Only offsets 0x13 and 0x48 are accessed (both bytes); pad to reach them. */
typedef struct {
    u8 pad_0x00[0x13];
    u8 field_0x13;
    u8 pad_0x14[0x48 - 0x13 - 1];
    u8 field_0x48;
} S_8004397C_Entity;

/* a one-byte code; an extern, so absolute (lui/sb) in ASPSX */
extern u8 entity_spawn_variant_code;

/* Maps modes 0xD and 0xF of type 0x16 entities to global codes 0xF and 0xA. */
void set_code_for_entity_mode(S_8004397C_Entity *entity)
{
    if (entity->field_0x13 == 0x16) {
        u8 mode = entity->field_0x48;
        if (mode == 0xD) {
            entity_spawn_variant_code = 0xF;
        } else if (mode == 0xF) {
            entity_spawn_variant_code = 0xA;
        }
    }
}
