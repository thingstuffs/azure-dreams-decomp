#ifndef DUNGEON_LEVEL_ROOM_FLAGS_H
#define DUNGEON_LEVEL_ROOM_FLAGS_H

/* apply_room_holy_beam_item announces Holy Beam and sets bit 2. Its timer
 * clears that bit; movement and target selection exclude enemies there. */
enum DungeonRoomFlags {
    ROOM_HOLY_BEAM = 0x2,
    ROOM_HOLY_BEAM_CLEAR_MASK = 0xFFFD,
};

#endif
