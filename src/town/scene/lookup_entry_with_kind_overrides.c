#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/scene.h"

extern u8 D_80018A58[];
extern u8 D_80019104[];
extern u8 D_800197D0[];
extern u8 D_8001AE04[];

/* Look up the entry for (key, kind); kinds 0x2D and 0x2E have override records when func_80017A54 accepts them. */
void *lookup_scene_entry_with_kind_overrides(s32 key, s32 unused, s32 kind) {
    void *entry;

    entry = apply_entry_position(D_80018A58, D_80019104, key, kind);
    if (kind == 0x2D && resolve_entry_flag(D_80018A58, key, 0x2D) != 0) {
        return D_800197D0;
    }
    if (kind == 0x2E && resolve_entry_flag(D_80018A58, key, 0x2E) != 0) {
        return D_8001AE04;
    }
    return entry;
}
