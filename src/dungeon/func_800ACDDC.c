#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"


extern s32 func_800A2BDC(void *arg0);
extern void func_800ACB98(void *arg0, s32 arg1, s32 arg2, void *arg3);
extern void func_800ACD74(void *arg0, s32 arg1, s32 arg2, void *arg3);

extern s16 D_800DCE68;
extern u8 D_80083460[0x14];




typedef struct S_800B253C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x2];
    void * unk_0C;
    s32 unk_10;
} S_800B253C_2;   /* state in func_800B253C */

/* Updates actor state from pending entity flags when entity processing is allowed. */
void func_800B253C(Rec_func_800A9E70_arg0 *actor, s32 update_arg1, s32 update_arg2, Rec_D_800E3D7C *entity) {
    u8 *shared_state;
    void *active_entity;
    s32 entity_flags;
    s32 next_state;

    if ((entity->unk_1C.as_s32 & 0x2000) || (entity->unk_14.as_s32 & 0x4000)) {
        if ((u32)(actor->unk_9A.as_u8 - 0x13) >= 2U) {
            if (entity->unk_6D.as_s8 == 0) {
                if (D_800DCE68 == 0) {
                    if ((func_800A2BDC(entity) << 0x10) != 0) {
                        return;
                    }
                    goto update_state;
                }
                shared_state = D_80083460;
                active_entity = ((S_800B253C_2 *)shared_state)->unk_0C;
                if (active_entity != entity) {
                    if ((((S_800B253C_2 *)shared_state)->unk_10 == 0) && (active_entity == 0) &&
                        (((S_800B253C_2 *)shared_state)->unk_08 == 0) &&
                        !(((S_800B253C_2 *)shared_state)->unk_02 & 0x2008) &&
                        (entity->unk_43 == 0xFD)) {
                        ((S_800B253C_2 *)shared_state)->unk_0C = entity;
                        goto check_entity;
                    }
                } else {
                check_entity:
                    if (entity->unk_43 == 0xFD) {
                    update_state:
                        if (entity->unk_1C.as_s32 & 0x400000) {
                            actor->unk_8C = 0;
                            entity_flags = entity->unk_14.as_s32;
                            entity->unk_1C.as_s32 &= 0xFFBFFFFF;
                            if (entity_flags & 0x20000000) {
                                entity->unk_14.as_s32 = entity_flags | 0x400000;
                                actor->unk_AD = 0;
                                func_800ACB98(actor, update_arg1, update_arg2, entity);
                                return;
                            }
                            entity->unk_14.as_s32 = entity_flags & 0xFFBFFFFF;
                            next_state = entity_flags & 0x4000;
                            if (!next_state) {
                                next_state = 2;
                            } else {
                                next_state = 1;
                            }
                            actor->unk_9A.as_u8 = next_state;
                            goto reset_phase;
                        }
                        if (entity->unk_1C.as_s32 & 0x02000000) {
                            actor->unk_8C = 0;
                            entity->unk_71.as_u8 = 0;
                            entity->unk_1C.as_s32 &= 0xFDFFFFFF;
                            if (entity->unk_14.as_s32 & 0x20000000) {
                                func_800ACD74(actor, update_arg1, update_arg2, entity);
                                return;
                            }
                            actor->unk_9A.as_u8 = 0;
                        reset_phase:
                            actor->unk_9B.as_u8 = 0;
                        }
                    }
                }
            }
        }
    }
}
