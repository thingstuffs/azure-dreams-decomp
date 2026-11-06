#ifndef FRONTEND_LIBCARD_CARD_BOOT_CREATE_OR_RESET_MESSAGE_DIALOG_API_H
#define FRONTEND_LIBCARD_CARD_BOOT_CREATE_OR_RESET_MESSAGE_DIALOG_API_H

#include "common.h"
struct ObjectNodeHeader;

u8 *card_boot_create_or_reset_message_dialog(struct ObjectNodeHeader *, s32, s32, void *);

#endif
