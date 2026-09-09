#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171438(void *, void *, void *, void *);
extern void func_8017167C(void *, void *, void *, void *);
extern s32 func_80171E28(void *, void *, void *, void *);
extern void func_8017208C(void *, void *, void *, void *);
extern s32 func_80172230(void *, void *, void *, s32);
extern void func_80173A84(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170EA8;
extern u8 D_80174038[];
extern u8 D_80174040[];
extern u8 D_80174070[];
extern u8 D_80174080[];
extern u8 D_80174088[];


typedef struct S_80170EA8_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    union { u16 n; volatile u16 v; } unk_98;   /* accessed as both */
    u8 unk_9A;
    u8 unk_9B;
} S_80170EA8_0;   /* arg0 in func_80170EA8 */


typedef struct S_80170EA8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170EA8_2;   /* arg2 in func_80170EA8 */


typedef struct S_80170EA8_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170EA8_4;   /* origin in func_80170EA8 */

typedef struct S_80170EA8_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170EA8_5;   /* global in func_80170EA8 */

/* Updates the entity action, facing direction, and animation from dungeon state. */
void func_80170EA8(void *actor, void *context, void *sprite, void *entity)
{
    u8 *anim_table;
    register u8 *next_table ASM_REG("$5");
    s32 tile_record;
    s32 direction_aux;
    u32 dungeon_flags = D_80083462;

    if (dungeon_flags & 0x1000) {
        ((S_80170EA8_0 *)actor)->unk_9A = 0xE;
        func_80171438(actor, context, sprite, entity);
        return;
    }

    if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v == 0) {
        func_800AA79C(actor, context, sprite, entity);
        if (((S_80170EA8_2 *)sprite)->unk_2C != D_80174088) {
            next_table = D_80174080;
            goto set_table;
        }
        return;
    }

    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x200) {
        if (((S_80170EA8_2 *)sprite)->unk_2C == D_80174088) {
            ((S_80170EA8_0 *)actor)->unk_9A = 0xD;
            ((S_80170EA8_0 *)actor)->unk_9B = 1;
            ((S_80170EA8_0 *)actor)->unk_8C = 0;
            ((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_80174080)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        if (((S_80170EA8_0 *)actor)->unk_9A != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_80174038;
            if (((S_80170EA8_2 *)sprite)->unk_2C != anim_table) {
                (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
                func_80047784(sprite,
                    anim_table[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                    0);
            }
            ((S_80170EA8_0 *)actor)->unk_9A = next_state;
        }

        ((S_80170EA8_0 *)actor)->unk_98.n &= 0xFFF3;
        if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80174040)) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(actor, context, sprite, entity);
            func_80173A84(actor, context, sprite, entity);
            return;
        }

        if ((s16)func_800A1C58(entity) != 0) {
            func_800AAB10(actor, context, sprite, entity);
        }
    }

    tile_record = func_8009FB34(((S_80170EA8_2 *)sprite)->unk_24.at00.v, ((S_80170EA8_2 *)sprite)->unk_24.at01.v);
    ((S_80170EA8_2 *)sprite)->unk_26 = tile_record;

    if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x20) {
            goto special_cleanup;
        }
        if (((S_80170EA8_2 *)sprite)->unk_24.at00u.v == D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(entity,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172230(actor, context, sprite, 0) == 0) {
                return;
            }
            ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v |= 0x4000;
            if (!(((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

#ifdef __mips__
        {
            static void *volatile dispatch_labels[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&ordinary_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&case8_setup, &&handler_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            s32 dispatch_index;

            dispatch_index = (((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x3FFF) - 1;
            if ((u32)dispatch_index >= 12) {
                goto ordinary_cleanup;
            }
            goto *D_80170808[dispatch_index];
        }
case8_setup:
#else
        switch (((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x3FFF) {
        case 8:
#endif
            ((S_80170EA8_0 *)actor)->unk_98.v |= 0x8000;
            if (((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x2000) {
                if ((((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x3FFF) == 8) {
                    ((S_80170EA8_0 *)actor)->unk_98.v &= 0x7FFF;
                }
            }

#ifdef __mips__
handler_case:
#else
        case 9:
#endif
            if ((s16)func_80171E28(actor, context, sprite, entity) == 0) {
                func_8017208C(actor, context, sprite, entity);
                return;
            }
            return;

#ifdef __mips__
coords_case:
#else
        case 5:
        case 6:
        case 7:
#endif
        {
            u8 *origin = D_80082E80;
            void *global_actor;
            s32 direction;

            direction = func_800A0818(
                ((S_80170EA8_2 *)sprite)->unk_24.at00.v, ((S_80170EA8_2 *)sprite)->unk_24.at01.v,
                ((S_80170EA8_4 *)origin)->unk_24, ((S_80170EA8_4 *)origin)->unk_25,
                &direction_aux);
            global_actor = D_800814A8;
            ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = direction;
            if (((S_80170EA8_5 *)global_actor)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
            goto special_cleanup;
        }
#ifndef __mips__
        case 1:
        case 2:
        case 3:
            goto aaf_cleanup;

        case 12:
            goto special_cleanup;

        default:
            goto ordinary_cleanup;
        }
#endif

special_cleanup:
        func_800A9A0C(entity);
        return;

aaf_cleanup:
        func_800AAF00(actor, context, sprite, D_80174070, &D_80170EA8);
        return;

ordinary_cleanup:
        func_8017167C(actor, context, sprite, entity);
        return;
    } else if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(((S_80170EA8_2 *)sprite)->unk_24.at00.v,
                        ((S_80170EA8_2 *)sprite)->unk_24.at01.v, ((S_80170EA8_4 *)origin)->unk_24,
                        ((S_80170EA8_4 *)origin)->unk_25) != 0) {
                    ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = func_800A0818(
                        ((S_80170EA8_2 *)sprite)->unk_24.at00.v, ((S_80170EA8_2 *)sprite)->unk_24.at01.v,
                        ((S_80170EA8_4 *)origin)->unk_24, ((S_80170EA8_4 *)origin)->unk_25,
                        &direction_aux);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170EA8_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174038;
    if (((S_80170EA8_2 *)sprite)->unk_2C == anim_table) {
        return;
    }
    next_table = anim_table;
set_table:
    (*(void * *)((u8 *)sprite + (0x2C))) = next_table;
    func_80047784(sprite,
        *(u8 *)((((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32)next_table),
        0);
}
