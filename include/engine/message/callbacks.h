#ifndef ENGINE_MESSAGE_CALLBACKS_H
#define ENGINE_MESSAGE_CALLBACKS_H

#include "engine/message.h"

typedef void (*MessageFlagHandler)(struct S_80038478_0 *);
typedef void (*MessageConfirmHandler)(struct S_80038588_0 *);
typedef void (*MessageInputHandler)(struct S_800385E8_0 *);
typedef void (*MessageReadyHandler)(struct S_80038648_0 *);

#endif
