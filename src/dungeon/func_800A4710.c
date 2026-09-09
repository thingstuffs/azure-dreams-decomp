#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern s32 func_800A9E38(void *arg0);
extern s32 func_800A2BDC(void *arg0);
extern void func_8003DB94(void *arg0, s32 arg1, s8 arg2);
extern void func_80047738(void *arg0, u8 arg1, s8 arg2);
extern void func_800478B8(void *arg0);
extern void func_800ACB98(void *arg0, s32 arg1, void *arg2, void *arg3);
extern void func_800ACD74(void *arg0, s32 arg1, void *arg2, void *arg3);

extern s16 D_80083228;
extern s16 D_800DCE68;
extern u8 D_8006CCF8[8];
extern u8 D_80083460[0x14];

typedef struct S_800A9E70_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    union { s32 * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_800A9E70_2;   /* arg2 in func_800A9E70 */

typedef struct S_800A9E70_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x2];
    void * unk_0C;
    s32 unk_10;
} S_800A9E70_3;   /* state in func_800A9E70 */

/* Updates entity facing and applies pending animation changes. */
s32 func_800A9E70(Rec_func_800A9E70_arg0 *anim, s32 action_arg, S_800A9E70_2 *sprite, Rec_D_800E3D7C *entity) {
    u8 *interaction_state;
    void *active_entity;
    s32 entity_flags;
    s32 direction;
    s32 action_type;
    u16 action_flags;

    if (entity->unk_14.as_s32 & 0x100000) {
        direction = ((D_80083228 + entity->unk_2A.as_s16 + 0x100) >> 9) & 7;
        if (anim->unk_94 != direction) {
            if (func_800A9E38(entity) != 0) {
                func_8003DB94(sprite, sprite->unk_2C.p[direction],
                              sprite->unk_04);
                anim->unk_94 = direction;
            } else {
                func_80047738(sprite, sprite->unk_2C.p2[direction],
                              sprite->unk_04);
                anim->unk_94 = direction;
            }
        }
        if (D_8006CCF8[direction] != 0) {
            sprite->unk_14 |= 1;
        } else {
            sprite->unk_14 &= 0xFFFE;
        }
        func_800478B8(sprite);
        return 1;
    }

    if (entity->unk_1C.as_s32 & 0x400) {
        action_flags = entity->unk_44.at02_u16.v;
        if (action_flags & 0x8000) {
            if (!(action_flags & 0x4000)) {
                action_type = action_flags & 0x3FFF;
                if (((u32)(action_type - 5) < 3U) || (action_type == 0xC)) {
                    entity->unk_44.at02_u16.v = action_flags & 0x7FFF;
                }
            }
        }
    }

    if (!(sprite->unk_14 & 0x8000)) {
        if (anim->unk_98 & 0x400) {
            direction = ((D_80083228 + entity->unk_2A.as_s16 + 0x100) >> 9) & 7;
            if (func_800A9E38(entity) != 0) {
                func_8003DB94(sprite, sprite->unk_2C.p[direction],
                              sprite->unk_04);
            } else {
                func_80047738(sprite, sprite->unk_2C.p2[direction],
                              sprite->unk_04);
            }
            anim->unk_98 &= 0xFBFF;
        }
    } else {
        anim->unk_98 |= 0x400;
    }

    if ((entity->unk_1C.as_s32 & 0x2000) ||
        (entity->unk_14.as_s32 & 0x4000)) {
        if ((u32)(anim->unk_9A.as_u8 - 0x13) >= 2U) {
            if (entity->unk_6D.as_s8 == 0) {
                if (D_800DCE68 == 0) {
                    if ((func_800A2BDC(entity) << 0x10) != 0) {
                        return 0;
                    }
                    goto update_anim;
                }
                interaction_state = D_80083460;
                active_entity = ((S_800A9E70_3 *)interaction_state)->unk_0C;
                if (active_entity != entity) {
                    if ((((S_800A9E70_3 *)interaction_state)->unk_10 == 0) && (active_entity == 0) &&
                        (((S_800A9E70_3 *)interaction_state)->unk_08 == 0) &&
                        !(((S_800A9E70_3 *)interaction_state)->unk_02 & 0x2008) &&
                        (entity->unk_43 == 0xFD)) {
                        ((S_800A9E70_3 *)interaction_state)->unk_0C = entity;
                        goto check_active_entity;
                    }
                } else {
                check_active_entity:
                    if (entity->unk_43 == 0xFD) {
                    update_anim:
                        if (entity->unk_1C.as_s32 & 0x400000) {
                            anim->unk_8C = 0;
                            entity_flags = entity->unk_14.as_s32;
                            entity->unk_1C.as_s32 &= 0xFFBFFFFF;
                            if (entity_flags & 0x20000000) {
                                entity->unk_14.as_s32 = entity_flags | 0x400000;
                                func_800ACB98(anim, action_arg, sprite, entity);
                                return 0;
                            }
                            entity->unk_14.as_s32 = entity_flags & 0xFFBFFFFF;
                            {
                                u32 next_anim = entity_flags & 0x4000;
                                if (next_anim) {
                                    next_anim = 1;
                                } else {
                                    next_anim = 2;
                                }
                                anim->unk_9A.as_u8 = next_anim;
                            }
                            goto reset_anim_step;
                        }
                        if (entity->unk_1C.as_s32 & 0x02000000) {
                            anim->unk_8C = 0;
                            entity->unk_71.as_u8 = 0;
                            entity->unk_1C.as_s32 &= 0xFDFFFFFF;
                            if (entity->unk_14.as_s32 & 0x20000000) {
                                func_800ACD74(anim, action_arg, sprite, entity);
                                return 0;
                            }
                            anim->unk_9A.as_u8 = 0;
                        reset_anim_step:
                            anim->unk_9B.as_u8 = 0;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
