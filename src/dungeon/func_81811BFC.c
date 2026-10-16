#include "modules/dungeon_ovl_1831370.h"

u32 dungeonHasAvailableObject(void *object) {
    if (object != 0) {
        if (*(s32 *)((s8 *)object + 0x28) == 0) {
            return 1;
        }
    }
    return 0;
}
