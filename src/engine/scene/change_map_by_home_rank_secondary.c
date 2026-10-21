#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/scene.h"
#include "slus/data.h"
typedef struct InputRecord InputRecord;
s32 get_player_homerank();                                /* extern */

/* Pass the selected D_8006AFF4 entry to change_map. */
void change_map_by_home_rank_secondary(void) {
    change_map(home_rank_secondary_map_table[get_player_homerank()]);
}
