#ifndef SHARED_TOWN_EVENT_STATE_H
#define SHARED_TOWN_EVENT_STATE_H

/* The pointer word D_8001E950 addresses byte state used by town event logic.
 * +1 is reset to zero, set to one/two, and indexes the callback table in the
 * town event dispatcher. +3/+4 index several value tables; their game meanings
 * are not established. +6 is read, set to one, and reset to zero. This layout
 * covers the observed seven bytes, without claiming an allocation boundary. */
/* Town event selection and dispatch bytes reached through town_event_state.
 * select_next_event_state chooses the event mode and entry; start_dispatch_event starts dispatch. */
typedef struct TownEventState {
    /* 0x00 */ unsigned char unk_00;
    /* 0x01 */ unsigned char dispatchState; /* dispatch phase: 0 select/start, 1 pending dispatch, 2 dispatched */
    /* 0x02 */ unsigned char unk_02; /* cycling entry-list index; 0xFF is the initial sentinel, read as -1 */
    /* 0x03 */ unsigned char unk_03; /* saved enabled-entry id, reused by the event selection modes */
    /* 0x04 */ unsigned char unk_04; /* current selected entry id; zero means no selected entry */
    /* 0x05 */ unsigned char unk_05; /* event selection mode, used to choose data tables and command result builders */
    /* 0x06 */ unsigned char unk_06; /* response-table latch; first lookup sets it and later lookups use the alternate table */
} TownEventState;
extern TownEventState *town_event_state;


/* Exact access views shared across registered binary consumers. */
/* Town event entries expose a signed result at +8; their callers supply stride. */
/* Value/result slice in caller-owned town entry tables; observed callers use 0x10 or 0x1C strides.
 * Store callbacks fill +8 with a command result or pointer; search callbacks treat zero as the terminator. */
typedef struct TownEventEntryValueView {
    unsigned char pad_00[8];
    int unk_08; /* entry value/result word; zero terminates searched tables, and callers supply the record stride */
} TownEventEntryValueView;

/* Paired town-event arguments returned by select_event_data_table. */
/* Two signed arguments selected from the town event data tables by select_event_data_table.
 * start_dispatch_event and dispatch_enabled_message_coordinates pass them to service +0x2F8. */
typedef struct TownEventArgumentPair16 {
    short unk_00; /* first event-service argument, checked against 0x27 by the active-event handler */
    short unk_02; /* second event-service argument, checked against 0x200 by the active-event handler */
} TownEventArgumentPair16;

/* Indexed value records rooted at D_80016470; the two tail words stay opaque. */
/* Town value-table view rooted at D_80016470; this view owns no separate allocation.
 * copy_indexed_entry_to_state and copy_indexed_entry_value select its leading word. */
typedef struct TownIndexedValueEntry {
    int value; /* selected value copied to the destination town state at +0x20 */
    int unk4;
    int unk8;
} TownIndexedValueEntry;

#endif
