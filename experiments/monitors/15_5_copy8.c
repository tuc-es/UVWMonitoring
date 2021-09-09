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

const uint16_t lut0[32] = {0x60c0,0x60c0,0x6800,0x6800,0x60e0,0x60e0,0x6800,0x6800,
    0x66c8,0x66c8,0x6800,0x6800,0x66e8,0x66e8,0x6800,0x6800,
    0x6001,0x7011,0x6000,0x7000,0x65a1,0x75b1,0x65a4,0x75a4,
    0x6601,0x7611,0x6608,0x7608,0x67a1,0x77b1,0x67ac,0x77ac};
const uint8_t lut1[32] = {0x4,0x4,0x40,0x40,0x5,0xd,0x41,0x49,
    0x20,0x20,0x60,0x60,0x4,0x4,0x40,0x40,
    0x6,0x16,0x4,0x4,0x7,0x1f,0x5,0xd,
    0x22,0x32,0x20,0x20,0x6,0x16,0x4,0x4};
const uint16_t lut2[32] = {0x14,0x1c,0x94,0x14,0x17,0x1d,0x96,0x17,
    0xc14,0x1c,0xc94,0xc14,0xc33,0x10d,0xcb2,0xc33,
    0x3014,0x301c,0x94,0x3014,0x3053,0x320d,0x96,0x3053,
    0x3c14,0x301c,0xc94,0x3c14,0x3c73,0x330d,0xcb2,0x3c73};
const uint8_t lut3[32] = {0x20,0x31,0x20,0x30,0x22,0x31,0x22,0x32,
    0x20,0x20,0x2c,0x2c,0x22,0x22,0x2e,0x2e,
    0x0,0x31,0x0,0x30,0x2,0x31,0x2,0x32,
    0x0,0x0,0xc,0xc,0x2,0x2,0xe,0xe};
const uint8_t lut4[32] = {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x1,0x0,0x0,0x0,0x1,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1,
    0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0};
