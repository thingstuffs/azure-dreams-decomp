#ifndef SHARED_MINIGAME_BODY_H
#define SHARED_MINIGAME_BODY_H
/* Alternate minigame record view, demonstrated both behind the ball nodes
 * and at D_800834B8. Halfwords +14/+16/+18/+1C/+22 differ from EntityRec's
 * word layout. The state update and direction-table selector share +08/+10/+48.
 * Names remain offsets; 0x60 is the observed layout, not an allocation bound. */
typedef struct MinigameBody {
    unsigned char pad_00[0x4];
    int actor_speed;
    short player_state;
    unsigned char pad_0A[0x2];
    int actor_impulse_x;
    int unk_10;
    short cycles;
    short zone_index;
    short actor_state;
    unsigned char pad_1A[0x2];
    short waypoint_index;
    unsigned char pad_1E[0x4];
    short path_index;
    unsigned char pad_24[0x24];
    int player_speed;
    unsigned char pad_4C[0xC];
    int player_impulse_x;
    int player_impulse_y;
} MinigameBody;
extern MinigameBody scene_object_payload_alias;

/* Exact access views shared across registered binary consumers. */
/* Minigame progress stage and elapsed time, retained as two signed halves. */
typedef struct MinigameProgressPair16 {
    short lap_count;
    short checkpoint_index;
} MinigameProgressPair16;

/* The shop display stores three panel nodes before its timing and score fields. */
struct RisingScorePanelNode;
typedef struct TownScoreCounterView {
    struct RisingScorePanelNode *panels[3];
    short state;
    short timer;
    short index;
    short completed;
    short score;
    unsigned short counter;
    short area;
    unsigned short flags;
} TownScoreCounterView;

#endif
