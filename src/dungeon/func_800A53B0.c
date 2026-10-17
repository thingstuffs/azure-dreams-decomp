#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80083460.h"

s32 func_80042900(void *, s32);
s32 func_800A1C58(void *);
void raiseEntityLevel(void *, s32);
void func_800A56E0(s32);
void dungeonSelectNearbyTargetAndInitializeSlot(s32 slot_id, void *target, s32 target_id, s16 slot_value);
extern s32 D_8007359C;
extern s8 D_80080A88;
extern s8 D_80080AA0;


typedef struct S_800AAB10_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    s32 unk_0C;
} S_800AAB10_0;   /* state in dungeonProcessSelectedActorRecord */


typedef struct S_800AAB10_2_pre {
    u16 unk_00;
    u8 pad_02[0x12];
} S_800AAB10_2_pre;   /* 0x14-byte header immediately before the payload. */


/* Processes the selected record, checks eligibility, and clears completed state. */
s32 dungeonProcessSelectedActorRecord(s32 buffer_addr, M2C_UNK source, M2C_UNK unused, EntityRec *record) {
    s32 eligible;
    u8 type_id;

    eligible = 0;
    if (D_800E296C & 0x100000) {
        if (((s32)dungeonStatus.unk_0C) != 0) {
            if (((s32)dungeonStatus.unk_0C) == record) {
                if (dungeonStatus.unk_0A == 0) {
                    if (!(dungeonStatus.flags & 8)) {
                        dungeonSelectNearbyTargetAndInitializeSlot((void *)(buffer_addr - 0x20), source, 8, 0x300);
                        raiseEntityLevel(record, 1);
                        func_800A56E0(0x201);
                        if (!(D_80013714 & 2)) {
                            D_80080AA0 = 1;
                            D_80080A88 = 0;
                        }
                        if (!(record->unk_54 & 0x800000) && (record->flags14 & 0x4000)) {
                            type_id = (*(u8 *)((u8 *)&record->unk_10 + 3));
                            if ((((S_800AAB10_2_pre *)(((type_id * 0x14) + D_8007359C)))[-1].unk_00 & 0x80)
                                && (type_id >= 2U) && ((u8) (*(u8 *)((u8 *)&record->unk_10 + 1)) >= 0x14U)
                                && !(record->flags1C & 0x228) && ((func_80042900(record, 0x18) << 0x10) == 0)) {
                                eligible = 1;
                            }
                        }
                        if ((func_800A1C58(record) << 0x10) != 0) {
                            return 0;
                        }
                        ((Rec_D_80083460 *)(&dungeonStatus.unk_00))->unk_0C = 0;
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    return eligible;
}
