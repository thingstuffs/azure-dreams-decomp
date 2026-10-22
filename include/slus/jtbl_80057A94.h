#ifndef SLUS_JTBL_80057A94_H
#define SLUS_JTBL_80057A94_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

#include "common.h"

typedef struct {
    u8 pad00[0x4C];
    u8 f4C;
    u8 f4D;
    u8 f4E;
} S_80057A94;

typedef struct {
    u8 pad00[1];
    u8 x1;
    u8 pad2[4];
    u8 x6;
    u8 x7;
    u8 pad8[8];
    u16 h10;
    u16 h12;
} S_80057A94_cell;

typedef struct {
    s32 type;
    s32 f4;
    s16 x;
    s16 y;
    s32 fc;
    s32 f10;
    s32 f14;
} S_80057A94_msg;

extern s32 audio_get_current_bank_tone_record(void *row, s32 column);
extern s32 is_tone_parameter_flag_set(void);
extern void SpuSetReverb(s32 enable);
extern s32 SpuSetReverbModeParam(void *settings);

extern u8 sound_ram_reserve_mode[0x10];

/* Apply a command value to a cell field or dispatch a control message. */

void apply_tone_parameter_command(S_80057A94 *command);
void func_80057A94(S_80057A94 *command);

#endif
