#include "modules/town_town_windows.h"

/* Run both update routines on the shared state and clear the global flag. */
void func_8009CEA8(void) {
    void *state = D_80100900;

    func_8009D5C0(state);
    func_8009D73C(state);
    D_801007F8[0] = 0;
}
