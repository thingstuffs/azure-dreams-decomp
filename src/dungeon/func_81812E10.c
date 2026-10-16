#include "modules/dungeon_ovl_1831cd8.h"

void dungeonTickMenuCountdown(s32 *countdownState) {
    D_80029524[countdownState[5]](countdownState);
    countdownState[0]--;
    if (countdownState[0] < 0) {
        countdownState[0] = 0;
        countdownState[-4] = (s32)(void *)dungeonHandleMenuRecordCheck;
    }
    dungeonInvokeEnabledMenuCallback(countdownState);
}
