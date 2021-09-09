#ifndef NO_MONITORING
#include "UVWMonitor.h"
#include <stdbool.h>
/* Declare variables for monitoring */
bool uvwState0 = 0;
bool uvwState1 = 0;
bool uvwState2 = 0;
bool uvwState3 = 0;
bool uvwState4 = 0;
bool uvwState5 = 0;
bool uvwState6 = 0;
bool uvwState7 = 0;
bool uvwState8 = 0;
bool uvwState9 = 0;
bool uvwState10 = 0;
bool uvwState11 = 0;
bool uvwState12 = 0;
bool uvwState13 = 0;
bool uvwState14 = 0;
bool uvwState15 = 0;
bool uvwState16 = 0;
bool uvwState17 = 1;
bool uvwState18 = 0;
bool uvwState19 = 0;
bool uvwState20 = 1;
bool uvwState21 = 1;
struct bufType {
  uint32_t b0p0;
  uint32_t b1p0;
  uint32_t b2p0;
  uint32_t b3p0;
  uint32_t b4p0;
  uint32_t b5p0;
  uint32_t b6p0;
  uint32_t b7p0;
  uint32_t b8p0;
  uint32_t b9p0;
  uint32_t b10p0;
  uint32_t b11p0;
  uint32_t b12p0;
  uint32_t b13p0;
  uint32_t b14p0;
  uint32_t b15p0;
  uint32_t b16p0;
  uint32_t b18p0;
  uint32_t b19p0;
} buf = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint32_t b17p0 = 0;
const uint32_t b20p0 = 0;
const uint32_t b21p0 = 0;

const uint32_t lut0[64] = {0xc0180,0xc0001,0xc6000,0xc0000,0xc01c0,0xc0b41,0xc6000,0xc0b44,
    0xc0d88,0xc0c01,0xc6000,0xc0c08,0xc0dc8,0xc0f41,0xc6000,0xc0f4c,
    0xc0180,0xed011,0xc7000,0xed000,0xc01c0,0xedb51,0xc7000,0xedb44,
    0xc0d88,0xedc11,0xc7000,0xedc08,0xc0dc8,0xedf51,0xc7000,0xedf4c,
    0xc0180,0xf0021,0xf6020,0xf0000,0xc01c0,0xf0b61,0xf6020,0xf0b44,
    0xc0d88,0xf0c21,0xf6020,0xf0c08,0xc0dc8,0xf0f61,0xf6020,0xf0f4c,
    0xc0180,0xfd031,0xf7020,0xfd000,0xc01c0,0xfdb71,0xf7020,0xfdb44,
    0xc0d88,0xfdc31,0xf7020,0xfdc08,0xc0dc8,0xfdf71,0xf7020,0xfdf4c};
const uint32_t lut1[128] = {0x1,0x3,0x41,0x1,0x1,0x3,0x1c1,0x1,
    0x1,0x3,0x41,0x1,0x4,0x6,0x1c1,0x4,
    0x1208,0x120a,0x41,0x1208,0x1201,0x120a,0x1c1,0x1201,
    0x1208,0x120a,0x41,0x1208,0x1204,0x120e,0x1c1,0x1204,
    0x6001,0x3,0x6041,0x6001,0x6010,0x1403,0x61d0,0x6010,
    0x6001,0x3,0x6041,0x6001,0x6014,0x1406,0x61d0,0x6014,
    0x7208,0x120a,0x6041,0x7208,0x7210,0x160a,0x61d0,0x7210,
    0x7208,0x120a,0x6041,0x7208,0x7214,0x160e,0x61d0,0x7214,
    0x18001,0x18003,0x41,0x18001,0x18020,0x19803,0x1c1,0x18020,
    0x18001,0x18003,0x41,0x18001,0x18024,0x19806,0x1c1,0x18024,
    0x19208,0x1920a,0x41,0x19208,0x19220,0x19a0a,0x1c1,0x19220,
    0x19208,0x1920a,0x41,0x19208,0x19224,0x19a0e,0x1c1,0x19224,
    0x1e001,0x18003,0x6041,0x1e001,0x1e030,0x19c03,0x61d0,0x1e030,
    0x1e001,0x18003,0x6041,0x1e001,0x1e034,0x19c06,0x61d0,0x1e034,
    0x1f208,0x1920a,0x6041,0x1f208,0x1f230,0x19e0a,0x61d0,0x1f230,
    0x1f208,0x1920a,0x6041,0x1f208,0x1f234,0x19e0e,0x61d0,0x1f234};
