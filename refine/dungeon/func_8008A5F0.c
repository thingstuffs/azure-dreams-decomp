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
extern s32 func_80094F74(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);

extern s16 D_80083228;
extern State D_80083460;
extern M2C_UNK D_8008EAC8;
extern u8 D_800DD0E0[];

/* Updates movement toward the destination tile and handles arrival when the timer expires. */
void func_8008FD50(void *actor, void *motion, void *sprite, void *facing) {
    State *timer_state;
    register State *state;
    u16 ticks_left;

    state = &D_80083460;
    if (state->flags & 0x80) {
        state->timer = 0;
    }
    if (state->timer != 0) {
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (s32) ((s32) ((((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 0x10) - ((Rec_D_800E3D7C *)motion)->unk_00.at00_s32.v) / state->timer);
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (s32) ((s32) ((((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 0x10) - ((Rec_D_800E3D7C *)motion)->unk_04.at00_s32.v) / state->timer);
    }
    if ((((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x100) && (state->timer == 6)) {
        func_8008D94C(actor, motion, sprite, facing);
        return;
    }
    if (!(((Rec_func_8008ACDC_arg0 *)actor)->unk_A2 & 0x10)) {
        u8 *old_anim_table = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;
        u8 *anim_table = D_800DD0E0;
        if (old_anim_table != anim_table) {
            (*(u8 **)((u8 *)sprite + (0x2C))) = anim_table;
            func_80048A44(sprite, anim_table[((s32) (D_80083228 + ((Rec_D_800E3D7C *)facing)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
        }
    }
    timer_state = &D_80083460;
    ticks_left = timer_state->timer - 1;
    timer_state->timer = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        timer_state->timer = 0U;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if ((func_80094F74(actor, motion, sprite, facing) << 0x10) > 0) {
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_8C.as_pm = &D_8008EAC8;
        }
    }
}
