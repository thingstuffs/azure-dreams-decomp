#ifndef FRONTEND_CARD_MESSAGE_OBJECT_H
#define FRONTEND_CARD_MESSAGE_OBJECT_H

#include "common.h"

/* Initialize or retrieve the memory-card message object. */
struct ObjectNodeHeader;
u8 * init_card_message_object(struct ObjectNodeHeader *,  s32, s32, s32);

#endif
