#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern struct {
    s8 pad[0xA];
    u16 field_0xA;
} D_80083460;




/* Sets entity state 0x14, resets progress, sets status flags, and increments the global counter. */
void func_800ACB98(Rec_func_800A9E70_arg0 *entity, void *unused, Rec_D_80082E80 *status, Rec_D_800E3D7C *event_state) {
    entity->unk_9A.as_s8 = 0x14;
    entity->unk_9B.as_s8 = 0;
    entity->unk_8C = 0;
    status->unk_14.at00_u16.v = (u16)(status->unk_14.at00_u16.v | 0x800);
    entity->unk_96.as_s16 = 0;
    D_80083460.field_0xA = D_80083460.field_0xA + 1;
    event_state->unk_1C.as_s32 = (s32)(event_state->unk_1C.as_s32 | 0x10000000);
}
