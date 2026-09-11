#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80064624();                /* extern */
M2C_UNK func_80064D20();                      /* extern */
M2C_UNK func_80064D50();                      /* extern */
M2C_UNK func_80064EC0();   /* extern */
M2C_UNK func_80064EE0();   /* extern */
M2C_UNK func_80064F00();            /* extern */
M2C_UNK func_80064F20();                     /* extern */
extern M2C_UNK D_8006ADBC;
extern u8 D_80083160[];
extern u8 D_801C9E40[16];
extern u8 D_801DA714[];

typedef struct S_800AB7FC_0 {
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
    u8 pad_8C[0x4];
    u8 unk_90;
    u8 unk_91;
    u8 unk_92;
} S_800AB7FC_0;   /* temp_s0 in func_800AB7FC */

typedef struct S_800AB7FC_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_800AB7FC_1;   /* temp_global_a0 in func_800AB7FC */

typedef struct S_800AB7FC_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800AB7FC_2;   /* temp_s1 in func_800AB7FC */

/* Initialize town projection, lighting, view bounds, and color state. */
void func_800AB7FC(void) {
    S_800AB7FC_0 *view_state;
    u8 *render_data;
    s32 screen_distance;
    void *light_matrix;
    S_800AB7FC_1 *scene_state;
    s32 light_coeff_a;
    s32 light_coeff_b;
    s32 ambient_red;
    s32 ambient_green;
    s32 ambient_blue;
    u8 *color_data;

    render_data = D_80083160;
    view_state = render_data + 0x18;
    screen_distance = 0x200;
    view_state->unk_88 = screen_distance;
    func_80064F20(screen_distance);
    view_state->unk_78 = 0;
    view_state->unk_7C = 0;
    view_state->unk_80 = 0;
    func_80064EE0(0, 0, 0);
    view_state->unk_5A = -0x100;
    view_state->unk_60 = -0x100;
    view_state->unk_66 = -0x100;
    view_state->unk_5C = 0;
    view_state->unk_62 = 0;
    view_state->unk_68 = 0;
    func_80064D50(render_data + 0x70);
    light_matrix = render_data + 0x50;
    do {
        light_coeff_b = -0x800;
    } while (0);
    light_coeff_a = 0x800;
    ASM_KEEP(light_coeff_a);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    view_state->unk_38 = light_coeff_b;
    view_state->unk_3C = light_coeff_b;
    light_coeff_b = 0x800;
    view_state->unk_3A = light_coeff_a;
    light_coeff_a = -0x800;
    view_state->unk_3E = light_coeff_b;
    view_state->unk_40 = light_coeff_a;
    view_state->unk_42 = light_coeff_b;
    view_state->unk_44 = 0;
    view_state->unk_46 = 0;
    view_state->unk_48 = 0;
    func_80064D20(light_matrix);
    view_state->unk_84 = 0x1000;
    func_80064624(0x1000, view_state->unk_88);
    scene_state = &D_8006ADBC;
    if ((scene_state->unk_18 == 0xC) && (scene_state->unk_1A != 0x34)) {
        ambient_red = 0xA0;
        ambient_green = ambient_red;
        ambient_blue = ambient_red;
        view_state->unk_58 = screen_distance;
        view_state->unk_5E = screen_distance;
        view_state->unk_64 = screen_distance;
    } else {
        ambient_red = 0xB0;
        ambient_green = ambient_red;
        ambient_blue = ambient_red;
        view_state->unk_58 = 0x3C0;
        view_state->unk_5E = 0x3C0;
        view_state->unk_64 = 0x3C0;
    }
    func_80064EC0(ambient_red, ambient_green, ambient_blue);
    func_80064F00(0xA0, 0x78);
    ((S_800AB7FC_2 *)render_data)->unk_18 = -0xBC;
    ((S_800AB7FC_2 *)render_data)->unk_1A = -0x88;
    ((S_800AB7FC_2 *)render_data)->unk_1C = 0x172;
    ((S_800AB7FC_2 *)render_data)->unk_1E = 0x19A;
    view_state->unk_90 = 0x80;
    view_state->unk_91 = 0x80;
    view_state->unk_92 = 0x80;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    color_data = D_801C9E40;
    color_data[0x19] = 0;
    color_data[0x1A] = 0;
    color_data[0x1B] = 0;
    color_data = D_801DA714;
    color_data[0x19] = 0;
    color_data[0x1A] = 0;
    color_data[0x1B] = 0;
}
