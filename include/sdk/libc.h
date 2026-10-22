/* Stand-in declarations for the Psy-Q SDK library libc. The SDK is copyrighted and not distributed here; builders who own it can replace this file with the SDK header. */
/* Generated call contracts; maintained by tools/headers. */
#ifndef SDK_LIBC_H
#define SDK_LIBC_H

#include "common.h"

s32 abs(s32);
#include "sdk/bzero.h"
char * func_80069E38(char *, const char *);
char * func_80069E78(char *, const char *);
char * func_80069E88(char *, const char *, s32);
s32 func_80069E98(const char *);
void func_80069EC8(void *, s32);
void * func_80069ED8(void *, const void *, s32);
s32 func_80069EF8(void);
void * func_80069F28(void *, const void *, s32);
void * memcpy(void *, const void *, s32);
void * memset(void *, s32, s32);
s32 printf(const char *, ...);
s32 puts(const char *);
s32 rand(void);
void srand(u32);
char * strcat(char *, const char *);
s32 strcmp(const char *, const char *);
char * strcpy(char *, const char *);
s32 strlen(const char *);
char * strncat(char *, const char *, s32);
s32 strncmp(const char *, const char *, s32);
char * strncpy(char *, const char *, s32);

#endif
