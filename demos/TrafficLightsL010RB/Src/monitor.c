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
bool uvwState9 = 1;
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
} buf = {0,0,0,0,0,0,0,0,0};
const uint32_t b9p0 = 0;
uint32_t cnt1 = 0;
uint32_t cnt2 = 0;
uint32_t cnt3 = 0;
uint32_t cnt4 = 0;

uint16_t lut0[32] = {0x0,0x0,0x0,0x0,0x18,0x18,0x0,0x18,
    0x23,0x21,0x0,0x23,0x3b,0x39,0x0,0x3b,
    0xfd0,0xff4,0xfd0,0xfd0,0xfd8,0xffc,0xfd0,0xfd8,
    0xff3,0xff5,0xfd0,0xff3,0xffb,0xffd,0xfd0,0xffb};
uint8_t lut1[32] = {0x0,0x1,0x0,0x0,0xc,0xd,0x0,0xc,
    0x22,0x23,0x0,0x22,0x2e,0x2f,0x0,0x2e,
    0x8,0x39,0x8,0x8,0xc,0x3d,0x8,0xc,
    0x2a,0x3b,0x8,0x2a,0x2e,0x3f,0x8,0x2e};
uint8_t lut2[32] = {0x0,0x1,0x2,0x0,0xc,0xd,0x2,0xc,
    0x0,0x1,0x2,0x0,0xc,0xd,0x2,0xc,
    0x8,0x19,0xa,0x8,0xc,0x1d,0xa,0xc,
    0x8,0x19,0xa,0x8,0xc,0x1d,0xa,0xc};
uint8_t lut3[32] = {0x0,0x0,0x0,0x0,0x18,0x18,0x0,0x18,
    0x23,0x21,0x0,0x23,0x3b,0x39,0x0,0x3b,
    0x10,0x34,0x10,0x10,0x18,0x3c,0x10,0x18,
    0x33,0x35,0x10,0x33,0x3b,0x3d,0x10,0x3b};
uint8_t lut4[32] = {0x4,0xb,0x0,0xb,0x4,0xd,0x0,0x9,
    0x4,0x4,0x0,0x0,0x4,0x4,0x0,0x0,
    0xc,0xb,0x8,0xb,0xc,0xd,0x8,0x9,
    0xc,0xc,0x8,0x8,0xc,0xc,0x8,0x8};
uint8_t lut5[32] = {0x0,0x0,0x1,0x0,0x0,0x0,0x1,0x0,
    0x0,0x2,0x1,0x2,0x2,0x2,0x3,0x2,
    0x0,0x2,0x1,0x2,0x2,0x2,0x3,0x2,
    0x0,0x2,0x1,0x2,0x2,0x2,0x3,0x2};
