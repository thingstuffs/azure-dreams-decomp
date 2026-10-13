#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

void func_80064624(s32, s32);                /* extern */
void func_80064D20(void *);                      /* extern */
void func_80064D50(void *);                      /* extern */
void func_80064EC0(s32, s32, s32);   /* extern */
void func_80064EE0(s32, s32, s32);   /* extern */
void func_80064F00(s32, s32);            /* extern */
void func_80064F20(s32);                     /* extern */
extern M2C_UNK D_8006ADBC;
/* Retail writes +0x19..+0x1B; the asset allocation extent is not established here. */
extern u8 D_801C9E40[];
extern u8 D_801DA714[];

typedef struct S_800AB7FC_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_800AB7FC_1;   /* temp_global_a0 in func_800AB7FC */

/* Initialize town projection, lighting, view bounds, and color state. */
void func_800AB7FC(void) {
    GameView *view_state;
    GameWork *render_data;
    s32 screen_distance;
    S_800AB7FC_1 *scene_state;
    s32 light_negative;
    s32 light_positive;
    s32 ambient_red;
    s32 ambient_green;
    s32 ambient_blue;

    render_data = &gameWork;
    view_state = &render_data->view;
    screen_distance = 0x200;
    view_state->unk_088 = screen_distance;
    func_80064F20(screen_distance);
    view_state->unk_078 = 0;
    view_state->unk_07C = 0;
    view_state->unk_080 = 0;
    func_80064EE0(0, 0, 0);
    view_state->unk_05A = -0x100;
    view_state->unk_060 = -0x100;
    view_state->unk_066 = -0x100;
    view_state->unk_05C = 0;
    view_state->unk_062 = 0;
    view_state->unk_068 = 0;
    func_80064D50((u8 *)render_data + 0x70);
    scene_state = (u8 *)render_data + 0x50;
    light_negative = -0x800;
    view_state->unk_038 = light_negative;
    view_state->unk_03A = 0x800;
    view_state->unk_03C = light_negative;
    light_positive = 0x800;
    view_state->unk_03E = light_positive;
    view_state->unk_040 = -0x800;
    view_state->unk_042 = light_positive;
    view_state->unk_044 = 0;
    view_state->unk_046 = 0;
    view_state->unk_048 = 0;
    func_80064D20(scene_state);
    view_state->unk_084 = 0x1000;
    func_80064624(0x1000, view_state->unk_088);
    scene_state = &D_8006ADBC;
    if ((scene_state->unk_18 == 0xC) && (scene_state->unk_1A != 0x34)) {
        ambient_red = 0xA0;
        ambient_green = ambient_red;
        ambient_blue = ambient_red;
        view_state->unk_058 = screen_distance;
        view_state->unk_05E = screen_distance;
        view_state->unk_064 = screen_distance;
    } else {
        ambient_red = 0xB0;
        ambient_green = ambient_red;
        ambient_blue = ambient_red;
        view_state->unk_058 = 0x3C0;
        view_state->unk_05E = 0x3C0;
        view_state->unk_064 = 0x3C0;
    }
    func_80064EC0(ambient_red, ambient_green, ambient_blue);
    func_80064F00(0xA0, 0x78);
    render_data->view.unk_000 = -0xBC;
    render_data->view.unk_002 = -0x88;
    render_data->view.unk_004 = 0x172;
    render_data->view.unk_006 = 0x19A;
    view_state->unk_090 = 0x80;
    view_state->unk_091 = 0x80;
    view_state->unk_092 = 0x80;
    D_801C9E40[0x19] = 0;
    D_801C9E40[0x1A] = 0;
    D_801C9E40[0x1B] = 0;
    D_801DA714[0x19] = 0;
    D_801DA714[0x1A] = 0;
    D_801DA714[0x1B] = 0;
}
