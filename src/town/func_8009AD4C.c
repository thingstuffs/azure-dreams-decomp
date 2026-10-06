#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_80095388();                 /* extern */
s16 func_80095978();               /* extern */
void func_80095A94();      /* extern */
void func_80098928();        /* extern */


/* Update the actor's fall and handle contact with the ground. */
void func_800984AC(s32 context, EntityRec *actor, s32 action_arg) {
    s16 ground_height;

    ground_height = func_80095978(actor, &D_800FE488);
    if (actor->z.w.i >= ground_height) {
        func_80095A94(actor, ground_height, &D_800FE488);
        func_80098928(context, actor, action_arg);
        return;
    }
    func_80095388(actor);
}
