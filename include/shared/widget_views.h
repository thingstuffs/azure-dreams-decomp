#ifndef SHARED_WIDGET_VIEWS_H
#define SHARED_WIDGET_VIEWS_H
#include "common.h"


/* Exact access views shared across registered binary consumers. */
/* Unsigned high coordinate half at +A used by menu placement. */
typedef struct UnsignedWidgetYView {
    unsigned char pad_00[0xA];
    unsigned short unk_0A;
} UnsignedWidgetYView;

/* Menu widget projection exposing the +8 component pointer. */
typedef struct WidgetComponentView {
    unsigned char pad_00[0x8];
    void * unk_08;
} WidgetComponentView;

/* Signed high coordinate half at +A used by menu row and icon placement. */
typedef struct SignedWidgetYView {
    unsigned char pad_00[0xA];
    short unk_0A;
} SignedWidgetYView;

/* Card-menu callback record projection. Callback data is passed at +0x10;
 * card_dev_*_wait_countdown and card_boot_wait_before_* subtract 0x10 and
 * decrement the signed counter at +0x4C. The child-label setup routines
 * install the same kind of raw callback/table pointer at +0. No allocation
 * extent is inferred; consumers use pointers, never this type's stride. */
typedef struct CardCallbackState {
    /* 0x00 */ s32 *callback;
    /* 0x04 */ u8 pad_04[0x48];
    /* 0x4C */ s32 countdown;
} CardCallbackState;

#endif
