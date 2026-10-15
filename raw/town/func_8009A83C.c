/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_80095388();                 
s16 func_80095978();               
void func_80095A94();      
void func_80095C80();                      
void func_80098B70();        

void func_80097F9C(s32 context, EntityRec *record, s32 action_data) {
    s16 threshold;

    func_80095C80(record);
    threshold = func_80095978(record, &D_800FE488);
    if (record->z.w.i >= threshold) {
        func_80095A94(record, threshold, &D_800FE488);
        func_80098B70(context, record, action_data);
        return;
    }
    func_80095388(record, threshold);
}
