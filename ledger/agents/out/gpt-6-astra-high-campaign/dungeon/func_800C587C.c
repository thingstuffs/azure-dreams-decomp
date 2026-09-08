#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800CAFDC_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800CAFDC_5;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_800CAFDC */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s16 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800CAED0;
extern M2C_UNK D_800E03B0;

typedef struct S_800CAFDC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800CAFDC_0;   /* temp_v0 in func_800CAFDC */

typedef struct S_800CAFDC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0x2];
    s16 unk_16;
} S_800CAFDC_1;   /* temp_s1 in func_800CAFDC */

typedef struct S_800CAFDC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800CAFDC_2;   /* temp_v1 in func_800CAFDC */

typedef struct S_800CAFDC_3 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x18];
    s16 unk_B0;
} S_800CAFDC_3;   /* temp_s0 in func_800CAFDC */

/* Spawns two salam particles near the source with randomized positions and velocities. */
void func_800CAFDC(Rec_D_800E3D7C *source, s16 effect_param, s32 render_param) {
    s16 angle;
    s32 remaining;
    S_800CAFDC_3 *effect_state;
    S_800CAFDC_1 *motion;
    void *particle;
    S_800CAFDC_2 *render;

    remaining = 2;
    do {
        particle = func_8003FD64(0x212, source);
        if (particle != NULL) {
            ((S_800CAFDC_0 *)particle)->unk_10 = &D_800CAED0;
            func_8004491C(particle, &D_80045340);
            motion = ((S_800CAFDC_0 *)particle)->unk_08;
            motion->unk_02 = (s16) ((((S_800CAFDC_5 *)(source->unk_08.at00_pv.v))->unk_02 + (rand() & 0x3F)) - 0x20);
            motion->unk_06 = (s16) ((((S_800CAFDC_5 *)(source->unk_08.at00_pv.v))->unk_06 + (rand() & 0x3F)) - 0x20);
            motion->unk_0A = (s16) ((((S_800CAFDC_5 *)(source->unk_08.at00_pv.v))->unk_0A + (rand() & 0x3F)) - 0x20);
            angle = rand();
            motion->unk_0C = (s32) (func_80064584(angle) << 5);
            motion->unk_10 = (s32) (func_800644B8(angle) << 5);
            motion->unk_16 = (s16) ((0 - (rand() & 7)) - 8);
            render = ((S_800CAFDC_0 *)particle)->unk_0C;
            effect_state = particle + 0x20;
            render->unk_1E = 0x1000;
            render->unk_1C = 0x1000;
            render->unk_08 = &D_800E03B0;
            render->unk_0C = render_param;
            render->unk_06 = 8;
            effect_state->unk_B0 = effect_param;
            effect_state->unk_96 = (s16) ((rand() & 0xFF) | 0x80);
        }
        remaining -= 1;
    } while (remaining > 0);
}
