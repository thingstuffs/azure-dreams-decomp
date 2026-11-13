#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_payload.h"
#include "town/player/coordinates.h"
#include "town/player.h"


   /* ((S_8001ACA0_3 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68 in copy_scene_payload_position */





/* Copy three 16-bit components from the current nested record to the output. */
void copy_scene_payload_position(void *output) {
    MovingPosition *source_record;
    u16 *components;

    components = output;
    source_record = ((ObjectPayloadView *)(town_scene_root->unk_24->unk_68))->unk_08;
    components[0] = (u16) source_record->x;
    components[1] = (u16) source_record->y;
    components[2] = (u16) source_record->z;
}
