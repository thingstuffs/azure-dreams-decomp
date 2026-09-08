#include "common.h"

typedef struct Message {
    s16 x;
    s16 y;
} Message;

typedef struct CallbackTable {
    u8 pad[0x2F8];
    void (*callback)(s16, s16);
} CallbackTable;

typedef struct SystemData {
    u8 pad[0x20];
    CallbackTable *callbacks;
} SystemData;

typedef struct TownState {
    u8 pad0[1];
    u8 enabled;
    u8 pad2[3];
    u8 messageId;
} TownState;

extern TownState *D_8001E950;
extern SystemData *D_80016000;
extern Message *func_80019AFC(s32, u8);
extern void func_8001E578(s32);

/* Dispatch the enabled town message coordinates and advance the town state. */
s32 func_8001BED0(void) {
    Message *message;

    if (D_8001E950->enabled == 1) {
        do {
            message = func_80019AFC(0, D_8001E950->messageId);
        } while (0);
        D_80016000->callbacks->callback(message->x, message->y);
        D_8001E950->enabled++;
        func_8001E578(0x408);
        return 1;
    }
    return 0;
}