uint8_t lut6[32] = {0x1,0x3,0x1,0x3,0x1,0x3,0x1,0x3,
    0x1,0x3,0x1,0x3,0x1,0x3,0x1,0x3,
    0x0,0x3,0x1,0x3,0x1,0x3,0x1,0x3,
    0x1,0x3,0x1,0x3,0x1,0x3,0x1,0x3};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = ((apValues & 64)>0?1:0) + ((apValues & 128)>0?2:0) + (uvwState4>0?4:0) + (uvwState8>0?8:0) + (uvwState9>0?16:0);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((apValues & 1)>0?1:0) + ((apValues & 2)>0?2:0) + (uvwState1>0?4:0) + (uvwState5>0?8:0) + (uvwState9>0?16:0);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = ((apValues & 16)>0?1:0) + ((apValues & 32)>0?2:0) + (uvwState3>0?4:0) + (uvwState6>0?8:0) + (uvwState9>0?16:0);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = ((apValues & 4)>0?1:0) + ((apValues & 8)>0?2:0) + (uvwState2>0?4:0) + (uvwState6>0?8:0) + (uvwState9>0?16:0);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = (uvwState7>0?1:0) + ((lut3output & 2)>0?2:0) + ((lut2output & 1)>0?4:0) + ((lut2output & 2)>0?8:0) + ((lut2output & 16)>0?16:0);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = ((lut1output & 1)>0?1:0) + ((lut1output & 2)>0?2:0) + ((lut2output & 1)>0?4:0) + ((lut3output & 4)>0?8:0) + ((lut0output & 4)>0?16:0);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState0>0?1:0) + ((lut5output & 1)>0?2:0) + ((lut0output & 2)>0?4:0) + ((lut5output & 2)>0?8:0) + ((lut4output & 4)>0?16:0);
  uint32_t lut6output = lut6[lut6input];
  if ((lut6output & 2)) {
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut5output & 1)) {
    buf.b0p0 = buf.b5p0 | (apValues << 9) | (0 << 18);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut3output & 2)) {
    buf.b0p0 = buf.b6p0 | (apValues << 9) | (1 << 18);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
    buf.b0p0 = buf.b7p0 | (apValues << 9) | (2 << 18);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut0output & 2)) {
    buf.b0p0 = buf.b8p0 | (apValues << 9) | (3 << 18);
    logViolationExplanation(0,&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
    buf.b0p0 = b9p0 | (apValues << 9) | (4 << 18);
    logViolationExplanation(0,&(buf.b0p0),4);
  }
  if ((lut1output & 4)) {
    cnt1++;
    if ((cnt1 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(1,cnt1, &buf.b1p0,1);
    }
  } else if ((lut0output & 64)) {
    buf.b1p0 = b9p0 | (apValues << 0);
  }
  if ((lut3output & 8)) {
    cnt2++;
    if ((cnt2 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(2,cnt2, &buf.b2p0,1);
    }
  } else if ((lut0output & 128)) {
    buf.b2p0 = b9p0 | (apValues << 0);
  }
  if ((lut2output & 4)) {
    cnt3++;
    if ((cnt3 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(3,cnt3, &buf.b3p0,1);
    }
  } else if ((lut0output & 256)) {
    buf.b3p0 = b9p0 | (apValues << 0);
  }
  if ((lut0output & 8)) {
    cnt4++;
    if ((cnt4 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(4,cnt4, &buf.b4p0,1);
    }
  } else if ((lut0output & 512)) {
    buf.b4p0 = b9p0 | (apValues << 0);
  }
  if ((lut1output & 2)) {
  } else if ((lut1output & 16)) {
    buf.b5p0 = b9p0 | (apValues << 0);
  }
  if ((lut3output & 1)) {
  } else if ((lut3output & 4)) {
    buf.b6p0 = b9p0 | (apValues << 0);
  }
  if ((lut4output & 1)) {
  } else if ((lut2output & 16)) {
    buf.b7p0 = b9p0 | (apValues << 0);
  }
  if ((lut0output & 1)) {
  } else if ((lut0output & 4)) {
    buf.b8p0 = b9p0 | (apValues << 0);
  }
  if ((lut0output & 1024)) {
  }
  uvwState0 = ((lut6output & 1))>0?1:0;
  uvwState1 = ((lut1output & 8))>0?1:0;
  uvwState2 = ((lut3output & 16))>0?1:0;
  uvwState3 = ((lut2output & 8))>0?1:0;
  uvwState4 = ((lut0output & 16))>0?1:0;
  uvwState5 = ((lut1output & 32))>0?1:0;
  uvwState6 = ((lut3output & 32))>0?1:0;
  uvwState7 = ((lut4output & 8))>0?1:0;
  uvwState8 = ((lut0output & 32))>0?1:0;
  uvwState9 = ((lut0output & 2048))>0?1:0;
}


/* Decoding information for the buffers:
   -------------------------------------

 - UVW state 0 with LTL subformula (Polish notation):
    Bits 0 to 8: previous buffer
    Bits 9 to 17: propositions
    Bits 18 to 20: incoming transition
       -> Value 0 for transition from UVW state 5
       -> Value 1 for transition from UVW state 6
       -> Value 2 for transition from UVW state 7
       -> Value 3 for transition from UVW state 8
       -> Value 4 for transition from UVW state 9
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
    Bits 0 to 8: propositions
 - UVW state 7 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 8 with LTL subformula (Polish notation):
    Bits 0 to 8: propositions
 - UVW state 9 with LTL subformula (Polish notation):
    Initial state only


UVW on which the monitor is based:
 UVW with 10 states and initial states [9]:
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
 - State No. 5 with name || reject R & ! a1 a2 | & a1 ! a2 & ! a1 a2:
   - t.t.s. 5 for ite(a1, TRUE, (~ a2))
   - t.t.s. 0 for ite(a1, a2, (~ a2))
 - State No. 6 with name || reject R & ! b1 b2 | & b1 ! b2 & ! b1 b2:
   - t.t.s. 6 for ite(b1, TRUE, (~ b2))
   - t.t.s. 0 for ite(b1, b2, (~ b2))
 - State No. 7 with name || reject R & ! c1 c2 | & c1 ! c2 & ! c1 c2:
   - t.t.s. 7 for ite(c1, TRUE, (~ c2))
   - t.t.s. 0 for ite(c1, c2, (~ c2))
 - State No. 8 with name || reject R & ! d1 d2 | & d1 ! d2 & ! d1 d2:
   - t.t.s. 8 for ite(d1, TRUE, (~ d2))
   - t.t.s. 0 for ite(d1, d2, (~ d2))
 - State No. 9 with name & G | | ! d1 d2 | ! c1 c2 & G | | ! d1 d2 | ! a1 a2 & G | | ! c1 c2 | ! d1 d2 & G | | ! c1 c2 | ! b1 b2 & G | | ! b1 b2 | ! c1 c2 & G | | ! b1 b2 | ! a1 a2 & G | | ! a1 a2 | ! d1 d2 & G | | ! a1 a2 | ! b1 b2 & G | | ! d1 d2 R & ! d1 d2 | & d1 ! d2 & ! d1 d2 & G | | ! c1 c2 R & ! c1 c2 | & c1 ! c2 & ! c1 c2 & G | | ! b1 b2 R & ! b1 b2 | & b1 ! b2 & ! b1 b2 & G | | ! a1 a2 R & ! a1 a2 | & a1 ! a2 & ! a1 a2 & G F & ! d1 d2 & G F & ! c1 c2 & G F & ! b1 b2 G F & ! a1 a2:
   - t.t.s. 0 for (~ ite(a1, ite(a2, ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), TRUE), ite(c1, c2, TRUE)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), TRUE)), ite(b1, ite(b2, ite(d1, d2, TRUE), FALSE), ite(d1, d2, TRUE))), ite(b1, ite(b2, ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), TRUE), ite(c1, c2, TRUE)), ite(c1, ite(c2, TRUE, ite(d1, d2, TRUE)), TRUE))))
   - t.t.s. 9 for TRUE
   - t.t.s. 8 for (~ ite(d1, d2, TRUE))
   - t.t.s. 7 for (~ ite(c1, c2, TRUE))
   - t.t.s. 6 for (~ ite(b1, b2, TRUE))
   - t.t.s. 5 for (~ ite(a1, a2, TRUE))
   - t.t.s. 4 for TRUE
   - t.t.s. 3 for TRUE
   - t.t.s. 2 for TRUE
   - t.t.s. 1 for TRUE

*/

/* Lookup-Table contents:
- LUT 0 has:
  -> Inputs d1 d2 uvwState4 uvwState8 uvwState9
  -> Outputs uvwState8incoming0 uvwState0incoming4 uvwState8incoming1 uvwState4incoming0 uvwState4Next uvwState8Next uvwState1incoming1 uvwState2incoming1 uvwState3incoming1 uvwState4incoming1 uvwState9incoming0 uvwState9Next
- LUT 1 has:
  -> Inputs a1 a2 uvwState1 uvwState5 uvwState9
  -> Outputs new_n53_ uvwState5incoming0 uvwState1incoming0 uvwState1Next uvwState5incoming1 uvwState5Next
- LUT 2 has:
  -> Inputs c1 c2 uvwState3 uvwState6 uvwState9
  -> Outputs new_n61_ new_n62_ uvwState3incoming0 uvwState3Next uvwState7incoming1
- LUT 3 has:
  -> Inputs b1 b2 uvwState2 uvwState6 uvwState9
  -> Outputs uvwState6incoming0 uvwState0incoming2 uvwState6incoming1 uvwState2incoming0 uvwState2Next uvwState6Next
- LUT 4 has:
  -> Inputs uvwState7 uvwState0incoming2 new_n61_ new_n62_ uvwState7incoming1
  -> Outputs uvwState7incoming0 uvwState0incoming3 new_n75_ uvwState7Next
- LUT 5 has:
  -> Inputs new_n53_ uvwState5incoming0 new_n61_ uvwState6incoming1 uvwState8incoming1
  -> Outputs uvwState0incoming1 uvwState0incoming5
- LUT 6 has:
  -> Inputs uvwState0 uvwState0incoming1 uvwState0incoming4 uvwState0incoming5 new_n75_
  -> Outputs uvwState0Next uvwState0incoming0
*/
