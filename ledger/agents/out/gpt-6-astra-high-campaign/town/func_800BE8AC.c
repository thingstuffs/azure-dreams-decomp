#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800BC00C_0 {
    u16 unk_00;
    u8 pad_02[0xC];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x2];
    s16 unk_4E;
} S_800BC00C_0;   /* arg0 in func_800BC00C; pointer addresses record offset 0x2 */


typedef struct S_800BC00C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC00C_2;   /* arg1 in func_800BC00C */


typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
} State1;

M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[3];

/* Update effect motion, size and brightness, then mark it finished. */
s32 func_800BC00C(void *effect_fields, S_800BC00C_2 *position, Rec_D_80082E80 *sprite) {
    s16 state;
    s32 fade_end_state;
    s32 global_flags;
    s32 grow_end_state;
    u16 size;

    ((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_4A = (u16) (((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_4A - 1);
    func_800478B8(sprite);
    state = ((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_4E;
    if (state == 1) {
        goto fade;
    }
    if (state >= 2) {
        goto check_finished;
    }
    if (state == 0) {
        goto grow;
    }
    return;

check_finished:
    if (state == 0xFF) {
        goto finished;
    }
    return 255;

grow:
    size = sprite->unk_1C.at02_u16.v + 0x80;
    sprite->unk_1C.at02_u16.v = size;
    sprite->unk_1C.at00_u16.v = size;
    sprite->unk_0C.at00_s32.v = (s32) (sprite->unk_0C.at00_s32.v + 0x80808);
    position->unk_02 = (s16) ((u16) position->unk_02 + ((s32) (((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_0E - position->unk_02) >> 2));
    position->unk_06 = (s16) ((u16) position->unk_06 + ((s32) (((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_10 - position->unk_06) >> 2));
    position->unk_0A = (s16) ((u16) position->unk_0A + ((s32) (((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_12 - position->unk_0A) >> 2));
    grow_end_state = 0xFF;
    if ((s16) ((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_4A > 0) {
        goto grow_done;
    }
    ((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_4E = grow_end_state;
grow_done:
    return grow_end_state;

fade:
    {
        State1 *motion = (State1 *)position;
        motion->f0 = motion->f0 + motion->fc;
        motion->f4 = motion->f4 + motion->f10;
        motion->f8 = motion->f8 + motion->f14;
        motion->fc = motion->fc - (motion->fc >> 3);
        motion->f10 = motion->f10 - (motion->f10 >> 3);
        motion->f14 = motion->f14 - (motion->f14 >> 3);
    }
    sprite->unk_0C.at00_s32.v = (s32) (sprite->unk_0C.at00_s32.v + 0xFFF7F7F8);
    fade_end_state = 0xFF;
    if ((u8) sprite->unk_0C.at00_s32.v == 0) {
        return (((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_4E = fade_end_state);
    }
    return fade_end_state;

finished:
    ((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_00 = (u16) (((S_800BC00C_0 *)((u8 *)effect_fields - 0x2))->unk_00 | 0x8000);
    global_flags = D_800814A0[0] | 0x8000;
    D_800814A0[0] = global_flags;
    return global_flags;
}
