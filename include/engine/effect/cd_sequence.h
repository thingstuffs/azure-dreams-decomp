#ifndef ENGINE_EFFECT_CD_SEQUENCE_H
#define ENGINE_EFFECT_CD_SEQUENCE_H
#include "common.h"
#include "shared/object_node.h"
/* Legacy parent leaves preserve the unsigned completion count and word clear
 * used by this callback; the resident Controller remains its separate view. */
typedef struct CdCueSequenceOwnerView {
    u8 pad_00[6];
    u16 completion_count;
    u8 pad_08[0x14];
    s32 group_word;
} CdCueSequenceOwnerView;
typedef struct CdCueSequenceFrame {
    s16 tick;
    u16 x;
    u16 y;
    s16 line_units;
    u8 pad_08[8];
} CdCueSequenceFrame;
typedef struct CdCueSequenceChildBody {
    u8 pad_00[6];
    s16 activation_state;
    u8 pad_08[2];
    s16 x;
    u16 y;
    s16 line_width;
    s16 line_x;
} CdCueSequenceChildBody;
typedef struct CdCueSequenceChildNode {
    ObjectNodeHeader header;
    CdCueSequenceChildBody body;
} CdCueSequenceChildNode;
typedef struct CdCueSequenceBody {
    CdCueSequenceOwnerView *owner;
    s16 state;
    u16 timer;
    s16 slot_index;
    s16 trigger;
    CdCueSequenceFrame *frame;
    CdCueSequenceChildNode *children[16];
} CdCueSequenceBody;
typedef struct CdCueSequenceNode {
    ObjectNodeHeader header;
    CdCueSequenceBody body;
} CdCueSequenceNode;
#endif
