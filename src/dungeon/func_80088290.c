#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_8008D024_arg0.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_80083120 {
    s16 field0;
    s16 field2;
    s16 field4;
    s16 field6;
} S_80083120;

extern u8 D_800DCFB0[8];
extern s16 D_80083228[5];
extern s16 D_800814E8;
extern S_80083120 D_80083120[8];

extern s16 func_80042900(void *, s32);
extern void func_80048A44(void *, u8, s32, s32);
extern s16 func_800A4474(u8, u8);
extern s16 func_8003F794(s32, s32);
extern void func_800A9024(s32);





extern void func_80094E34(Rec_func_8008D024_arg0 *);
/* Initializes action state and animation, then handles the current tile type. */
void func_8008D9F0(Rec_func_8008D024_arg0 *state, s32 unused, Rec_D_80082E80 *entity, Rec_D_800E3D7C *actor) {
    s16 tile_type;
    s16 slot_index;

    state->unk_9A = 0x25;
    state->unk_9B.as_s8 = 0;
    state->unk_8C = 0;
    func_80094E34(state);
    if (func_80042900(actor, 0xA) == 0) {
        entity->unk_2C.as_pu8 = D_800DCFB0;
        func_80048A44(entity, D_800DCFB0[((s32)(D_80083228[0] + actor->unk_2A.as_s16 + 0x100) >> 9) & 7], 0, 1);
    }
    tile_type = func_800A4474(entity->unk_24, entity->unk_25);
    if (tile_type == 3) {
        slot_index = func_8003F794(6, 0x20);
        D_800814E8 = slot_index;
        D_80083120[slot_index].field6 = 1;
        state->unk_9B.as_s8 = 0x10;
        return;
    }
    if (tile_type == 4) {
        *(s32 *)0x80012090 = 2;
        func_800A9024(2);
    }
}
