#ifndef SLUS_CACHE_AFE_H
#define SLUS_CACHE_AFE_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

extern s32 VSync(s32 mode);
extern s32 func_800542BC(void);

/* Cached upper bits of VSync(1), separate from the slot selector at AFC. */
extern u16 D_80080AFE;

/* Updates the cached upper bits and calls func_800542BC when they change. */

s32 update_vsync_frame_id(s32 id_mode);
s32 func_80044618(s32 id_mode);

#endif
