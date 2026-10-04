#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 func_800A2B5C();                          /* extern */
s32 func_800A4ACC();                      /* extern */
s32 func_800C7930(); /* extern */


typedef struct S_80174824_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80174824_1;   /* arg0 in func_80174824 */

/* Clears an entity flag and resets its action state after processing completes. */
void func_80174824(S_80174824_1 *action_state, s32 context, s32 unused, EntityRec *entity) {
    entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930((u8 *)entity - 0x20, context, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A = 0x17;
            action_state->unk_9B = 0;
            func_800A4ACC(entity);
            entity->unk_6D = (u8) (((u8)entity->unk_6D) - 1);
            action_state->unk_96 = 0;
        }
    }
}
