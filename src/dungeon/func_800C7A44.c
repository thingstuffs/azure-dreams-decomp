#include "common.h"
#include "records/Rec_D_800E3D7C.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80099844(void *, void *);
extern void func_800A56E0(s32);
extern void func_800A6508(void);
extern void func_800C5BBC(s32, s32, s32, s32, s32, s32);
extern s32 func_800C8ABC(void *, s32, s32);
extern void func_800DC1B8(s32);
extern s32 D_800DCF0C;
extern u8 D_800E1BF3[];
extern u8 D_800E3D40[];


typedef struct S_800CD1A4_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD1A4_0_pre;   /* the 0x14 bytes before actor in func_800CD1A4, addressed as actor[-1] */


typedef struct S_800CD1A4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD1A4_1;   /* owner in func_800CD1A4 */

/* Roll the actor's trap check; on a hit mark it, play the burst at the owner's tile and raise event 0x520. */
s32 func_800CD1A4(void *actor) {
    s32 chance;
    S_800CD1A4_1 *owner;

    chance = 0x40;
    if (D_800E3D40[0] != 0) {
        chance = 0x400;
    }
    if (func_800C8ABC(actor, chance, 0x10) == 0) {
        if (((Rec_D_800E3D7C *)actor)->unk_10.at03_u8.v == 0) {
            func_800A6508();
            return 1;
        }
        return 1;
    }
    func_80099844(actor, &D_800E1BF3);
    if (((Rec_D_800E3D7C *)actor)->unk_10.at03_u8.v == 0) {
        func_800DC1B8(D_800DCF0C);
    }
    owner = ((S_800CD1A4_0_pre *)actor)[-1].unk_00;
    if (!(owner->unk_14 & 0x8000)) {
        func_800C5BBC((owner->unk_24 << 6) | 0x20,
                      (owner->unk_25 << 6) | 0x20,
                      ((Rec_D_800E3D7C *)actor)->unk_88.as_s16, 0x808080, 0x20, 0);
        func_800A56E0(0x520);
    }
    return 1;
}
