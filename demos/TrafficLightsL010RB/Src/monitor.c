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
bool uvwState17 = 0;
bool uvwState18 = 0;
bool uvwState19 = 0;
bool uvwState20 = 0;
bool uvwState21 = 1;
bool uvwState22 = 0;
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
  uint32_t b17p0;
  uint32_t b18p0;
  uint32_t b19p0;
  uint32_t b20p0;
  uint32_t b22p0;
} buf = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint32_t b21p0 = 0;
uint32_t cnt1 = 0;
uint32_t cnt2 = 0;
uint32_t cnt3 = 0;
uint32_t cnt4 = 0;

uint32_t lut0[32] = {0x183fe38,0x181fe10,0x199fe09,0x181fe18,0x183fe30,0x181fe10,0x199fe01,0x181fe10,
    0x1c3fe2a,0x1c1fe02,0x1d9fe0b,0x1c1fe0a,0x183fe38,0x181fe10,0x199fe09,0x181fe18,
    0x183fe38,0x1b5ff54,0x19dfe09,0x1b5fe58,0x183fe30,0x1b5ff54,0x19dfe01,0x1b5fe50,
    0x1c3fe2a,0x1f5ff46,0x1ddfe0b,0x1f5fe4a,0x183fe38,0x1b5ff54,0x19dfe09,0x1b5fe58};
uint16_t lut1[32] = {0x638,0x12,0x1014,0x18,0x6b8,0x92,0x1014,0x98,
    0x738,0xd13,0x1014,0xd49,0x7b8,0xd93,0x1014,0xdc9,
    0x628,0x2,0x1004,0x8,0x6a8,0x82,0x1004,0x88,
    0x728,0xd03,0x1004,0xd49,0x7a8,0xd83,0x1004,0xdc9};
uint16_t lut2[16] = {0x60,0x0,0x400,0x0,0x70,0x2d0,0x400,0x2d5,
    0x36a,0x300,0x400,0x30a,0x37a,0x3d0,0x400,0x3df};
uint16_t lut3[32] = {0x10e,0x4,0x5,0x6,0x14e,0x44,0x5,0x46,
    0x18e,0xb84,0x5,0xb92,0x1ce,0xbc4,0x5,0xbd2,
    0xd2a,0xc04,0x5,0xc22,0xd6a,0xc44,0x5,0xc62,
    0xdaa,0xf84,0x5,0xfb2,0xdea,0xfc4,0x5,0xff2};
uint16_t lut4[32] = {0x31a,0x8,0x9,0xa,0x39a,0x1688,0x9,0x16ae,
    0x1b52,0x1808,0x9,0x1842,0x1bd2,0x1e88,0x9,0x1ee6,
    0x312,0x0,0x1,0x2,0x392,0x1680,0x1,0x16a6,
    0x1b52,0x1800,0x1,0x1842,0x1bd2,0x1e80,0x1,0x1ee6};
uint8_t lut5[32] = {0x0,0x2,0x0,0x2,0x0,0x0,0x0,0x0,
    0x0,0x2,0x0,0x2,0x0,0x0,0x0,0x0,
    0x1,0x3,0x0,0x2,0x1,0x1,0x0,0x0,
    0x0,0x2,0x0,0x2,0x0,0x0,0x0,0x0};
uint16_t lut6[32] = {0x0,0x0,0x20,0x0,0x8,0x8,0x20,0x8,
    0x0,0x171,0x30,0x170,0x8,0x179,0x30,0x178,
    0x0,0x186,0x1a6,0x180,0x8,0x18e,0x1a6,0x188,
    0x0,0x1f7,0x1b6,0x1f0,0x8,0x1ff,0x1b6,0x1f8};
uint8_t lut7[32] = {0x2,0x4,0x2,0x2,0x0,0x4,0x0,0x0,
    0x2,0x4,0x2,0x2,0x0,0x4,0x0,0x0,
    0x2,0x4,0x2,0x2,0x0,0x4,0x0,0x0,
    0x3,0x5,0x3,0x3,0x1,0x5,0x1,0x1};
