#include "common.h"

#include "shared/entity.h"

extern void update_boss_actor_action(void *actor, void *context, void *sprite, EntityRec *entity);

typedef struct S_801707D4_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
} S_801707D4_0;   /* arg0 in set_boss_effect_data_pointer */

typedef struct S_801707D4_1 {
    u8 pad_00[0x46];
    u16 unk_46;
} S_801707D4_1;   /* arg3 in set_boss_effect_data_pointer */

/* Set the object's data pointer and clear the flag owner's high flag bit. */
void set_boss_effect_data_pointer(S_801707D4_0 *object, s32 unused_1, s32 unused_2, S_801707D4_1 *flag_owner) {
    object->unk_8C = &update_boss_actor_action;
    flag_owner->unk_46 = (u16) (flag_owner->unk_46 & 0x7FFF);
}
