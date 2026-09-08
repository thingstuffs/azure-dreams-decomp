#include "common.h"

/* S_80079970: playback rate/queue slot. Field at offset 0 is read/written
 * as a plain u16 (low half of a padded 32-bit slot); offset 4 aliases the
 * scalar seen by sibling func_8005D1D0/w_8005E7E0 as D_80079974. Padded
 * past 8 bytes so %hi/%lo (not gp_rel) addressing is used. */
typedef struct {
    u16 low16;
    u16 _pad0;
    s32 _pad1[3];
} S_80079970;
extern S_80079970 D_80079970;

/* S_80079974: playback/queue busy flag; nonzero selects the "already
 * playing" (func_8005CE98) path instead of the fresh-start (func_8005D1D0)
 * sequence. Padded so total size exceeds 8 bytes, forcing hi/lo addressing. */
typedef struct {
    s32 value;
    s32 _pad[2];
} S_80079974;
extern S_80079974 D_80079974;

/* S_80079980: shared shift/pitch amount table entry (index 0). Padded past
 * 8 bytes so hi/lo (not gp_rel) addressing is used, matching sibling views. */
typedef struct {
    s32 value;
    s32 _pad[2];
} S_80079980;
extern S_80079980 D_80079980;

extern s32 func_8005D1D0();
extern s32 func_8005CE98(s32 a0, s32 a1);

/* Starts or restarts channel playback and returns the playback parameter. */
s32 func_8005D460(s32 channel, s32 playback_param)
{
    s32 saved_channel = channel;
    s32 saved_param = playback_param;

    if (D_80079974.value != 0) {
        func_8005CE98(saved_channel, saved_param);
        return saved_param;
    }

    func_8005D1D0(2, (s32)D_80079970.low16 << D_80079980.value);
    func_8005D1D0(1);
    func_8005D1D0(3, saved_channel, saved_param);
    return saved_param;
}
