#ifndef SHARED_SLUS_CD_CALLBACK_H
#define SHARED_SLUS_CD_CALLBACK_H

/* This callback is defined as set_byte_one in src/slus/code.c at
 * 0x8003E140; Control_CD(0xFF) invokes it on a status byte. */
void set_byte_one(unsigned char *flag);

#endif
