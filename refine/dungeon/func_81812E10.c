#include "common.h"

extern void (*D_80029524[])(void);
extern void func_80027A20(s32 *);
extern s32 D_80027A88[];

// Dispatches a callback, decrements the countdown, and resets the state pointer on expiry.
void func_80027E10(s32 *countdownState) {
    D_80029524[countdownState[5]]();
    countdownState[0]--;
    if (countdownState[0] < 0) {
        countdownState[0] = 0;
        countdownState[-4] = (s32)D_80027A88;
    }
    func_80027A20(countdownState);
}
