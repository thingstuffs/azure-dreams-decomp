#include "common.h"
#include "town/scene.h"
#include "town/player.h"

/* Returns whether func_80018B00 reports zero. */
s32 is_status_zero(void) {
    return get_town_state_count() == 0;
}
