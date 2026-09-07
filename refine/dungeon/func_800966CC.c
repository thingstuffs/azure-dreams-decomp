#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009BE2C_0 {
    void * unk_00;
} S_8009BE2C_0;   /* &D_80083160 in func_8009BE2C */

typedef struct S_8009BE2C_1 {
    u8 pad_00[0x3];
    s8 unk_03;
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} S_8009BE2C_1;   /* temp_s0 in func_8009BE2C */

typedef struct S_8009BE2C_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
} S_8009BE2C_2;   /* arg2 in func_8009BE2C */

typedef struct S_8009BE2C_3 {
    void * unk_00;
} S_8009BE2C_3;   /* temp_s1 in func_8009BE2C */

typedef struct S_8009BE2C_4_pre {
    u16 unk_00;
} S_8009BE2C_4_pre;   /* the 0x2 bytes before arg0 in func_8009BE2C, addressed as arg0[-1] */

typedef struct S_8009BE2C_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_8009BE2C_5;   /* ((S_8009BE2C_0 *)(&D_80083160))->unk_00 in func_8009BE2C */

typedef struct S_8009BE2C_6 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_8009BE2C_6;   /* ((S_8009BE2C_3 *)temp_s1)->unk_00 in func_8009BE2C */


/* cfail-repair: tf7-phase1-cache-v3 */
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern s32 D_800814A0[3];
M2C_UNK func_8006658C();              /* extern */
M2C_UNK func_800667A8();                  /* extern */

/* Draw a full-screen fade and mark the effect complete when its countdown ends. */
void func_8009BE2C(void *effect, s32 unused, S_8009BE2C_2 *fade) {
    s32 intensity;
    s16 color_value;
    s8 frames_left;
    void *packet;
    void **render_context;

    packet = ((S_8009BE2C_5 *)(((S_8009BE2C_0 *)(&D_80083160))->unk_00))->unk_8D0;
    ((S_8009BE2C_5 *)(((S_8009BE2C_0 *)(&D_80083160))->unk_00))->unk_8D0 = (void *) (packet + 0x10);
    ((S_8009BE2C_1 *)packet)->unk_0C = 0x140;
    ((S_8009BE2C_1 *)packet)->unk_08 = 0;
    ((S_8009BE2C_1 *)packet)->unk_0A = 0;
    ((S_8009BE2C_1 *)packet)->unk_0E = 0xE0;
    intensity = (0xC0 / (s16) fade->unk_06) * fade->unk_05;
    color_value = intensity;
    render_context = (void **)&D_80083160;
    if (fade->unk_04 == 0) {
        goto set_word;
    }
    ((S_8009BE2C_1 *)packet)->unk_04.at02.v = color_value;
    ((S_8009BE2C_1 *)packet)->unk_04.at01.v = color_value;
    ((S_8009BE2C_1 *)packet)->unk_04.at00.v = color_value;
    goto set_done;

set_word:
    {
        ((S_8009BE2C_1 *)packet)->unk_04.at00u.v = (s32) (s16) color_value;
    }

set_done:
    func_800667A8(packet, intensity);
    ((S_8009BE2C_1 *)packet)->unk_04.at03.v = (u8) (((S_8009BE2C_1 *)packet)->unk_04.at03.v | 2);
    func_8006658C(((S_8009BE2C_3 *)render_context)->unk_00 + 0xB0, packet);
    packet = ((S_8009BE2C_6 *)(((S_8009BE2C_3 *)render_context)->unk_00))->unk_8D0;
    ((S_8009BE2C_6 *)(((S_8009BE2C_3 *)render_context)->unk_00))->unk_8D0 = (void *) (packet + 0xC);
    ((S_8009BE2C_1 *)packet)->unk_03 = 1;
    ((S_8009BE2C_1 *)packet)->unk_04.at00u.v = 0xE1000020;
    func_8006658C(((S_8009BE2C_3 *)render_context)->unk_00 + 0xB0, packet);
    frames_left = (u8) fade->unk_05 - 1;
    fade->unk_05 = frames_left;
    if ((frames_left << 0x18) == 0) {
        ((S_8009BE2C_4_pre *)effect)[-1].unk_00 = (u16) (((S_8009BE2C_4_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
