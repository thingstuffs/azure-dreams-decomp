#include "common.h"

extern void SD_Call(s32 flags);
extern void townSpawnRandomizedEffectParts(void *source_data, s32 spawn_arg);
extern void townUnlinkSceneListNode(void *node);
extern void func_80033D08(void *block_data);
extern void townRunTheFollowUpActionHasEligibleTypePassesCheck(s32 check_value);
struct S_800814A0 {
    s32 v;
    s32 pad[2];
};
extern struct S_800814A0 D_800814A0;

/* Process an object action and set the object and global 0x8000 flags. */
void townSpawnAndFlagObjectParts(unsigned short *object, s32 unused, s32 action_id)
{
    SD_Call(0x600);
    townSpawnRandomizedEffectParts(object, action_id);
    townUnlinkSceneListNode(object);
    func_80033D08(object);
    object[-1] |= 0x8000;
    D_800814A0.v |= 0x8000;
    townRunTheFollowUpActionHasEligibleTypePassesCheck(action_id);
}
