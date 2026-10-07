#ifndef SHARED_SOUND_STATE_H
#define SHARED_SOUND_STATE_H
#include "shared/sound_volume.h"
/* Opt-in declarations: older source views can coexist during partial apply.
 * Interior symbol aliases D_80084864 / D_80084904 are not allocation evidence. */
extern SoundPlaybackState D_800847D0;
extern SoundTask D_80084858;
extern SoundTask D_800848F8;
/* The standalone +0x0C alias keeps its own relocation identity. Only word 0
 * is observed. An unsized word declaration preserves absolute addressing;
 * no array/allocation extent is claimed. */
extern int D_80084864[];
#endif
