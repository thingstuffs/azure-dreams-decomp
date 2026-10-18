#include "modules/town_minigame_dispatch.h"
#include "common.h"

typedef struct InputRecord InputRecord;

void change_map(InputRecord *input);
extern s32 D_800D4758[];

/* change_map_of: Change the map using the selected table entry. */
s32 change_map_of(s32 map_index) {
    change_map(D_800D4758[map_index]);
    return 0;
}
