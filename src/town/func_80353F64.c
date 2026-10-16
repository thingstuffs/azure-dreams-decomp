#include "modules/town_ovl_2d3f0c.h"

/* Set the current record's linked state fields to 0x15 and 0x12. */
void townSetCurrentRecordLinkedStates(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 0x15;
    ((TownPositionState *)D_80016000->unk_1C)->y = 0x12;
}
