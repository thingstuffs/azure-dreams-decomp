#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s8 D_80082710;
extern void D_800C5620();
extern s32 D_800D5360[];


/* Initialize the actor, clear the shared flag, and set its handler and counter. */
void initialize_actor_clear_shared_flag(Rec_func_80094268_arg0 *actor, s32 unused, void *init_param) {
    initialize_object_entries((Struct800C5724 *)(actor), init_param, D_800D5360);
    D_80082710 = 0;
    actor->unk_54 = &D_800C5620;
    actor->unk_6C.as_s16 = 0x15;
}
