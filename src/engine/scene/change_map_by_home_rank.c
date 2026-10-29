#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "engine/scene.h"
#include "slus/data.h"
#include "town/shop.h"

typedef struct InputRecord InputRecord;

/* Pass the selected table entry to change_map. */
void change_map_by_home_rank(void) {
    change_map(home_rank_primary_map_table[get_player_homerank()]);
}
