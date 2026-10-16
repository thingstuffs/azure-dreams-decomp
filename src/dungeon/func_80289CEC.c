#include "modules/dungeon_floor_generate.h"

void dungeonPickRelativeRoomEdgePoint(s16 side, s16 *out_x, s16 *out_y, floor_generate_isolated_80289CEC_Entry *room) {
    if (room->fieldA == 0) {
        *out_x = 0;
        *out_y = 0;
        return;
    }

    switch (side) {
    case 0:
        *out_x = room->field4;
        *out_y = ((u16)func_800A6D30() % (room->field6 - 2)) + 1;
        break;

    case 2:
        *out_x = ((u16)func_800A6D30() % (room->field4 - 2)) + 1;
        *out_y = room->field6;
        break;

    case 4:
        *out_x = -1;
        *out_y = ((u16)func_800A6D30() % (room->field6 - 2)) + 1;
        break;

    default:
        *out_x = ((u16)func_800A6D30() % (room->field4 - 2)) + 1;
        *out_y = -1;
        break;
    }
}

/* MECHANISM: The two output pointers and record pointer stay live across RNG calls,
   naturally producing the retail s1/s2/s0 hold set and 0x20-byte frame.
   Each mode selects a copy/random/-1 pair using exact halfword field widths. */
