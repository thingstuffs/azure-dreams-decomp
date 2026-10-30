#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene.h"



void invoke_callback_and_set_shared_pointer(void);                            /* extern */
extern M2C_UNK D_80017A7C;
extern s32 *D_80017B90;
extern M2C_UNK D_80017F64;


/* Run setup and install the global and context pointers. */
void init_scene_pointers(s32 setup_input, s32 setup_param) {
    invoke_callback_and_set_shared_pointer();
    D_80017B90 = &D_80017A7C;
    town_scene_root->position->unk_40 = &D_80017F64;
}
