#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/scene.h"
#include "slus/data.h"
#include "town/shop.h"
typedef struct InputRecord InputRecord;

/* Changes to the map selected by the player home rank in home_rank_secondary_map_table. */
void change_map_by_home_rank_secondary(void) {
    change_map(home_rank_secondary_map_table[get_player_homerank()]);
}
