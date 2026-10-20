#include "common.h"
#include "m2c_compat.h"

#include "common.h"
typedef struct InputRecord InputRecord;
void change_map(InputRecord *input);                         /* extern */
s32 get_player_homerank();                                /* extern */
extern M2C_UNK D_8006AFF4[];

/* Pass the selected D_8006AFF4 entry to change_map. */
void change_map_by_home_rank_secondary(void) {
    change_map(D_8006AFF4[get_player_homerank()]);
}
