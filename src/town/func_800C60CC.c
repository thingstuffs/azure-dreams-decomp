#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_800C382C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_800C382C_0;   /* arg1 in func_800C382C */

extern s32 func_800374F4(s32 arg0);
extern void func_800C2E84(void *arg0, void *arg1, void *arg2);
extern s32 D_800C355C;

/* Chooses a random movement direction and advances the entity state. */
void func_800C382C(Rec_func_80094268_arg0 *entity, S_800C382C_0 *movement, void *context) {
    s32 attempt;
    s32 direction;
    void *next_node;

    movement->unk_0C = 0;
    movement->unk_10 = 0;

    for (attempt = 0; attempt < 16; attempt++) {
        direction = func_800374F4(4) & 0xFFFF;

        if (direction == 0) {
            if (movement->unk_02 <
                entity->unk_84.as_s16 + entity->unk_8C) {
                entity->unk_72.as_s16 = 0x400;
                break;
            }
        } else if (direction == 1) {
            if (movement->unk_06 <
                entity->unk_86.as_s16 + entity->unk_8E) {
                entity->unk_72.as_s16 = 0;
                break;
            }
        } else if (direction == 2) {
            if (entity->unk_84.as_s16 - entity->unk_8C <
                movement->unk_02) {
                entity->unk_72.as_s16 = 0xC00;
                break;
            }
        } else {
            if (entity->unk_86.as_s16 - entity->unk_8E <
                movement->unk_06) {
                entity->unk_72.as_s16 = 0x800;
                break;
            }
        }
    }

    next_node = *(volatile void **)((u8 *)entity->unk_7C.as_pv + 4);
    func_800C2E84(entity, context, next_node);
    entity->unk_50.as_pv = &D_800C355C;
}
