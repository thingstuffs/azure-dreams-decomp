#include "common.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"


extern void func_80033D08(void *);
extern void func_80095388(void *);
extern s16 func_800C2AE8(void *);
extern void func_800C8B5C(void *, void *, s32);
extern void func_800C8D34(void *, void *, s32);
extern s32 D_800D636C[2];



/* Advance motion and handle ground contact or continued movement. */
void func_800C8C3C(Rec_D_80082D58 *entity, EntityRec *motion, s32 context)
{
    s32 *velocity;
    u16 contacts_left;

    velocity = D_800D636C;
    motion->x.v += velocity[0];
    motion->y.v += velocity[1];
    motion->z.v += motion->flags14;
    if (func_800C2AE8(motion) < motion->z.w.i) {
        motion->z.w.i = func_800C2AE8(motion);
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
