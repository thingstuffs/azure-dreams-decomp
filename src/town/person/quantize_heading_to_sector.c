#include "common.h"
#include "shared/game_work.h"

/* D_80083160: shared state table (own view here); only the s16 field at
 * +0xC8 is read via this view. */


/* Quantizes the wrapped angle from the shared heading plus a quarter turn into sectors. */
s32 quantize_heading_to_sector(s32 referenceAngle, s16 sectorCount)
{
    GameWork *sharedState = &g_game_work;
    s16 effectiveSectorCount;
    s32 sectorAngle;
    s32 roundedAngle;

    effectiveSectorCount = sectorCount;
    if (sectorCount == 0) {
        effectiveSectorCount = 1;
    }
    sectorAngle = 0x1000 / effectiveSectorCount;
    roundedAngle = sharedState->view.camera_rotation.parts.viewAngle + (s16) sectorAngle / 2;
    roundedAngle += 0x400;
    roundedAngle -= referenceAngle;
    return (s32) (roundedAngle & 0xFFF) / (s16) sectorAngle;
}
