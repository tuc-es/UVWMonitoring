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
const uint32_t lut1[64] = {0x4,0x6,0x44,0x4,0x5,0x7,0x1c4,0x5,
    0x1208,0x120a,0x44,0x1208,0x1205,0x120b,0x1c4,0x1205,
    0x6004,0x6,0x6044,0x6004,0x6011,0x1407,0x61d0,0x6011,
    0x7208,0x120a,0x6044,0x7208,0x7211,0x160b,0x61d0,0x7211,
    0x18004,0x18006,0x44,0x18004,0x18021,0x19807,0x1c4,0x18021,
    0x19208,0x1920a,0x44,0x19208,0x19221,0x19a0b,0x1c4,0x19221,
    0x1e004,0x18006,0x6044,0x1e004,0x1e031,0x19c07,0x61d0,0x1e031,
    0x1f208,0x1920a,0x6044,0x1f208,0x1f231,0x19e0b,0x61d0,0x1f231};
const uint8_t lut2[64] = {0x0,0x8,0x40,0x0,0x4,0xc,0x44,0x4,
    0x1,0x9,0x41,0x1,0x0,0x8,0x40,0x0,
    0x0,0x8,0x50,0x0,0x4,0xc,0x54,0x4,
    0x11,0x19,0x51,0x11,0x0,0x8,0x50,0x0,
    0x0,0x8,0x42,0x0,0x4,0xc,0x46,0x4,
    0x21,0x29,0x63,0x21,0x0,0x8,0x42,0x0,
    0x0,0x8,0x52,0x0,0x4,0xc,0x56,0x4,
    0x31,0x39,0x73,0x31,0x0,0x8,0x52,0x0};
const uint8_t lut3[64] = {0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x0,
    0x1,0x3,0x0,0x2,0x1,0x2,0x0,0x2,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x2,0x0,0x2,0x0,0x2,0x0,0x2,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x2,0x0,0x2,0x0,0x2,0x0,0x2,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x2,0x0,0x2,0x0,0x2,0x0,0x2};
const uint8_t lut4[64] = {0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x6,0x2,0x6,0x2,0x6,0x2,0x6,
    0x2,0x6,0x2,0x6,0x2,0x6,0x2,0x6,
    0x0,0x0,0x2,0x2,0x1,0x1,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x0,0x4,0x2,0x6,0x1,0x4,0x2,0x6,
    0x2,0x6,0x2,0x6,0x2,0x6,0x2,0x6};
const uint16_t lut5[64] = {0x8,0x9,0x20,0x21,0x8,0x9,0x30,0x31,
    0x8,0x9,0x1a4,0x1a4,0x8,0x9,0x1b4,0x1b4,
    0x0,0x1,0x0,0x1,0x172,0x172,0x170,0x171,
    0x184,0x184,0x180,0x181,0x1f6,0x1f6,0x1f0,0x1f1,
    0x8,0x8,0x20,0x20,0x8,0x8,0x30,0x30,
    0x8,0x8,0x1a4,0x1a4,0x8,0x8,0x1b4,0x1b4,
    0x0,0x0,0x0,0x0,0x172,0x172,0x170,0x170,
    0x184,0x184,0x180,0x180,0x1f6,0x1f6,0x1f0,0x1f0};
const uint16_t lut6[64] = {0x60,0x70,0x362,0x372,0x0,0x2d0,0x300,0x3d0,
    0x800,0x800,0x800,0x800,0x0,0x2d1,0x302,0x3d3,
    0x60,0x70,0x362,0x372,0x5c04,0x5ed4,0x5f04,0x5fd4,
    0xc00,0xc00,0xc00,0xc00,0x5c00,0x5ed1,0x5f02,0x5fd3,
    0x60,0x70,0x362,0x372,0x6008,0x62d8,0x6308,0x63d8,
    0x6808,0x6808,0x6808,0x6808,0x6000,0x62d1,0x6302,0x63d3,
    0x60,0x70,0x362,0x372,0x7c0c,0x7edc,0x7f0c,0x7fdc,
    0x6c08,0x6c08,0x6c08,0x6c08,0x7c00,0x7ed1,0x7f02,0x7fd3};
