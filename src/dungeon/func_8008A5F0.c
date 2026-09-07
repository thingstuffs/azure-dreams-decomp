#include "common.h"

typedef s32 M2C_UNK;

typedef struct {
    s16 unk0;
    u16 flags;
    s16 timer;
    s16 pad[4];
} State;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80048A44(void *, s16, s16, s32);
extern void func_8008D94C(void *, void *, void *, void *);
extern void func_8008FEF8(void);
extern s32 func_80094F74(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);

extern s16 D_80083228;
extern State D_80083460;
extern M2C_UNK D_8008EAC8;
extern u8 D_800DD0E0[];


typedef struct S_8008FD50_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8008FD50_0;   /* arg1 in func_8008FD50 */

typedef struct S_8008FD50_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8008FD50_1;   /* arg2 in func_8008FD50 */

typedef struct S_8008FD50_2 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x12];
    u16 unk_A2;
} S_8008FD50_2;   /* arg0 in func_8008FD50 */

typedef struct S_8008FD50_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_8008FD50_3;   /* arg3 in func_8008FD50 */

void func_8008FD50(void *arg0, void *arg1, void *arg2, void *arg3) {
    State *var_v0;
    register State *state;
    u16 temp_v0;

    state = &D_80083460;
    if (state->flags & 0x80) {
        state->timer = 0;
    }
    if (state->timer != 0) {
        ((S_8008FD50_0 *)arg1)->unk_0C = (s32) ((s32) ((((((S_8008FD50_1 *)arg2)->unk_24 << 6) + 0x20) << 0x10) - ((S_8008FD50_0 *)arg1)->unk_00) / state->timer);
        ((S_8008FD50_0 *)arg1)->unk_10 = (s32) ((s32) ((((((S_8008FD50_1 *)arg2)->unk_25 << 6) + 0x20) << 0x10) - ((S_8008FD50_0 *)arg1)->unk_04) / state->timer);
    }
    if ((((S_8008FD50_2 *)arg0)->unk_A2 & 0x100) && (state->timer == 6)) {
        func_8008D94C(arg0, arg1, arg2, arg3);
        func_8008FEF8();
        return;
    }
    if (!(((S_8008FD50_2 *)arg0)->unk_A2 & 0x10)) {
        u8 *old_table = ((S_8008FD50_1 *)arg2)->unk_2C;
        u8 *table = D_800DD0E0;
        if (old_table != table) {
            (*(u8 **)((u8 *)arg2 + (0x2C))) = table;
            func_80048A44(arg2, table[((s32) (D_80083228 + ((S_8008FD50_3 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
        }
    }
    var_v0 = &D_80083460;
    temp_v0 = var_v0->timer - 1;
    var_v0->timer = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        var_v0->timer = 0U;
        ((S_8008FD50_0 *)arg1)->unk_14 = 0;
        ((S_8008FD50_0 *)arg1)->unk_10 = 0;
        ((S_8008FD50_0 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_8008FD50_1 *)arg2)->unk_24, ((S_8008FD50_1 *)arg2)->unk_25);
        if ((func_80094F74(arg0, arg1, arg2, arg3) << 0x10) > 0) {
            ((S_8008FD50_2 *)arg0)->unk_8C = &D_8008EAC8;
        }
    }
}
