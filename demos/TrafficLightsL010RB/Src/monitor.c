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
} buf = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint32_t b17p0 = 0;

uint32_t lut0[64] = {0x1803000,0x1803000,0x1803000,0x1803000,0x1803800,0x1803800,0x1803800,0x1803800,
    0x181b104,0x181b104,0x181b104,0x181b104,0x181b904,0x181b904,0x181b904,0x181b904,
    0x1800002,0x1da020a,0x1e00422,0x1fa062a,0x1816802,0x1db6a0a,0x1e16c22,0x1fb6e2a,
    0x1818002,0x1db820a,0x1e18422,0x1fb862a,0x181e802,0x1dbea0a,0x1e1ec22,0x1fbee2a,
    0x18c0010,0x18e0010,0x1ec0430,0x1ee0430,0x18c0010,0x18e0010,0x1ec0430,0x1ee0430,
    0x18c0010,0x18e0010,0x1ec0430,0x1ee0430,0x18c0010,0x18e0010,0x1ec0430,0x1ee0430,
    0x1800000,0x1da0000,0x1e00000,0x1fa0000,0x1816881,0x1db6881,0x1e16881,0x1fb6881,
    0x1818104,0x1db8104,0x1e18104,0x1fb8104,0x181e985,0x1dbe985,0x1e1e985,0x1fbe985};
uint8_t lut1[128] = {0xa,0x8,0x28,0x8,0xb,0x1,0x29,0x9,
    0xa,0x8,0x20,0x8,0xa,0x8,0x28,0x8,
    0xa,0x8,0x28,0x8,0xb,0x1,0x29,0x9,
    0x2,0x0,0x20,0x0,0xa,0x8,0x28,0x8,
    0x4a,0x48,0x60,0x48,0x4b,0x41,0x61,0x49,
    0x4a,0x48,0x60,0x48,0x4a,0x48,0x60,0x48,
    0x5a,0x58,0x70,0x58,0x5b,0x51,0x71,0x59,
    0x52,0x50,0x70,0x50,0x5a,0x58,0x70,0x58,
    0xe,0x4,0x2c,0xc,0xf,0x5,0x2d,0xd,
    0xe,0x4,0x24,0xc,0xe,0x4,0x2c,0xc,
    0xe,0x4,0x2c,0xc,0xf,0x5,0x2d,0xd,
    0x6,0x4,0x24,0x4,0xe,0x4,0x2c,0xc,
    0xa,0x8,0x28,0x8,0xb,0x1,0x29,0x9,
    0xa,0x8,0x20,0x8,0xa,0x8,0x28,0x8,
    0xa,0x8,0x28,0x8,0xb,0x1,0x29,0x9,
    0x2,0x0,0x20,0x0,0xa,0x8,0x28,0x8};
uint32_t lut2[128] = {0x100,0x0,0x2000,0x0,0x140,0x40,0x62000,0x40,
    0x180,0xb80,0x2000,0xb81,0x1c0,0xbc0,0x62000,0xbc1,
    0xd02,0xc00,0x2000,0xc02,0xd42,0xc40,0x62000,0xc42,
    0xd82,0xf80,0x2000,0xf83,0xdc2,0xfc0,0x62000,0xfc3,
    0x100,0x17014,0x3000,0x17000,0x140,0x17054,0x63000,0x17040,
    0x180,0x17b94,0x3000,0x17b81,0x1c0,0x17bd4,0x63000,0x17bc1,
    0xd02,0x17c14,0x3000,0x17c02,0xd42,0x17c54,0x63000,0x17c42,
    0xd82,0x17f94,0x3000,0x17f83,0xdc2,0x17fd4,0x63000,0x17fc3,
    0x100,0x18028,0x1a028,0x18000,0x140,0x18068,0x7a028,0x18040,
    0x180,0x18ba8,0x1a028,0x18b81,0x1c0,0x18be8,0x7a028,0x18bc1,
    0xd02,0x18c28,0x1a028,0x18c02,0xd42,0x18c68,0x7a028,0x18c42,
    0xd82,0x18fa8,0x1a028,0x18f83,0xdc2,0x18fe8,0x7a028,0x18fc3,
    0x100,0x1f03c,0x1b028,0x1f000,0x140,0x1f07c,0x7b028,0x1f040,
    0x180,0x1fbbc,0x1b028,0x1fb81,0x1c0,0x1fbfc,0x7b028,0x1fbc1,
    0xd02,0x1fc3c,0x1b028,0x1fc02,0xd42,0x1fc7c,0x7b028,0x1fc42,
    0xd82,0x1ffbc,0x1b028,0x1ff83,0xdc2,0x1fffc,0x7b028,0x1ffc3};