const uint16_t lut2[128] = {0x1,0x1,0x1,0x1,0x5,0x5,0x5,0x5,
    0x81,0x81,0x81,0x81,0x1,0x1,0x1,0x1,
    0x8,0x20a,0x8,0x20a,0xc,0x20e,0xc,0x20e,
    0x88,0x28a,0x88,0x28a,0x8,0x20a,0x8,0x20a,
    0x100,0x302,0x140,0x342,0x104,0x306,0x144,0x346,
    0x1a0,0x3a2,0x1e0,0x3e2,0x100,0x302,0x140,0x342,
    0x0,0x200,0x0,0x200,0x4,0x204,0x4,0x204,
    0x80,0x280,0x80,0x280,0x0,0x200,0x0,0x200,
    0x1,0x1,0x11,0x11,0x5,0x5,0x15,0x15,
    0x91,0x91,0x91,0x91,0x1,0x1,0x11,0x11,
    0x8,0x20a,0x18,0x21a,0xc,0x20e,0x1c,0x21e,
    0x98,0x29a,0x98,0x29a,0x8,0x20a,0x18,0x21a,
    0x100,0x302,0x150,0x352,0x104,0x306,0x154,0x356,
    0x1b0,0x3b2,0x1f0,0x3f2,0x100,0x302,0x150,0x352,
    0x0,0x200,0x10,0x210,0x4,0x204,0x14,0x214,
    0x90,0x290,0x90,0x290,0x0,0x200,0x10,0x210};
const uint8_t lut3[128] = {0x1,0x1,0x1,0x2,0x1,0x1,0x2,0x2,
    0x1,0x2,0x1,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2};
const uint8_t lut4[128] = {0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2};
const uint16_t lut5[128] = {0xc0,0xd0,0x6c8,0x6d8,0x0,0x10,0x600,0x610,
    0x1000,0x1010,0x1000,0x1010,0x0,0x10,0x608,0x618,
    0xc0,0xd0,0x6c8,0x6d8,0xb801,0xb801,0xbe01,0xbe01,
    0x1800,0x1810,0x1800,0x1810,0xb800,0xb810,0xbe08,0xbe18,
    0xc0,0xd0,0x6c8,0x6d8,0xc002,0xc002,0xc602,0xc602,
    0xd002,0xd002,0xd002,0xd002,0xc000,0xc010,0xc608,0xc618,
    0xc0,0xd0,0x6c8,0x6d8,0xf803,0xf803,0xfe03,0xfe03,
    0xd802,0xd802,0xd802,0xd802,0xf800,0xf810,0xfe08,0xfe18,
    0xe0,0xf0,0x6e8,0x6f8,0x5a0,0x5b0,0x7a0,0x7b0,
    0x1000,0x1010,0x1000,0x1010,0x5a4,0x5b4,0x7ac,0x7bc,
    0xe0,0xf0,0x6e8,0x6f8,0xbda1,0xbda1,0xbfa1,0xbfa1,
    0x1800,0x1810,0x1800,0x1810,0xbda4,0xbdb4,0xbfac,0xbfbc,
    0xe0,0xf0,0x6e8,0x6f8,0xc5a2,0xc5a2,0xc7a2,0xc7a2,
    0xd002,0xd002,0xd002,0xd002,0xc5a4,0xc5b4,0xc7ac,0xc7bc,
    0xe0,0xf0,0x6e8,0x6f8,0xfda3,0xfda3,0xffa3,0xffa3,
    0xd802,0xd802,0xd802,0xd802,0xfda4,0xfdb4,0xffac,0xffbc};
