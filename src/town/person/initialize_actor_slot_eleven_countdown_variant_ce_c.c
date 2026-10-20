/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


extern void func_800C2E84(void *state, s8 *output, s32 *entries);

extern s32 D_800D64DC[];
extern u8 D_800C9FBC[];
extern s8 D_800826B8;


void initialize_actor_slot_eleven_countdown_variant_4ce5c(Rec_func_80094268_arg0 *actor, s32 unused, s8 *output) {
    func_800C2E84(actor, output, D_800D64DC);
    D_800826B8 = 0;
    actor->unk_54 = D_800C9FBC;
    actor->unk_6C.as_s16 = 0x8;
}
