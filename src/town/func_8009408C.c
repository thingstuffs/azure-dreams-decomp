#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800374F4();
M2C_UNK func_80094048();
M2C_UNK func_80094378();
M2C_UNK func_80094944();
M2C_UNK func_80094C1C();
M2C_UNK func_8009503C();
M2C_UNK func_800951B4();
s16 func_80095978();
M2C_UNK func_80095A94();
M2C_UNK func_80095C80();
M2C_UNK func_800A895C();
extern u8 D_80083160[];
extern u8 D_800CFCEF[];
extern u8 D_800D043C[];
extern u8 D_800FE488[];
extern s32 D_800FE4E0;


typedef struct S_800917EC_0 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800917EC_0;   /* arg1 in func_800917EC */


typedef struct S_800917EC_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800917EC_2;   /* temp_s0 in func_800917EC */

typedef struct S_800917EC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800917EC_3;   /* state in func_800917EC */

/* Updates actor height, emits periodic effects, and handles the active state. */
void func_800917EC(Rec_func_80094268_arg0 *actor, S_800917EC_0 *position, M2C_UNK context) {
    u8 *state = D_80083160;
    s16 surface_height;
    s16 action_timer;
    s32 *effect_pos;
    s32 state_flags;
    u16 effect_timer;

    func_80095C80(position);
    func_800951B4(position);
    surface_height = func_80095978(position, D_800FE488);
    if ((surface_height - position->unk_08.at02.v) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(actor, position, context);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        func_80095A94(position, surface_height, D_800FE488);
    }
    effect_timer = actor->unk_0A.as_u16 - 1;
    actor->unk_0A.as_u16 = effect_timer;
    if ((effect_timer << 0x10) <= 0) {
        actor->unk_0A.as_u16 = (u16)(func_800374F4(4) + 3);
        D_800FE4E0 = position->unk_00;
        effect_pos = &D_800FE4E0;
        ((S_800917EC_2 *)effect_pos)->unk_04 = position->unk_04;
        ((S_800917EC_2 *)effect_pos)->unk_08 =
            position->unk_08.at00.v + 0xFFB00000;
        func_800A895C(effect_pos, D_800D043C,
                      (func_800374F4(2) & 0xFFFF) + 2);
    }
    state_flags = ((S_800917EC_3 *)state)->unk_08;
    if ((state_flags & 0xF000) && (state_flags & 0x20)) {
        action_timer = actor->unk_3E.as_u16 - 1;
        actor->unk_3E.as_u16 = (u16)action_timer;
        func_80094944(action_timer, 8);
        func_80094C1C(actor);
        func_8009503C(position);
        return;
    }
    func_80094048(actor, position, context);
}
