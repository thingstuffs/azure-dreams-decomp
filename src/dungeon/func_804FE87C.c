#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_804FE87C_0 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    u8 pad_4A[0xE];
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    s16 unk_62;
    s16 unk_64;
    s16 unk_66;
    s16 unk_68;
    u8 pad_6A[0xE];
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
} S_804FE87C_0;   /* state in func_804FE87C */


extern void func_80064F20(s32);
extern void func_80064EE0(s32, s32, s32);
extern void func_80064D50(void *);
extern void func_80064D20(void *);
extern void func_80064624(s32, s32);
extern void func_80064EC0(s32, s32, s32);
extern void func_80064F00(s32, s32);

extern u8 D_800DDC7C[];
extern u8 D_801C9E40[16];
extern u8 D_801DA714[16];

static __inline__ void set_light_vectors(S_804FE87C_0 *state, s16 x, s16 y) {
    state->unk_38 = x;
    state->unk_3A = y;
    state->unk_3C = x;
    state->unk_3E = -x;
    state->unk_40 = -y;
    state->unk_42 = -x;
    state->unk_44 = 0;
    state->unk_46 = 0;
    state->unk_48 = 0;
}

/* Initializes lighting, projection, and viewport state and selects the floor monster table. */
void func_804FE87C(void)
{
    GameWork *render_data = &gameWork;
    u8 *render_state = (u8 *)render_data + 0x18;
    void *light_matrix;

    ((S_804FE87C_0 *)render_state)->unk_88 = 0x200;
    func_80064F20(0x200);

    ((S_804FE87C_0 *)render_state)->unk_78 = 0;
    ((S_804FE87C_0 *)render_state)->unk_7C = 0;
    ((S_804FE87C_0 *)render_state)->unk_80 = 0;
    func_80064EE0(0, 0, 0);

    ((S_804FE87C_0 *)render_state)->unk_58 = 0x200;
    ((S_804FE87C_0 *)render_state)->unk_5E = 0x200;
    ((S_804FE87C_0 *)render_state)->unk_64 = 0x200;
    ((S_804FE87C_0 *)render_state)->unk_5A = -0x100;
    ((S_804FE87C_0 *)render_state)->unk_60 = -0x100;
    ((S_804FE87C_0 *)render_state)->unk_66 = -0x100;
    ((S_804FE87C_0 *)render_state)->unk_5C = 0;
    ((S_804FE87C_0 *)render_state)->unk_62 = 0;
    ((S_804FE87C_0 *)render_state)->unk_68 = 0;
    func_80064D50((u8 *)render_data + 0x70);

    light_matrix = (u8 *)render_data + 0x50;
    set_light_vectors((S_804FE87C_0 *)render_state, -0x800, 0x800);
    func_80064D20(light_matrix);

    ((S_804FE87C_0 *)render_state)->unk_84 = 0x1000;
    func_80064624(0x1000, ((S_804FE87C_0 *)render_state)->unk_88);
    func_80064EC0(0xA0, 0xA0, 0xA0);

    D_801C9E40[0x19] = 0;
    D_801C9E40[0x1A] = 0;
    D_801C9E40[0x1B] = 0;
    D_801DA714[0x19] = 0;
    D_801DA714[0x1A] = 0;
    D_801DA714[0x1B] = 0;
    func_80064F00(0xA0, 0x78);

    render_data->view.unk_000 = -0xBC;
    render_data->view.unk_002 = -0x88;
    render_data->view.unk_004 = 0x172;
    render_data->view.unk_006 = 0x19A;
    dungeonStatus.unk_18 = D_800DDC7C;
}