uint8_t lut8[32] = {0x0,0x6,0x9,0xf,0x0,0x0,0x9,0x9,
    0x0,0x6,0x0,0x6,0x0,0x0,0x0,0x0,
    0x4,0x6,0xd,0xf,0x4,0x4,0xd,0xd,
    0x4,0x6,0x4,0x6,0x4,0x4,0x4,0x4};
uint8_t lut9[32] = {0x1,0x13,0x8,0x1a,0x1,0x13,0x1,0x13,
    0x1,0x1,0x8,0x8,0x1,0x1,0x1,0x1,
    0x1,0x16,0x8,0x1e,0x1,0x16,0x1,0x16,
    0x1,0x4,0x8,0xc,0x1,0x4,0x1,0x4};
uint8_t lut10[32] = {0x1,0x1,0x1,0x1,0x1,0x4,0x1,0x4,
    0x1,0x19,0x1,0x19,0x1,0x19,0x1,0x19,
    0x1,0x1,0x2,0x2,0x1,0x4,0x2,0x6,
    0x1,0x19,0x2,0x1a,0x1,0x19,0x2,0x1a};
uint8_t lut11[32] = {0x1,0x1,0x0,0x0,0x20,0x20,0x0,0x0,
    0x1,0xb,0x0,0xa,0x20,0x2a,0x0,0xa,
    0x1,0x1,0x74,0x74,0x30,0x30,0x74,0x74,
    0x1,0xb,0x74,0x7e,0x30,0x3a,0x74,0x7e};
uint8_t lut12[32] = {0x6,0x7,0x4,0x6,0x3,0x3,0x1,0x3,
    0x0,0x1,0x0,0x0,0x2,0x3,0x0,0x2,
    0x6,0x6,0x4,0x6,0x2,0x2,0x0,0x2,
    0x0,0x0,0x0,0x0,0x2,0x2,0x0,0x2};
uint8_t lut13[32] = {0x0,0xe,0x0,0xc,0x1,0xe,0x1,0xd,
    0x0,0x2,0x0,0x0,0x1,0x2,0x1,0x1,
    0x8,0xe,0x8,0xc,0x9,0xe,0x9,0xd,
    0x8,0xa,0x8,0x8,0x9,0xa,0x9,0x9};
uint8_t lut14[32] = {0x2,0x2,0x1,0x2,0x1,0x2,0x1,0x2,
    0x6,0x6,0x5,0x6,0x5,0x6,0x5,0x6,
    0x6,0x6,0x5,0x6,0x5,0x6,0x5,0x6,
    0x6,0x6,0x5,0x6,0x5,0x6,0x5,0x6};
uint8_t lut15[32] = {0x0,0x0,0x8,0x0,0x0,0xd,0xc,0xc,
    0x0,0x0,0x8,0x0,0x0,0xd,0xc,0xc,
    0x0,0x0,0x8,0x0,0x0,0xd,0xc,0xc,
    0x2,0x2,0xa,0x2,0x2,0xf,0xe,0xe};
uint8_t lut16[32] = {0x0,0x2,0x0,0x2,0x0,0x2,0x0,0x2,
    0x0,0x2,0x0,0x2,0x0,0x2,0x1,0x3,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x3,0x3};
