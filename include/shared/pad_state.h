#ifndef SHARED_PAD_STATE_H
#define SHARED_PAD_STATE_H
/* D_801379A8: the menu repeat handler reads held at +0 and pressed at +8.
 * +4 is unclassified. The standalone +8 symbol has an unresolved declaration
 * identity; volatile scalar consumers retain their declarations until exact. */
/* Controller snapshot used by the memory-card menu and its key-repeat handler.
 * The card input service supplies held and newly pressed masks. */
typedef struct PadState {
    /* 0x00 */ int held; /* held controller-button bits; directions use 0x1000/0x2000/0x4000/0x8000 */
    /* 0x04 */ int unk_04;
    /* 0x08 */ int pressed; /* newly pressed controller-button bits, used for single menu actions */
} PadState;
extern PadState boot_pad_state;

/* Exact access views shared across registered binary consumers. */
/* Current, previous and newly pressed controller words rooted at GameWork.buttons. */
/* Three consecutive input-history words within GameWork, starting at buttons.
 * update_controller_buttons_and_triggers saves the old sample and computes the trigger mask. */
typedef struct ControllerButtonHistory {
    int cur; /* current held-button mask */
    int old; /* previous held-button mask */
    int trg; /* newly pressed bits, (cur ^ old) & cur */
} ControllerButtonHistory;

#endif
