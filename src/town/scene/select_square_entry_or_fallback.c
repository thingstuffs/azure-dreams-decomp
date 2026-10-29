#include "town/scene.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"
extern u8 D_8001BB9C[];
extern u8 D_8001EA73[];
extern u8 D_8001C354[];

void *select_square_entry_or_fallback(SquareSceneEntry *entry, s32 unused, s32 selection) {
    void *records = D_8001BB9C;
    void *result;
    void *selected;
    result = apply_entry_position(records, D_8001C354, entry, selection);
    if (resolve_entry_flag(records, entry, selection) == 0) {
        selected = result;
    } else {
        selected = D_8001EA73;
    }
    return selected;
}