uint8_t lut17[32] = {0x4,0x5,0x6,0x7,0x4,0x5,0x6,0x7,
    0x4,0x5,0x6,0x7,0x4,0x5,0x6,0x7,
    0x4,0x5,0x6,0x7,0x4,0x5,0x6,0x7,
    0x4,0x5,0x6,0x7,0x0,0x5,0x6,0x7};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = ((apValues & 1)>0?1:0) + ((apValues & 2)>0?2:0) + ((apValues & 16)>0?4:0) + ((apValues & 32)>0?8:0) + (uvwState13>0?16:0);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((apValues & 64)>0?1:0) + ((apValues & 128)>0?2:0) + (uvwState4>0?4:0) + (uvwState11>0?8:0) + ((lut0output & 4)>0?16:0);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = ((apValues & 4)>0?1:0) + ((apValues & 8)>0?2:0) + (uvwState7>0?4:0) + (uvwState8>0?8:0);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = ((apValues & 1)>0?1:0) + ((apValues & 2)>0?2:0) + (uvwState1>0?4:0) + (uvwState5>0?8:0) + (uvwState6>0?16:0);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = ((apValues & 16)>0?1:0) + ((apValues & 32)>0?2:0) + (uvwState9>0?4:0) + (uvwState10>0?8:0) + ((lut2output & 2)>0?16:0);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState3>0?1:0) + ((lut2output & 1)>0?2:0) + ((lut4output & 1)>0?4:0) + ((lut4output & 4)>0?8:0) + ((lut1output & 16)>0?16:0);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = ((apValues & 4)>0?1:0) + ((apValues & 8)>0?2:0) + (uvwState2>0?4:0) + (uvwState15>0?8:0) + (uvwState16>0?16:0);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState18>0?1:0) + ((lut4output & 2)>0?2:0) + ((lut6output & 2)>0?4:0) + ((lut5output & 1)>0?8:0) + ((lut3output & 4)>0?16:0);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = (uvwState14>0?1:0) + (uvwState18>0?2:0) + ((lut3output & 8)>0?4:0) + ((lut4output & 16)>0?8:0) + ((lut0output & 64)>0?16:0);
  uint32_t lut8output = lut8[lut8input];
  uint32_t lut9input = (uvwState12>0?1:0) + (uvwState14>0?2:0) + ((lut3output & 2)>0?4:0) + ((lut1output & 4)>0?8:0) + ((lut1output & 8)>0?16:0);
  uint32_t lut9output = lut9[lut9input];
  uint32_t lut10input = ((apValues & 256)>0?1:0) + (uvwState19>0?2:0) + (uvwState22>0?4:0) + ((lut3output & 1)>0?8:0) + ((lut1output & 2)>0?16:0);
  uint32_t lut10output = lut10[lut10input];
  uint32_t lut11input = ((apValues & 16)>0?1:0) + ((apValues & 64)>0?2:0) + ((apValues & 128)>0?4:0) + (uvwState17>0?8:0) + (uvwState19>0?16:0);
  uint32_t lut11output = lut11[lut11input];
  uint32_t lut12input = ((apValues & 4)>0?1:0) + ((apValues & 8)>0?2:0) + ((apValues & 64)>0?4:0) + ((apValues & 128)>0?8:0) + ((lut0output & 8)>0?16:0);
  uint32_t lut12output = lut12[lut12input];
  uint32_t lut13input = (uvwState20>0?1:0) + ((lut1output & 8)>0?2:0) + ((lut7output & 2)>0?4:0) + ((lut12output & 4)>0?8:0) + ((lut11output & 4)>0?16:0);
  uint32_t lut13output = lut13[lut13input];
  uint32_t lut14input = ((lut12output & 1)>0?1:0) + ((lut12output & 2)>0?2:0) + ((lut0output & 16)>0?4:0) + ((lut11output & 2)>0?8:0) + ((lut8output & 1)>0?16:0);
  uint32_t lut14output = lut14[lut14input];
  uint32_t lut15input = ((apValues & 16)>0?1:0) + ((apValues & 32)>0?2:0) + (uvwState17>0?4:0) + ((lut4output & 8)>0?8:0) + ((lut9output & 1)>0?16:0);
  uint32_t lut15output = lut15[lut15input];
  uint32_t lut16input = ((lut1output & 1)>0?1:0) + ((lut14output & 1)>0?2:0) + ((lut13output & 1)>0?4:0) + ((lut15output & 2)>0?8:0) + ((lut9output & 2)>0?16:0);
  uint32_t lut16output = lut16[lut16input];
  uint32_t lut17input = ((lut6output & 1)>0?1:0) + ((lut15output & 1)>0?2:0) + ((lut10output & 1)>0?4:0) + ((lut7output & 1)>0?8:0) + ((lut16output & 1)>0?16:0);
  uint32_t lut17output = lut17[lut17input];
  if ((lut0output & 128)) {
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut3output & 16)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut3output & 32)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut2output & 4)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut2output & 8)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut4output & 32)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut4output & 64)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut1output & 64)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut9output & 4)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut0output & 256)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut9output & 8)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut17output & 1)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut17output & 2)) {
        buf.b0p0 = buf.b17p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut7output & 4)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut10output & 2)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut13output & 2)) {
        buf.b0p0 = buf.b20p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut14output & 2)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut10output & 4)) {
        buf.b0p0 = buf.b22p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(0,&(buf.b0p0),4);
  }
  if ((lut3output & 64)) {
    cnt1++;
    if ((cnt1 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(1,cnt1, &buf.b1p0,1);
    }
  } else if ((lut0output & 512)) {
        buf.b1p0 = b21p0 | (apValues << 0);
  }
  if ((lut6output & 8)) {
    cnt2++;
    if ((cnt2 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(2,cnt2, &buf.b2p0,1);
    }
  } else if ((lut0output & 2048)) {
        buf.b2p0 = b21p0 | (apValues << 0);
  }
  if ((lut5output & 2)) {
    cnt3++;
    if ((cnt3 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(3,cnt3, &buf.b3p0,1);
    }
  } else if ((lut0output & 8192)) {
        buf.b3p0 = b21p0 | (apValues << 0);
  }
  if ((lut1output & 128)) {
    cnt4++;
    if ((cnt4 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(4,cnt4, &buf.b4p0,1);
    }
  } else if ((lut0output & 32768)) {
        buf.b4p0 = b21p0 | (apValues << 0);
  }
  if ((lut3output & 128)) {
  } else if ((lut0output & 131072)) {
        buf.b5p0 = b21p0 | (apValues << 0);
  }
  if ((lut3output & 512)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut3output & 1024)) {
  }
  if ((lut2output & 16)) {
  } else if ((lut2output & 32)) {
        buf.b7p0 = b21p0 | (apValues << 0);
  }
  if ((lut2output & 128)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut2output & 256)) {
  }
  if ((lut4output & 128)) {
  } else if ((lut4output & 256)) {
        buf.b9p0 = b21p0 | (apValues << 0);
  }
  if ((lut4output & 1024)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut4output & 2048)) {
  }
  if ((lut1output & 256)) {
  } else if ((lut1output & 512)) {
        buf.b11p0 = b21p0 | (apValues << 0);
  }
  if ((lut1output & 2048)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut9output & 16)) {
  }
  if ((lut0output & 262144)) {
  } else if ((lut0output & 524288)) {
        buf.b13p0 = b21p0 | (apValues << 0);
  }
  if ((lut0output & 2097152)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut8output & 2)) {
  }
  if ((lut6output & 16)) {
  } else if ((lut2output & 1024)) {
        buf.b15p0 = b21p0 | (apValues << 0);
  }
  if ((lut6output & 64)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut6output & 128)) {
  }
  if ((lut15output & 4)) {
  } else if ((lut0output & 4194304)) {
        buf.b17p0 = b21p0 | (apValues << 0);
  }
  if ((lut11output & 8)) {
        buf.b18p0 = buf.b17p0 | (apValues << 9);
  } else if ((lut8output & 8)) {
  }
  if ((lut11output & 16)) {
  } else if ((lut1output & 4096)) {
        buf.b19p0 = b21p0 | (apValues << 0);
  }
  if ((lut11output & 64)) {
        buf.b20p0 = buf.b19p0 | (apValues << 9);
  } else if ((lut13output & 4)) {
  }
  if ((lut0output & 8388608)) {
  }
  if ((lut10output & 8)) {
        buf.b22p0 = b21p0 | (apValues << 0);
  }
  uvwState0 = ((lut17output & 4))>0?1:0;
  uvwState1 = ((lut0output & 1024))>0?1:0;
  uvwState2 = ((lut0output & 4096))>0?1:0;
  uvwState3 = ((lut0output & 16384))>0?1:0;
  uvwState4 = ((lut0output & 65536))>0?1:0;
  uvwState5 = ((lut3output & 256))>0?1:0;
  uvwState6 = ((lut3output & 2048))>0?1:0;
  uvwState7 = ((lut2output & 64))>0?1:0;
  uvwState8 = ((lut2output & 512))>0?1:0;
  uvwState9 = ((lut4output & 512))>0?1:0;
  uvwState10 = ((lut4output & 4096))>0?1:0;
  uvwState11 = ((lut1output & 1024))>0?1:0;
  uvwState12 = ((lut16output & 2))>0?1:0;
  uvwState13 = ((lut0output & 1048576))>0?1:0;
  uvwState14 = ((lut8output & 4))>0?1:0;
  uvwState15 = ((lut6output & 32))>0?1:0;
  uvwState16 = ((lut6output & 256))>0?1:0;
  uvwState17 = ((lut15output & 8))>0?1:0;
  uvwState18 = ((lut14output & 4))>0?1:0;
  uvwState19 = ((lut11output & 32))>0?1:0;
  uvwState20 = ((lut13output & 8))>0?1:0;
  uvwState21 = ((lut0output & 16777216))>0?1:0;
  uvwState22 = ((lut10output & 16))>0?1:0;
}

