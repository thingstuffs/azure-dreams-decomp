#ifndef SHARED_DUNGEON_STATUS_H
#define SHARED_DUNGEON_STATUS_H

/* dungeonStatus: the global block at 0x80083460 (SLUS .bss; read and written by the DUNGEON overlay and by
 * the SLUS dungeon-entity helper slus/w_80042BDC).  One object: 527 of the 836 rows that touch
 * 0x80083460..0x8008347F form ONE lui/addiu base at 0x80083460 and reach every field below from it
 * (r78 types pilot census, work/native_lane/r78_types_pilot/census/).  Nothing between 0x80083480 and the
 * next object (0x80083498, passed around by address) is accessed, so the size stops at 0x20.
 * Retail's lui/addiu (not $gp) in slus/w_80042BDC, compiled -G16, shows the original declaration was
 * larger than 16 bytes.  Widths/signedness are the retail access widths (lh = signed, lhu = unsigned;
 * the minority of the other kind are casts at the use).  Names: only what the accesses prove. */
/* Resident dungeon turn/activity work; floor runtime setup clears pending work and active references.
 * Player/actor/trap callbacks balance the activity counters; initialize_dungeon_floor_state resets floor turns. */
typedef struct DungeonGlobalStatus {
    /* 0x00 */ short turn_scale; /* turn/movement scale; reset_dungeon_runtime_state sets 0x100 */
    /* 0x02 */ unsigned short flags; /* dungeon activity/control bits; reset to zero on floor runtime initialization */
    /* 0x04 */ short movement_frames_left; /* remaining movement-frame counter; reset to zero with floor runtime state */
    /* 0x06 */ short unk_06;            /* lhu 1, sh 3 (sign unproven) */
    /* 0x008 */ union {
        unsigned int word;
        struct {
            short pending_movement_count; /* outstanding movement work; incremented when a movement is queued */
            short pending_action_count; /* outstanding action work; balanced as item/actor actions begin and complete */
        } parts;
    } activity_counts; /* two signed counters sharing a word; the player turn controller tests the pair together when waiting for idle */
    /* 0x0C */ void *active_actor; /* currently selected/active actor pointer, or null after reset */
    /* 0x10 */ void *pending_display_owner; /* actor/object pointer whose display work is pending, or null */
    /* 0x014 */ union {
        unsigned int word;
        struct {
            short pending_trap_count; /* outstanding trap work; cleared with the other activity counters */
            short unk_16;            /* never accessed */
        } parts;
    } trap_counts;
    /* 0x18 */ unsigned char *monster_spawn_table; /* floor monster-spawn byte table selected by dungeon view setup */
    /* 0x1C */ short monster_count; /* live monster counter; reset to zero on floor runtime initialization */
    /* 0x1E */ unsigned short turn_counter; /* floor turn count, reset on floor setup and incremented by the player turn controller; 16-bit storage wraps */
} DungeonGlobalStatus;

extern DungeonGlobalStatus g_dungeon_status;

/* D_800814A8 remaining player-action count, also reached through the player owner.
 * This is a sparse counter view, with the original 0xA8 extent. */
typedef struct PlayerRemainingActionsView {
    unsigned char pad_00[0xA6];
    unsigned short remaining;
} PlayerRemainingActionsView;

#endif
