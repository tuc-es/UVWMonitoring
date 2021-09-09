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

const uint32_t lut0[64] = {0xc0180,0xc0180,0xc0180,0xc0180,0xc01c0,0xc01c0,0xc01c0,0xc01c0,
    0xc0d88,0xc0d88,0xc0d88,0xc0d88,0xc0dc8,0xc0dc8,0xc0dc8,0xc0dc8,
    0xc0001,0xed011,0xf0021,0xfd031,0xc0b41,0xedb51,0xf0b61,0xfdb71,
    0xc0c01,0xedc11,0xf0c21,0xfdc31,0xc0f41,0xedf51,0xf0f61,0xfdf71,
    0xc6000,0xc7000,0xf6020,0xf7020,0xc6000,0xc7000,0xf6020,0xf7020,
    0xc6000,0xc7000,0xf6020,0xf7020,0xc6000,0xc7000,0xf6020,0xf7020,
    0xc0000,0xed000,0xf0000,0xfd000,0xc0b44,0xedb44,0xf0b44,0xfdb44,
    0xc0c08,0xedc08,0xf0c08,0xfdc08,0xc0f4c,0xedf4c,0xf0f4c,0xfdf4c};
const uint16_t lut1[64] = {0x3c,0x34,0x74,0x34,0x2d,0x21,0x65,0x25,
    0xac,0xa4,0xe0,0xa4,0x2c,0x24,0x64,0x24,
    0x1e,0x12,0x56,0x16,0xf,0x3,0x47,0x7,
    0x8e,0x82,0xc2,0x86,0xe,0x2,0x46,0x6,
    0x11c,0x114,0x150,0x114,0x10d,0x101,0x141,0x105,
    0x18c,0x184,0x1c0,0x184,0x10c,0x104,0x140,0x104,
    0x1c,0x14,0x54,0x14,0xd,0x1,0x45,0x5,
    0x8c,0x84,0xc0,0x84,0xc,0x4,0x44,0x4};
const uint16_t lut2[64] = {0x20,0x0,0x400,0x0,0x30,0x170,0x400,0x171,
    0x1a2,0x180,0x400,0x182,0x1b2,0x1f0,0x400,0x1f3,
    0x20,0x2e04,0x600,0x2e00,0x30,0x2f74,0x600,0x2f71,
    0x1a2,0x2f84,0x600,0x2f82,0x1b2,0x2ff4,0x600,0x2ff3,
    0x20,0x3008,0x3408,0x3000,0x30,0x3178,0x3408,0x3171,
    0x1a2,0x3188,0x3408,0x3182,0x1b2,0x31f8,0x3408,0x31f3,
    0x20,0x3e0c,0x3608,0x3e00,0x30,0x3f7c,0x3608,0x3f71,
    0x1a2,0x3f8c,0x3608,0x3f82,0x1b2,0x3ffc,0x3608,0x3ff3};
const uint8_t lut3[64] = {0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,
    0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,
    0x0,0x0,0x0,0x0,0x1,0x0,0x1,0x0,
    0x0,0x0,0x0,0x0,0x1,0x0,0x1,0x0,
    0x0,0x0,0x0,0x0,0x1,0x1,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,
    0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1};
const uint16_t lut4[64] = {0x8,0x8,0x8,0x8,0xc,0xc,0x68,0xc,
    0x481,0x481,0x8,0x481,0x48c,0x485,0x68,0x48c,
    0x1808,0x8,0x1808,0x1808,0x1806,0x50c,0x1862,0x1806,
    0x1c81,0x481,0x1808,0x1c81,0x1c86,0x585,0x1862,0x1c86,
    0x6008,0x6008,0x8,0x6008,0x6014,0x660c,0x68,0x6014,
    0x6481,0x6481,0x8,0x6481,0x6494,0x6685,0x68,0x6494,
    0x7808,0x6008,0x1808,0x7808,0x7816,0x670c,0x1862,0x7816,
    0x7c81,0x6481,0x1808,0x7c81,0x7c96,0x6785,0x1862,0x7c96};
const uint8_t lut5[64] = {0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x6,0x6,0x6,0x6,
    0x2,0x2,0x2,0x2,0x6,0x6,0x6,0x6,
    0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x2,
    0x1,0x1,0x1,0x2,0x1,0x1,0x1,0x2,
    0x0,0x0,0x0,0x2,0x4,0x4,0x4,0x6,
    0x1,0x1,0x1,0x2,0x4,0x4,0x4,0x6};
