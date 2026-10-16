/* Relink of matched dungeon/func_80F88A58; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern void func_8016582C(void *, void *, void *, void *);

s32 func_800A2BDC();
void func_800A9A0C();
s32 func_800ADDA0();
/* Update entity state and flags according to the state query result. */
s32 func_80166258(EntityRec *actor, void *primary_context, void *secondary_context, s32 force_move) {
    s16 state_type;
    s32 result;
    EntityRec *entity = actor;   /* the copy is load-bearing: it changes the callee-save order */

    state_type = (s16)func_800ADDA0(primary_context, secondary_context, entity, 3, 6, entity->pad_9C);
    if (state_type < 0) return 0;
    if ((force_move << 0x10) != 0) {
        func_8016582C(entity, primary_context, secondary_context, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        entity->unk_9A = 0xE;
        func_800A9A0C(entity);
        result = 0;
        return result;
    case 2:
        func_8016582C(entity, primary_context, secondary_context, entity);
        result = 0;
        return result;
    case 1:
        entity->unk_71 &= 0x7F;
        if ((func_800A2BDC(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        entity->unk_71 &= 0x7F;
        if ((dungeonStatus.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    entity->unk_46 &= 0x7FFF;
    return result;
}

