#include "common.h"
#include "records/Rec_D_80082D58.h"
#include "shared/object_payload.h"
#include "shared/vector.h"

void func_80033D08(void *block_data);
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
void clear_object_slot_and_mark_removed();                      /* extern */
s32 is_default_object_data();                          /* extern */

typedef struct S_800CB9B8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800CB9B8_1;

   /* arg1 in update_entity_relative_position */





typedef struct S_800CB9B8_5 {
    u8 pad_00[0x72];
    s16 unk_72;
} S_800CB9B8_5;   /* ((Rec_D_80082D58 *)arg0)->unk_9C in update_entity_relative_position */

typedef struct S_800CB9B8_6 {
    u8 pad_00[0x3];
    s8 unk_03;
} S_800CB9B8_6;

/* extern */

/* Compute an entity-relative position, or run fallback updates if its state check fails. */
void update_entity_relative_position(Rec_D_80082D58 *entity, IntVector3 *out_pos) {
    void *state;
    IntVector3 *base_pos;
    ObjectPayloadView *height_info;
    S_800CB9B8_1 *state_header;

    state = entity->unk_9C;
    state_header = state - 0x20;
    base_pos = state_header->unk_08;
    height_info = state_header->unk_0C;
    if (is_default_object_data(state) == 0) {
        func_80033D08(entity);
        clear_object_slot_and_mark_removed(entity);
        return;
    }
    out_pos->x = (s32) (base_pos->x + (func_800644B8(((S_800CB9B8_5 *)(entity->unk_9C))->unk_72) * 0x140));
    out_pos->y = (s32) (base_pos->y + (func_80064584(((S_800CB9B8_5 *)(entity->unk_9C))->unk_72) * 0x140));
    out_pos->z = (s32) (base_pos->z + (((S_800CB9B8_6 *)(height_info->unk_08))->unk_03 << 0x11) + 0x100000);
}
