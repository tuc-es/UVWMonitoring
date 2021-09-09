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

const uint16_t lut0[64] = {0x628,0x609,0x648,0x608,0x62a,0x603,0x64a,0x60a,
    0x6a8,0x689,0x6c0,0x688,0x628,0x609,0x648,0x608,
    0x62c,0x605,0x64c,0x60c,0x62e,0x607,0x64e,0x60e,
    0x6ac,0x685,0x6c4,0x68c,0x62c,0x605,0x64c,0x60c,
    0x728,0x709,0x740,0x708,0x72a,0x703,0x742,0x70a,
    0x7a8,0x789,0x7c0,0x788,0x728,0x709,0x740,0x708,
    0x628,0x609,0x648,0x608,0x62a,0x603,0x64a,0x60a,
    0x6a8,0x689,0x6c0,0x688,0x628,0x609,0x648,0x608};
const uint16_t lut1[64] = {0x60,0x70,0x60,0x70,0x60,0x70,0x60,0x70,
    0x368,0x378,0x368,0x378,0x368,0x378,0x368,0x378,
    0x0,0x2d0,0x1,0x2d1,0x2,0x2d2,0x3,0x2d3,
    0x300,0x3d0,0x301,0x3d1,0x302,0x3d2,0x303,0x3d3,
    0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
    0x400,0x400,0x400,0x400,0x400,0x400,0x400,0x400,
    0x0,0x2d4,0x0,0x2d4,0x0,0x2d4,0x0,0x2d4,
    0x308,0x3dc,0x308,0x3dc,0x308,0x3dc,0x308,0x3dc};
const uint8_t lut2[64] = {0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x1,0x2,0x2,0x2,0x1,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x1,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x1,0x2,0x2,0x2,0x1,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2};
const uint16_t lut3[64] = {0x4,0x4,0x481,0x481,0x1804,0x4,0x1c81,0x481,
    0x6004,0x6004,0x6481,0x6481,0x7804,0x6004,0x7c81,0x6481,
    0x6,0x6,0x486,0x483,0x180a,0x506,0x1c8a,0x583,
    0x6012,0x6606,0x6492,0x6683,0x781a,0x6706,0x7c9a,0x6783,
    0x4,0x4,0x4,0x4,0x1804,0x4,0x1804,0x4,
    0x4,0x4,0x4,0x4,0x1804,0x4,0x1804,0x4,
    0x64,0x4,0x64,0x4,0x1868,0x4,0x1868,0x4,
    0x64,0x4,0x64,0x4,0x1868,0x4,0x1868,0x4};
const uint16_t lut4[64] = {0x60,0x0,0x800,0x0,0x64,0x2c4,0x800,0x2c5,
    0x362,0x300,0x800,0x302,0x366,0x3c4,0x800,0x3c7,
    0x60,0x5c08,0xc00,0x5c00,0x64,0x5ecc,0xc00,0x5ec5,
    0x362,0x5f08,0xc00,0x5f02,0x366,0x5fcc,0xc00,0x5fc7,
    0x60,0x6010,0x6810,0x6000,0x64,0x62d4,0x6810,0x62c5,
    0x362,0x6310,0x6810,0x6302,0x366,0x63d4,0x6810,0x63c7,
    0x60,0x7c18,0x6c10,0x7c00,0x64,0x7edc,0x6c10,0x7ec5,
    0x362,0x7f18,0x6c10,0x7f02,0x366,0x7fdc,0x6c10,0x7fc7};
const uint8_t lut5[64] = {0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x1,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x2,0x2,0x0,0x1,0x2,0x2,
    0x0,0x0,0x2,0x2,0x0,0x0,0x2,0x2,
    0x0,0x0,0x2,0x2,0x0,0x0,0x2,0x2,
    0x0,0x0,0x2,0x2,0x0,0x0,0x2,0x2};
const uint16_t lut6[64] = {0x60,0x61,0x370,0x371,0x0,0x2c1,0x300,0x3c1,
    0x800,0x800,0x800,0x800,0x0,0x2c5,0x310,0x3d5,
    0x60,0x61,0x370,0x371,0x5c08,0x5ec9,0x5f08,0x5fc9,
    0xc00,0xc00,0xc00,0xc00,0x5c00,0x5ec5,0x5f10,0x5fd5,
    0x60,0x61,0x370,0x371,0x6002,0x62c3,0x6302,0x63c3,
    0x6802,0x6802,0x6802,0x6802,0x6000,0x62c5,0x6310,0x63d5,
    0x60,0x61,0x370,0x371,0x7c0a,0x7ecb,0x7f0a,0x7fcb,
    0x6c02,0x6c02,0x6c02,0x6c02,0x7c00,0x7ec5,0x7f10,0x7fd5};
