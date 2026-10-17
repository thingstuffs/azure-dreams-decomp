#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_8009A344_1 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_8009A344_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in townInitializePlayerMotionParameters */


extern void townCallTheHandlerSelectsNonzeroEntry(M2C_UNK entries, void *record, M2C_UNK handler_param);
extern void townSetPlayerTravelTiming(void *actor, M2C_UNK motion, M2C_UNK context);



/* Initialize the record from linked data and apply its update parameters. */
void townInitializePlayerMotionParameters(void *record, M2C_UNK update_value, M2C_UNK init_context) {
    townCallTheHandlerSelectsNonzeroEntry(((S_8009A344_1 *)(((Rec_func_80094268_arg0 *)record)->unk_44))->unk_24, record, init_context);
    townSetPlayerTravelTiming(record, update_value, init_context);
}
