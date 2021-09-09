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

const uint16_t lut0[128] = {0xc180,0xc180,0xe000,0xe000,0xc181,0xc191,0xe001,0xe011,
    0xd180,0xd180,0xf000,0xf000,0xc180,0xc180,0xe000,0xe000,
    0xc1a0,0xc1a0,0xe000,0xe000,0xc1a1,0xc1b1,0xe001,0xe011,
    0xd1a0,0xd1a0,0xf000,0xf000,0xc1a0,0xc1a0,0xe000,0xe000,
    0xcdc0,0xcdc0,0xe000,0xe000,0xcdc1,0xcdd1,0xe001,0xe011,
    0xddc0,0xddc0,0xf000,0xf000,0xcdc0,0xcdc0,0xe000,0xe000,
    0xcde0,0xcde0,0xe000,0xe000,0xcde1,0xcdf1,0xe001,0xe011,
    0xdde0,0xdde0,0xf000,0xf000,0xcde0,0xcde0,0xe000,0xe000,
    0xc002,0xc002,0xc000,0xc000,0xc003,0xc013,0xc001,0xc011,
    0xd002,0xd002,0xd000,0xd000,0xc002,0xc002,0xc000,0xc000,
    0xcb22,0xcb22,0xcb28,0xcb28,0xcb23,0xcb33,0xcb29,0xcb39,
    0xdb22,0xdb22,0xdb28,0xdb28,0xcb22,0xcb22,0xcb28,0xcb28,
    0xcc02,0xcc02,0xcc40,0xcc40,0xcc03,0xcc13,0xcc41,0xcc51,
    0xdc02,0xdc02,0xdc40,0xdc40,0xcc02,0xcc02,0xcc40,0xcc40,
    0xcf22,0xcf22,0xcf68,0xcf68,0xcf23,0xcf33,0xcf69,0xcf79,
    0xdf22,0xdf22,0xdf68,0xdf68,0xcf22,0xcf22,0xcf68,0xcf68};
const uint32_t lut1[128] = {0x1,0x5,0x41,0x1,0x1,0x5,0x1c1,0x1,
    0x1,0x5,0x41,0x1,0x2,0x6,0x1c1,0x2,
    0x1208,0x120c,0x41,0x1208,0x1201,0x120c,0x1c1,0x1201,
    0x1208,0x120c,0x41,0x1208,0x1202,0x120e,0x1c1,0x1202,
    0x6001,0x5,0x6041,0x6001,0x6010,0x1405,0x61d0,0x6010,
    0x6001,0x5,0x6041,0x6001,0x6012,0x1406,0x61d0,0x6012,
    0x7208,0x120c,0x6041,0x7208,0x7210,0x160c,0x61d0,0x7210,
    0x7208,0x120c,0x6041,0x7208,0x7212,0x160e,0x61d0,0x7212,
    0x18001,0x18005,0x41,0x18001,0x18020,0x19805,0x1c1,0x18020,
    0x18001,0x18005,0x41,0x18001,0x18022,0x19806,0x1c1,0x18022,
    0x19208,0x1920c,0x41,0x19208,0x19220,0x19a0c,0x1c1,0x19220,
    0x19208,0x1920c,0x41,0x19208,0x19222,0x19a0e,0x1c1,0x19222,
    0x1e001,0x18005,0x6041,0x1e001,0x1e030,0x19c05,0x61d0,0x1e030,
    0x1e001,0x18005,0x6041,0x1e001,0x1e032,0x19c06,0x61d0,0x1e032,
    0x1f208,0x1920c,0x6041,0x1f208,0x1f230,0x19e0c,0x61d0,0x1f230,
    0x1f208,0x1920c,0x6041,0x1f208,0x1f232,0x19e0e,0x61d0,0x1f232};
const uint16_t lut2[128] = {0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x8,0x8,0x8,0x8,0x1689,0x1689,0x1689,0x1689,
    0x180a,0x180a,0x180a,0x180a,0x1e8b,0x1e8b,0x1e8b,0x1e8b,
    0x300,0x340,0x320,0x360,0x380,0x3c0,0x3a0,0x3e0,
    0x1b02,0x1b42,0x1b22,0x1b62,0x1b82,0x1bc2,0x1ba2,0x1be2,
    0x0,0x0,0x0,0x0,0x1680,0x1680,0x1680,0x1680,
    0x1800,0x1800,0x1800,0x1800,0x1e80,0x1e80,0x1e80,0x1e80,
    0x4,0x14,0x14,0x14,0x4,0x14,0x14,0x14,
    0x4,0x14,0x14,0x14,0x4,0x14,0x14,0x14,
    0x8,0x18,0x18,0x18,0x1689,0x1699,0x1699,0x1699,
    0x180a,0x181a,0x181a,0x181a,0x1e8b,0x1e9b,0x1e9b,0x1e9b,
    0x300,0x350,0x330,0x370,0x380,0x3d0,0x3b0,0x3f0,
    0x1b02,0x1b52,0x1b32,0x1b72,0x1b82,0x1bd2,0x1bb2,0x1bf2,
    0x0,0x10,0x10,0x10,0x1680,0x1690,0x1690,0x1690,
    0x1800,0x1810,0x1810,0x1810,0x1e80,0x1e90,0x1e90,0x1e90};
