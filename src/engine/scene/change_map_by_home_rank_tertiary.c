#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct InputRecord InputRecord;

void change_map(InputRecord *input);
s32 get_player_homerank();                                /* extern */
extern M2C_UNK home_rank_tertiary_map_table[];

/* Pass the selected table entry to change_map. */
void change_map_by_home_rank_tertiary(void) {
    change_map(home_rank_tertiary_map_table[get_player_homerank()]);
}
