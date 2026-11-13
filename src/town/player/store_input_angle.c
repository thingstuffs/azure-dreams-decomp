#include "common.h"
#include "shared/game_work.h"
#include "town.h"
#include "town/player.h"
#include "town/player/record.h"

/* Sparse view of the shared global state struct D_80083160: only the two
 * fields this function reads (offsets 0x8 and 0xC8). Declared >8 bytes so
 * codegen uses %hi/%lo addressing, matching sibling functions elsewhere
 * (e.g. func_800978DC) that touch the same pair of fields. */

/* Stores the valid shared angle in the record at offset 0x10. */
void store_input_angle(void *record_arg) {
    TownPlayerRecord *record = record_arg;

    s16 angle = input_angle_with_offset(g_game_work.buttons, g_game_work.view.camera_rotation.parts.viewAngle);

    if (angle != -1) {
        record->unk_10 = angle;
    }
}