const uint8_t lut5[32] = {0x0,0x1,0x0,0x1,0x0,0x1,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x1,0x0,0x0,0x0,0x1,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
const uint8_t lut6[32] = {0x2,0x2,0x2,0x2,0x0,0x0,0x1,0x1,
    0x2,0x6,0x2,0x6,0x0,0x4,0x1,0x4,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x2,0x6,0x2,0x6,0x2,0x6,0x2,0x6};
const uint8_t lut7[16] = {0x18,0x1c,0xda,0xde,0x0,0xb4,0xc0,0xf4,
    0x0,0x0,0x0,0x0,0x0,0xb5,0xc2,0xf7};
const uint16_t lut8[32] = {0x8,0x9,0x20,0x21,0x8,0x9,0x30,0x31,
    0x8,0x9,0x1a4,0x1a4,0x8,0x9,0x1b4,0x1b4,
    0x0,0x1,0x0,0x1,0x172,0x172,0x170,0x171,
    0x184,0x184,0x180,0x181,0x1f6,0x1f6,0x1f0,0x1f1};
const uint8_t lut9[32] = {0x0,0x1,0x8,0x9,0x0,0x1,0xc,0xd,
    0x0,0x1,0x3a,0x3a,0x0,0x1,0x3e,0x3e,
    0x0,0x1,0x0,0x1,0x2c,0x2c,0x2c,0x2d,
    0x32,0x32,0x30,0x31,0x3e,0x3e,0x3c,0x3d};
const uint8_t lut10[32] = {0x0,0x4,0x0,0x4,0x0,0x4,0xc2,0xc2,
    0x10,0x14,0xd2,0xd2,0x0,0x4,0xc0,0xc4,
    0x0,0x4,0x0,0x4,0xb9,0xb9,0xfb,0xfb,
    0x18,0x1c,0xda,0xda,0xb8,0xbc,0xf8,0xfc};
const uint16_t lut11[32] = {0x8,0x0,0x20,0x0,0x9,0x1,0x21,0x1,
    0x8,0x184,0x1a4,0x180,0x9,0x184,0x1a4,0x181,
    0x8,0x172,0x30,0x170,0x9,0x172,0x31,0x171,
    0x8,0x1f6,0x1b4,0x1f0,0x9,0x1f6,0x1b4,0x1f1};
const uint8_t lut12[32] = {0x8,0x18,0x0,0x10,0xc,0x1c,0x0,0x10,
    0xca,0xca,0x0,0x10,0xce,0xce,0x0,0x10,
    0x0,0x10,0x0,0x10,0xac,0xbc,0xad,0xad,
    0xc0,0xd0,0xc2,0xc2,0xec,0xfc,0xef,0xef};
const uint8_t lut13[32] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
const uint8_t lut14[32] = {0x14,0x4,0x4,0x4,0x1c,0xbc,0x4,0xbd,
    0xd6,0xc4,0x4,0xc6,0xde,0xfc,0x4,0xff,
    0x10,0x0,0x0,0x0,0x18,0xb8,0x0,0xbd,
    0xd6,0xc0,0x0,0xc6,0xde,0xf8,0x0,0xff};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = ((apValues & 32)>0?2:0) | (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState13 & 1) | (apValues & 16);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((apValues & 128)>0?2:0) | ((apValues & 64)>0?16:0) | (lut0output & 1) | (apValues & 12);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = ((apValues & 256)>0?4:0) | (uvwState20>0?8:0) | (uvwState21>0?16:0) | (apValues & 3);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = ((lut2output & 128)>0?8:0) | (uvwState19 & 1) | (lut2output & 22);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = ((lut2output & 128)>0?16:0) | (lut1output & 7) | (lut2output & 8);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = ((lut0output & 2048)>0?2:0) | ((lut1output & 32)>0?4:0) | ((lut1output & 64)>0?16:0) | (lut4output & 1) | (lut1output & 8);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = ((lut5output & 1)>0?4:0) | (uvwState18>0?8:0) | (lut2output & 1) | (lut3output & 2) | (lut1output & 16);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState4>0?2:0) | (uvwState3 & 1) | (apValues & 12);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = ((apValues & 128)>0?2:0) | (uvwState15>0?4:0) | (uvwState16>0?8:0) | ((apValues & 64)>0?16:0) | (lut6output & 1);
  uint32_t lut8output = lut8[lut8input];
  uint32_t lut9input = ((apValues & 32)>0?2:0) | (uvwState13>0?4:0) | (uvwState14>0?8:0) | (lut8output & 1) | (apValues & 16);
  uint32_t lut9output = lut9[lut9input];
  uint32_t lut10input = (uvwState12>0?2:0) | (uvwState11>0?16:0) | (lut9output & 1) | (apValues & 12);
  uint32_t lut10output = lut10[lut10input];
  uint32_t lut11input = (uvwState10>0?8:0) | (uvwState9>0?16:0) | (apValues & 3) | (lut10output & 4);
  uint32_t lut11output = lut11[lut11input];
  uint32_t lut12input = ((apValues & 128)>0?2:0) | (uvwState7>0?4:0) | (uvwState8>0?8:0) | ((apValues & 64)>0?16:0) | (lut11output & 1);
  uint32_t lut12output = lut12[lut12input];
  uint32_t lut13input = (lut7output & 3) | (lut0output & 12) | (lut12output & 16);
  uint32_t lut13output = lut13[lut13input];
  uint32_t lut14input = (uvwState1>0?4:0) | (uvwState2>0?8:0) | ((lut13output & 1)>0?16:0) | (apValues & 3);
  uint32_t lut14output = lut14[lut14input];
  if ((lut0output & 2)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut14output & 1)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut14output & 2)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 1)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 4)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 8)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut12output & 1)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut12output & 2)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut11output & 2)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut11output & 4)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut10output & 1)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut10output & 2)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 16)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut9output & 2)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 2)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 4)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 1)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 32)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 64)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut14output & 8)) {
  } else if ((lut11output & 8)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut14output & 32)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut14output & 64)) {
  }
  if ((lut7output & 4)) {
  } else if ((lut7output & 8)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 32)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut7output & 64)) {
  }
  if ((lut0output & 32)) {
  } else if ((lut0output & 64)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 256)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut0output & 512)) {
  }
  if ((lut12output & 4)) {
  } else if ((lut8output & 8)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut12output & 32)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut12output & 64)) {
  }
  if ((lut11output & 16)) {
  } else if ((lut2output & 128)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut11output & 64)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut11output & 128)) {
  }
  if ((lut10output & 8)) {
  } else if ((lut1output & 32)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut10output & 32)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut10output & 64)) {
  }
  if ((lut9output & 4)) {
  } else if ((lut0output & 2048)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 4096)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut9output & 16)) {
  }
  if ((lut8output & 16)) {
  } else if ((lut1output & 64)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut8output & 64)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut8output & 128)) {
  }
  if ((lut0output & 8192)) {
  }
  if ((lut3output & 4)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 16)) {
  } else if ((lut2output & 256)) {
        buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  } else if ((lut2output & 512)) {
        buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  if ((lut2output & 1024)) {
  }
  if ((lut2output & 4096)) {
  }
  uvwState0 = (lut14output & 4);
  uvwState1 = (lut14output & 16);
  uvwState2 = (lut14output & 128);
  uvwState3 = (lut7output & 16);
  uvwState4 = (lut7output & 128);
  uvwState5 = (lut0output & 128);
  uvwState6 = (lut0output & 1024);
  uvwState7 = (lut12output & 8);
  uvwState8 = (lut12output & 128);
  uvwState9 = (lut11output & 32);
  uvwState10 = (lut11output & 256);
  uvwState11 = (lut10output & 16);
  uvwState12 = (lut10output & 128);
  uvwState13 = (lut9output & 8);
  uvwState14 = (lut9output & 32);
  uvwState15 = (lut8output & 32);
  uvwState16 = (lut8output & 256);
  uvwState17 = (lut0output & 16384);
  uvwState18 = (lut3output & 8);
  uvwState19 = (lut3output & 32);
  uvwState20 = (lut2output & 2048);
  uvwState21 = (lut2output & 8192);
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
  -> Inputs uvwState13 c2 uvwState5 uvwState6 c1
  -> Outputs new_n46 uvwState0incoming0 uvwState0incoming5 uvwState0incoming6 uvwState0incoming13 uvwState5incoming0 uvwState5incoming1 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming1 uvwState14incoming0 uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs new_n46 d2 b1 b2 d1
  -> Outputs new_n40 new_n52 new_n65 new_n72 new_n76 uvwState11incoming1 uvwState15incoming1
- LUT 2 has:
  -> Inputs a1 a2 m uvwState20 uvwState21
  -> Outputs new_n79 new_n82 new_n87 new_n34 new_n156 uvwState0incoming20 uvwState0incoming21 uvwState9incoming1 uvwState19incoming1 uvwState19incoming2 uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 3 has:
  -> Inputs uvwState19 new_n82 new_n87 uvwState9incoming1 new_n156
  -> Outputs uvwState0incoming19 new_n88 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19Next
- LUT 4 has:
  -> Inputs new_n40 new_n52 new_n65 new_n34 uvwState9incoming1
  -> Outputs new_n69
- LUT 5 has:
  -> Inputs new_n69 uvwState13incoming1 uvwState11incoming1 new_n72 uvwState15incoming1
  -> Outputs new_n75
- LUT 6 has:
  -> Inputs new_n79 new_n88 new_n75 uvwState18 new_n76
  -> Outputs new_n90 uvwState0incoming17 uvwState0incoming18
- LUT 7 has:
  -> Inputs uvwState3 uvwState4 b1 b2
  -> Outputs uvwState0incoming3 uvwState0incoming4 uvwState3incoming0 uvwState3incoming1 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next
- LUT 8 has:
  -> Inputs new_n90 d2 uvwState15 uvwState16 d1
  -> Outputs new_n92 uvwState0incoming15 uvwState0incoming16 uvwState7incoming1 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 9 has:
  -> Inputs new_n92 c2 uvwState13 uvwState14 c1
  -> Outputs new_n94 uvwState0incoming14 uvwState13incoming0 uvwState13Next uvwState14incoming1 uvwState14Next
- LUT 10 has:
  -> Inputs new_n94 uvwState12 b1 b2 uvwState11
  -> Outputs uvwState0incoming11 uvwState0incoming12 new_n96 uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 11 has:
  -> Inputs a1 a2 new_n96 uvwState10 uvwState9
  -> Outputs new_n98 uvwState0incoming9 uvwState0incoming10 uvwState1incoming1 uvwState9incoming0 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 12 has:
  -> Inputs new_n98 d2 uvwState7 uvwState8 d1
  -> Outputs uvwState0incoming7 uvwState0incoming8 uvwState7incoming0 uvwState7Next new_n100 uvwState8incoming0 uvwState8incoming1 uvwState8Next
- LUT 13 has:
  -> Inputs uvwState0incoming3 uvwState0incoming4 uvwState0incoming5 uvwState0incoming6 new_n100
  -> Outputs new_n104
- LUT 14 has:
  -> Inputs a1 a2 uvwState1 uvwState2 new_n104
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0Next uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next
*/
