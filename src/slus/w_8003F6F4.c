#include "common.h"
#include "shared/transition_slots.h"

extern int abs(int);
extern s16 func_80053428(TransitionSlot *a0);
extern s16 func_80053604(TransitionSlot *a0);
/* Processes type 5 and 6 entries in reverse order, clearing their type when handled. */
void func_8003F6F4(void)
{
    s32 entry_index;

    for (entry_index = 7; entry_index >= 0; entry_index--) {
        switch (abs(D_80083120[entry_index].type)) {
        case 5:
            if (func_80053428(&D_80083120[entry_index]) != 0) {
                D_80083120[entry_index].type = 0;
            }
            break;
        case 6:
            if (func_80053604(&D_80083120[entry_index]) != 0) {
                D_80083120[entry_index].type = 0;
            }
            break;
        }
    }
}