uint8_t lut3[128] = {0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x1,0x1,0x1,0x2,0x1,0x1,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x1,0x1,0x1,0x2,0x1,0x1,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x1,0x1,0x1,0x2,0x1,0x1,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,
    0x4,0x4,0x4,0x6,0x4,0x4,0x6,0x6,
    0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,
    0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6};
uint16_t lut4[128] = {0x8,0x9,0x20,0x21,0x8,0x9,0x30,0x31,
    0x8,0x8,0x20,0x20,0x8,0x8,0x30,0x30,
    0x8,0x9,0x1a4,0x1a4,0x8,0x9,0x1b4,0x1b4,
    0x8,0x8,0x1a4,0x1a4,0x8,0x8,0x1b4,0x1b4,
    0x8,0x8,0x20,0x20,0x8,0x8,0x30,0x30,
    0x8,0x8,0x20,0x20,0x8,0x8,0x30,0x30,
    0x8,0x8,0x1a4,0x1a4,0x8,0x8,0x1b4,0x1b4,
    0x8,0x8,0x1a4,0x1a4,0x8,0x8,0x1b4,0x1b4,
    0x0,0x1,0x0,0x1,0x172,0x172,0x170,0x171,
    0x0,0x0,0x0,0x0,0x172,0x172,0x170,0x170,
    0x184,0x184,0x180,0x181,0x1f6,0x1f6,0x1f0,0x1f1,
    0x184,0x184,0x180,0x180,0x1f6,0x1f6,0x1f0,0x1f0,
    0x0,0x0,0x0,0x0,0x172,0x172,0x170,0x170,
    0x0,0x0,0x0,0x0,0x172,0x172,0x170,0x170,
    0x184,0x184,0x180,0x180,0x1f6,0x1f6,0x1f0,0x1f0,
    0x184,0x184,0x180,0x180,0x1f6,0x1f6,0x1f0,0x1f0};
uint8_t lut5[128] = {0x0,0x2,0x0,0x2,0x0,0x2,0xc4,0xc4,
    0x10,0x12,0xd4,0xd4,0x0,0x2,0xc0,0xc2,
    0x0,0x0,0x0,0x0,0x0,0x0,0xc4,0xc4,
    0x10,0x10,0xd4,0xd4,0x0,0x0,0xc0,0xc0,
    0x0,0x0,0x0,0x0,0x0,0x0,0xc4,0xc4,
    0x10,0x10,0xd4,0xd4,0x0,0x0,0xc0,0xc0,
    0x0,0x0,0x0,0x0,0x0,0x0,0xc4,0xc4,
    0x10,0x10,0xd4,0xd4,0x0,0x0,0xc0,0xc0,
    0x0,0x2,0x0,0x2,0xb9,0xb9,0xfd,0xfd,
    0x18,0x1a,0xdc,0xdc,0xb8,0xba,0xf8,0xfa,
    0x0,0x0,0x0,0x0,0xb9,0xb9,0xfd,0xfd,
    0x18,0x18,0xdc,0xdc,0xb8,0xb8,0xf8,0xf8,
    0x0,0x0,0x0,0x0,0xb9,0xb9,0xfd,0xfd,
    0x18,0x18,0xdc,0xdc,0xb8,0xb8,0xf8,0xf8,
    0x0,0x0,0x0,0x0,0xb9,0xb9,0xfd,0xfd,
    0x18,0x18,0xdc,0xdc,0xb8,0xb8,0xf8,0xf8};
uint8_t lut6[128] = {0x8,0x8,0x18,0x8,0x8,0x8,0x8,0x8,
    0xca,0xca,0xca,0xca,0xca,0xca,0xca,0xca,
    0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x0,
    0xc,0xc,0x1c,0xc,0xc,0xc,0xc,0xc,
    0xce,0xce,0xce,0xce,0xce,0xce,0xce,0xce,
    0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x0,
    0xc0,0xc0,0xd0,0xc0,0xc0,0xc0,0xc0,0xc0,
    0x0,0x0,0x10,0x0,0x0,0x0,0x0,0x0,
    0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,0xc2,
    0xac,0xac,0xbc,0xac,0xac,0xac,0xac,0xac,
    0xec,0xec,0xfc,0xec,0xec,0xec,0xec,0xec,
    0xad,0xad,0xad,0xad,0xad,0xad,0xad,0xad,
    0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef};
