#include "common.h"
#include "dungeon/entity_spawn_variant_data.h"
#include "shared/entity.h"
#include "engine/entity.h"

/* a one-byte code; an extern, so absolute (lui/sb) in ASPSX */

/* Maps modes 0xD and 0xF of type 0x16 entities to global codes 0xF and 0xA. */
void set_code_for_entity_mode(ActorRecord *entity)
{
    if (entity->species == 0x16) {
        u8 mode = entity->unk_48;
        if (mode == 0xD) {
            entity_spawn_variant_code = 0xF;
        } else if (mode == 0xF) {
            entity_spawn_variant_code = 0xA;
        }
    }
}
