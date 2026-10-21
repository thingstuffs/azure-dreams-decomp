#ifndef SHARED_TOWN_EVENT_STATE_H
#define SHARED_TOWN_EVENT_STATE_H

/* The pointer word D_8001E950 addresses byte state used by town event logic.
 * +1 is reset to zero, set to one/two, and indexes the callback table in the
 * town event dispatcher. +3/+4 index several value tables; their game meanings
 * are not established. +6 is read, set to one, and reset to zero. This layout
 * covers the observed seven bytes, without claiming an allocation boundary. */
typedef struct TownEventState {
    /* 0x00 */ unsigned char unk_00;
    /* 0x01 */ unsigned char dispatchState;
    /* 0x02 */ unsigned char unk_02;
    /* 0x03 */ unsigned char unk_03;
    /* 0x04 */ unsigned char unk_04;
    /* 0x05 */ unsigned char unk_05;
    /* 0x06 */ unsigned char unk_06;
} TownEventState;
extern TownEventState *town_event_state;


/* Exact access views shared across registered binary consumers. */
/* Town event entries expose a signed result at +8; their callers supply stride. */
typedef struct TownEventEntryValueView {
    unsigned char pad_00[8];
    int unk_08;
} TownEventEntryValueView;

/* Paired town-event arguments returned by select_event_data_table. */
typedef struct TownEventArgumentPair16 {
    short unk_00;
    short unk_02;
} TownEventArgumentPair16;

/* Indexed value records rooted at D_80016470; the two tail words stay opaque. */
typedef struct TownIndexedValueEntry {
    int value;
    int unk4;
    int unk8;
} TownIndexedValueEntry;

#endif