const uint16_t lut6[128] = {0x8,0x0,0x20,0x0,0x8,0x0,0x20,0x0,
    0x8,0x0,0x20,0x0,0x8,0x0,0x20,0x0,
    0x9,0x1,0x21,0x1,0x8,0x0,0x20,0x0,
    0x8,0x0,0x20,0x0,0x8,0x0,0x20,0x0,
    0x8,0x172,0x30,0x170,0x8,0x172,0x30,0x170,
    0x8,0x172,0x30,0x170,0x8,0x172,0x30,0x170,
    0x9,0x172,0x31,0x171,0x8,0x172,0x30,0x170,
    0x8,0x172,0x30,0x170,0x8,0x172,0x30,0x170,
    0x8,0x184,0x1a4,0x180,0x8,0x184,0x1a4,0x180,
    0x8,0x184,0x1a4,0x180,0x8,0x184,0x1a4,0x180,
    0x9,0x184,0x1a4,0x181,0x8,0x184,0x1a4,0x180,
    0x8,0x184,0x1a4,0x180,0x8,0x184,0x1a4,0x180,
    0x8,0x1f6,0x1b4,0x1f0,0x8,0x1f6,0x1b4,0x1f0,
    0x8,0x1f6,0x1b4,0x1f0,0x8,0x1f6,0x1b4,0x1f0,
    0x9,0x1f6,0x1b4,0x1f1,0x8,0x1f6,0x1b4,0x1f0,
    0x8,0x1f6,0x1b4,0x1f0,0x8,0x1f6,0x1b4,0x1f0};
const uint16_t lut7[128] = {0x8,0x18,0x8,0x18,0xc,0x1c,0xc,0x1c,
    0xca,0xca,0xca,0xca,0xce,0xce,0xce,0xce,
    0x0,0x10,0x800,0x810,0xac,0xbc,0x8ac,0x8bc,
    0xc0,0xd0,0x8c0,0x8d0,0xec,0xfc,0x8ec,0x8fc,
    0x200,0x210,0xa00,0xa10,0x200,0x210,0xa00,0xa10,
    0x200,0x210,0xa00,0xa10,0x200,0x210,0xa00,0xa10,
    0x0,0x10,0x800,0x810,0xad,0xad,0x8ad,0x8ad,
    0xc2,0xc2,0x8c2,0x8c2,0xef,0xef,0x8ef,0x8ef,
    0x8,0x18,0x8,0x18,0xc,0x1c,0xc,0x1c,
    0xca,0xca,0xca,0xca,0xce,0xce,0xce,0xce,
    0xf00,0xf10,0xf00,0xf10,0xfac,0xfbc,0xfac,0xfbc,
    0xfc0,0xfd0,0xfc0,0xfd0,0xfec,0xffc,0xfec,0xffc,
    0x300,0x310,0xb00,0xb10,0x300,0x310,0xb00,0xb10,
    0x300,0x310,0xb00,0xb10,0x300,0x310,0xb00,0xb10,
    0xf00,0xf10,0xf00,0xf10,0xfad,0xfad,0xfad,0xfad,
    0xfc2,0xfc2,0xfc2,0xfc2,0xfef,0xfef,0xfef,0xfef};
