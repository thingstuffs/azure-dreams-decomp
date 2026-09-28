#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern s32 func_800990FC(s32, s32, s32, s32);
extern s32 func_80099194(void *, s32);
extern s32 func_80099734(s32, s32);
extern void func_80099290(s32);
extern void func_800A5720(s32);
extern u8 D_80176440[9];
extern u8 D_80176455[9];
/* Builds and displays a message containing the record's name between fixed text. */
void func_80175DA4(s32 record, s32 unused_1, s32 unused_2, s32 unused_3)
{
  s32 text_arg;
  s32 message;
  unsigned int cursor;

  text_arg = func_800990FC(record, unused_1, unused_2, unused_3);
  message = text_arg;
  cursor = func_80099194(D_80176440, message);
  text_arg = record;
  func_80099290(func_80099194(D_80176455, func_80099734(text_arg, cursor)));
  func_800A5720(message);
}