const uint8_t lut7[64] = {0x0,0x4,0x0,0x0,0x0,0x4,0x0,0x0,
    0x0,0x4,0x0,0x0,0x0,0x4,0x0,0x0,
    0x0,0x4,0x0,0x0,0xb9,0xb9,0xb9,0xb9,
    0xc2,0xc2,0xc2,0xc2,0xfb,0xfb,0xfb,0xfb,
    0x10,0x14,0x10,0x10,0x18,0x1c,0x18,0x18,
    0xd2,0xd2,0xd2,0xd2,0xda,0xda,0xda,0xda,
    0x0,0x4,0x0,0x0,0xb8,0xbc,0xb8,0xb8,
    0xc0,0xc4,0xc0,0xc0,0xf8,0xfc,0xf8,0xf8};
const uint8_t lut8[64] = {0x0,0x0,0x8,0x0,0x20,0x20,0x28,0x20,
    0x0,0x0,0x8,0x0,0x0,0x0,0x8,0x0,
    0x0,0x9d,0xc,0x9c,0x20,0x9d,0x2c,0xbc,
    0x0,0x9d,0xc,0x9c,0x0,0x9d,0xc,0x9c,
    0x0,0xc2,0xca,0xc0,0x20,0xc2,0xca,0xe0,
    0x0,0xc2,0xca,0xc0,0x0,0xc2,0xca,0xc0,
    0x0,0xdf,0xce,0xdc,0x20,0xdf,0xce,0xfc,
    0x0,0xdf,0xce,0xdc,0x0,0xdf,0xce,0xdc};