const uint8_t lut3[128] = {0x1,0x1,0x1,0x1,0x1,0x2,0x2,0x2,
    0x1,0x2,0x2,0x2,0x1,0x2,0x2,0x2,
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
const uint8_t lut4[128] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x2,0x0,0x0,0x0,0x2,0x0,0x0,
    0x0,0x2,0x0,0x0,0x0,0x2,0x0,0x0,
    0x10,0x10,0x10,0x10,0x18,0x18,0x18,0x18,
    0xd4,0xd4,0xd4,0xd4,0xdc,0xdc,0xdc,0xdc,
    0x10,0x12,0x10,0x10,0x18,0x1a,0x18,0x18,
    0xd4,0xd4,0xd4,0xd4,0xdc,0xdc,0xdc,0xdc,
    0x0,0x0,0x0,0x0,0xb9,0xb9,0xb9,0xb9,
    0xc4,0xc4,0xc4,0xc4,0xfd,0xfd,0xfd,0xfd,
    0x0,0x2,0x0,0x0,0xb9,0xb9,0xb9,0xb9,
    0xc4,0xc4,0xc4,0xc4,0xfd,0xfd,0xfd,0xfd,
    0x0,0x0,0x0,0x0,0xb8,0xb8,0xb8,0xb8,
    0xc0,0xc0,0xc0,0xc0,0xf8,0xf8,0xf8,0xf8,
    0x0,0x2,0x0,0x0,0xb8,0xba,0xb8,0xb8,
    0xc0,0xc2,0xc0,0xc0,0xf8,0xfa,0xf8,0xf8};
const uint8_t lut5[64] = {0x2,0x2,0x6,0x2,0x0,0x0,0x4,0x0,
    0x10,0x10,0x14,0x10,0x0,0x0,0x4,0x0,
    0x2,0x2,0x6,0x2,0xc1,0xc1,0xc1,0xc1,
    0xd1,0xd1,0xd1,0xd1,0xc0,0xc0,0xc4,0xc0,
    0x2,0x2,0x6,0x2,0xb8,0xb8,0xb8,0xb8,
    0x18,0x18,0x1c,0x18,0xb8,0xb8,0xbc,0xb8,
    0x2,0x2,0x6,0x2,0xf9,0xf9,0xf9,0xf9,
    0xd9,0xd9,0xd9,0xd9,0xf8,0xf8,0xfc,0xf8};
const uint16_t lut6[128] = {0xc0,0x0,0x1000,0x0,0xc1,0x1,0x1001,0x1,
    0x6d0,0x600,0x1000,0x610,0x6d1,0x601,0x1001,0x611,
    0xc0,0xb804,0x1800,0xb800,0xc1,0xb804,0x1801,0xb801,
    0x6d0,0xbe04,0x1800,0xbe10,0x6d1,0xbe04,0x1801,0xbe11,
    0xc0,0xc008,0xd008,0xc000,0xc1,0xc008,0xd008,0xc001,
    0x6d0,0xc608,0xd008,0xc610,0x6d1,0xc608,0xd008,0xc611,
    0xc0,0xf80c,0xd808,0xf800,0xc1,0xf80c,0xd808,0xf801,
    0x6d0,0xfe0c,0xd808,0xfe10,0x6d1,0xfe0c,0xd808,0xfe11,
    0xe0,0x5a0,0x1000,0x5a2,0xe1,0x5a1,0x1001,0x5a3,
    0x6f0,0x7a0,0x1000,0x7b2,0x6f1,0x7a1,0x1001,0x7b3,
    0xe0,0xbda4,0x1800,0xbda2,0xe1,0xbda4,0x1801,0xbda3,
    0x6f0,0xbfa4,0x1800,0xbfb2,0x6f1,0xbfa4,0x1801,0xbfb3,
    0xe0,0xc5a8,0xd008,0xc5a2,0xe1,0xc5a8,0xd008,0xc5a3,
    0x6f0,0xc7a8,0xd008,0xc7b2,0x6f1,0xc7a8,0xd008,0xc7b3,
    0xe0,0xfdac,0xd808,0xfda2,0xe1,0xfdac,0xd808,0xfda3,
    0x6f0,0xffac,0xd808,0xffb2,0x6f1,0xffac,0xd808,0xffb3};
