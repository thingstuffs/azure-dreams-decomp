#include "shared/town_root.h"
#include "common.h"

typedef void (*TownCall0)(s32);
typedef void (*TownCall1)(void *);



extern void func_80018A64(s32);
extern void func_800172BC(void);
extern u8 D_80010000[];
extern u8 D_800190B8[];

/* Town scene entry: queue requests 0x5C2 and 0x5BF, run the init hook, then invoke the town dispatch table's 0x340 and 0x218 handlers. */
void func_80017300(void) {
    TownServiceTable *dispatch;

    func_80018A64(0x5C2);
    func_80018A64(0x5BF);
    func_800172BC();

    dispatch = *(TownServiceTable **)(*(u8 **)(D_80010000 + 0x6000) + 0x20);
    ((TownCall0)dispatch->callback_340)(0);

    dispatch = *(TownServiceTable **)(*(u8 **)(D_80010000 + 0x6000) + 0x20);
    ((TownCall1)dispatch->callback_218)(D_800190B8);
}
