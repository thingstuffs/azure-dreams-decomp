#include "common.h"

typedef struct S_80170224_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x3E];
    u16 unk_B0;
} S_80170224_0;   /* base in func_80170224 */

typedef struct S_80170224_1 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170224_1;   /* arg0 in func_80170224 */



extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8016FCE4(void *, s32, s32, void *);
extern void func_800A9A0C(void *);
extern s16 func_800A2BDC(void *);
extern u16 D_80083462;

/* Updates an entity's state and flags according to its action result. */
s32 func_80170224(S_80170224_1 *entity, s32 target_x, s32 target_y, s16 force_action) {
    void *entity_data = entity;
    s16 action_result;

    if (((S_80170224_0 *)entity_data)->unk_B0 != 0) {
        action_result = func_800ADDA0(target_x, target_y, entity_data, 3, 6, (u8 *)entity_data + 0x9C);
        if (action_result < 0) {
            return 0;
        }
        if (force_action != 0) {
            func_8016FCE4(entity_data, target_x, target_y, entity_data);
            return 0;
        }
    } else {
        action_result = 0;
    }

    switch (action_result) {
    case 0:
        entity->unk_9A = 14;
        func_800A9A0C(entity_data);
        return 0;

    case 2:
        func_8016FCE4(entity, target_x, target_y, entity_data);
        return 0;

    case 1:
        ((S_80170224_0 *)entity_data)->unk_71 &= 0x7F;
        if (func_800A2BDC(entity_data) != 0) {
            ((S_80170224_0 *)entity_data)->unk_46 &= 0x7FFF;
            return 0;
        }
        /* fallthrough */
    default:
        ((S_80170224_0 *)entity_data)->unk_71 &= 0x7F;
        if (!(D_80083462 & 8)) {
            return 1;
        }
        ((S_80170224_0 *)entity_data)->unk_46 &= 0x7FFF;
        return 0;
    }
}
