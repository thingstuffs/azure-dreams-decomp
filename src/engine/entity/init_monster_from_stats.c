#include "common.h"
#include "engine/entity.h"
#include "slus/data.h"

/* D_8006D6D8: word array indexed by monster id (used to seed obj+0x54). */

/* apply_entity_effects: post-init fixup on the struct just filled in (still
 * nonmatching elsewhere; only the arg setup here needs to match). */

/* 16-byte block (4 words) used to copy the first 4 record fields into the
 * object in one shot, matching retail's load-x4/store-x4 grouping. */
typedef struct {
    u32 w0, w1, w2, w3;
} S_80042640_Block16;

/* Initialize a monster object from its initial-stats record and run the post-init fixup. */
/* Detail: copies the first 0x14 bytes of the record, ORs the record's flag word into the
 * object's existing flags, tags the object with its monster id, seeds a few fixed/derived
 * byte fields and the per-id word from D_8006D6D8 at obj+0x54, then runs apply_entity_effects. */
void init_monster_from_stats(void *obj, s16 monsterId)
{
    u8 *dst = (u8 *)obj;
    u8 *rec = (u8 *)initialStatsTable + (s32)monsterId * 24;
    s32 *d6d8 = &D_8006D6D8[monsterId];
    u32 oldFlags, recFlags;

    *(S_80042640_Block16 *)(dst + 0x00) = *(S_80042640_Block16 *)(rec + 0x00);
    *(u32 *)(dst + 0x10) = *(u32 *)(rec + 0x10);

    oldFlags = *(u32 *)(dst + 0x14);
    recFlags = *(u32 *)(rec + 0x14);
    dst[0x13] = (u8)monsterId;
    *(u32 *)(dst + 0x14) = oldFlags | recFlags;

    dst[0x28] = rec[0x05];
    dst[0x25] = rec[0x04];
    dst[0x24] = 0xFF;
    dst[0x26] = rec[0x00];
    dst[0x27] = rec[0x01];
    dst[0x45] = 6;
    dst[0x42] = 0;
    dst[0x41] = 0;
    *(u32 *)(dst + 0x54) = *d6d8;
    apply_entity_effects(obj);
}
