#include "common.h"
#include "engine/entity.h"
#include "engine/scene.h"
#include "slus.h"

typedef struct S_80041E28_Dst {
    u8  pad0[0x54];
    s32 f54;
} S_80041E28_Dst;

typedef struct S_80041E28_Src {
    u8  pad0[0x50];
    s32 f50;
} S_80041E28_Src;

/* Copy 0x13 words and the trailing field from src to dst, then finish initializing dst. */
void restore_actor_stats_from_snapshot(S_80041E28_Dst *dst, S_80041E28_Src *src)
{
    copy_words_forward((int *)dst, (int *)src, 0x13);
    dst->f54 = src->f50;
    apply_entity_effects(dst);
}