uint16_t lut7[128] = {0xd0,0xd1,0xd2,0xd3,0x10,0x11,0x12,0x13,
    0x810,0x811,0x812,0x813,0x10,0x11,0x12,0x13,
    0xc0,0xd1,0xd2,0xd3,0x0,0x11,0x12,0x13,
    0x800,0x811,0x812,0x813,0x0,0x11,0x12,0x13,
    0x6d8,0x6d9,0x6da,0x6db,0x610,0x611,0x612,0x613,
    0x810,0x811,0x812,0x813,0x618,0x619,0x61a,0x61b,
    0x6d8,0x6d9,0x6da,0x6db,0x600,0x611,0x612,0x613,
    0x800,0x811,0x812,0x813,0x618,0x619,0x61a,0x61b,
    0xf0,0xf1,0xf2,0xf3,0x5b0,0x5b1,0x5b2,0x5b3,
    0x810,0x811,0x812,0x813,0x5b4,0x5b5,0x5b6,0x5b7,
    0xe0,0xf1,0xf2,0xf3,0x5a0,0x5b1,0x5b2,0x5b3,
    0x800,0x811,0x812,0x813,0x5b4,0x5b5,0x5b6,0x5b7,
    0x6f8,0x6f9,0x6fa,0x6fb,0x7b0,0x7b1,0x7b2,0x7b3,
    0x810,0x811,0x812,0x813,0x7bc,0x7bd,0x7be,0x7bf,
    0x6f8,0x6f9,0x6fa,0x6fb,0x7a0,0x7b1,0x7b2,0x7b3,
    0x800,0x811,0x812,0x813,0x7bc,0x7bd,0x7be,0x7bf};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = (uvwState14>0?2:0) | (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState13 & 1) | (apValues & 48);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((apValues & 128)>0?32:0) | (apValues & 79) | (lut0output & 16);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = ((apValues & 256)>0?4:0) | (uvwState1>0?8:0) | (uvwState2>0?16:0) | (uvwState9>0?32:0) | (uvwState10>0?64:0) | (apValues & 3);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (uvwState18>0?32:0) | (lut1output & 29) | (lut0output & 2) | (lut2output & 64);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = ((apValues & 128)>0?2:0) | (uvwState15>0?4:0) | (uvwState16>0?16:0) | (lut3output & 1) | (lut0output & 40) | (apValues & 64);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState12>0?2:0) | (uvwState11>0?64:0) | (lut4output & 1) | (apValues & 12) | (lut2output & 48);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState8>0?8:0) | ((apValues & 128)>0?16:0) | (uvwState7>0?32:0) | (lut0output & 5) | (lut5output & 2) | (apValues & 64);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState4>0?32:0) | (uvwState3>0?64:0) | (lut2output & 3) | (apValues & 12) | (lut6output & 16);
  uint32_t lut7output = lut7[lut7input];
  if ((lut0output & 64)) {
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut7output & 1)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut7output & 4)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut7output & 8)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut0output & 128)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut0output & 256)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut6output & 1)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut2output & 4)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut2output & 8)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut5output & 1)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut5output & 4)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut0output & 512)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut0output & 1024)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut4output & 4)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut3output & 2)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut3output & 4)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  }
  if ((lut2output & 128)) {
  } else if ((lut1output & 2)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 512)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut2output & 1024)) {
  }
  if ((lut7output & 32)) {
  } else if ((lut7output & 64)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 256)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut7output & 512)) {
  }
  if ((lut0output & 2048)) {
  } else if ((lut0output & 4096)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 16384)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut0output & 32768)) {
  }
  if ((lut6output & 4)) {
  } else if ((lut4output & 8)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 32)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut6output & 64)) {
  }
  if ((lut2output & 4096)) {
  } else if ((lut1output & 32)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 16384)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut2output & 32768)) {
  }
  if ((lut5output & 8)) {
  } else if ((lut7output & 2048)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 32)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut5output & 64)) {
  }
  if ((lut0output & 131072)) {
  } else if ((lut0output & 262144)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 1048576)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut0output & 2097152)) {
  }
  if ((lut4output & 16)) {
  } else if ((lut1output & 64)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 64)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut4output & 128)) {
  }
  if ((lut0output & 8388608)) {
  }
  if ((lut2output & 131072)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  uvwState0 = (lut7output & 16);
  uvwState1 = (lut2output & 256);
  uvwState2 = (lut2output & 2048);
  uvwState3 = (lut7output & 128);
  uvwState4 = (lut7output & 1024);
  uvwState5 = (lut0output & 8192);
  uvwState6 = (lut0output & 65536);
  uvwState7 = (lut6output & 8);
  uvwState8 = (lut6output & 128);
  uvwState9 = (lut2output & 8192);
  uvwState10 = (lut2output & 65536);
  uvwState11 = (lut5output & 16);
  uvwState12 = (lut5output & 128);
  uvwState13 = (lut0output & 524288);
  uvwState14 = (lut0output & 4194304);
  uvwState15 = (lut4output & 32);
  uvwState16 = (lut4output & 256);
  uvwState17 = (lut0output & 16777216);
  uvwState18 = (lut2output & 262144);
}

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


