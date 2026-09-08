#include "common.h"

extern void func_80018614(s32, s32, s32);
extern void func_80018674(void);

/* Forward values for code 0x1E, otherwise call the fallback handler. */
void func_800186AC(s32 first_value, s32 second_value, s32 code) {
    if (code != 0x1E) {
        func_80018674();
        return;
    }
    func_80018614(first_value, second_value, 0x1E);
}
