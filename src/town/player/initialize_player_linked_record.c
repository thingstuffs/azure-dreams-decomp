#include "common.h"
#include "town/player/scene_action_setup.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player.h"


typedef struct S_8009A1A4_2 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_8009A1A4_2;   /* ((TownObjectRecord *)arg0)->unk_44 in initialize_player_linked_record */


extern void D_80099B70();


/* Set up the object using its linked record and assign its next handler. */
void initialize_player_linked_record(TownObjectRecord *object, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) ((S_8009A1A4_2 *)object->unk_44)->unk_20, object, ptr2);
    object->unk_04.as_pm = &D_80099B70;
}
