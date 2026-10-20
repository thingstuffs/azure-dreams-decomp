#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Slot 0x2D8 of the town service table (still padding in shared/town_services.h). */
typedef struct TownServiceSlot2D8 {
    u8 pad_000[0x2D8];
    int (*callback_2D8)();
} TownServiceSlot2D8;

/* Run town service callback 0x2D8 with code 3. */
void run_scene_service_2d8_with_3(void) {
    ((TownServiceSlot2D8 *)D_80016000->unk_20)->callback_2D8(3);
}
