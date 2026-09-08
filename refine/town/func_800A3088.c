#include "common.h"

typedef struct {
    u8 pad00[0x50];
    void *unk50;
    u8 pad54[0x68 - 0x54];
    s16 unk68;
    u8 pad6A[0x72 - 0x6A];
    s16 unk72;
} S800A3088Arg0;

typedef struct {
    u8 pad0[2];
    s16 unk2;
    u8 pad4[2];
    s16 unk6;
} S800A3088Arg2;

extern s32 func_800A0668(S800A3088Arg0 *);
extern s32 func_800A0F10(S800A3088Arg0 *arg0, s32 arg1);
extern void func_8009A674(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_800A0884[16];

/* Set the entity effect and emit it at the supplied position when the checks pass. */
void func_800A07E8(S800A3088Arg0 *entity, s32 action, S800A3088Arg2 *position) {
    register s32 saved_action;
    register S800A3088Arg2 *saved_position ASM_REG("$18");

    saved_action = action;
    saved_position = position;
    if (entity->unk68 == 0) {
        s32 state;

        state = func_800A0668(entity);
        if (state == 0) {
            if (func_800A0F10(entity, saved_action) != 0) {
                entity->unk50 = D_800A0884;
                func_8009A674(entity->unk72, saved_position->unk2, saved_position->unk6);
            }
        }
    } else if ((func_800A0668(entity) != 0) && (func_800A0F10(entity, saved_action) != 0)) {
        entity->unk50 = D_800A0884;
        func_8009A674(entity->unk72, saved_position->unk2, saved_position->unk6);
    }
}
