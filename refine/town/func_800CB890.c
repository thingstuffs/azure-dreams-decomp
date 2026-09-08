#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C907C;
extern M2C_UNK D_800D6268;



typedef struct S_800C8FF0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C8FF0_1;   /* arg1 in func_800C8FF0 */

/* Decrement the entity's timer, updating motion until the next state begins. */
void func_800C8FF0(Rec_func_80094268_arg0 *entity, S_800C8FF0_1 *motion, M2C_UNK context) {
    u16 ticks_left;
    M2C_UNK transition_context;

    ticks_left = entity->unk_6C.as_u16 - 1;
    entity->unk_6C.as_u16 = ticks_left;
    transition_context = context;
    if ((s16) ticks_left < 0) {
        func_800C2E84(entity, transition_context, &D_800D6268);
        entity->unk_6C.as_u16 = 3U;
        entity->unk_50.as_pm = &D_800C907C;
        entity->unk_72.as_s16 = 0xC00;
        return;
    }
    entity->unk_72.as_s16 = 0x800;
    motion->unk_04 = (s32) (motion->unk_04 + 0xFFEAAAAB);
}
