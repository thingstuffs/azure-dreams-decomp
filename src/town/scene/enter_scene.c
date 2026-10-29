#include "script_symbols.h"
#include "shared/town_root.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/flags.h"

typedef void (*TownCall0)(s32);
typedef void (*TownCall1)(void *);

extern u8 D_80010000[];
extern u8 D_800190B8[];

/* Town scene entry: queue requests 0x5C2 and 0x5BF, run the init hook, then invoke the town dispatch table's 0x340 and 0x218 handlers. */
void enter_scene(void) {
    TownServiceTable *dispatch;

    func_80018A64(F_sbs11_pad31);
    func_80018A64(F_sbs11_pad28);
    update_scene_flag_5_c_4();

    dispatch = *(TownServiceTable **)(*(u8 **)(D_80010000 + 0x6000) + 0x20);
    ((TownCall0)dispatch->callback_340)(0);

    dispatch = *(TownServiceTable **)(*(u8 **)(D_80010000 + 0x6000) + 0x20);
    ((TownCall1)dispatch->callback_218)(D_800190B8);
}
