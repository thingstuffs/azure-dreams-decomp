#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

M2C_UNK func_80095388();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80098928();        /* extern */
extern M2C_UNK D_800FE488;


/* Update the actor's fall and handle contact with the ground. */
void func_800984AC(s32 context, EntityRec *actor, M2C_UNK action_arg) {
    s16 ground_height;

    ground_height = func_80095978(actor, &D_800FE488);
    if (actor->z.w.i >= ground_height) {
        func_80095A94(actor, ground_height, &D_800FE488);
        func_80098928(context, actor, action_arg);
        return;
    }
    func_80095388(actor);
}
