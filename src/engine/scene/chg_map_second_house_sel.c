#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/scene.h"
#include "slus/data.h"
typedef struct InputRecord InputRecord;
s32 get_player_homerank();                                /* extern */

/* Pass the selected table entry to change_map. */
void chg_map_second_house_sel(void) {
    change_map(second_house_rank_map_table[get_player_homerank()]);
}
