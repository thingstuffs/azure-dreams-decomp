#ifndef SLUS_MESSAGE_MODE_81550_H
#define SLUS_MESSAGE_MODE_81550_H

#include "common.h"

typedef void (*MessageModeHandler)(char *buffer);

extern s32 message_handler_mode;
extern MessageModeHandler message_mode_handlers[];
extern char *strcpy(char *dst, const char *src);
extern char *strrchr(const char *str, s32 ch);

#endif
