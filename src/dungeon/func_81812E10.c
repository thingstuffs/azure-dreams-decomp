#include "modules/dungeon_ovl_1831cd8.h"

void func_80027E10(s32 *countdownState) {
    D_80029524[countdownState[5]](countdownState);
    countdownState[0]--;
    if (countdownState[0] < 0) {
        countdownState[0] = 0;
        countdownState[-4] = (s32)(void *)func_80027A88;
    }
    func_80027A20(countdownState);
}