const uint8_t lut9[64] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
const uint8_t lut10[64] = {0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0x10,0x0,0x0,0x0,0x14,0x4,0x4,0x4,
    0xd6,0xc0,0x0,0xc6,0xd6,0xc4,0x4,0xc6,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0x18,0xb8,0x0,0xbd,0x1c,0xbc,0x4,0xbd,
    0xde,0xf8,0x0,0xff,0xde,0xfc,0x4,0xff};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = ((apValues & 64)>0?16:0) | ((apValues & 128)>0?32:0) | (apValues & 15);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = (uvwState6>0?8:0) | (uvwState5 & 1) | (lut0output & 6) | (apValues & 48);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = ((lut0output & 128)>0?4:0) | ((lut1output & 1024)>0?16:0) | ((lut0output & 256)>0?32:0) | (lut1output & 3) | (lut0output & 8);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (uvwState19>0?2:0) | (uvwState20>0?4:0) | (uvwState21>0?8:0) | ((apValues & 256)>0?16:0) | ((lut0output & 64)>0?32:0) | (lut0output & 1);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = ((apValues & 64)>0?1:0) | ((apValues & 128)>0?2:0) | (uvwState7>0?4:0) | (uvwState8>0?8:0) | (uvwState15>0?16:0) | (uvwState16>0?32:0);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState18>0?32:0) | (lut2output & 1) | (lut3output & 6) | (lut4output & 24);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState4>0?2:0) | (uvwState11>0?16:0) | (uvwState12>0?32:0) | (uvwState3 & 1) | (apValues & 12);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState13>0?4:0) | (uvwState14>0?8:0) | (lut5output & 1) | (lut6output & 2) | (apValues & 48);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = (uvwState9>0?16:0) | (uvwState10>0?32:0) | (apValues & 3) | (lut7output & 4) | (lut6output & 8);
  uint32_t lut8output = lut8[lut8input];
  uint32_t lut9input = (lut4output & 3) | (lut1output & 12) | (lut6output & 16) | (lut8output & 32);
  uint32_t lut9output = lut9[lut9input];
  uint32_t lut10input = (uvwState2>0?8:0) | ((lut9output & 1)>0?16:0) | (uvwState1>0?32:0) | (apValues & 3) | (lut6output & 4);
  uint32_t lut10output = lut10[lut10input];
  if ((lut0output & 16)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut10output & 1)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut10output & 2)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 16)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 4)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 8)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 1)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 1)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 2)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 8)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 1)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 8)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 16)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 2)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 1)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 8)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 16)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut10output & 8)) {
  } else if ((lut0output & 32)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut10output & 32)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut10output & 64)) {
  }
  if ((lut6output & 1)) {
  } else if ((lut6output & 32)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 128)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut6output & 256)) {
  }
  if ((lut1output & 16)) {
  } else if ((lut1output & 32)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 128)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut1output & 256)) {
  }
  if ((lut4output & 4)) {
  } else if ((lut4output & 32)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 128)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut4output & 256)) {
  }
  if ((lut8output & 4)) {
  } else if ((lut0output & 64)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut8output & 16)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut8output & 64)) {
  }
  if ((lut6output & 1024)) {
  } else if ((lut0output & 128)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 4096)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut6output & 8192)) {
  }
  if ((lut7output & 8)) {
  } else if ((lut1output & 1024)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 32)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut7output & 64)) {
  }
  if ((lut4output & 1024)) {
  } else if ((lut0output & 256)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 4096)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut4output & 8192)) {
  }
  if ((lut0output & 512)) {
  }
  if ((lut3output & 32)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 128)) {
  } else if ((lut3output & 256)) {
        buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  } else if ((lut3output & 512)) {
        buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  if ((lut3output & 2048)) {
  }
  if ((lut3output & 8192)) {
  }
  uvwState0 = (lut10output & 4);
  uvwState1 = (lut10output & 16);
  uvwState2 = (lut10output & 128);
  uvwState3 = (lut6output & 64);
  uvwState4 = (lut6output & 512);
  uvwState5 = (lut1output & 64);
  uvwState6 = (lut1output & 512);
  uvwState7 = (lut4output & 64);
  uvwState8 = (lut4output & 512);
  uvwState9 = (lut8output & 8);
  uvwState10 = (lut8output & 128);
  uvwState11 = (lut6output & 2048);
  uvwState12 = (lut6output & 16384);
  uvwState13 = (lut7output & 16);
  uvwState14 = (lut7output & 128);
  uvwState15 = (lut4output & 2048);
  uvwState16 = (lut4output & 16384);
  uvwState17 = (lut0output & 1024);
  uvwState18 = (lut3output & 64);
  uvwState19 = (lut3output & 1024);
  uvwState20 = (lut3output & 4096);
  uvwState21 = (lut3output & 16384);
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
  -> Inputs a1 a2 b1 b2 d1 d2
  -> Outputs new_n34 new_n40 new_n52 new_n69 uvwState0incoming0 uvwState1incoming1 uvwState9incoming1 uvwState11incoming1 uvwState15incoming1 uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs uvwState5 new_n40 new_n52 uvwState6 c1 c2
  -> Outputs new_n72 new_n76 uvwState0incoming5 uvwState0incoming6 uvwState5incoming0 uvwState5incoming1 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming1
- LUT 2 has:
  -> Inputs new_n72 new_n76 uvwState11incoming1 new_n69 uvwState13incoming1 uvwState15incoming1
  -> Outputs new_n77 uvwState0incoming17
- LUT 3 has:
  -> Inputs new_n34 uvwState19 uvwState20 uvwState21 m uvwState9incoming1
  -> Outputs uvwState0incoming19 new_n79 new_n88 uvwState0incoming20 uvwState0incoming21 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 4 has:
  -> Inputs d1 d2 uvwState7 uvwState8 uvwState15 uvwState16
  -> Outputs uvwState0incoming7 uvwState0incoming8 uvwState7incoming0 uvwState0incoming15 uvwState0incoming16 uvwState7incoming1 uvwState7Next uvwState8incoming0 uvwState8incoming1 uvwState8Next uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 5 has:
  -> Inputs new_n77 new_n79 new_n88 uvwState0incoming15 uvwState0incoming16 uvwState18
  -> Outputs new_n92 uvwState0incoming18
- LUT 6 has:
  -> Inputs uvwState3 uvwState4 b1 b2 uvwState11 uvwState12
  -> Outputs uvwState3incoming0 uvwState0incoming12 uvwState0incoming3 uvwState0incoming11 uvwState0incoming4 uvwState3incoming1 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 7 has:
  -> Inputs new_n92 uvwState0incoming12 uvwState13 uvwState14 c1 c2
  -> Outputs uvwState0incoming13 uvwState0incoming14 new_n95 uvwState13incoming0 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next
- LUT 8 has:
  -> Inputs a1 a2 new_n95 uvwState0incoming11 uvwState9 uvwState10
  -> Outputs uvwState0incoming9 uvwState0incoming10 uvwState9incoming0 uvwState9Next uvwState10incoming0 new_n98 uvwState10incoming1 uvwState10Next
- LUT 9 has:
  -> Inputs uvwState0incoming7 uvwState0incoming8 uvwState0incoming5 uvwState0incoming6 uvwState0incoming4 new_n98
  -> Outputs new_n103
- LUT 10 has:
  -> Inputs a1 a2 uvwState0incoming3 uvwState2 new_n103 uvwState1
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0Next uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next
*/