const uint8_t lut6[64] = {0x0,0x1,0x10,0x11,0x0,0x1,0x18,0x19,
    0x0,0x1,0xd4,0xd4,0x0,0x1,0xdc,0xdc,
    0x0,0x1,0x0,0x1,0xba,0xba,0xb8,0xb9,
    0xc4,0xc4,0xc0,0xc1,0xfe,0xfe,0xf8,0xf9,
    0x0,0x0,0x10,0x10,0x0,0x0,0x18,0x18,
    0x0,0x0,0xd4,0xd4,0x0,0x0,0xdc,0xdc,
    0x0,0x0,0x0,0x0,0xba,0xba,0xb8,0xb8,
    0xc4,0xc4,0xc0,0xc0,0xfe,0xfe,0xf8,0xf8};
const uint16_t lut7[64] = {0x4,0x5,0x194,0x195,0x0,0x145,0x180,0x1c5,
    0x400,0x400,0x400,0x400,0x0,0x14d,0x190,0x1dd,
    0x4,0x5,0x194,0x195,0x2e02,0x2f47,0x2f82,0x2fc7,
    0x600,0x600,0x600,0x600,0x2e00,0x2f4d,0x2f90,0x2fdd,
    0x4,0x5,0x194,0x195,0x3020,0x3165,0x31a0,0x31e5,
    0x3420,0x3420,0x3420,0x3420,0x3000,0x314d,0x3190,0x31dd,
    0x4,0x5,0x194,0x195,0x3e22,0x3f67,0x3fa2,0x3fe7,
    0x3620,0x3620,0x3620,0x3620,0x3e00,0x3f4d,0x3f90,0x3fdd};
