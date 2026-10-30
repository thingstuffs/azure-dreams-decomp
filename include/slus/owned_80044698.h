#ifndef SLUS_OWNED_80044698_H
#define SLUS_OWNED_80044698_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

extern s32 read_sound_mode_blocking_status(s32 a0);
extern s16 SD_Call(s32 a0);
extern s32 update_vsync_frame_id(s32 id_mode);
extern void func_80044618(s32 a0);
extern s32 VSync(s32 mode);

extern u16 sound_idle_vsync_frame_alias;

/* Pumps frames until polling returns zero, handling the first poll and caching the VSync field. */

void wait_until_sound_idle(void);
void func_80044698(void);

#endif