const uint8_t lut8[128] = {0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0x10,0x0,0x0,0x0,0x14,0x4,0x4,0x4,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0x18,0xb8,0x0,0xbd,0x1c,0xbc,0x4,0xbd,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc0,0x0,0xc6,0xd6,0xc4,0x4,0xc6,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xf8,0x0,0xff,0xde,0xfc,0x4,0xff,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = ((apValues & 64)>0?1:0) | ((apValues & 128)>0?2:0) | (uvwState7>0?4:0) | (uvwState8>0?8:0) | (uvwState15>0?16:0) | (uvwState16>0?32:0);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((apValues & 256)>0?4:0) | (uvwState18>0?8:0) | (uvwState19>0?16:0) | (uvwState20>0?32:0) | (uvwState21>0?64:0) | (apValues & 3);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = ((lut0output & 8192)>0?2:0) | (uvwState14 & 1) | (apValues & 60) | (lut1output & 64);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (lut0output & 1) | (lut1output & 2) | (lut2output & 124);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = ((lut3output & 1)>0?4:0) | (uvwState13>0?64:0) | (lut1output & 1) | (lut2output & 10) | (lut0output & 48);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState4>0?2:0) | (uvwState11>0?16:0) | (uvwState12>0?32:0) | (uvwState3>0?64:0) | (lut4output & 1) | (apValues & 12);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState9>0?32:0) | (uvwState10>0?64:0) | (apValues & 3) | (lut0output & 12) | (lut5output & 16);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState14>0?2:0) | (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState13>0?64:0) | (lut6output & 1) | (apValues & 48);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = (uvwState1>0?32:0) | (uvwState2>0?64:0) | (apValues & 3) | (lut5output & 12) | (lut7output & 16);
  uint32_t lut8output = lut8[lut8input];
  if ((lut0output & 2)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 1)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 2)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 4)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 8)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 1)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 4)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 8)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 1)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 2)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 16)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 32)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 2)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 4)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 8)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 16)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 32)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut8output & 8)) {
  } else if ((lut6output & 8)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut8output & 32)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut8output & 64)) {
  }
  if ((lut5output & 32)) {
  } else if ((lut5output & 64)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 256)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut5output & 512)) {
  }
  if ((lut7output & 4)) {
  } else if ((lut2output & 1)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 32)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut7output & 64)) {
  }
  if ((lut0output & 64)) {
  } else if ((lut0output & 128)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 512)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut0output & 1024)) {
  }
  if ((lut6output & 16)) {
  } else if ((lut1output & 64)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 64)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut6output & 128)) {
  }
  if ((lut5output & 2048)) {
  } else if ((lut2output & 128)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 8192)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut5output & 16384)) {
  }
  if ((lut7output & 256)) {
  } else if ((lut2output & 256)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 1024)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut2output & 512)) {
  }
  if ((lut0output & 4096)) {
  } else if ((lut0output & 8192)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 32768)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut0output & 65536)) {
  }
  if ((lut0output & 262144)) {
  }
  if ((lut1output & 128)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 512)) {
  } else if ((lut1output & 1024)) {
        buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  } else if ((lut1output & 2048)) {
        buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  if ((lut1output & 8192)) {
  }
  if ((lut1output & 32768)) {
  }
  uvwState0 = (lut8output & 4);
  uvwState1 = (lut8output & 16);
  uvwState2 = (lut8output & 128);
  uvwState3 = (lut5output & 128);
  uvwState4 = (lut5output & 1024);
  uvwState5 = (lut7output & 8);
  uvwState6 = (lut7output & 128);
  uvwState7 = (lut0output & 256);
  uvwState8 = (lut0output & 2048);
  uvwState9 = (lut6output & 32);
  uvwState10 = (lut6output & 256);
  uvwState11 = (lut5output & 4096);
  uvwState12 = (lut5output & 32768);
  uvwState13 = (lut7output & 512);
  uvwState14 = (lut7output & 2048);
  uvwState15 = (lut0output & 16384);
  uvwState16 = (lut0output & 131072);
  uvwState17 = (lut0output & 524288);
  uvwState18 = (lut1output & 256);
  uvwState19 = (lut1output & 4096);
  uvwState20 = (lut1output & 16384);
  uvwState21 = (lut1output & 65536);
}

