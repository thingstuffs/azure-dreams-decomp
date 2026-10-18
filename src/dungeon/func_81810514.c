#include "common.h"
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
void process_mode_gated_entity(Entity *entity);

typedef struct S_80025514_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_80025514_0;   /* arg0 in set_object_data_pointer */

/* Set the object's data pointer to process_mode_gated_entity. */
void set_object_data_pointer(S_80025514_0 *object) {
    object->unk_10 = &process_mode_gated_entity;
}
