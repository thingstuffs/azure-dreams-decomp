#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct {
    u8 pad[3];
    u8 flags;
} DungeonEntry;

extern s16 func_8009FD40(void *, void *);
extern void func_800A9A0C(void *, void *);
extern void func_800AAA28(void *, void *);
extern s16 func_800B500C(u8, u8, s16);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern DungeonEntry D_800E3648[];


typedef struct S_800AD9B4_0_pre {
    u16 unk_00;
} S_800AD9B4_0_pre;   /* the 0x2 bytes before arg1 in func_800AD9B4, addressed as arg1[-1] */


typedef struct S_800AD9B4_1 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_800AD9B4_1;   /* base in func_800AD9B4 */


typedef struct S_800AD9B4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
} S_800AD9B4_3;   /* state in func_800AD9B4 */

/* Process an eligible dungeon entry and apply its state updates. */
s32 func_800AD9B4(Rec_D_80082E80 *actor, void *target)
{
    u8 *player;
    u8 *dungeon_state;
    DungeonEntry *entries;
    register u8 *data_page ASM_REG("$2");
    s32 entry_index;
    s32 result;
    s8 adjustment;

    if (((S_800AD9B4_0_pre *)target)[-1].unk_00 & 0x8000) {
        goto skip;
    }
    data_page = (u8 *)0x80080000;
    ASM_KEEP(data_page);
    player = data_page + 0x2E80;
    ASM_KEEP(player);
    if (((S_800AD9B4_1 *)player)->unk_26 == actor->unk_26.as_s8) {
        goto process_entry;
    }
    if (func_8009FD40(player, actor) < 7) {
        goto process_entry;
    }

skip:
    return 1;

process_entry:
    if (((Rec_D_800E3D7C *)target)->unk_24.at01_u8.v == 0) {
        goto skip;
    }

    entry_index = func_800B500C(actor->unk_24,
                           actor->unk_25,
                           ((Rec_D_800E3D7C *)target)->unk_88.as_s16);
    ASM_KEEP(entry_index);
    result = 1;
    if (entry_index >= 0) {
        entries = D_800E3648;
        ASM_KEEP(entries);
        if (!(entries[entry_index].flags & 0x80)) {
            goto skip;
        }

        data_page = (u8 *)0x80080000;
        ASM_KEEP(data_page);
        dungeon_state = data_page + 0x3460;
        ASM_KEEP(dungeon_state);
        if (((S_800AD9B4_3 *)dungeon_state)->unk_02 & 0x1000) {
            adjustment = ((Rec_D_800E3D7C *)target)->unk_71.as_s8;
            if (adjustment > 0) {
                ((S_800AD9B4_3 *)dungeon_state)->unk_08 =
                    ((S_800AD9B4_3 *)dungeon_state)->unk_08 -
                    (adjustment - ((Rec_D_800E3D7C *)target)->unk_8A.as_u16);
                ((Rec_D_800E3D7C *)target)->unk_71.as_s8 = 0;
            }
        }

        func_800A9A0C(target, dungeon_state);
        func_800AAA28(actor, target);
        result = 0;
    }
    return result;
}
