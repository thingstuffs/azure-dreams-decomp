#include "common.h"
#include "shared/dungeon_effect_source.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_7FFE7CBC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
    u8 pad_30[0xE];
    s16 unk_3E;
    u8 pad_40[0x4];
    void * unk_44;
} S_7FFE7CBC_0;

typedef struct S_7FFE7CBC_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_7FFE7CBC_1;



typedef struct S_7FFE7CBC_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_7FFE7CBC_3;   /* arg0 in create_colored_source_effect */

typedef struct S_7FFE7CBC_4 {
    u8 pad_00[0xC];
    union {
        struct { u8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFE7CBC_4;

   /* ((S_7FFE7CBC_3 *)arg0)->unk_08 in create_colored_source_effect */



M2C_UNK func_7003A7C4();
void *func_7003CF18();
extern u16 emitted_effect_counter[5];
extern M2C_UNK D_8010AC34;

/* Creates an effect at the source position with the given color. */
void create_colored_source_effect(S_7FFE7CBC_3 *source, s32 color) {
    s32 effect_color;
    S_7FFE7CBC_1 *render_state;
    S_7FFE7CBC_4 *render_data;
    S_7FFE7CBC_0 *effect;
    MovingPosition *position;

    effect = func_7003CF18(0x12);
    if (effect != NULL) {
        render_state = effect->unk_0C;
        effect->unk_10 = &D_8010AC34;
        effect->unk_44 = source;
        effect->unk_3E = 0x3C;
        render_state->unk_10 = 0x20;
        render_state->unk_14 =
            (u16)(render_state->unk_14 | 0xC);
        position = effect->unk_08;
        position->unk_02 =
            (u16)((MovingPosition *)(source->unk_08))->unk_02;
        position->unk_06 =
            (u16)((MovingPosition *)(source->unk_08))->unk_06;
        position->unk_0A =
            (u16)((MovingPosition *)(source->unk_08))->unk_0A;
        render_data = effect->unk_0C;
        render_data->unk_0C.at02.v = 0x80;
        render_data->unk_0C.at01.v = 0x80;
        render_data->unk_0C.at00.v = 0x80;
        effect_color = *(s32 *)&color;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        render_data->unk_0C.at00u.v = effect_color;
        effect->unk_2C = effect_color;
        render_data->unk_12 = 0x7DCE;
        render_data->unk_14 =
            (u16)(render_data->unk_14 | 0x100);
        func_7003A7C4(render_data, positioned_effect_source, 0);
        emitted_effect_counter[0] += 1;
    }
}