/* Decoding information for the buffers:
   -------------------------------------

 - UVW state 0 with LTL subformula (Polish notation):
    Bits 0 to 17: previous buffer
    Bits 18 to 26: propositions
    Bits 27 to 31: incoming transition
       -> Value 0 for transition from UVW state 5
       -> Value 1 for transition from UVW state 6
       -> Value 2 for transition from UVW state 7
       -> Value 3 for transition from UVW state 8
       -> Value 4 for transition from UVW state 9
       -> Value 5 for transition from UVW state 10
       -> Value 6 for transition from UVW state 11
       -> Value 7 for transition from UVW state 12
       -> Value 8 for transition from UVW state 13
       -> Value 9 for transition from UVW state 14
       -> Value 10 for transition from UVW state 15
       -> Value 11 for transition from UVW state 16
       -> Value 12 for transition from UVW state 17
       -> Value 13 for transition from UVW state 18
       -> Value 14 for transition from UVW state 19
       -> Value 15 for transition from UVW state 20
       -> Value 16 for transition from UVW state 21
       -> Value 17 for transition from UVW state 22
 - UVW state 1 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 2 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 3 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 4 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
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
    Bits 0 to 8: propositions
 - UVW state 18 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 19 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 20 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
 - UVW state 21 with LTL subformula (Polish notation):
    Initial state only
 - UVW state 22 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions


UVW on which the monitor is based:
 UVW with 23 states and initial states [21]:
 - State No. 0 with name reject (rej.):
   - t.t.s. 0 for TRUE
 - State No. 1 with name F & ! a1 a2 (rej.):
   - t.t.s. 1 for ite(a1, TRUE, (~ a2))
 - State No. 2 with name F & ! b1 b2 (rej.):
   - t.t.s. 2 for ite(b1, TRUE, (~ b2))
 - State No. 3 with name F & ! c1 c2 (rej.):
   - t.t.s. 3 for ite(c1, TRUE, (~ c2))
 - State No. 4 with name F & ! d1 d2 (rej.):
   - t.t.s. 4 for ite(d1, TRUE, (~ d2))
 - State No. 5 with name || reject R & ! a1 a2 | | & ! a1 ! a2 & ! a1 a2 & & a1 ! a2 R & ! a1 a2 | & ! a1 a2 & a1 ! a2:
   - t.t.s. 5 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for ite(a1, a2, FALSE)
   - t.t.s. 6 for a1
 - State No. 6 with name || reject || reject || reject || reject R & ! a1 a2 | & ! a1 a2 & a1 ! a2:
   - t.t.s. 6 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for ite(a1, a2, (~ a2))
 - State No. 7 with name || reject R & ! b1 b2 | | & ! b1 ! b2 & ! b1 b2 & & b1 ! b2 R & ! b1 b2 | & ! b1 b2 & b1 ! b2:
   - t.t.s. 7 for ite(b1, TRUE, (~ b2))
   - t.t.s. 0 for ite(b1, b2, FALSE)
   - t.t.s. 8 for b1
 - State No. 8 with name || reject || reject || reject || reject R & ! b1 b2 | & ! b1 b2 & b1 ! b2:
   - t.t.s. 8 for ite(b1, TRUE, (~ b2))
   - t.t.s. 0 for ite(b1, b2, (~ b2))
 - State No. 9 with name || reject R & ! c1 c2 | | & ! c1 ! c2 & ! c1 c2 & & c1 ! c2 R & ! c1 c2 | & ! c1 c2 & c1 ! c2:
   - t.t.s. 9 for ite(c1, TRUE, (~ c2))
   - t.t.s. 0 for ite(c1, c2, FALSE)
   - t.t.s. 10 for c1
 - State No. 10 with name || reject || reject || reject || reject R & ! c1 c2 | & ! c1 c2 & c1 ! c2:
   - t.t.s. 10 for ite(c1, TRUE, (~ c2))
   - t.t.s. 0 for ite(c1, c2, (~ c2))
 - State No. 11 with name || reject R & ! d1 d2 | | & ! d1 ! d2 & ! d1 d2 & & d1 ! d2 R & ! d1 d2 | & ! d1 d2 & d1 ! d2:
   - t.t.s. 11 for ite(d1, TRUE, (~ d2))
   - t.t.s. 0 for ite(d1, d2, FALSE)
   - t.t.s. 12 for d1
 - State No. 12 with name || reject || reject || reject || reject R & ! d1 d2 | & ! d1 d2 & d1 ! d2:
   - t.t.s. 12 for ite(d1, TRUE, (~ d2))
   - t.t.s. 0 for ite(d1, d2, (~ d2))
 - State No. 13 with name || reject R & ! a1 ! a2 | | & ! a1 a2 & ! a1 ! a2 & & a1 a2 R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2:
   - t.t.s. 13 for ite(a1, TRUE, a2)
   - t.t.s. 0 for (~ ite(a1, a2, TRUE))
   - t.t.s. 14 for a1
 - State No. 14 with name || reject || reject || reject || reject R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2:
   - t.t.s. 14 for ite(a1, TRUE, a2)
   - t.t.s. 0 for (~ ite(a1, a2, (~ a2)))
 - State No. 15 with name || reject R & ! b1 ! b2 | | & ! b1 b2 & ! b1 ! b2 & & b1 b2 R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2:
   - t.t.s. 15 for ite(b1, TRUE, b2)
   - t.t.s. 0 for (~ ite(b1, b2, TRUE))
   - t.t.s. 16 for b1
 - State No. 16 with name || reject || reject || reject || reject R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2:
   - t.t.s. 16 for ite(b1, TRUE, b2)
   - t.t.s. 0 for (~ ite(b1, b2, (~ b2)))
 - State No. 17 with name || reject R & ! c1 ! c2 | | & ! c1 c2 & ! c1 ! c2 & & c1 c2 R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2:
   - t.t.s. 17 for ite(c1, TRUE, c2)
   - t.t.s. 0 for (~ ite(c1, c2, TRUE))
   - t.t.s. 18 for c1
 - State No. 18 with name || reject || reject || reject || reject R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2:
   - t.t.s. 18 for ite(c1, TRUE, c2)
   - t.t.s. 0 for (~ ite(c1, c2, (~ c2)))
 - State No. 19 with name || reject R & ! d1 ! d2 | | & ! d1 d2 & ! d1 ! d2 & & d1 d2 R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2:
   - t.t.s. 19 for ite(d1, TRUE, d2)
   - t.t.s. 0 for (~ ite(d1, d2, TRUE))
   - t.t.s. 20 for d1
 - State No. 20 with name || reject || reject || reject || reject R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2:
   - t.t.s. 20 for ite(d1, TRUE, d2)
   - t.t.s. 0 for (~ ite(d1, d2, (~ d2)))
 - State No. 21 with name & & & & & & & & & & & & & & & & & & G | | d1 ! d2 R & ! d1 ! d2 | | & ! d1 d2 & ! d1 ! d2 & & d1 d2 R & ! d1 ! d2 | & ! d1 ! d2 & d1 d2 & G | | c1 ! c2 R & ! c1 ! c2 | | & ! c1 c2 & ! c1 ! c2 & & c1 c2 R & ! c1 ! c2 | & ! c1 ! c2 & c1 c2 & G | | b1 ! b2 R & ! b1 ! b2 | | & ! b1 b2 & ! b1 ! b2 & & b1 b2 R & ! b1 ! b2 | & ! b1 ! b2 & b1 b2 & G | | a1 ! a2 R & ! a1 ! a2 | | & ! a1 a2 & ! a1 ! a2 & & a1 a2 R & ! a1 ! a2 | & ! a1 ! a2 & a1 a2 & G | | d1 d2 R & ! d1 d2 | | & ! d1 ! d2 & ! d1 d2 & & d1 ! d2 R & ! d1 d2 | & ! d1 d2 & d1 ! d2 & G | | c1 c2 R & ! c1 c2 | | & ! c1 ! c2 & ! c1 c2 & & c1 ! c2 R & ! c1 c2 | & ! c1 c2 & c1 ! c2 & G | | b1 b2 R & ! b1 b2 | | & ! b1 ! b2 & ! b1 b2 & & b1 ! b2 R & ! b1 b2 | & ! b1 b2 & b1 ! b2 & G | | a1 a2 R & ! a1 a2 | | & ! a1 ! a2 & ! a1 a2 & & a1 ! a2 R & ! a1 a2 | & ! a1 a2 & a1 ! a2 & G F & ! d1 d2 & G F & ! c1 c2 & G F & ! b1 b2 G F & ! a1 a2 G | | a1 ! a2 | b1 ! b2 G | | a1 ! a2 | d1 ! d2 G | | b1 ! b2 | a1 ! a2 G | | b1 ! b2 | c1 ! c2 G | | c1 ! c2 | b1 ! b2 G | | c1 ! c2 | d1 ! d2 G | | d1 ! d2 | a1 ! a2 G | | d1 ! d2 | c1 ! c2 G | | ! a1 a2 | ! b1 b2 G | | ! a1 a2 | ! d1 d2 G | | ! b1 b2 | ! a1 a2 G | | ! b1 b2 | ! c1 c2 G | | ! c1 c2 | ! b1 b2 G | | ! c1 c2 | ! d1 d2 G | | ! d1 d2 | ! a1 a2 G | | ! d1 d2 | ! c1 c2 G | | | a1 ! a2 ! m X | ! m & ! a1 a2:
   - t.t.s. 19 for (~ ite(d1, TRUE, (~ d2)))
   - t.t.s. 21 for TRUE
   - t.t.s. 17 for (~ ite(c1, TRUE, (~ c2)))
   - t.t.s. 15 for (~ ite(b1, TRUE, (~ b2)))
   - t.t.s. 13 for (~ ite(a1, TRUE, (~ a2)))
   - t.t.s. 11 for (~ ite(d1, TRUE, d2))
   - t.t.s. 9 for (~ ite(c1, TRUE, c2))
   - t.t.s. 7 for (~ ite(b1, TRUE, b2))
   - t.t.s. 5 for (~ ite(a1, TRUE, a2))
   - t.t.s. 4 for TRUE
   - t.t.s. 3 for TRUE
   - t.t.s. 2 for TRUE
   - t.t.s. 1 for TRUE
   - t.t.s. 0 for (~ ite(a1, ite(a2, ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)), ite(c1, c2, ite(c2, ite(d1, TRUE, (~ d2)), TRUE))), ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), (~ c2)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)))), ite(b1, ite(b2, ite(c1, ite(d1, d2, TRUE), ite(c2, ite(d1, d2, (~ d2)), ite(d1, d2, TRUE))), FALSE), ite(b2, ite(c1, ite(d1, d2, TRUE), (~ ite(c2, TRUE, (~ ite(d1, d2, TRUE))))), ite(c1, ite(d1, d2, TRUE), ite(c2, ite(d1, d2, (~ d2)), ite(d1, d2, TRUE)))))), ite(a2, ite(b1, ite(b2, ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), ite(d1, d2, (~ d2))), ite(d1, TRUE, (~ d2))), ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), FALSE), ite(d1, TRUE, (~ d2)))), (~ ite(b2, TRUE, (~ ite(c1, ite(c2, ite(d1, TRUE, (~ d2)), ite(d1, d2, (~ d2))), ite(d1, TRUE, (~ d2))))))), ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)), ite(c1, c2, ite(c2, ite(d1, TRUE, (~ d2)), TRUE))), ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), (~ c2)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), ite(c2, ite(d1, TRUE, (~ d2)), TRUE)))))))
   - t.t.s. 22 for (~ ite(a1, TRUE, (~ ite(a2, m, FALSE))))
 - State No. 22 with name || reject | ! m & ! a1 a2:
   - t.t.s. 0 for ite(a1, m, (~ ite(a2, TRUE, (~ m))))

*/

