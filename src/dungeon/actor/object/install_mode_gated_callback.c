#include "common.h"
#include "dungeon/actor/object.h"
typedef struct {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
} Entity;

/* cfail-repair: tf7-phase1-cache-v3 */
void release_entity_and_flag_removal(Entity *entity);

typedef struct S_80025514_0 {
    u8 pad_00[0x10];
    void (*unk_10)(Entity *);
} S_80025514_0;   /* arg0 in install_mode_gated_callback */

/* Set the object's data pointer to release_entity_and_flag_removal. */
void install_mode_gated_callback(S_80025514_0 *object) {
    object->unk_10 = &release_entity_and_flag_removal;
}
