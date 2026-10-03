#ifndef SHARED_RUNTIME_DISPATCH_H
#define SHARED_RUNTIME_DISPATCH_H

/* Shared state at D_80082E60, used by SLUS, MAIN, TOWN and DUNGEON.
 * The existing SlotTransitionState tag/field spellings are retained so its
 * current consumers need no mandatory source edits. field_0 is a flag word;
 * field_4 holds the dispatch value (including callback addresses). +0x08 is
 * a halfword with one low-byte read, which retains an explicit byte cast.
 * +0x0A selects resource/CD processing mode. +0x10..+0x16 are reached using
 * this same aggregate base; splitting them changes register/address formation.
 * Size 0x1C preserves >8-byte extern handling; it is a declaration bound,
 * not proof of the physical allocation's end. See phase-12 size/boundary A/B.
 * Older standalone D_80082E6A/6F/76 spellings remain unmodified pending their
 * own relocation/link proof; no adjacent symbol is absorbed by this header. */
typedef struct SlotTransitionState {
    /* 0x00 */ int field_0;
    /* 0x04 */ int field_4;
    /* 0x08 */ unsigned short unk_08;
    /* 0x0A */ unsigned char mode;
    /* 0x0B */ unsigned char field_B;
    /* 0x0C */ unsigned char field_C;
    /* 0x0D */ unsigned char field_D;
    /* 0x0E */ unsigned char unk_0E;
    /* 0x0F */ unsigned char flags0F;
    /* 0x10 */ short unk_10;
    /* 0x12 */ short unk_12;
    /* 0x14 */ short unk_14;
    /* 0x16 */ unsigned short flags16;
    /* 0x18 */ unsigned char field_18;
    /* 0x19 */ unsigned char pad_19[3];
} RuntimeDispatchState;
extern RuntimeDispatchState D_80082E60;

#endif
