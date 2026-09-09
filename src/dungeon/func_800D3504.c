#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800AA258_arg2.h"

extern void func_8003DB94(void *, void *, s32);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, s32);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800D904C(void *, void *, void *, void *);
extern void func_800D92C0(void *, void *, void *, void *);
extern void func_800DA660(void *, void *, void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern u16 D_80083462;
extern void *D_800E262C[];
extern s8 D_800E2970[];

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

typedef struct S_800D8C64_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800D8C64_4;   /* target in func_800D8C64 */

/* Updates actor state, facing, and directional animation. */
void func_800D8C64(void *actor, void *motion, void *sprite, void *status)
{
    void **anim_table;
    s32 cell_record;
    s32 direction_aux;

    if (D_80083462 & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_800D904C(actor, motion, sprite, status);
        return;
    }

    if (((Rec_D_800E3D7C *)status)->unk_24.at01_u8.v == 0) {
        void *current_anim;

        func_800AA79C(actor, motion, sprite, status);
        current_anim = ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv;
        anim_table = D_800E262C;
        if (current_anim == anim_table) {
            return;
        }
    } else {

        if (((Rec_D_800E3D7C *)status)->unk_1C.as_u32 & 0x200) {
            if (((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv == D_800E262C) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                ((Rec_D_800E3D7C *)status)->unk_1C.as_u32 &= ~0x40000;
                return;
            }
            if (func_800AA924(actor, motion, sprite, 0)) {
                return;
            }
        }

        if (!(D_80083462 & 0x2000)) {
            if (((Rec_D_800E3D7C *)status)->unk_1C.as_u32 & 0x100) {
                func_800AA258(actor, motion, sprite, status);
                return;
            }

            if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
                u8 next_state = 0xE;

                anim_table = D_800E262C;
                if (((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv != anim_table) {
                    (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
                    func_8003DB94(sprite,
                        *(void **)((u8 *)anim_table +
                            (((D_80083228 + ((Rec_D_800E3D7C *)status)->unk_2A.as_s16 + 0x100) >> 7) & 0x1C)),
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = next_state;
            }

            ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
            if (((Rec_D_800E3D7C *)status)->unk_64.as_s16 != 0) {
                if (func_800AA6B4(actor, motion, sprite, 0)) {
                    return;
                }
            }

            if (((Rec_D_800E3D7C *)status)->unk_1C.as_u32 & 0x80000) {
                ((Rec_func_800A9E70_arg0 *)actor)->unk_90.at00_s32.v = 0;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFFE;
                ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
                func_800AA888(actor, motion, sprite, status);
                func_800DA660(actor, motion, sprite, status);
                return;
            }

            if ((s16)func_800A1C58(status) != 0) {
                func_800AAB10(actor, motion, sprite, status);
            }
        }

        cell_record = func_8009FB34(((Rec_func_800AA258_arg2 *)sprite)->unk_24, ((Rec_func_800AA258_arg2 *)sprite)->unk_25);
        ((Rec_func_800AA258_arg2 *)sprite)->unk_26.as_u8 = cell_record;

        if (((Rec_D_800E3D7C *)status)->unk_6D.as_s8 > 0) {
            if (((Rec_D_800E3D7C *)status)->unk_1C.as_u32 & 0x20) {
                func_800A9A0C(status);
                return;
            }
            func_800D92C0(actor, motion, sprite, status);
            return;
        }

        if (!(((Rec_D_800E3D7C *)status)->unk_1C.as_u32 & 0x2000)) {
            s32 record_index = (s8)cell_record;

            if ((record_index < 0) ||
                !(((DungeonRecord *)D_800E2970)[record_index].flags & 2)) {
                if (!(((Rec_D_800E3D7C *)status)->unk_1C.as_u32 & 0x430)) {
                    u8 *target = D_80082E80;

                    if ((s16)func_8009FD7C(((Rec_func_800AA258_arg2 *)sprite)->unk_24,
                            ((Rec_func_800AA258_arg2 *)sprite)->unk_25, ((S_800D8C64_4 *)target)->unk_24,
                            ((S_800D8C64_4 *)target)->unk_25) != 0) {
                        ((Rec_D_800E3D7C *)status)->unk_2A.as_s16 = func_800A0818(
                            ((Rec_func_800AA258_arg2 *)sprite)->unk_24, ((Rec_func_800AA258_arg2 *)sprite)->unk_25,
                            ((S_800D8C64_4 *)target)->unk_24, ((S_800D8C64_4 *)target)->unk_25,
                            &direction_aux);
                    }
                }
            }
        }

        if (D_80083462 & 0x2000) {
            return;
        }
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x40) {
            return;
        }
        anim_table = D_800E262C;
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv == anim_table) {
            return;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 1) {
            return;
        }
    }
    (*(void * *)((u8 *)sprite + (0x2C))) = anim_table;
    func_8003DB94(sprite,
        *(void **)((((D_80083228 + ((Rec_D_800E3D7C *)status)->unk_2A.as_s16 + 0x100) >> 7) & 0x1C) +
            (u32)anim_table),
        0);
}