#endif
/* Decoding information for the buffers:
   -------------------------------------

 - UVW state 0 with LTL subformula (Polish notation):
    Bits 0 to 17: previous buffer
    Bits 18 to 26: propositions
    Bits 27 to 31: incoming transition
       -> Value 0 for transition from UVW state 1
       -> Value 1 for transition from UVW state 2
       -> Value 2 for transition from UVW state 3
       -> Value 3 for transition from UVW state 4
       -> Value 4 for transition from UVW state 5
       -> Value 5 for transition from UVW state 6
       -> Value 6 for transition from UVW state 7
       -> Value 7 for transition from UVW state 8
       -> Value 8 for transition from UVW state 9
       -> Value 9 for transition from UVW state 10
       -> Value 10 for transition from UVW state 11
       -> Value 11 for transition from UVW state 12
       -> Value 12 for transition from UVW state 13
       -> Value 13 for transition from UVW state 14
       -> Value 14 for transition from UVW state 15
       -> Value 15 for transition from UVW state 16
       -> Value 16 for transition from UVW state 17
       -> Value 17 for transition from UVW state 18
       -> Value 18 for transition from UVW state 19
       -> Value 19 for transition from UVW state 20
       -> Value 20 for transition from UVW state 21
 - UVW state 1 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 2 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 3 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 4 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 5 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 6 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 7 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 8 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 9 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 10 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 11 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 12 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 13 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 14 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 15 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 16 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 17 with LTL subformula (Polish notation):
    Initial state only
 - UVW state 18 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 19 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
    Bits 9 to 9: incoming transition
       -> Value 0 for transition from UVW state 20
       -> Value 1 for transition from UVW state 21
 - UVW state 20 with LTL subformula (Polish notation):
    Initial state only
 - UVW state 21 with LTL subformula (Polish notation):
    Initial state only


UVW on which the monitor is based:
 UVW with 22 states and initial states [17, 20, 21]:
 - State No. 0 with name reject (rej.):
   - t.t.s. 0 for TRUE
 - State No. 1 with name || reject R & ! a1 a2 | | & ! a1 ! a2 & ! a1 a2 & & a1 ! a2 R & ! a1 a2 | & ! a1 a2 & a1 ! a2:
   - t.t.s. 1 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for ite(a1, a2, FALSE)
   - t.t.s. 2 for a1
 - State No. 2 with name || reject || reject || reject || reject R & ! a1 a2 | & ! a1 a2 & a1 ! a2:
   - t.t.s. 2 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for ite(a1, a2, (~ a2))
 - State No. 3 with name || reject R & ! b1 b2 | | & ! b1 ! b2 & ! b1 b2 & & b1 ! b2 R & ! b1 b2 | & ! b1 b2 & b1 ! b2:
   - t.t.s. 3 for ite(b1, TRUE, (~ b2))
   - t.t.s. 0 for ite(b1, b2, FALSE)
   - t.t.s. 4 for b1
 - State No. 4 with name || reject || reject || reject || reject R & ! b1 b2 | & ! b1 b2 & b1 ! b2:
   - t.t.s. 4 for ite(b1, TRUE, (~ b2))
   - t.t.s. 0 for ite(b1, b2, (~ b2))
 - State No. 5 with name || reject R & ! c1 c2 | | & ! c1 ! c2 & ! c1 c2 & & c1 ! c2 R & ! c1 c2 | & ! c1 c2 & c1 ! c2:
   - t.t.s. 5 for ite(c1, TRUE, (~ c2))
   - t.t.s. 0 for ite(c1, c2, FALSE)
   - t.t.s. 6 for c1
 - State No. 6 with name || reject || reject || reject || reject R & ! c1 c2 | & ! c1 c2 & c1 ! c2:
   - t.t.s. 6 for ite(c1, TRUE, (~ c2))
   - t.t.s. 0 for ite(c1, c2, (~ c2))
 - State No. 7 with name || reject R & ! d1 d2 | | & ! d1 ! d2 & ! d1 d2 & & d1 ! d2 R & ! d1 d2 | & ! d1 d2 & d1 ! d2:
   - t.t.s. 7 for ite(d1, TRUE, (~ d2))
   - t.t.s. 0 for ite(d1, d2, FALSE)
   - t.t.s. 8 for d1
 - State No. 8 with name || reject || reject || reject || reject R & ! d1 d2 | & ! d1 d2 & d1 ! d2:
   - t.t.s. 8 for ite(d1, TRUE, (~ d2))
   - t.t.s. 0 for ite(d1, d2, (~ d2))
 - State No. 9 with name || reject R & ! a1 ! a2 | | & ! a1 a2 & ! a1 ! a2 & & a1 a2 R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2:
   - t.t.s. 9 for ite(a1, TRUE, a2)
   - t.t.s. 0 for (~ ite(a1, a2, TRUE))
   - t.t.s. 10 for a1
 - State No. 10 with name || reject || reject || reject || reject R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2:
   - t.t.s. 10 for ite(a1, TRUE, a2)
   - t.t.s. 0 for (~ ite(a1, a2, (~ a2)))
 - State No. 11 with name || reject R & ! b1 ! b2 | | & ! b1 b2 & ! b1 ! b2 & & b1 b2 R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2:
   - t.t.s. 11 for ite(b1, TRUE, b2)
   - t.t.s. 0 for (~ ite(b1, b2, TRUE))
   - t.t.s. 12 for b1
 - State No. 12 with name || reject || reject || reject || reject R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2:
   - t.t.s. 12 for ite(b1, TRUE, b2)
   - t.t.s. 0 for (~ ite(b1, b2, (~ b2)))
 - State No. 13 with name || reject R & ! c1 ! c2 | | & ! c1 c2 & ! c1 ! c2 & & c1 c2 R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2:
   - t.t.s. 13 for ite(c1, TRUE, c2)
   - t.t.s. 0 for (~ ite(c1, c2, TRUE))
   - t.t.s. 14 for c1
 - State No. 14 with name || reject || reject || reject || reject R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2:
   - t.t.s. 14 for ite(c1, TRUE, c2)
   - t.t.s. 0 for (~ ite(c1, c2, (~ c2)))
 - State No. 15 with name || reject R & ! d1 ! d2 | | & ! d1 d2 & ! d1 ! d2 & & d1 d2 R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2:
   - t.t.s. 15 for ite(d1, TRUE, d2)
   - t.t.s. 0 for (~ ite(d1, d2, TRUE))
   - t.t.s. 16 for d1
 - State No. 16 with name || reject || reject || reject || reject R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2:
   - t.t.s. 16 for ite(d1, TRUE, d2)
   - t.t.s. 0 for (~ ite(d1, d2, (~ d2)))
 - State No. 17 with name & & & & & & & & & & & & & & & & & & G | | d1 ! d2 R & ! d1 ! d2 | | & ! d1 d2 & ! d1 ! d2 & & d1 d2 R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2 & G | | c1 ! c2 R & ! c1 ! c2 | | & ! c1 c2 & ! c1 ! c2 & & c1 c2 R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2 & G | | b1 ! b2 R & ! b1 ! b2 | | & ! b1 b2 & ! b1 ! b2 & & b1 b2 R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2 & G | | a1 ! a2 R & ! a1 ! a2 | | & ! a1 a2 & ! a1 ! a2 & & a1 a2 R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2 & G | | d1 d2 R & ! d1 d2 | | & ! d1 ! d2 & ! d1 d2 & & d1 ! d2 R & ! d1 d2 | & ! d1 d2 & d1 ! d2 & G | | c1 c2 R & ! c1 c2 | | & ! c1 ! c2 & ! c1 c2 & & c1 ! c2 R & ! c1 c2 | & ! c1 c2 & c1 ! c2 & G | | b1 b2 R & ! b1 b2 | | & ! b1 ! b2 & ! b1 b2 & & b1 ! b2 R & ! b1 b2 | & ! b1 b2 & b1 ! b2 G | | a1 a2 R & ! a1 a2 | | & ! a1 ! a2 & ! a1 a2 & & a1 ! a2 R & ! a1 a2 | & ! a1 a2 & a1 ! a2 G | | a1 ! a2 | b1 ! b2 G | | a1 ! a2 | d1 ! d2 G | | b1 ! b2 | a1 ! a2 G | | b1 ! b2 | c1 ! c2 G | | c1 ! c2 | b1 ! b2 G | | c1 ! c2 | d1 ! d2 G | | d1 ! d2 | a1 ! a2 G | | d1 ! d2 | c1 ! c2 G | | ! a1 a2 | ! b1 b2 G | | ! a1 a2 | ! d1 d2 G | | ! b1 b2 | ! a1 a2 G | | ! b1 b2 | ! c1 c2 G | | ! c1 c2 | ! b1 b2 G | | ! c1 c2 | ! d1 d2 G | | ! d1 d2 | ! a1 a2 G | | ! d1 d2 | ! c1 c2 G | | | a1 ! a2 ! m X | ! m & ! a1 a2:
   - t.t.s. 15 for (~ ite(d1, TRUE, (~ d2)))
   - t.t.s. 17 for TRUE
   - t.t.s. 13 for (~ ite(c1, TRUE, (~ c2)))
   - t.t.s. 11 for (~ ite(b1, TRUE, (~ b2)))
   - t.t.s. 9 for (~ ite(a1, TRUE, (~ a2)))
   - t.t.s. 7 for (~ ite(d1, TRUE, d2))
   - t.t.s. 5 for (~ ite(c1, TRUE, c2))
   - t.t.s. 3 for (~ ite(b1, TRUE, b2))
   - t.t.s. 1 for (~ ite(a1, TRUE, a2))
   - t.t.s. 0 for (~ ite(a1, ite(a2, ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)), ite(c1, c2, ite(c2, ite(d1, TRUE, (~ d2)), TRUE))), ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), (~ c2)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)))), ite(b1, ite(b2, ite(c1, ite(d1, d2, TRUE), ite(c2, ite(d1, d2, (~ d2)), ite(d1, d2, TRUE))), FALSE), ite(b2, ite(c1, ite(d1, d2, TRUE), (~ ite(c2, TRUE, (~ ite(d1, d2, TRUE))))), ite(c1, ite(d1, d2, TRUE), ite(c2, ite(d1, d2, (~ d2)), ite(d1, d2, TRUE)))))), ite(a2, ite(b1, ite(b2, ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), ite(d1, d2, (~ d2))), ite(d1, TRUE, (~ d2))), ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), FALSE), ite(d1, TRUE, (~ d2)))), (~ ite(b2, TRUE, (~ ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), ite(d1, d2, (~ d2))), ite(d1, TRUE, (~ d2))))))), ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)), ite(c1, c2, ite(c2, ite(d1, TRUE, (~ d2)), TRUE))), ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), (~ c2)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)))))))
   - t.t.s. 18 for (~ ite(a1, TRUE, (~ ite(a2, m, FALSE))))
 - State No. 18 with name || reject | ! m & ! a1 a2:
   - t.t.s. 0 for ite(a1, m, (~ ite(a2, TRUE, (~ m))))
 - State No. 19 with name || reject R & ! a1 a2 | & & | a2 m | ! a1 m | ! a1 a2 X 0:
   - t.t.s. 19 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for (~ ite(a1, ite(a2, m, FALSE), ite(a2, TRUE, m)))
 - State No. 20 with name & R & a1 ! a2 | | | ! a1 a2 ! m X R & ! a1 a2 | & & | a2 m | ! a1 m | ! a1 a2 X 0 R & a1 ! a2 | & | a1 ! m | ! a2 ! m X 0:
   - t.t.s. 20 for ite(a1, a2, TRUE)
   - t.t.s. 19 for (~ ite(a1, ite(a2, TRUE, (~ m)), TRUE))
   - t.t.s. 0 for ite(a1, ite(a2, m, FALSE), m)
 - State No. 21 with name & R & ! a1 a2 | | | ! a1 a2 ! m X R & ! a1 a2 | & & | a2 m | ! a1 m | ! a1 a2 X 0 R & ! a1 a2 | & | | a1 a2 ! m | | ! a1 ! a2 ! m X 0:
   - t.t.s. 21 for ite(a1, TRUE, (~ a2))
   - t.t.s. 19 for (~ ite(a1, ite(a2, TRUE, (~ m)), TRUE))
   - t.t.s. 0 for ite(a1, ite(a2, m, FALSE), (~ ite(a2, TRUE, (~ m))))

*/