/* Lookup-Table contents:
- LUT 0 has:
  -> Inputs a1 a2 c1 c2 uvwState13
  -> Outputs new_n34 new_n46 new_n57 new_n66 new_n69 new_n97 new_n118 uvwState0incoming0 uvwState0incoming9 uvwState1incoming1 uvwState1Next uvwState2incoming1 uvwState2Next uvwState3incoming1 uvwState3Next uvwState4incoming1 uvwState4Next uvwState5incoming1 uvwState13incoming0 uvwState13incoming1 uvwState13Next uvwState14incoming0 uvwState17incoming1 uvwState21incoming0 uvwState21Next
- LUT 1 has:
  -> Inputs d1 d2 uvwState4 uvwState11 new_n57
  -> Outputs new_n51 new_n53 new_n54 new_n55 new_n79 new_n112 uvwState0incoming7 uvwState4incoming0 uvwState11incoming0 uvwState11incoming1 uvwState11Next uvwState12incoming0 uvwState19incoming1
- LUT 2 has:
  -> Inputs b1 b2 uvwState7 uvwState8
  -> Outputs new_n40 new_n44 uvwState0incoming3 uvwState0incoming4 uvwState7incoming0 uvwState7incoming1 uvwState7Next uvwState8incoming0 uvwState8incoming1 uvwState8Next uvwState15incoming1
- LUT 3 has:
  -> Inputs a1 a2 uvwState1 uvwState5 uvwState6
  -> Outputs new_n34 new_n35 new_n81 new_n97 uvwState0incoming1 uvwState0incoming2 uvwState1incoming0 uvwState5incoming0 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next
- LUT 4 has:
  -> Inputs c1 c2 uvwState9 uvwState10 new_n44
  -> Outputs new_n46 new_n47 new_n49 new_n86 new_n107 uvwState0incoming5 uvwState0incoming6 uvwState9incoming0 uvwState9incoming1 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 5 has:
  -> Inputs uvwState3 new_n40 new_n46 new_n49 new_n79
  -> Outputs new_n80 uvwState3incoming0
- LUT 6 has:
  -> Inputs b1 b2 uvwState2 uvwState15 uvwState16
  -> Outputs new_n59 new_n60 uvwState0incoming12 uvwState2incoming0 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 7 has:
  -> Inputs uvwState18 new_n47 new_n60 new_n80 new_n81
  -> Outputs new_n82 new_n84 uvwState0incoming14
- LUT 8 has:
  -> Inputs uvwState14 uvwState18 new_n97 new_n107 new_n118
  -> Outputs new_n129 uvwState14incoming1 uvwState14Next uvwState18incoming1
- LUT 9 has:
  -> Inputs uvwState12 uvwState14 new_n35 new_n54 new_n55
  -> Outputs new_n87 new_n114 uvwState0incoming8 uvwState0incoming10 uvwState12incoming1
- LUT 10 has:
  -> Inputs m uvwState19 uvwState22 new_n34 new_n53
  -> Outputs new_n76 uvwState0incoming15 uvwState0incoming18 uvwState22incoming0 uvwState22Next
- LUT 11 has:
  -> Inputs c1 d1 d2 uvwState17 uvwState19
  -> Outputs new_n112 new_n128 new_n133 uvwState18incoming0 uvwState19incoming0 uvwState19Next uvwState20incoming0
- LUT 12 has:
  -> Inputs b1 b2 d1 d2 new_n66
  -> Outputs new_n67 new_n68 new_n112
- LUT 13 has:
  -> Inputs uvwState20 new_n55 new_n84 new_n112 new_n133
  -> Outputs new_n85 uvwState0incoming16 uvwState20incoming1 uvwState20Next
- LUT 14 has:
  -> Inputs new_n67 new_n68 new_n69 new_n128 new_n129
  -> Outputs new_n71 uvwState0incoming17 uvwState18Next
- LUT 15 has:
  -> Inputs c1 c2 uvwState17 new_n86 new_n87
  -> Outputs new_n61 new_n88 uvwState17incoming0 uvwState17Next
- LUT 16 has:
  -> Inputs new_n51 new_n71 new_n85 new_n88 new_n114
  -> Outputs new_n90 uvwState12Next
- LUT 17 has:
  -> Inputs new_n59 new_n61 new_n76 new_n82 new_n90
  -> Outputs uvwState0incoming11 uvwState0incoming13 uvwState0Next
*/
