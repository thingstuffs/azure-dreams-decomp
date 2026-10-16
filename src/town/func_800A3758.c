#include "modules/town_door.h"

/* into_dn_door_jobs: Run dungeon entrance setup and reset entry flags. */
void into_dn_door_jobs(void) {
    townProcessTerminatedShopIds();
    clearResidentBitmapBit(0x16);
    townApplyBuildingPendingUpdates();
    townDispatchConditionalTablePairs();
    D_8008146C = 1;
    D_80082E60.flags16 = 0;
    D_80013714 &= 0xFFF8;
}