const uint16_t lut7[64] = {0x44,0x0,0x800,0x0,0x45,0x2c1,0x800,0x2c9,
    0x354,0x300,0x800,0x310,0x355,0x3c1,0x800,0x3d9,
    0x44,0x5c02,0xc00,0x5c00,0x45,0x5ec3,0xc00,0x5ec9,
    0x354,0x5f02,0xc00,0x5f10,0x355,0x5fc3,0xc00,0x5fd9,
    0x44,0x6020,0x6820,0x6000,0x45,0x62e1,0x6820,0x62c9,
    0x354,0x6320,0x6820,0x6310,0x355,0x63e1,0x6820,0x63d9,
    0x44,0x7c22,0x6c20,0x7c00,0x45,0x7ee3,0x6c20,0x7ec9,
    0x354,0x7f22,0x6c20,0x7f10,0x355,0x7fe3,0x6c20,0x7fd9};
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
  uint32_t lut1input = ((apValues & 256)>0?4:0) | (uvwState19>0?8:0) | (uvwState20>0?16:0) | (uvwState21>0?32:0) | (apValues & 3);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = ((apValues & 64)>0?1:0) | ((apValues & 128)>0?2:0) | ((lut1output & 64)>0?16:0) | ((lut0output & 8192)>0?32:0) | (apValues & 12);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (lut0output & 1) | (lut1output & 2) | (lut2output & 60);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = ((lut3output & 2)>0?8:0) | (uvwState18>0?16:0) | ((lut3output & 1)>0?32:0) | (lut1output & 5) | (lut2output & 2);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = ((apValues & 128)>0?2:0) | (uvwState15>0?4:0) | (uvwState16>0?8:0) | ((apValues & 64)>0?16:0) | (lut4output & 1) | (lut0output & 32);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState4>0?2:0) | (uvwState11>0?16:0) | (uvwState12>0?32:0) | (uvwState3 & 1) | (apValues & 12);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState1>0?4:0) | (uvwState2>0?8:0) | (uvwState9>0?16:0) | (uvwState10>0?32:0) | (apValues & 3);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = (lut5output & 1) | (lut7output & 34) | (lut6output & 12) | (lut0output & 16);
  uint32_t lut8output = lut8[lut8input];
  uint32_t lut9input = ((apValues & 128)>0?2:0) | (uvwState7>0?4:0) | ((apValues & 64)>0?16:0) | (uvwState8>0?32:0) | (lut8output & 1) | (lut0output & 8);
  uint32_t lut9output = lut9[lut9input];
  uint32_t lut10input = (lut6output & 3) | (lut0output & 4) | (lut7output & 24) | (lut9output & 32);
  uint32_t lut10output = lut10[lut10input];
  if ((lut0output & 2)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 8)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 16)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 1)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
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
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 32)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 8)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 16)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 32)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 4)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 4)) {
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
  if ((lut7output & 1)) {
  } else if ((lut7output & 4)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 128)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut7output & 256)) {
  }
  if ((lut6output & 16)) {
  } else if ((lut6output & 32)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 128)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut6output & 256)) {
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
  } else if ((lut5output & 8)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut9output & 16)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut9output & 64)) {
  }
  if ((lut7output & 1024)) {
  } else if ((lut1output & 64)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 4096)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut7output & 8192)) {
  }
  if ((lut6output & 1024)) {
  } else if ((lut2output & 1)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 4096)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut6output & 8192)) {
  }
  if ((lut0output & 4096)) {
  } else if ((lut0output & 8192)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 32768)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut0output & 65536)) {
  }
  if ((lut5output & 16)) {
  } else if ((lut2output & 64)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 64)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut5output & 128)) {
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
  uvwState0 = (lut10output & 1);
  uvwState1 = (lut7output & 64);
  uvwState2 = (lut7output & 512);
  uvwState3 = (lut6output & 64);
  uvwState4 = (lut6output & 512);
  uvwState5 = (lut0output & 256);
  uvwState6 = (lut0output & 2048);
  uvwState7 = (lut9output & 8);
  uvwState8 = (lut9output & 128);
  uvwState9 = (lut7output & 2048);
  uvwState10 = (lut7output & 16384);
  uvwState11 = (lut6output & 2048);
  uvwState12 = (lut6output & 16384);
  uvwState13 = (lut0output & 16384);
  uvwState14 = (lut0output & 131072);
  uvwState15 = (lut5output & 32);
  uvwState16 = (lut5output & 256);
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
  -> Inputs uvwState13 uvwState14 uvwState5 uvwState6 c1 c2
  -> Outputs new_n46 uvwState0incoming0 uvwState0incoming5 uvwState0incoming6 uvwState0incoming13 uvwState0incoming14 uvwState5incoming0 uvwState5incoming1 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13incoming1 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs a1 a2 m uvwState19 uvwState20 uvwState21
  -> Outputs new_n79 new_n34 new_n88 uvwState0incoming19 uvwState0incoming20 uvwState0incoming21 uvwState9incoming1 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 2 has:
  -> Inputs d1 d2 b1 b2 uvwState9incoming1 uvwState13incoming1
  -> Outputs uvwState11incoming1 new_n74 new_n40 new_n52 new_n66 new_n70 uvwState15incoming1
- LUT 3 has:
  -> Inputs new_n46 new_n34 new_n40 new_n52 new_n66 new_n70
  -> Outputs new_n73 new_n76
- LUT 4 has:
  -> Inputs new_n79 new_n74 new_n88 new_n76 uvwState18 new_n73
  -> Outputs new_n90 uvwState0incoming17 uvwState0incoming18
- LUT 5 has:
  -> Inputs new_n90 d2 uvwState15 uvwState16 d1 uvwState0incoming14
  -> Outputs new_n93 uvwState0incoming15 uvwState0incoming16 uvwState7incoming1 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 6 has:
  -> Inputs uvwState3 uvwState4 b1 b2 uvwState11 uvwState12
  -> Outputs uvwState0incoming3 uvwState0incoming4 uvwState0incoming11 uvwState0incoming12 uvwState3incoming0 uvwState3incoming1 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 7 has:
  -> Inputs a1 a2 uvwState1 uvwState2 uvwState9 uvwState10
  -> Outputs uvwState1incoming0 uvwState0incoming9 uvwState1incoming1 uvwState0incoming1 uvwState0incoming2 uvwState0incoming10 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next uvwState9incoming0 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 8 has:
  -> Inputs new_n93 uvwState0incoming9 uvwState0incoming11 uvwState0incoming12 uvwState0incoming13 uvwState0incoming10
  -> Outputs new_n98
- LUT 9 has:
  -> Inputs new_n98 d2 uvwState7 uvwState0incoming6 d1 uvwState8
  -> Outputs uvwState0incoming7 uvwState0incoming8 uvwState7incoming0 uvwState7Next uvwState8incoming0 new_n101 uvwState8incoming1 uvwState8Next
- LUT 10 has:
  -> Inputs uvwState0incoming3 uvwState0incoming4 uvwState0incoming5 uvwState0incoming1 uvwState0incoming2 new_n101
  -> Outputs uvwState0Next
*/
