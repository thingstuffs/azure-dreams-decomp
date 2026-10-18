#include "common.h"
#include "m2c_compat.h"

#include "common.h"
typedef struct InputRecord InputRecord;
void change_map(InputRecord *input);                         /* extern */
s32 get_player_homerank();                                /* extern */
extern M2C_UNK D_8006AFDC[];

/* Pass the selected table entry to change_map. */
void chg_map_second_house_sel(void) {
    change_map(D_8006AFDC[get_player_homerank()]);
}
