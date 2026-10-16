#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[0x9B];
    u8 state;
    u8 pad9C[0x100 - 0x9C];
    s16 h100;
} Actor;

extern u8 D_800E3648[];
extern u8 D_800E0B39[];
extern u8 D_80088B14[];
extern u8 D_800E0B4C[];

extern s32 func_800A2B5C(s32);
extern void dungeonRestorePlayerControlCallback(Actor *, s32);
extern s32 func_800990FC();
extern s32 func_80099194(u8 *src, u8 *dst);
extern s32 dungeonWriteTextByteAndAdvance(s8 value, s8 *dest);
extern s32 dungeonAppendValueSevenSuffix(u8 *dst);
extern s32 dungeonAppendTypedFormattedValue(void *, s32);
extern void dungeonCopyFullwidthVowelBytes(s32, s32);
extern s32 dungeonWriteStatusPrefixBytes(s32);
extern void func_80099290(s8 *byte_ptr);
extern void func_800A5720(s8 *text);
extern void dungeonRevealTriggeredTrap(Actor *, s32, s32, s32);
extern s16 dungeonCallSlotHandlerAndUpdateStatus(s32 handler_id, void *object_ptr, s32 slot_id, s8 update_state);

/* Advance the actor's entry action and clear pending state when it finishes. */
void dungeonUpdatePlayerTrapTrigger(Actor *actor, s32 context_a, s32 context_b, s32 target_arg) {
    u8 *entry;
    u8 *tab;
    int state = actor->state;
    s32 target = target_arg;
    if (state != 1) {
        if (state >= 2) {
            return;
        }
        if (state != 0) {
            return;
        }
        if (dungeonStatus.flags & 0x1000) {
            return;
        }
        if ((s16) func_800A2B5C(target) != 0) {
            return;
        }
        tab = D_800E3648;
        entry = &tab[actor->h100 * 4];
        if (entry[0] == 0) {
            dungeonRestorePlayerControlCallback(actor, target);
            dungeonStatus.unk_0C = 0;
            dungeonStatus.unk_14--;
            dungeonStatus.flags &= 0xFFF7;
            return;
        }
        if (!(entry[3] & 0x40)) {

            s32 cursor;
            s32 buffer_start;
            s32 patch_pos;
            s32 entry_pos;
            cursor = func_800990FC();
            buffer_start = cursor;
            cursor = dungeonAppendValueSevenSuffix(func_80099194(D_800E0B39, dungeonWriteTextByteAndAdvance(8, cursor)));
            patch_pos = cursor - 2;
            cursor = func_80099194(D_80088B14, cursor);
            entry_pos = cursor;
            cursor = dungeonAppendTypedFormattedValue(&D_800E3648[actor->h100 * 4], entry_pos);
            dungeonCopyFullwidthVowelBytes(patch_pos, entry_pos);
            func_80099290(dungeonWriteStatusPrefixBytes(func_80099194(D_800E0B4C, dungeonWriteTextByteAndAdvance(10, cursor))));
            func_800A5720(buffer_start);
        }
        actor->state++;
        dungeonRevealTriggeredTrap(actor, context_a, context_b, target);
    }
    if (D_800E3648[actor->h100 * 4] == 0) {
        dungeonRestorePlayerControlCallback(actor, target);
        dungeonStatus.unk_0C = 0;
        dungeonStatus.unk_14--;
        dungeonStatus.flags &= 0xFFF7;
        return;
    } else {
        s16 result = (s16) dungeonCallSlotHandlerAndUpdateStatus(D_800E3648[actor->h100 * 4], target, actor->h100, 0);
        if (result != 0) {
            dungeonStatus.unk_0C = 0;
            dungeonStatus.unk_14--;
            dungeonStatus.flags &= 0xFFF7;
            if (result > 0) {
                dungeonRestorePlayerControlCallback(actor, target);
            }
            actor->state++;
        }
    }
}
