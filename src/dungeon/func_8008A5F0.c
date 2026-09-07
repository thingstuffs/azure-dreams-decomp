#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"


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
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (s32) ((s32) ((((((Rec_D_80082E80 *)arg2)->unk_24 << 6) + 0x20) << 0x10) - ((Rec_D_800E3D7C *)arg1)->unk_00.at00_s32.v) / state->timer);
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (s32) ((s32) ((((((Rec_D_80082E80 *)arg2)->unk_25 << 6) + 0x20) << 0x10) - ((Rec_D_800E3D7C *)arg1)->unk_04.at00_s32.v) / state->timer);
    }
    if ((((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x100) && (state->timer == 6)) {
        func_8008D94C(arg0, arg1, arg2, arg3);
        func_8008FEF8();
        return;
    }
    if (!(((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x10)) {
        u8 *old_table = ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8;
        u8 *table = D_800DD0E0;
        if (old_table != table) {
            (*(u8 **)((u8 *)arg2 + (0x2C))) = table;
            func_80048A44(arg2, table[((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
        }
    }
    var_v0 = &D_80083460;
    temp_v0 = var_v0->timer - 1;
    var_v0->timer = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        var_v0->timer = 0U;
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        if ((func_80094F74(arg0, arg1, arg2, arg3) << 0x10) > 0) {
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_pm = &D_8008EAC8;
        }
    }
}