UVW on which the monitor is based:
 UVW with 19 states and initial states [17]:
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
 - State No. 17 with name & & & & & & & & & & & & & & & & & & G | | d1 ! d2 R & ! d1 ! d2 | | & ! d1 d2 & ! d1 ! d2 & & d1 d2 R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2 & G | | c1 ! c2 R & ! c1 ! c2 | | & ! c1 c2 & ! c1 ! c2 & & c1 c2 R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2 & G | | b1 ! b2 R & ! b1 ! b2 | | & ! b1 b2 & ! b1 ! b2 & & b1 b2 R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2 & G | | a1 ! a2 R & ! a1 ! a2 | | & ! a1 a2 & ! a1 ! a2 & & a1 a2 R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2 & G | | d1 d2 R & ! d1 d2 | | & ! d1 ! d2 & ! d1 d2 & & d1 ! d2 R & ! d1 d2 | & ! d1 d2 & d1 ! d2 & G | | c1 c2 R & ! c1 c2 | | & ! c1 ! c2 & ! c1 c2 & & c1 ! c2 R & ! c1 c2 | & ! c1 c2 & c1 ! c2 & G | | b1 b2 R & ! b1 b2 | | & ! b1 ! b2 & ! b1 b2 & & b1 ! b2 R & ! b1 b2 | & ! b1 b2 & b1 ! b2 & G | | a1 a2 R & ! a1 a2 | | & ! a1 ! a2 & ! a1 a2 & & a1 ! a2 R & ! a1 a2 | & ! a1 a2 & a1 ! a2 & G F & ! d1 d2 & G F & ! c1 c2 & G F & ! b1 b2 G F & ! a1 a2 G | | a1 ! a2 | b1 ! b2 G | | a1 ! a2 | d1 ! d2 G | | b1 ! b2 | a1 ! a2 G | | b1 ! b2 | c1 ! c2 G | | c1 ! c2 | b1 ! b2 G | | c1 ! c2 | d1 ! d2 G | | d1 ! d2 | a1 ! a2 G | | d1 ! d2 | c1 ! c2 G | | ! a1 a2 | ! b1 b2 G | | ! a1 a2 | ! d1 d2 G | | ! b1 b2 | ! a1 a2 G | | ! b1 b2 | ! c1 c2 G | | ! c1 c2 | ! b1 b2 G | | ! c1 c2 | ! d1 d2 G | | ! d1 d2 | ! a1 a2 G | | ! d1 d2 | ! c1 c2 G | | | a1 ! a2 ! m X | ! m & ! a1 a2:
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

*/

/* Lookup-Table contents:
- LUT 0 has:
  -> Inputs uvwState13 uvwState14 uvwState5 uvwState6 c1 c2
  -> Outputs new_n42 new_n43 new_n46 new_n57 new_n44 new_n58 uvwState0incoming0 uvwState0incoming5 uvwState0incoming6 uvwState0incoming13 uvwState0incoming14 uvwState5incoming0 uvwState5incoming1 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13incoming1 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs a1 a2 b1 b2 new_n44 d2 d1
  -> Outputs new_n37 uvwState1incoming1 new_n49 new_n68 new_n71 uvwState9incoming1 uvwState15incoming1
- LUT 2 has:
  -> Inputs a1 a2 m uvwState1 uvwState2 uvwState9 uvwState10
  -> Outputs new_n30 new_n34 uvwState0incoming9 uvwState0incoming10 new_n53 new_n54 new_n76 uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next uvwState9incoming0 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next uvwState18incoming0 uvwState18Next
- LUT 3 has:
  -> Inputs new_n37 new_n43 new_n49 new_n68 new_n71 uvwState18 new_n76
  -> Outputs new_n78 uvwState0incoming17 uvwState0incoming18
- LUT 4 has:
  -> Inputs new_n78 d2 uvwState15 new_n57 uvwState16 new_n58 d1
  -> Outputs new_n82 uvwState0incoming15 uvwState0incoming16 uvwState7incoming1 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 5 has:
  -> Inputs new_n82 uvwState12 b1 b2 new_n53 new_n54 uvwState11
  -> Outputs uvwState0incoming11 new_n86 uvwState0incoming12 uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 6 has:
  -> Inputs new_n42 new_n86 new_n46 uvwState8 d2 uvwState7 d1
  -> Outputs uvwState0incoming7 uvwState0incoming8 uvwState7incoming0 uvwState7Next new_n90 uvwState8incoming0 uvwState8incoming1 uvwState8Next
- LUT 7 has:
  -> Inputs new_n30 new_n34 b1 b2 new_n90 uvwState4 uvwState3
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0incoming3 uvwState0incoming4 uvwState0Next uvwState3incoming0 uvwState3incoming1 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming1
*/
