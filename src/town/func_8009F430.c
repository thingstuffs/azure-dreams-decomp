#include "common.h"
#include "m2c_compat.h"

void townInitializeActorActionWithDefaults();                   /* extern */
extern M2C_UNK D_800F8A4C;

/* Initialize the object's action state using D_800F8A4C. */
void townInitializeObjectActionWithDefaultData(s32 object, s32 action, s32 state) {
    townInitializeActorActionWithDefaults(object, action, state, &D_800F8A4C);
}
