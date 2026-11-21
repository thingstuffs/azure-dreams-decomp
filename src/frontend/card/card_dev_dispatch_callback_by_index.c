#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"

typedef void (*Callback_8001F2F4)();

typedef struct CallbackTable_8001F2F4 {
    Callback_8001F2F4 entries[4];
} CallbackTable_8001F2F4;

extern CallbackTable_8001F2F4 D_8040076C;

/* Invoke the callback selected by the object's callback index. */
void card_dev_dispatch_callback_by_index(CardDevSaveMenuBody *object)
{
    CallbackTable_8001F2F4 callbacks;

    callbacks = D_8040076C;
    callbacks.entries[object->callback_index](object);
}
