#ifndef SHARED_MINIGAME_BODY_H
#define SHARED_MINIGAME_BODY_H
/* Alternate minigame record view, demonstrated both behind the ball nodes
 * and at D_800834B8. Halfwords +14/+16/+18/+1C/+22 differ from EntityRec's
 * word layout. The state update and direction-table selector share +08/+10/+48.
 * Names remain offsets; 0x60 is the observed layout, not an allocation bound. */
typedef struct MinigameBody {
    unsigned char pad_00[0x4];
    int unk_04;
    short unk_08;
    unsigned char pad_0A[0x2];
    int unk_0C;
    int unk_10;
    short unk_14;
    short unk_16;
    short unk_18;
    unsigned char pad_1A[0x2];
    short unk_1C;
    unsigned char pad_1E[0x4];
    short unk_22;
    unsigned char pad_24[0x24];
    int unk_48;
    unsigned char pad_4C[0xC];
    int unk_58;
    int unk_5C;
} MinigameBody;
extern MinigameBody scene_object_payload_alias;

/* Exact access views shared across registered binary consumers. */
/* Minigame progress stage and elapsed time, retained as two signed halves. */
typedef struct MinigameProgressPair16 {
    short unk_00;
    short unk_02;
} MinigameProgressPair16;

/* Score/collection total rooted at the rising-effect controller's first pointer.
 * It shares an offset with sprite flags but is updated as a counter. */
typedef struct TownScoreCounterView {
    unsigned char pad_00[0x14];
    unsigned short unk_14;
} TownScoreCounterView;

#endif
