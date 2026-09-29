#include "common.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct {
    u8 pad[3];
    u8 flags;
} DungeonEntry;

extern s16 func_8009FD40(void *, void *);
extern void func_800A9A0C(void *, void *);
extern void func_800AAA28(void *, void *);
extern s16 func_800B500C(u8, u8, s16);

extern DungeonEntry D_800E3648[];


typedef struct S_800AD9B4_0_pre {
    u16 unk_00;
} S_800AD9B4_0_pre;   /* the 0x2 bytes before arg1 in func_800AD9B4, addressed as arg1[-1] */



/* Process an eligible dungeon entry and apply its state updates. */
s32 func_800AD9B4(Rec_D_80082E80 *actor, EntityRec *target)
{
    TileObject *player;
    DungeonGlobalStatus *dungeon_state;
    DungeonEntry *entries;
    s32 entry_index;
    s32 result;
    s8 adjustment;

    if (!(((S_800AD9B4_0_pre *)target)[-1].unk_00 & 0x8000)) {
        player = &D_80082E80;
        if (player->unk_026 == actor->unk_26.as_s8) {
            goto process_entry;
        }
        if (func_8009FD40(player, actor) < 7) {
            goto process_entry;
        }
    }
skip:
    return 1;

process_entry:
    if (target->tileY == 0) {
        goto skip;
    }

    entry_index = func_800B500C(actor->unk_24,
                           actor->unk_25,
                           target->unk_88);
    ASM_KEEP(entry_index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    result = 1;
    if (entry_index >= 0) {
        entries = D_800E3648;
        if (!(entries[entry_index].flags & 0x80)) {
            goto skip;
        }

        dungeon_state = &dungeonStatus;
        if (dungeon_state->flags & 0x1000) {
            adjustment = ((s8)target->unk_71);
            if (adjustment > 0) {
                dungeon_state->unk_08 =
                    ((u16)dungeon_state->unk_08) -
                    (adjustment - ((u16)target->unk_8A));
                target->unk_71 = 0;
            }
        }

        func_800A9A0C(target, dungeon_state);
        func_800AAA28(actor, target);
        result = 0;
    }
    return result;
}