const uint8_t lut7[128] = {0x10,0x11,0xd4,0xd4,0x18,0x19,0xdc,0xdc,
    0x10,0x10,0xd4,0xd4,0x18,0x18,0xdc,0xdc,
    0x0,0x1,0xc0,0xc1,0xb8,0xb9,0xf8,0xf9,
    0x0,0x0,0xc0,0xc0,0xb8,0xb8,0xf8,0xf8,
    0x0,0x1,0x0,0x1,0x0,0x1,0x0,0x1,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x1,0xc4,0xc4,0xba,0xba,0xfe,0xfe,
    0x0,0x0,0xc4,0xc4,0xba,0xba,0xfe,0xfe,
    0x10,0x10,0xd4,0xd4,0x18,0x18,0xdc,0xdc,
    0x10,0x10,0xd4,0xd4,0x18,0x18,0xdc,0xdc,
    0x0,0x0,0xc0,0xc0,0xb8,0xb8,0xf8,0xf8,
    0x0,0x0,0xc0,0xc0,0xb8,0xb8,0xf8,0xf8,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0xc4,0xc4,0xba,0xba,0xfe,0xfe,
    0x0,0x0,0xc4,0xc4,0xba,0xba,0xfe,0xfe};
const uint8_t lut8[128] = {0x14,0x10,0x14,0x14,0x4,0x0,0x4,0x4,
    0x4,0x0,0x4,0x4,0x4,0x0,0x4,0x4,
    0x14,0x14,0x14,0x14,0x4,0x4,0x4,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0xd6,0xd6,0xd6,0xd6,0xc4,0xc0,0xc4,0xc4,
    0x4,0x0,0x4,0x4,0xc6,0xc6,0xc6,0xc6,
    0xd6,0xd6,0xd6,0xd6,0xc4,0xc4,0xc4,0xc4,
    0x4,0x4,0x4,0x4,0xc6,0xc6,0xc6,0xc6,
    0x1c,0x18,0x1c,0x1c,0xbc,0xb8,0xbc,0xbc,
    0x4,0x0,0x4,0x4,0xbd,0xbd,0xbd,0xbd,
    0x1c,0x1c,0x1c,0x1c,0xbc,0xbc,0xbc,0xbc,
    0x4,0x4,0x4,0x4,0xbd,0xbd,0xbd,0xbd,
    0xde,0xde,0xde,0xde,0xfc,0xf8,0xfc,0xfc,
    0x4,0x0,0x4,0x4,0xff,0xff,0xff,0xff,
    0xde,0xde,0xde,0xde,0xfc,0xfc,0xfc,0xfc,
    0x4,0x4,0x4,0x4,0xff,0xff,0xff,0xff};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = ((apValues & 128)>0?2:0) | (uvwState7>0?16:0) | (uvwState8>0?32:0) | (uvwState11 & 1) | (apValues & 76);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((apValues & 256)>0?4:0) | (uvwState18>0?8:0) | (uvwState19>0?16:0) | (uvwState20>0?32:0) | (uvwState21>0?64:0) | (apValues & 3);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = ((lut0output & 8192)>0?1:0) | ((lut0output & 4096)>0?2:0) | (uvwState13>0?4:0) | (uvwState14>0?8:0) | (apValues & 48) | (lut1output & 64);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (lut0output & 3) | (lut1output & 4) | (lut2output & 120);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = (uvwState15>0?4:0) | (uvwState16>0?8:0) | ((lut3output & 1)>0?16:0) | ((apValues & 128)>0?32:0) | (lut1output & 1) | (lut2output & 2) | (apValues & 64);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState12>0?16:0) | (uvwState11>0?32:0) | (lut2output & 1) | (lut4output & 2) | (apValues & 12);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState2>0?8:0) | (uvwState9>0?16:0) | (uvwState10>0?32:0) | (uvwState1>0?64:0) | (apValues & 3) | (lut5output & 4);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState6>0?2:0) | (uvwState5>0?4:0) | (lut6output & 1) | (lut0output & 72) | (apValues & 48);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = (uvwState4>0?32:0) | (uvwState3>0?64:0) | (lut7output & 1) | (lut6output & 18) | (apValues & 12);
  uint32_t lut8output = lut8[lut8input];
  if ((lut0output & 4)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 16)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 1)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 2)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 4)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 8)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 64)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 8)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 16)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 1)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 1)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 2)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 1)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 4)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 2)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 2)) {
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
  if ((lut6output & 32)) {
  } else if ((lut6output & 64)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 256)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut6output & 512)) {
  }
  if ((lut8output & 8)) {
  } else if ((lut5output & 2)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut8output & 32)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut8output & 64)) {
  }
  if ((lut7output & 8)) {
  } else if ((lut2output & 4)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 32)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut7output & 64)) {
  }
  if ((lut0output & 32)) {
  } else if ((lut0output & 128)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 512)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut0output & 1024)) {
  }
  if ((lut6output & 2048)) {
  } else if ((lut1output & 64)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 8192)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut6output & 16384)) {
  }
  if ((lut5output & 8)) {
  } else if ((lut0output & 4096)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 32)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut5output & 64)) {
  }
  if ((lut2output & 128)) {
  } else if ((lut2output & 256)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 1024)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut2output & 2048)) {
  }
  if ((lut4output & 8)) {
  } else if ((lut0output & 8192)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 32)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut4output & 64)) {
  }
  if ((lut0output & 16384)) {
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
  uvwState1 = (lut6output & 128);
  uvwState2 = (lut6output & 1024);
  uvwState3 = (lut8output & 16);
  uvwState4 = (lut8output & 128);
  uvwState5 = (lut7output & 16);
  uvwState6 = (lut7output & 128);
  uvwState7 = (lut0output & 256);
  uvwState8 = (lut0output & 2048);
  uvwState9 = (lut6output & 4096);
  uvwState10 = (lut6output & 32768);
  uvwState11 = (lut5output & 16);
  uvwState12 = (lut5output & 128);
  uvwState13 = (lut2output & 512);
  uvwState14 = (lut2output & 4096);
  uvwState15 = (lut4output & 16);
  uvwState16 = (lut4output & 128);
  uvwState17 = (lut0output & 32768);
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
  -> Inputs uvwState11 d2 b1 b2 uvwState7 uvwState8 d1
  -> Outputs new_n40 new_n52 uvwState0incoming0 uvwState0incoming7 uvwState0incoming11 uvwState7incoming0 uvwState0incoming8 uvwState7incoming1 uvwState7Next uvwState8incoming0 uvwState8incoming1 uvwState8Next uvwState11incoming1 uvwState15incoming1 uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs a1 a2 m uvwState18 uvwState19 uvwState20 uvwState21
  -> Outputs new_n89 uvwState0incoming18 new_n34 uvwState0incoming19 uvwState0incoming20 uvwState0incoming21 uvwState9incoming1 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 2 has:
  -> Inputs uvwState15incoming1 uvwState11incoming1 uvwState13 uvwState14 c1 c2 uvwState9incoming1
  -> Outputs uvwState0incoming13 uvwState0incoming14 uvwState5incoming1 new_n46 new_n66 new_n70 new_n74 uvwState13incoming0 uvwState13incoming1 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next
- LUT 3 has:
  -> Inputs new_n40 new_n52 new_n34 new_n46 new_n66 new_n70 new_n74
  -> Outputs new_n77 uvwState0incoming17
- LUT 4 has:
  -> Inputs new_n89 uvwState0incoming14 uvwState15 uvwState16 new_n77 d2 d1
  -> Outputs uvwState0incoming15 new_n93 uvwState0incoming16 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 5 has:
  -> Inputs uvwState0incoming13 new_n93 b1 b2 uvwState12 uvwState11
  -> Outputs uvwState0incoming12 uvwState3incoming1 new_n96 uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 6 has:
  -> Inputs a1 a2 new_n96 uvwState2 uvwState9 uvwState10 uvwState1
  -> Outputs new_n98 uvwState0incoming1 uvwState0incoming9 uvwState0incoming10 uvwState0incoming2 uvwState1incoming0 uvwState1incoming1 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next uvwState9incoming0 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 7 has:
  -> Inputs new_n98 uvwState6 uvwState5 uvwState0incoming7 c1 c2 uvwState0incoming8
  -> Outputs new_n102 uvwState0incoming5 uvwState0incoming6 uvwState5incoming0 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next
- LUT 8 has:
  -> Inputs new_n102 uvwState0incoming1 b1 b2 uvwState0incoming2 uvwState4 uvwState3
  -> Outputs uvwState0incoming3 uvwState0incoming4 uvwState0Next uvwState3incoming0 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next
*/
