#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800374F4();
M2C_UNK func_8009196C();
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

typedef struct S_800917EC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x32];
    u16 unk_3E;
} S_800917EC_1;   /* arg0 in func_800917EC */

typedef struct S_800917EC_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800917EC_2;   /* temp_s0 in func_800917EC */

typedef struct S_800917EC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800917EC_3;   /* state in func_800917EC */

void func_800917EC(S_800917EC_1 *arg0, S_800917EC_0 *arg1, M2C_UNK arg2) {
    u8 *state = D_80083160;
    s16 temp_v0;
    s16 temp_v0_3;
    s32 *temp_s0;
    s32 state_flags;
    u16 temp_v0_2;

    func_80095C80(arg1);
    func_800951B4(arg1);
    temp_v0 = func_80095978(arg1, D_800FE488);
    if ((temp_v0 - arg1->unk_08.at02.v) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(arg0, arg1, arg2);
            func_8009196C();
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        func_80095A94(arg1, temp_v0, D_800FE488);
    }
    temp_v0_2 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        arg0->unk_0A = (u16)(func_800374F4(4) + 3);
        D_800FE4E0 = arg1->unk_00;
        temp_s0 = &D_800FE4E0;
        ((S_800917EC_2 *)temp_s0)->unk_04 = arg1->unk_04;
        ((S_800917EC_2 *)temp_s0)->unk_08 =
            arg1->unk_08.at00.v + 0xFFB00000;
        func_800A895C(temp_s0, D_800D043C,
                      (func_800374F4(2) & 0xFFFF) + 2);
    }
    state_flags = ((S_800917EC_3 *)state)->unk_08;
    if ((state_flags & 0xF000) && (state_flags & 0x20)) {
        temp_v0_3 = arg0->unk_3E - 1;
        arg0->unk_3E = (u16)temp_v0_3;
        func_80094944(temp_v0_3, 8);
        func_80094C1C(arg0);
        func_8009503C(arg1);
        func_8009196C();
        return;
    }
    func_80094048(arg0, arg1, arg2);
}
