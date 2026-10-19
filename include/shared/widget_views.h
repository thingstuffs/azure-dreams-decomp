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

#endif
