/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_80095388();                 
s16 func_80095978();               
void func_80095A94();      
void func_80098928();        

void func_8009AB74(s32 context, EntityRec *actor, s32 action_arg) {
    s16 ground_height;

    ground_height = func_80095978(actor, &D_800FE488);
    if (actor->z.w.i >= ground_height) {
        func_80095A94(actor, ground_height, &D_800FE488);
        func_80098928(context, actor, action_arg);
        return;
    }
    func_80095388(actor);
}
