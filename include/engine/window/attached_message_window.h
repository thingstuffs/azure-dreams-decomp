#ifndef ENGINE_WINDOW_ATTACHED_MESSAGE_WINDOW_H
#define ENGINE_WINDOW_ATTACHED_MESSAGE_WINDOW_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"

typedef union AttachedMessageWindowCounter {
    u16 unsigned_value;
    s16 signed_value;
} AttachedMessageWindowCounter;

/* Observed attached-window body prefix; callbacks remain opaque addresses. */
typedef struct AttachedMessageWindowBody {
    void *attached_object;
    s32 unk_04;
    void *draw_callback;
    u8 pad_0C[8];
    s32 initial_state_14;
    s32 initial_state_18;
    u8 pad_1C[0x28];
    void *unk_44;
    u8 active;
    u8 pad_49;
    s16 object_id;
    u8 pad_4C[0x18];
    /* 0x64 */ AttachedMessageWindowCounter counter;
    /* 0x66 */ u8 pad_66[2];
    void *handler;
    u8 pad_6C[8];
    void *owner;
    u8 unk_78;
} AttachedMessageWindowBody;
#endif
