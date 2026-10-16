#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

M2C_UNK func_80033D08();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
void townClearObjectSlotAndMarkRemoved();                      /* extern */
s32 townIsDefaultObjectData();                          /* extern */

typedef struct S_800CB9B8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800CB9B8_1;   /* temp_v0 in townUpdateEntityRelativePosition */

typedef struct S_800CB9B8_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800CB9B8_2;   /* arg1 in townUpdateEntityRelativePosition */

typedef struct S_800CB9B8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800CB9B8_3;   /* temp_s0 in townUpdateEntityRelativePosition */

typedef struct S_800CB9B8_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800CB9B8_4;   /* temp_s3 in townUpdateEntityRelativePosition */

typedef struct S_800CB9B8_5 {
    u8 pad_00[0x72];
    s16 unk_72;
} S_800CB9B8_5;   /* ((Rec_D_80082D58 *)arg0)->unk_9C in townUpdateEntityRelativePosition */

typedef struct S_800CB9B8_6 {
    u8 pad_00[0x3];
    s8 unk_03;
} S_800CB9B8_6;   /* ((S_800CB9B8_4 *)temp_s3)->unk_08 in townUpdateEntityRelativePosition */

/* extern */

/* Compute an entity-relative position, or run fallback updates if its state check fails. */
void townUpdateEntityRelativePosition(Rec_D_80082D58 *entity, S_800CB9B8_2 *out_pos) {
    void *state;
    S_800CB9B8_3 *base_pos;
    S_800CB9B8_4 *height_info;
    S_800CB9B8_1 *state_header;

    state = entity->unk_9C;
    state_header = state - 0x20;
    base_pos = state_header->unk_08;
    height_info = state_header->unk_0C;
    if (townIsDefaultObjectData(state) == 0) {
        func_80033D08(entity);
        townClearObjectSlotAndMarkRemoved(entity);
        return;
    }
    out_pos->unk_00 = (s32) (base_pos->unk_00 + (func_800644B8(((S_800CB9B8_5 *)(entity->unk_9C))->unk_72) * 0x140));
    out_pos->unk_04 = (s32) (base_pos->unk_04 + (func_80064584(((S_800CB9B8_5 *)(entity->unk_9C))->unk_72) * 0x140));
    out_pos->unk_08 = (s32) (base_pos->unk_08 + (((S_800CB9B8_6 *)(height_info->unk_08))->unk_03 << 0x11) + 0x100000);
}
