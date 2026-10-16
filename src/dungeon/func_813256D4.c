#include "common.h"
#include "m2c_compat.h"

/* extern */
s32 dungeonCheckActorFloorTrap();            /* extern */
extern M2C_UNK D_8016B778;

typedef struct S_8016CED4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_8016CED4_0;   /* arg0 in dungeonFinishLinkedActorMotion */


s32 dungeonUpdateLinkedActorMotion(void *, void *, void *, void *);
/* Runs the follow-up handler and assigns the shared record data when the check succeeds. */
void dungeonFinishLinkedActorMotion(S_8016CED4_0 *record, M2C_UNK check_context, M2C_UNK source, M2C_UNK target) {
    if (dungeonUpdateLinkedActorMotion(record, check_context, source, target) != 0) {
        dungeonCheckActorFloorTrap(source, target);
        record->unk_8C = &D_8016B778;
    }
}