/* Lookup-Table contents:
- LUT 0 has:
  -> Inputs d1 d2 uvwState7 uvwState8 uvwState15 uvwState16
  -> Outputs new_n52 uvwState0incoming0 uvwState0incoming7 uvwState0incoming8 uvwState0incoming15 uvwState0incoming16 uvwState7incoming0 uvwState7incoming1 uvwState7Next uvwState8incoming0 uvwState8incoming1 uvwState8Next uvwState15incoming0 uvwState15incoming1 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs a1 a2 m uvwState18 uvwState19 uvwState20 uvwState21
  -> Outputs new_n89 new_n34 uvwState0incoming18 uvwState0incoming19 uvwState0incoming20 uvwState0incoming21 uvwState9incoming1 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 2 has:
  -> Inputs uvwState14 uvwState15incoming1 b1 b2 c1 c2 uvwState9incoming1
  -> Outputs uvwState5incoming1 uvwState0incoming14 new_n40 new_n46 new_n66 new_n70 new_n74 uvwState11incoming1 uvwState13incoming1 uvwState14incoming1
- LUT 3 has:
  -> Inputs new_n52 new_n34 new_n40 new_n46 new_n66 new_n70 new_n74
  -> Outputs new_n77 uvwState0incoming17
- LUT 4 has:
  -> Inputs new_n89 uvwState0incoming14 new_n77 new_n46 uvwState0incoming15 uvwState0incoming16 uvwState13
  -> Outputs new_n94 uvwState0incoming13
- LUT 5 has:
  -> Inputs new_n94 uvwState4 b1 b2 uvwState11 uvwState12 uvwState3
  -> Outputs uvwState0incoming11 uvwState0incoming12 uvwState0incoming3 uvwState0incoming4 new_n96 uvwState3incoming0 uvwState3incoming1 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 6 has:
  -> Inputs a1 a2 uvwState0incoming7 uvwState0incoming8 new_n96 uvwState9 uvwState10
  -> Outputs new_n100 uvwState0incoming9 uvwState0incoming10 uvwState1incoming1 uvwState9incoming0 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 7 has:
  -> Inputs new_n100 uvwState14 uvwState5 uvwState6 c1 c2 uvwState13
  -> Outputs uvwState0incoming5 uvwState0incoming6 uvwState5incoming0 uvwState5Next new_n102 uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13Next uvwState14incoming0 uvwState14Next
- LUT 8 has:
  -> Inputs a1 a2 uvwState0incoming3 uvwState0incoming4 new_n102 uvwState1 uvwState2
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0Next uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next
*/
