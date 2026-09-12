#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();    /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800BB2E4(); /* extern */
M2C_UNK func_800C77D0(); /* extern */
extern M2C_UNK D_80083498;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800BB55C;
extern M2C_UNK D_800BBA20;
extern M2C_UNK D_800DF3C0;

typedef struct S_800BBA40_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800BBA40_0;   /* temp_v0 in func_800BBA40 */

typedef struct S_800BBA40_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BBA40_1;   /* temp_v1 in func_800BBA40 */

typedef struct S_800BBA40_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800BBA40_2;   /* temp_v1_2 in func_800BBA40 */

typedef struct S_800BBA40_3 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0xC];
    s16 unk_28;
    s16 unk_2A;
    u8 pad_2C[0x10];
    s16 unk_3C;
    u8 pad_3E[0x1E];
    s32 unk_5C;
    s32 unk_60;
} S_800BBA40_3;   /* var_v1 in func_800BBA40 */

/* Creates an effect at the tile center and initializes its rendering and five angles. */
void *func_800BBA40(s32 tile_x, s32 tile_y, s16 pos_z, M2C_UNK transform_data, s32 scale, s32 setup_word_5c, s32 setup_word_60) {
    s32 call_data[2];
    s16 angle;
    void *effect;
    S_800BBA40_1 *position;
    S_800BBA40_2 *render_data;
    s32 held_tile_x = tile_x;
    register s16 held_pos_z ASM_REG("$21") = pos_z;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register M2C_UNK held_transform ASM_REG("$22") = transform_data;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *setup_base;

    call_data[0] = 0x01000340;
    call_data[1] = 0x01000080;
    func_800BB2E4(0, 0, call_data, 1, 0);
    effect = func_8003FD64(0x12, &D_80083498);
    if (effect != NULL) {
        s32 angle_index;
        void *setup_cursor;

        func_800A56E0(0x704);
        ((S_800BBA40_0 *)effect)->unk_10 = &D_800BB55C;
        func_8004491C(effect, &D_800BBA20);
        position = ((S_800BBA40_0 *)effect)->unk_08;
        position->unk_02 = (s16) (((s32) (held_tile_x << 0x10) >> 0xA) + 0x20);
        position->unk_06 = (s16) (((s32) (tile_y << 0x10) >> 0xA) + 0x20);
        position->unk_0A = held_pos_z;
        render_data = ((S_800BBA40_0 *)effect)->unk_0C;
        render_data->unk_08 = &D_800DF3C0;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        render_data->unk_0C = 0x808080;
        render_data->unk_06 = 8;
        func_8003DB94(effect + 0x2C, held_transform, 0);
        ASM_KEEP(held_pos_z);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_transform);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        setup_base = effect + 0x20;
        ASM_KEEP(setup_base);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        setup_cursor = setup_base;
        ((S_800BBA40_3 *)setup_cursor)->unk_2A = (s16) scale;
        ((S_800BBA40_3 *)setup_cursor)->unk_28 = (s16) scale;
        ((S_800BBA40_3 *)setup_cursor)->unk_18 = 0x808080;
        angle = -0x400;
        ((S_800BBA40_3 *)setup_cursor)->unk_5C = setup_word_5c;
        angle_index = 0;
        ((S_800BBA40_3 *)setup_cursor)->unk_60 = setup_word_60;
        do {
            ((S_800BBA40_3 *)setup_cursor)->unk_3C = angle;
            angle += 0x999;
            angle_index += 1;
            ASM_KEEP(angle_index);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            setup_cursor += 2;
        } while (angle_index < 5);
        ASM_KEEP(setup_cursor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        func_800C77D0(&D_80083498, &D_80083780, 8, 0x300);
    }
    return effect;
}

/* MECHANISM: A two-word stack array preserves both call-data initializers in the 0x40 frame.
   Guarded s2/s4/s5/s6 argument holds reproduce the callee-saved prologue order.
   A pinned v0 split base copies into v1; the pinned a0 counter blocks countdown strength reduction. */
