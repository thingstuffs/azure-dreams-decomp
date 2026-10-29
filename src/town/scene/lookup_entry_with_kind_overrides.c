#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/scene.h"

extern void *func_80017B0C(void *, void *, s32, s32);
extern s32 func_80017A54(void *, s32, s32);
extern u8 D_80018A58[];
extern u8 D_80019104[];
extern u8 D_800197D0[];
extern u8 D_8001AE04[];

/* Look up the entry for (key, kind); kinds 0x2D and 0x2E have override records when func_80017A54 accepts them. */
void *lookup_scene_entry_with_kind_overrides(s32 key, s32 unused, s32 kind) {
    void *entry;

    entry = func_80017B0C(D_80018A58, D_80019104, key, kind);
    if (kind == 0x2D && func_80017A54(D_80018A58, key, 0x2D) != 0) {
        return D_800197D0;
    }
    if (kind == 0x2E && func_80017A54(D_80018A58, key, 0x2E) != 0) {
        return D_8001AE04;
    }
    return entry;
}
