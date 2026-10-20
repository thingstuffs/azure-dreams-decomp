#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Slot 0x2DC of the town service table (still padding in shared/town_services.h). */
typedef struct TownServiceSlot2DC {
    u8 pad_000[0x2DC];
    int (*callback_2DC)();
} TownServiceSlot2DC;

/* Run town service callback 0x2DC with zero (this TOWN module's copy of the town/func_8035A5E4 wrapper shape). */
void run_scene_service_2dc_zero(void) {
    ((TownServiceSlot2DC *)D_80016000->unk_20)->callback_2DC(0);
}
