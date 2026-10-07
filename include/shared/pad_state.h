#ifndef SHARED_PAD_STATE_H
#define SHARED_PAD_STATE_H
/* D_801379A8: the menu repeat handler reads held at +0 and pressed at +8.
 * +4 is unclassified. The standalone +8 symbol has an unresolved declaration
 * identity; volatile scalar consumers retain their declarations until exact. */
typedef struct PadState {
    /* 0x00 */ int held;
    /* 0x04 */ int unk_04;
    /* 0x08 */ int pressed;
} PadState;
extern PadState D_801379A8;
#endif
