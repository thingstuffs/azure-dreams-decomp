#ifndef SLUS_MESSAGE_MODE_81550_H
#define SLUS_MESSAGE_MODE_81550_H

#include "common.h"

typedef void (*MessageModeHandler)(char *buffer);

extern s32 D_80081550;
extern MessageModeHandler D_800714A4[];
extern char *strcpy(char *dst, const char *src);
extern char *strrchr(const char *str, s32 ch);

#endif
