#include "common.h"

extern s32 D_8001E954[];
extern s32 townCheckObjectCallbackReturnsTwo(void);

s32 townGetProgressStatusCode(void) {
    s32 value;
    if (D_8001E954[0] == 0) {
        return 0;
    }
    value = townCheckObjectCallbackReturnsTwo();
    if (value != 0) {
        return 2;
    }
    return 1;
}