const uint8_t lut8[64] = {0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
const uint8_t lut9[64] = {0x8,0x28,0x0,0x20,0xc,0x2c,0x0,0x20,
    0x8,0x8,0x0,0x0,0xc,0xc,0x0,0x0,
    0x0,0x20,0x0,0x20,0x9c,0xbc,0x9d,0x9d,
    0x0,0x0,0x0,0x0,0x9c,0x9c,0x9d,0x9d,
    0xca,0xca,0x0,0x20,0xce,0xce,0x0,0x20,
    0xca,0xca,0x0,0x0,0xce,0xce,0x0,0x0,
    0xc0,0xe0,0xc2,0xc2,0xdc,0xfc,0xdf,0xdf,
    0xc0,0xc0,0xc2,0xc2,0xdc,0xdc,0xdf,0xdf};
const uint8_t lut10[64] = {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = (uvwState14>0?2:0) | (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState13 & 1) | (apValues & 48);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((apValues & 64)>0?16:0) | ((apValues & 128)>0?32:0) | (apValues & 15);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = (uvwState1>0?4:0) | (uvwState2>0?8:0) | (uvwState9>0?16:0) | (uvwState10>0?32:0) | (apValues & 3);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = ((lut1output & 256)>0?2:0) | ((lut1output & 128)>0?8:0) | (lut1output & 5) | (apValues & 48);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = ((apValues & 256)>0?4:0) | (uvwState19>0?8:0) | (uvwState20>0?16:0) | (uvwState21>0?32:0) | (apValues & 3);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState18>0?16:0) | ((lut3output & 1)>0?32:0) | (lut0output & 1) | (lut1output & 2) | (lut4output & 12);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = ((apValues & 128)>0?2:0) | (uvwState15>0?4:0) | (uvwState16>0?8:0) | ((apValues & 64)>0?16:0) | (lut5output & 1) | (lut0output & 32);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState4>0?2:0) | (uvwState11>0?16:0) | (uvwState12>0?32:0) | (uvwState3 & 1) | (apValues & 12);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = (lut6output & 1) | (lut7output & 34) | (lut2output & 12) | (lut0output & 16);
  uint32_t lut8output = lut8[lut8input];
  uint32_t lut9input = ((apValues & 128)>0?2:0) | (uvwState7>0?4:0) | ((apValues & 64)>0?16:0) | (uvwState8>0?32:0) | (lut8output & 1) | (lut0output & 8);
  uint32_t lut9output = lut9[lut9input];
  uint32_t lut10input = (lut2output & 3) | (lut0output & 4) | (lut7output & 24) | (lut9output & 32);
  uint32_t lut10output = lut10[lut10input];
  if ((lut0output & 2)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 1)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 2)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 8)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 16)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 4)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 8)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut9output & 1)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut9output & 2)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 4)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 8)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 32)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 16)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 32)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 4)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 1)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 16)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut2output & 16)) {
  } else if ((lut1output & 8)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 64)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut2output & 128)) {
  }
  if ((lut7output & 1)) {
  } else if ((lut1output & 16)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 64)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut7output & 128)) {
  }
  if ((lut0output & 64)) {
  } else if ((lut0output & 128)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 512)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut0output & 1024)) {
  }
  if ((lut9output & 4)) {
  } else if ((lut1output & 32)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut9output & 16)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut9output & 64)) {
  }
  if ((lut2output & 512)) {
  } else if ((lut1output & 64)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 2048)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut2output & 4096)) {
  }
  if ((lut7output & 512)) {
  } else if ((lut1output & 128)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 2048)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut7output & 4096)) {
  }
  if ((lut0output & 4096)) {
  } else if ((lut0output & 8192)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 32768)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut0output & 65536)) {
  }
  if ((lut6output & 8)) {
  } else if ((lut1output & 256)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 32)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut6output & 64)) {
  }
  if ((lut0output & 262144)) {
  }
  if ((lut4output & 32)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 128)) {
  } else if ((lut4output & 256)) {
        buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  } else if ((lut4output & 512)) {
        buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  if ((lut4output & 2048)) {
  }
  if ((lut4output & 8192)) {
  }
  uvwState0 = (lut10output & 1);
  uvwState1 = (lut2output & 32);
  uvwState2 = (lut2output & 256);
  uvwState3 = (lut7output & 4);
  uvwState4 = (lut7output & 256);
  uvwState5 = (lut0output & 256);
  uvwState6 = (lut0output & 2048);
  uvwState7 = (lut9output & 8);
  uvwState8 = (lut9output & 128);
  uvwState9 = (lut2output & 1024);
  uvwState10 = (lut2output & 8192);
  uvwState11 = (lut7output & 1024);
  uvwState12 = (lut7output & 8192);
  uvwState13 = (lut0output & 16384);
  uvwState14 = (lut0output & 131072);
  uvwState15 = (lut6output & 16);
  uvwState16 = (lut6output & 128);
  uvwState17 = (lut0output & 524288);
  uvwState18 = (lut4output & 64);
  uvwState19 = (lut4output & 1024);
  uvwState20 = (lut4output & 4096);
  uvwState21 = (lut4output & 16384);
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
  -> Inputs uvwState13 uvwState14 uvwState5 uvwState6 c1 c2
  -> Outputs new_n46 uvwState0incoming0 uvwState0incoming5 uvwState0incoming6 uvwState0incoming13 uvwState0incoming14 uvwState5incoming0 uvwState5incoming1 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13incoming1 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs a1 a2 b1 b2 d1 d2
  -> Outputs new_n40 new_n52 new_n69 uvwState1incoming1 uvwState3incoming1 uvwState7incoming1 uvwState9incoming1 uvwState11incoming1 uvwState15incoming1
- LUT 2 has:
  -> Inputs a1 a2 uvwState1 uvwState2 uvwState9 uvwState10
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0incoming9 uvwState0incoming10 uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next uvwState9incoming0 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 3 has:
  -> Inputs new_n40 uvwState15incoming1 new_n69 uvwState11incoming1 c1 c2
  -> Outputs new_n75
- LUT 4 has:
  -> Inputs a1 a2 m uvwState19 uvwState20 uvwState21
  -> Outputs uvwState0incoming19 uvwState0incoming20 new_n79 new_n88 uvwState0incoming21 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 5 has:
  -> Inputs new_n46 new_n52 new_n79 new_n88 uvwState18 new_n75
  -> Outputs new_n90 uvwState0incoming17 uvwState0incoming18
- LUT 6 has:
  -> Inputs new_n90 d2 uvwState15 uvwState16 d1 uvwState0incoming14
  -> Outputs new_n93 uvwState0incoming15 uvwState0incoming16 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 7 has:
  -> Inputs uvwState3 uvwState4 b1 b2 uvwState11 uvwState12
  -> Outputs uvwState3incoming0 uvwState0incoming11 uvwState3Next uvwState0incoming3 uvwState0incoming4 uvwState0incoming12 uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 8 has:
  -> Inputs new_n93 uvwState0incoming11 uvwState0incoming9 uvwState0incoming10 uvwState0incoming13 uvwState0incoming12
  -> Outputs new_n98
- LUT 9 has:
  -> Inputs new_n98 d2 uvwState7 uvwState0incoming6 d1 uvwState8
  -> Outputs uvwState0incoming7 uvwState0incoming8 uvwState7incoming0 uvwState7Next uvwState8incoming0 new_n101 uvwState8incoming1 uvwState8Next
- LUT 10 has:
  -> Inputs uvwState0incoming1 uvwState0incoming2 uvwState0incoming5 uvwState0incoming3 uvwState0incoming4 new_n101
  -> Outputs uvwState0Next
*/
