#include "common.h"
#include "records/Rec_D_80082D58.h"


extern void func_80033D08(void *);
extern void func_80095388(void *);
extern s16 func_800C2AE8(void *);
extern void func_800C8B5C(void *, void *, s32);
extern void func_800C8D34(void *, void *, s32);
extern s32 D_800D636C[2];


typedef struct S_800C8C3C_0 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C8C3C_0;   /* arg1 in func_800C8C3C */


/* Advance motion and handle ground contact or continued movement. */
void func_800C8C3C(Rec_D_80082D58 *entity, S_800C8C3C_0 *motion, s32 context)
{
    s32 *velocity;
    u16 contacts_left;

    velocity = D_800D636C;
    motion->unk_00 += velocity[0];
    motion->unk_04 += velocity[1];
    motion->unk_08.at00.v += motion->unk_14;
    if (func_800C2AE8(motion) < motion->unk_08.at02.v) {
        motion->unk_08.at02.v = func_800C2AE8(motion);
        contacts_left = entity->unk_90.as_u16 - 1;
        entity->unk_90.as_u16 = contacts_left;
        if ((s16)contacts_left < 0) {
            func_80033D08(entity);
            func_800C8D34(entity, motion, context);
            return;
        }
        func_800C8B5C(entity, motion, context);
        return;
    }
    func_80095388(motion);
}
