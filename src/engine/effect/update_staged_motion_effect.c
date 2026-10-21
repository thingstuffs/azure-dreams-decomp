#include "common.h"
#include "shared/vector.h"
#include "engine/effect.h"
#include "sdk/libgte.h"
#include "slus.h"
#include "slus/data.h"

typedef struct S_80051548_Ptr
{
    u8 unk00[6];
    u16 cnt;
    u8 unk08[4];
    s32 unk0C;
}
S_80051548_Ptr;
typedef struct S_80051548_Obj
{
    S_80051548_Ptr *ptr0;
    s16 state;
    u16 field6;
    u8 unk08[4];
    s16 field0C;
}
S_80051548_Obj;
typedef struct S_80051548_VolState
{
    S_80051548_Ptr *ptr0;
    u16 state;
    u16 field6;
    u8 unk08[4];
    s16 field0C;
}
S_80051548_VolState;

typedef struct S_80051548_Flags
{
    u8 unk[0xC];
    u8 c;
    u8 d;
    u8 e;
}
S_80051548_Flags;
/* Advances staged object motion and marks completion. */
void update_staged_motion_effect(S_80051548_Obj *obj, IntVector3 *position, S_80051548_Flags *flags)
{
    s16 state;
    u16 prior_state;
    u16 *status_word;

    obj->field6 = obj->field6 + 1;
    func_800478B8(flags);
    state = obj->state;
    switch (state) {
    case 1:
        position->x = 0x01C00000 - (((rsin(((s16) obj->field6) << 4) >> 4) * 3) << 14);
        position->y = ((rcos(((s16) obj->field6) << 4) >> 4) << 13) + 0x900000;
        if (((s16) obj->field6) < 0x40) {
            return;
        }
        position->x = 0x01000000;
        position->y = 0x900000;
        position->z = 0x700000;
        prior_state = ((S_80051548_VolState *) obj)->state;
        obj->field6 = 0;
        obj->state = prior_state + 1;
        return;

    case 0:
    case 2:
        if (obj->field0C == 0) {
            return;
        }
        prior_state = ((S_80051548_VolState *) obj)->state;
        obj->field0C = 0;
        obj->field6 = 0;
        obj->state = prior_state + 1;
        return;

    case 3:
        position->x = position->x + 0xFFF40000;
        position->y = position->y + 0x20000;
        if (((s16) obj->field6) < 0x40) {
            return;
        }
        break;

    default:
        flags->e = 0;
        flags->d = 0;
        flags->c = 0;
        break;
    }
    obj->ptr0->unk0C = 0;
    obj->ptr0->cnt = obj->ptr0->cnt + 1;
    status_word = (u16 *) obj - 1;
    *status_word |= 0x8000;
    D_800814A0_abs |= 0x8000;
}
