#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801728B4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801728B4_0;   /* obj in func_801728B4 */

typedef struct S_801728B4_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
} S_801728B4_1;   /* entity in func_801728B4 */

typedef struct S_801728B4_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801728B4_2;   /* actor in func_801728B4 */


M2C_UNK func_8009C12C(); /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800AD594();             /* extern */
extern s32 D_8008346C;
extern M2C_UNK D_80170E5C;

/* Advances the object state from entity flags and updates the actor. */
void func_801728B4(void *obj, void *record, void *entity, void *actor) {
    s32 state;

    state = ((S_801728B4_0 *)obj)->unk_9B;
    switch (state) {
    case 0:
        if (((S_801728B4_1 *)entity)->unk_14 & 0x8000) {
            ((S_801728B4_0 *)obj)->unk_9B = 2U;
            ((S_801728B4_1 *)entity)->unk_14 =
                (u16)(((S_801728B4_1 *)entity)->unk_14 | 0x6000);
            func_8009C12C(actor, entity, ((S_801728B4_2 *)actor)->unk_2A, 1);
            return;
        }
        ((Rec_D_800E3D7C *)record)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)record)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)record)->unk_0C.as_s32 = 0;
        ((S_801728B4_0 *)obj)->unk_9B =
            (u8)(((S_801728B4_0 *)obj)->unk_9B + 1);
        return;

    case 1:
        if ((((S_801728B4_1 *)entity)->unk_04 == 7) &&
            (((S_801728B4_1 *)entity)->unk_14 & 0x1000)) {
            func_800A56E0(0x808);
        }
        if (((((S_801728B4_1 *)entity)->unk_04 == 9) &&
             (((S_801728B4_1 *)entity)->unk_14 & 0x1000)) ||
            (((S_801728B4_1 *)entity)->unk_14 & 0xE000)) {
            func_8009C12C(actor, entity, ((S_801728B4_2 *)actor)->unk_2A, 1);
            ((S_801728B4_0 *)obj)->unk_9B =
                (u8)(((S_801728B4_0 *)obj)->unk_9B + 1);
        } else {
            return;
        }
        /* fall through */

    case 2:
        if (!(((S_801728B4_1 *)entity)->unk_14 & 0xE000)) {
            return;
        }
        func_800AD594(actor, 0x100);
        ((S_801728B4_0 *)obj)->unk_8C = &D_80170E5C;
        D_8008346C = 0;
        ((S_801728B4_2 *)actor)->unk_46 =
            (u16)((*(u16 *)((u8 *)actor + 0x46)) & 0x7FFF);
        func_800A4ACC(actor);
        break;

    default:
        break;
    }
}
