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

void func_8008FD50(void *arg0, void *arg1, void *arg2, void *arg3) {
    State *var_v0;
    register State *state;
    u16 temp_v0;

    state = &D_80083460;
    if (state->flags & 0x80) {
        state->timer = 0;
    }
    if (state->timer != 0) {
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) ((((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20) << 0x10) - M2C_FIELD(arg1, s32 *, 0)) / state->timer);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) ((((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20) << 0x10) - M2C_FIELD(arg1, s32 *, 4)) / state->timer);
    }
    if ((M2C_FIELD(arg0, u16 *, 0xA2) & 0x100) && (state->timer == 6)) {
        func_8008D94C(arg0, arg1, arg2, arg3);
        func_8008FEF8();
        return;
    }
    if (!(M2C_FIELD(arg0, u16 *, 0xA2) & 0x10)) {
        u8 *old_table = M2C_FIELD(arg2, u8 **, 0x2C);
        u8 *table = D_800DD0E0;
        if (old_table != table) {
            M2C_FIELD(arg2, u8 **, 0x2C) = table;
            func_80048A44(arg2, table[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
        }
    }
    var_v0 = &D_80083460;
    temp_v0 = var_v0->timer - 1;
    var_v0->timer = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        var_v0->timer = 0U;
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        if ((func_80094F74(arg0, arg1, arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8008EAC8;
        }
    }
}
