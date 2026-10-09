#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

s32 func_800A2BDC();                          /* extern */
void func_800A9A0C();                      /* extern */
s32 func_800ADDA0(); /* extern */
void func_8017182C(); /* extern */

typedef struct S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} S_80172628_0;   /* hold_arg0 in func_80172258 */

/* Update entity state and flags according to the state query result. */
s32 func_80172258(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)func_800ADDA0(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        func_8017182C(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((S_80172628_0 *)entity)->unk_9A = 0xE;
        func_800A9A0C(entity);
        result = 0;
        return result;
    case 2:
        func_8017182C(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((S_80172628_0 *)entity)->unk_71 = (u8) (((S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((func_800A2BDC(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((S_80172628_0 *)entity)->unk_71 = (u8) (((S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((dungeonStatus.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((S_80172628_0 *)entity)->unk_46 = (u16) (((S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}
