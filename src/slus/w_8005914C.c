#include "common.h"

typedef struct 
{
  s32 unk00;
  s32 unk04;
  u32 unk08;
  u8 pad0C[0x10 - 0x0C];
  s32 unk10;
  s32 unk14;
  u8 pad18[0x2C - 0x18];
  s32 unk2C;
  s32 unk30;
  u8 pad34[0x40 - 0x34];
  s32 unk40;
  s32 unk44;
  u8 pad48[0x4A - 0x48];
  u8 unk4A;
  u8 unk4B;
  u8 pad4C[0x50 - 0x4C];
} S_80085FA8;
typedef struct 
{
  u8 pad00[0x4D];
  u8 unk4D;
  u8 pad4E[0x9C - 0x4E];
} S_80084960;
extern S_80085FA8 D_80085FA8[];
extern S_80084960 D_80084960[];
extern s32 D_800869B4[3];
extern s32 D_800869B8[3];
#ifdef NON_MATCHING
#define D_800869B4_PAGE D_800869B4
#define D_800869B4_PAGE_INDEX 0
#else
#define D_800869B4_PAGE ((s32 *)0x80080000)
#define D_800869B4_PAGE_INDEX (0x69B4 / sizeof(s32))
#endif
extern void func_80056E10(s32 a0, s32 a1, s32 a2);
extern void func_80057948(s32 a0, s32 a1, s32 a2);
extern void func_80057A48(s32 a0, s32 a1, s32 a2);
extern void func_80057D20(s32 a0, s32 a1, s32 a2);
extern void func_8005845C(s32 a0, s32 a1);
extern void func_8005848C(s32 a0, s32 a1);
extern void func_80058494(s32 a0, s32 a1, s32 a2);
/* Dispatch a MIDI channel event and handle track state save, restore, and repeat controls. */
void func_8005914C(S_80085FA8 *track_arg, s32 status, s32 first_data, s32 second_data)
{
  s32 channel;
  u32 track_index;
  s32 track_count;
  S_80085FA8 *track_iter;
  register S_80085FA8 *track ASM_REG("$13");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
  register s32 event_data ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  track = track_arg;
  channel = status & 0xF;
  event_data = first_data;
  switch (status & 0xF0)
  {
    case 0x80:
      func_80057948(channel, event_data & 0xFF, second_data & 0xFF);
      return;

    case 0x90:
      if ((second_data & 0xFF) != 0)
      {
        func_80056E10(channel, event_data & 0xFF, second_data & 0xFF);
      }
      else
      {
        func_80057948(channel, event_data & 0xFF, 0);
      }
      return;

    case 0xA0:
      func_80057A48(channel, event_data & 0xFF, second_data & 0xFF);
      return;

    case 0xB0:
      ASM_KEEP(track);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
      if ((event_data & 0xFF) == 0x63)
      {
        if ((second_data & 0xFF) == 0x14)
        {
          if (D_800869B8[0] != 0)
          {
            s32 *count_page;
            count_page = D_800869B4_PAGE;
            if (count_page[D_800869B4_PAGE_INDEX] != 0)
            {
              s32 value_00;
              s32 value_10;
              s32 value_40;
              s32 value_2c;
              s32 track_count;
              register u8 value_4a ASM_REG("$6");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
              s32 repeat_count;
              track_index = 0;
              repeat_count = 0x14;
              track_iter = D_80085FA8;
              do
              {
                value_00 = *(volatile s32 *)&track_iter->unk00;
                value_10 = *(volatile s32 *)&track_iter->unk10;
                value_40 = *(volatile s32 *)&track_iter->unk40;
                value_2c = *(volatile s32 *)&track_iter->unk2C;
                value_4a = *(volatile u8 *)&track_iter->unk4A;
                track_iter->unk04 = value_00;
                track_iter->unk4B = value_4a;
                track_count = count_page[D_800869B4_PAGE_INDEX];
                track_index++;
                track_iter->unk08 = repeat_count;
                track_iter->unk14 = value_10;
                track_iter->unk44 = value_40;
                track_iter->unk30 = value_2c;
                track_iter++;
              }
              while (track_index < ((u32) track_count));
            }
          }
          else
          {
            track->unk08 = 0x7F;
            track->unk04 = track->unk00;
          }
        }
        else if ((second_data & 0xFF) == 0x1E)
        {
          if (track->unk08 != 0)
          {
            if (track->unk08 < 0x7FU)
            {
              track->unk08 = track->unk08 - 1;
            }
            if (D_800869B8[0] != 0)
            {
              s32 *count_page;
              count_page = D_800869B4_PAGE;
              if (count_page[D_800869B4_PAGE_INDEX] != 0)
              {
                s32 saved_00;
                s32 saved_10;
                s32 saved_40;
                s32 saved_2c;
                s32 track_count;
                register u8 saved_4a ASM_REG("$6");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                track_index = 0;
                track_iter = D_80085FA8;
                do
                {
                  saved_00 = *(volatile s32 *)&track_iter->unk04;
                  saved_10 = *(volatile s32 *)&track_iter->unk14;
                  saved_40 = *(volatile s32 *)&track_iter->unk44;
                  saved_2c = *(volatile s32 *)&track_iter->unk30;
                  saved_4a = *(volatile u8 *)&track_iter->unk4B;
                  track_iter->unk00 = saved_00;
                  track_iter->unk4A = saved_4a;
                  track_count = count_page[D_800869B4_PAGE_INDEX];
                  track_index++;
                  track_iter->unk10 = saved_10;
                  track_iter->unk40 = saved_40;
                  track_iter->unk2C = saved_2c;
                  track_iter++;
                }
                while (track_index < ((u32) track_count));
              }
            }
            else
            {
              track->unk00 = track->unk04;
            }
          }
        }
      }
      if ((event_data & 0xFF) == 6)
      {
        if (D_80084960[channel & 0xFF].unk4D == 0x14)
        {
          if (D_800869B8[0] != 0)
          {
            if (D_800869B4[0] != 0)
            {
              s32 repeat_count;
              register S_80085FA8 *broadcast_track;
              track_index = 0;
              repeat_count = second_data & 0xFF;
              track_count = D_800869B4[0];
              broadcast_track = D_80085FA8;
              do
              {
                broadcast_track->unk08 = repeat_count;
                broadcast_track++;
                track_index++;
              }
              while (track_index < ((u32) track_count));
            }
          }
          else
          {
            track->unk08 = second_data & 0xFF;
            return;
          }
        }
      }
      func_80057D20(channel, event_data & 0xFF, second_data & 0xFF);
      return;

    case 0xE0:
      func_80058494(channel, event_data & 0xFF, second_data & 0xFF);
      return;

    case 0xC0:
      func_8005845C(channel, event_data & 0xFF);
      return;

    case 0xD0:
      func_8005848C(channel, event_data & 0xFF);
      return;
  }
}
