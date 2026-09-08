#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_80173F6C_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173F6C_5;   /* ((Rec_D_800E3D7C *)D_80083498)->unk_08.at00_pv.v in func_80173F6C */




extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80082E80[];
extern u8 D_80174C84[];
extern s16 D_80083228[5];
extern void *D_80174CE0[];
void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A152C();
M2C_UNK func_800A9C18();
M2C_UNK func_80047784();
M2C_UNK func_80172A14();
extern M2C_UNK D_801730AC;

typedef struct S_80173F6C_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x6A];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x1B];
    s8 unk_B6;
} S_80173F6C_0;   /* temp_s1 in func_80173F6C */

typedef struct S_80173F6C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80173F6C_1;   /* temp_v0 in func_80173F6C */

typedef struct S_80173F6C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173F6C_2;   /* temp_s3 in func_80173F6C */

typedef struct S_80173F6C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80173F6C_3;   /* temp_s0 in func_80173F6C */

/* Create and initialize an object with offset coordinates and directional animation. */
void func_80173F6C(void) {
    M2C_UNK unused;
    S_80173F6C_3 *sprite;
    S_80173F6C_0 *object_state;
    S_80173F6C_2 *model;
    void *object;
    u8 *origin;
    u16 sprite_flags;

    object = func_8003FD64(0x112, D_80083498);
    if (object != NULL) {
        object_state = object + 0x20;
        object_state->unk_13 = 0x18;
        object_state->unk_9A = 0;
        object_state->unk_96 = 0;
        ((S_80173F6C_1 *)object)->unk_10 = &D_801730AC;
        func_8004491C(object, D_80045340);
        origin = D_80082E80;
        model = ((S_80173F6C_1 *)object)->unk_08;
        model->unk_0A = (u16) ((S_80173F6C_5 *)(((Rec_D_800E3D7C *)D_80083498)->unk_08.at00_pv.v))->unk_0A;
        sprite = ((S_80173F6C_1 *)object)->unk_0C;
        sprite->unk_24 = (u8) (origin[0x24] + 9);
        sprite->unk_25 = (u8) (origin[0x25] - 9);
        sprite->unk_2C = D_80174C84;
        func_800A9C18(object, model, sprite, 0);
        object_state->unk_B6 = 1;
        object_state->unk_2A = 0x800;
        func_80047784(sprite, sprite->unk_2C[((s32) (*D_80083228 + 0x900) >> 9) & 7], 0);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        func_8009A3D0(sprite->unk_24, sprite->unk_25,
                      (object_state->unk_1C & 0x2000) ? 0x300 : 0x3000);
        func_8009A028(object_state);
        ((S_80173F6C_1 *)object)->unk_10 = (M2C_UNK *) ((s32) ((S_80173F6C_1 *)object)->unk_10 | 0x80000000);
        func_80172A14(object_state, model, sprite);
        sprite_flags = sprite->unk_14;
        *D_80174CE0 = object;
        sprite->unk_14 = (u16) (sprite_flags | 0x80);
        func_800A152C(0x18, 1);
    }
}
