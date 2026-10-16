#include "common.h"

extern void townAdvanceDispatchStateToTwo(void);
extern u8 D_8001601C[];
extern u8 D_80017774[];
extern u8 D_80022E7E[];

/* Select data by mode, calling townAdvanceDispatchStateToTwo for mode one. */
void *townSelectEventDataWithMode1Setup(s32 setup_value, s32 setup_option, s32 mode) {
    if (mode == 1) {
        townAdvanceDispatchStateToTwo();
        return D_80022E7E;
    } else if (mode == 4) {
        return D_8001601C;
    } else {
        return D_80017774;
    }
}
