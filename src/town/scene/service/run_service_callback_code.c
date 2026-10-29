#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

/* Slot 0x2D8 of the town service table (still padding in shared/town_services.h). */
typedef struct TownServiceSlot2D8 {
    u8 pad_000[0x2D8];
    int (*callback_2D8)();
} TownServiceSlot2D8;

/* Run town service callback 0x2D8 with code 3. */
void run_service_callback_0x2d8_with_code_3(void) {
    ((TownServiceSlot2D8 *)town_scene_root->services)->callback_2D8(3);
}
