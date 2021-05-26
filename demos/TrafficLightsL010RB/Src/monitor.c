#include "UVWMonitor.h"
/* Declare variables for monitoring */
uint32_t currentState = 0;
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

void livenessMonitoring(uint32_t mask) {
  if (mask & 1) {
    if ((cnt1 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(1,cnt1, &buf.b1p0,1);
    }
  }
  if (mask & 2) {
    if ((cnt2 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(2,cnt2, &buf.b2p0,1);
    }
  }
  if (mask & 4) {
    if ((cnt3 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(3,cnt3, &buf.b3p0,1);
    }
  }
  if (mask & 8) {
    if ((cnt4 & FREQUENCY_MASK_STARVATION_LOGGING)==0) {
      logLivenessStarvation(4,cnt4, &buf.b4p0,1);
    }
  }
}


void monitorUpdate(uint32_t v) {
  switch (currentState) {
    case 0:
      /* UVW states: 9 */
      if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 2;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 5;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
      } else if (((v & 0x22) == 0x22) || ((v & 18) == 2) || ((v & 0x21) == 0x20) || ((v & 17) == 0)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v | 0x1fc) != 0x1fd)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (1) {
        currentState = 16;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      }
      break;
    case 1:
      /* UVW states: 1 2 3 4 9 */
      if (((v & 0xff) == 0xaa)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
      } else if (((v & 0xbf) == 0xaa) || ((v & 0x7f) == 0x2a)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(8);
      } else if (((v & 0x3f) == 0x2a)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(8);
      } else if (((v & 0xef) == 0xaa) || ((v & 0xdf) == 0x8a)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xcf) == 0x8a)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xaf) == 0xaa) || ((v & 0x6f) == 0x2a) || ((v & 0x9f) == 0x8a) || ((v & 0x5f) == 10)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(12);
      } else if (((v & 0x8f) == 0x8a) || ((v & 0x4f) == 10)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(12);
      } else if (((v & 0x2f) == 0x2a) || ((v & 31) == 10)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(12);
      } else if (((v & 15) == 10)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xfb) == 0xaa) || ((v & 0xf7) == 0xa2)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xf3) == 0xa2)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xbb) == 0xaa) || ((v & 0x7b) == 0x2a) || ((v & 0xb7) == 0xa2) || ((v & 0x77) == 0x22)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(10);
      } else if (((v & 0xb3) == 0xa2) || ((v & 0x73) == 0x22)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0x3b) == 0x2a) || ((v & 0x37) == 0x22)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0x33) == 0x22)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0xeb) == 0xaa) || ((v & 0xdb) == 0x8a) || ((v & 0xe7) == 0xa2) || ((v & 0xd7) == 0x82)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xe3) == 0xa2) || ((v & 0xd3) == 0x82)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xcb) == 0x8a) || ((v & 0xc7) == 0x82)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xc3) == 0x82)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v | 0x1fe) != 0x1ff) && ((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fd) != 0x1fd)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(14);
      } else if (((v & 0xa3) == 0xa2) || ((v & 0x63) == 0x22) || ((v & 0x93) == 0x82) || ((v & 0x53) == 2)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0x8b) == 0x8a) || ((v & 0x4b) == 10) || ((v & 0x87) == 0x82) || ((v & 0x47) == 2)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0x2b) == 0x2a) || ((v & 27) == 10) || ((v & 0x27) == 0x22) || ((v & 23) == 2)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0x23) == 0x22) || ((v & 19) == 2)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0x83) == 0x82) || ((v & 0x43) == 2)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 11) == 10) || ((v & 7) == 2)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 3) == 2)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xfe) == 0xaa) || ((v & 0xfd) == 0xa8)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xfc) == 0xa8)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xbe) == 0xaa) || ((v & 0x7e) == 0x2a) || ((v & 0xbd) == 0xa8) || ((v & 0x7d) == 0x28)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(9);
      } else if (((v & 0xbc) == 0xa8) || ((v & 0x7c) == 0x28)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(9);
      } else if (((v & 0x3e) == 0x2a) || ((v & 0x3d) == 0x28)) {
        currentState = 6;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(9);
      } else if (((v & 0x3c) == 0x28)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xee) == 0xaa) || ((v & 0xde) == 0x8a) || ((v & 0xed) == 0xa8) || ((v & 0xdd) == 0x88)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xec) == 0xa8) || ((v & 0xdc) == 0x88)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xce) == 0x8a) || ((v & 0xcd) == 0x88)) {
        currentState = 4;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xcc) == 0x88)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v | 0x1fb) != 0x1ff) && ((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f7) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(13);
      } else if (((v & 0xac) == 0xa8) || ((v & 0x6c) == 0x28) || ((v & 0x9c) == 0x88) || ((v & 0x5c) == 8)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x8e) == 0x8a) || ((v & 0x4e) == 10) || ((v & 0x8d) == 0x88) || ((v & 0x4d) == 8)) {
        currentState = 4;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x8c) == 0x88) || ((v & 0x4c) == 8)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x2e) == 0x2a) || ((v & 30) == 10) || ((v & 0x2d) == 0x28) || ((v & 29) == 8)) {
        currentState = 6;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x2c) == 0x28) || ((v & 28) == 8)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 14) == 10) || ((v & 13) == 8)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 12) == 8)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xfa) == 0xaa) || ((v & 0xf6) == 0xa2) || ((v & 0xf9) == 0xa8) || ((v & 0xf5) == 0xa0)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf8) == 0xa8) || ((v & 0xf4) == 0xa0)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf2) == 0xa2) || ((v & 0xf1) == 0xa0)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf0) == 0xa0)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v | 0x1ef) != 0x1ff) && ((v | 0x13f) != 0x17f) && ((v | 0x1df) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(11);
      } else if (((v & 0xb8) == 0xa8) || ((v & 0x78) == 0x28) || ((v & 0xb4) == 0xa0) || ((v & 0x74) == 0x20)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0xb2) == 0xa2) || ((v & 0x72) == 0x22) || ((v & 0xb1) == 0xa0) || ((v & 0x71) == 0x20)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0x3a) == 0x2a) || ((v & 0x36) == 0x22) || ((v & 0x39) == 0x28) || ((v & 0x35) == 0x20)) {
        currentState = 6;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0x32) == 0x22) || ((v & 0x31) == 0x20)) {
        currentState = 7;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0xb0) == 0xa0) || ((v & 0x70) == 0x20)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x38) == 0x28) || ((v & 0x34) == 0x20)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x30) == 0x20)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v | 0x1bf) != 0x1ff) && ((v | 0x17f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xe8) == 0xa8) || ((v & 0xd8) == 0x88) || ((v & 0xe4) == 0xa0) || ((v & 0xd4) == 0x80)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xe2) == 0xa2) || ((v & 0xd2) == 0x82) || ((v & 0xe1) == 0xa0) || ((v & 0xd1) == 0x80)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xca) == 0x8a) || ((v & 0xc6) == 0x82) || ((v & 0xc9) == 0x88) || ((v & 0xc5) == 0x80)) {
        currentState = 4;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xc8) == 0x88) || ((v & 0xc4) == 0x80)) {
        currentState = 5;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xe0) == 0xa0) || ((v & 0xd0) == 0x80)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xc2) == 0x82) || ((v & 0xc1) == 0x80)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xc0) == 0x80)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(15);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 4;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 5;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 6;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v & 0x22) == 0x22) || ((v & 18) == 2) || ((v & 0x21) == 0x20) || ((v & 17) == 0)) {
        currentState = 7;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v | 0x1fc) != 0x1fd)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (1) {
        currentState = 16;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      }
      break;
    case 2:
      /* UVW states: 1 2 3 4 5 9 */
      if (((v & 0xff) == 0xaa)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
      } else if (((v & 0xbf) == 0xaa) || ((v & 0x7f) == 0x2a)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(8);
      } else if (((v & 0x3f) == 0x2a)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(8);
      } else if (((v & 0xef) == 0xaa) || ((v & 0xdf) == 0x8a)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xcf) == 0x8a)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xaf) == 0xaa) || ((v & 0x6f) == 0x2a) || ((v & 0x9f) == 0x8a) || ((v & 0x5f) == 10)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(12);
      } else if (((v & 0x8f) == 0x8a) || ((v & 0x4f) == 10)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(12);
      } else if (((v & 0x2f) == 0x2a) || ((v & 31) == 10)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(12);
      } else if (((v & 15) == 10)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xfb) == 0xaa) || ((v & 0xf7) == 0xa2)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xf3) == 0xa2)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xbb) == 0xaa) || ((v & 0x7b) == 0x2a) || ((v & 0xb7) == 0xa2) || ((v & 0x77) == 0x22)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(10);
      } else if (((v & 0xb3) == 0xa2) || ((v & 0x73) == 0x22)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0x3b) == 0x2a) || ((v & 0x37) == 0x22)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0x33) == 0x22)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0xeb) == 0xaa) || ((v & 0xdb) == 0x8a) || ((v & 0xe7) == 0xa2) || ((v & 0xd7) == 0x82)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xe3) == 0xa2) || ((v & 0xd3) == 0x82)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xcb) == 0x8a) || ((v & 0xc7) == 0x82)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xc3) == 0x82)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v | 0x1fe) != 0x1ff) && ((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fd) != 0x1fd)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(14);
      } else if (((v & 0xa3) == 0xa2) || ((v & 0x63) == 0x22) || ((v & 0x93) == 0x82) || ((v & 0x53) == 2)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0x8b) == 0x8a) || ((v & 0x4b) == 10) || ((v & 0x87) == 0x82) || ((v & 0x47) == 2)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0x2b) == 0x2a) || ((v & 27) == 10) || ((v & 0x27) == 0x22) || ((v & 23) == 2)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0x23) == 0x22) || ((v & 19) == 2)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0x83) == 0x82) || ((v & 0x43) == 2)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 11) == 10) || ((v & 7) == 2)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 3) == 2)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xff) == 0xa9)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xfc) == 0xa8)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0xbf) == 0xa9) || ((v & 0x7f) == 0x29)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(9);
      } else if (((v & 0x3f) == 0x29)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xbc) == 0xa8) || ((v & 0x7c) == 0x28)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0x3c) == 0x28)) {
        currentState = 11;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xef) == 0xa9) || ((v & 0xdf) == 0x89)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xcf) == 0x89)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xec) == 0xa8) || ((v & 0xdc) == 0x88)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0xcc) == 0x88)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xaf) == 0xa9) || ((v & 0x6f) == 0x29) || ((v & 0x9f) == 0x89) || ((v & 0x5f) == 9)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(13);
      } else if (((v & 0x8f) == 0x89) || ((v & 0x4f) == 9)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x2f) == 0x29) || ((v & 31) == 9)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 15) == 9)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xac) == 0xa8) || ((v & 0x6c) == 0x28) || ((v & 0x9c) == 0x88) || ((v & 0x5c) == 8)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0x8c) == 0x88) || ((v & 0x4c) == 8)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0x2c) == 0x28) || ((v & 28) == 8)) {
        currentState = 11;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 12) == 8)) {
        currentState = 14;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xfb) == 0xa9) || ((v & 0xf7) == 0xa1)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf3) == 0xa1)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xf8) == 0xa8) || ((v & 0xf4) == 0xa0)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0xf0) == 0xa0)) {
        currentState = 8;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xbb) == 0xa9) || ((v & 0x7b) == 0x29) || ((v & 0xb7) == 0xa1) || ((v & 0x77) == 0x21)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(11);
      } else if (((v & 0xb3) == 0xa1) || ((v & 0x73) == 0x21)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x3b) == 0x29) || ((v & 0x37) == 0x21)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x33) == 0x21)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xb8) == 0xa8) || ((v & 0x78) == 0x28) || ((v & 0xb4) == 0xa0) || ((v & 0x74) == 0x20)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0xb0) == 0xa0) || ((v & 0x70) == 0x20)) {
        currentState = 8;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x38) == 0x28) || ((v & 0x34) == 0x20)) {
        currentState = 11;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x30) == 0x20)) {
        currentState = 12;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xeb) == 0xa9) || ((v & 0xdb) == 0x89) || ((v & 0xe7) == 0xa1) || ((v & 0xd7) == 0x81)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xcb) == 0x89) || ((v & 0xc7) == 0x81)) {
        currentState = 5;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xe3) == 0xa1) || ((v & 0xd3) == 0x81)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xc3) == 0x81)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0xe8) == 0xa8) || ((v & 0xd8) == 0x88) || ((v & 0xe4) == 0xa0) || ((v & 0xd4) == 0x80)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0xe0) == 0xa0) || ((v & 0xd0) == 0x80)) {
        currentState = 8;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xc8) == 0x88) || ((v & 0xc4) == 0x80)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xc0) == 0x80)) {
        currentState = 10;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x1fd) != 0x1ff) && ((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fe) != 0x1fe)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(15);
      } else if (((v & 0x8b) == 0x89) || ((v & 0x4b) == 9) || ((v & 0x87) == 0x81) || ((v & 0x47) == 1)) {
        currentState = 5;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v & 0xa3) == 0xa1) || ((v & 0x63) == 0x21) || ((v & 0x93) == 0x81) || ((v & 0x53) == 1)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x83) == 0x81) || ((v & 0x43) == 1)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0x2b) == 0x29) || ((v & 27) == 9) || ((v & 0x27) == 0x21) || ((v & 23) == 1)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x23) == 0x21) || ((v & 19) == 1)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 11) == 9) || ((v & 7) == 1)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 3) == 1)) {
        currentState = 16;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df)) {
        currentState = 8;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 11;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df)) {
        currentState = 12;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f)) {
        currentState = 10;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7)) {
        currentState = 14;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (1) {
        currentState = 16;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      }
      break;
    case 3:
      /* UVW states: 1 2 3 4 6 9 */
      if (((v & 0xff) == 0xaa)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
      } else if (((v & 0xbf) == 0xaa) || ((v & 0x7f) == 0x2a)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(8);
      } else if (((v & 0x3f) == 0x2a)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(8);
      } else if (((v & 0xef) == 0xaa) || ((v & 0xdf) == 0x8a)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xcf) == 0x8a)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xaf) == 0xaa) || ((v & 0x6f) == 0x2a) || ((v & 0x9f) == 0x8a) || ((v & 0x5f) == 10)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(12);
      } else if (((v & 0x8f) == 0x8a) || ((v & 0x4f) == 10)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(12);
      } else if (((v & 0x2f) == 0x2a) || ((v & 31) == 10)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(12);
      } else if (((v & 15) == 10)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xff) == 0xa6)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xf3) == 0xa2)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0xbf) == 0xa6) || ((v & 0x7f) == 0x26)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(10);
      } else if (((v & 0x3f) == 0x26)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0xb3) == 0xa2) || ((v & 0x73) == 0x22)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0x33) == 0x22)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0xef) == 0xa6) || ((v & 0xdf) == 0x86)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xcf) == 0x86)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xe3) == 0xa2) || ((v & 0xd3) == 0x82)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0xc3) == 0x82)) {
        currentState = 9;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xaf) == 0xa6) || ((v & 0x6f) == 0x26) || ((v & 0x9f) == 0x86) || ((v & 0x5f) == 6)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(14);
      } else if (((v & 0x2f) == 0x26) || ((v & 31) == 6)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0x8f) == 0x86) || ((v & 0x4f) == 6)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 15) == 6)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xa3) == 0xa2) || ((v & 0x63) == 0x22) || ((v & 0x93) == 0x82) || ((v & 0x53) == 2)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0x83) == 0x82) || ((v & 0x43) == 2)) {
        currentState = 9;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0x23) == 0x22) || ((v & 19) == 2)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 3) == 2)) {
        currentState = 15;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xfe) == 0xaa) || ((v & 0xfd) == 0xa8)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xfc) == 0xa8)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xbe) == 0xaa) || ((v & 0x7e) == 0x2a) || ((v & 0xbd) == 0xa8) || ((v & 0x7d) == 0x28)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(9);
      } else if (((v & 0xbc) == 0xa8) || ((v & 0x7c) == 0x28)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(9);
      } else if (((v & 0x3e) == 0x2a) || ((v & 0x3d) == 0x28)) {
        currentState = 6;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(9);
      } else if (((v & 0x3c) == 0x28)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xee) == 0xaa) || ((v & 0xde) == 0x8a) || ((v & 0xed) == 0xa8) || ((v & 0xdd) == 0x88)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xec) == 0xa8) || ((v & 0xdc) == 0x88)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xce) == 0x8a) || ((v & 0xcd) == 0x88)) {
        currentState = 4;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xcc) == 0x88)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v | 0x1fb) != 0x1ff) && ((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f7) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(13);
      } else if (((v & 0xac) == 0xa8) || ((v & 0x6c) == 0x28) || ((v & 0x9c) == 0x88) || ((v & 0x5c) == 8)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x8e) == 0x8a) || ((v & 0x4e) == 10) || ((v & 0x8d) == 0x88) || ((v & 0x4d) == 8)) {
        currentState = 4;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x8c) == 0x88) || ((v & 0x4c) == 8)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x2e) == 0x2a) || ((v & 30) == 10) || ((v & 0x2d) == 0x28) || ((v & 29) == 8)) {
        currentState = 6;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x2c) == 0x28) || ((v & 28) == 8)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 14) == 10) || ((v & 13) == 8)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 12) == 8)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xfe) == 0xa6) || ((v & 0xfd) == 0xa4)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xfc) == 0xa4)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xf2) == 0xa2) || ((v & 0xf1) == 0xa0)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0xf0) == 0xa0)) {
        currentState = 8;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xbe) == 0xa6) || ((v & 0x7e) == 0x26) || ((v & 0xbd) == 0xa4) || ((v & 0x7d) == 0x24)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(11);
      } else if (((v & 0x3e) == 0x26) || ((v & 0x3d) == 0x24)) {
        currentState = 7;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0xbc) == 0xa4) || ((v & 0x7c) == 0x24)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x3c) == 0x24)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xb2) == 0xa2) || ((v & 0x72) == 0x22) || ((v & 0xb1) == 0xa0) || ((v & 0x71) == 0x20)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0xb0) == 0xa0) || ((v & 0x70) == 0x20)) {
        currentState = 8;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x32) == 0x22) || ((v & 0x31) == 0x20)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0x30) == 0x20)) {
        currentState = 12;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xee) == 0xa6) || ((v & 0xde) == 0x86) || ((v & 0xed) == 0xa4) || ((v & 0xdd) == 0x84)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xec) == 0xa4) || ((v & 0xdc) == 0x84)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xce) == 0x86) || ((v & 0xcd) == 0x84)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xcc) == 0x84)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0xe2) == 0xa2) || ((v & 0xd2) == 0x82) || ((v & 0xe1) == 0xa0) || ((v & 0xd1) == 0x80)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0xe0) == 0xa0) || ((v & 0xd0) == 0x80)) {
        currentState = 8;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xc2) == 0x82) || ((v & 0xc1) == 0x80)) {
        currentState = 9;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xc0) == 0x80)) {
        currentState = 10;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x1f7) != 0x1ff) && ((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1fb) != 0x1fb) && ((v | 0x1fc) != 0x1fd)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(15);
      } else if (((v & 0x2e) == 0x26) || ((v & 30) == 6) || ((v & 0x2d) == 0x24) || ((v & 29) == 4)) {
        currentState = 7;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v & 0xac) == 0xa4) || ((v & 0x6c) == 0x24) || ((v & 0x9c) == 0x84) || ((v & 0x5c) == 4)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x8e) == 0x86) || ((v & 0x4e) == 6) || ((v & 0x8d) == 0x84) || ((v & 0x4d) == 4)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0x8c) == 0x84) || ((v & 0x4c) == 4)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0x2c) == 0x24) || ((v & 28) == 4)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 14) == 6) || ((v & 13) == 4)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 12) == 4)) {
        currentState = 16;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1cf) != 0x1df)) {
        currentState = 8;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 9;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f)) {
        currentState = 10;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df)) {
        currentState = 12;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v | 0x1fc) != 0x1fd)) {
        currentState = 15;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (1) {
        currentState = 16;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      }
      break;
    case 4:
      /* UVW states: 1 2 3 4 7 9 */
      if (((v & 0xff) == 0xaa)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
      } else if (((v & 0xbf) == 0xaa) || ((v & 0x7f) == 0x2a)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(8);
      } else if (((v & 0x3f) == 0x2a)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(8);
      } else if (((v & 0xff) == 0x9a)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xcf) == 0x8a)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 0xbf) == 0x9a) || ((v & 0x7f) == 26)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(12);
      } else if (((v & 0x3f) == 26)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0x8f) == 0x8a) || ((v & 0x4f) == 10)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 15) == 10)) {
        currentState = 13;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xfb) == 0xaa) || ((v & 0xf7) == 0xa2)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xf3) == 0xa2)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xbb) == 0xaa) || ((v & 0x7b) == 0x2a) || ((v & 0xb7) == 0xa2) || ((v & 0x77) == 0x22)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(10);
      } else if (((v & 0xb3) == 0xa2) || ((v & 0x73) == 0x22)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0x3b) == 0x2a) || ((v & 0x37) == 0x22)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0x33) == 0x22)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0xfb) == 0x9a) || ((v & 0xf7) == 0x92)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xf3) == 0x92)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xcb) == 0x8a) || ((v & 0xc7) == 0x82)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 0xc3) == 0x82)) {
        currentState = 9;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xbb) == 0x9a) || ((v & 0x7b) == 26) || ((v & 0xb7) == 0x92) || ((v & 0x77) == 18)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(14);
      } else if (((v & 0xb3) == 0x92) || ((v & 0x73) == 18)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0x3b) == 26) || ((v & 0x37) == 18)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0x33) == 18)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0x8b) == 0x8a) || ((v & 0x4b) == 10) || ((v & 0x87) == 0x82) || ((v & 0x47) == 2)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 0x83) == 0x82) || ((v & 0x43) == 2)) {
        currentState = 9;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 11) == 10) || ((v & 7) == 2)) {
        currentState = 13;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 3) == 2)) {
        currentState = 15;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xfe) == 0xaa) || ((v & 0xfd) == 0xa8)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xfc) == 0xa8)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xbe) == 0xaa) || ((v & 0x7e) == 0x2a) || ((v & 0xbd) == 0xa8) || ((v & 0x7d) == 0x28)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(9);
      } else if (((v & 0xbc) == 0xa8) || ((v & 0x7c) == 0x28)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(9);
      } else if (((v & 0x3e) == 0x2a) || ((v & 0x3d) == 0x28)) {
        currentState = 6;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(9);
      } else if (((v & 0x3c) == 0x28)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xfe) == 0x9a) || ((v & 0xfd) == 0x98)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xfc) == 0x98)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xce) == 0x8a) || ((v & 0xcd) == 0x88)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 0xcc) == 0x88)) {
        currentState = 18;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xbe) == 0x9a) || ((v & 0x7e) == 26) || ((v & 0xbd) == 0x98) || ((v & 0x7d) == 24)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(13);
      } else if (((v & 0xbc) == 0x98) || ((v & 0x7c) == 24)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(13);
      } else if (((v & 0x3e) == 26) || ((v & 0x3d) == 24)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0x3c) == 24)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0x8e) == 0x8a) || ((v & 0x4e) == 10) || ((v & 0x8d) == 0x88) || ((v & 0x4d) == 8)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 0x8c) == 0x88) || ((v & 0x4c) == 8)) {
        currentState = 18;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 14) == 10) || ((v & 13) == 8)) {
        currentState = 13;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 12) == 8)) {
        currentState = 14;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xfa) == 0xaa) || ((v & 0xf6) == 0xa2) || ((v & 0xf9) == 0xa8) || ((v & 0xf5) == 0xa0)) {
        currentState = 1;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf8) == 0xa8) || ((v & 0xf4) == 0xa0)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf2) == 0xa2) || ((v & 0xf1) == 0xa0)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf0) == 0xa0)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v | 0x1ef) != 0x1ff) && ((v | 0x13f) != 0x17f) && ((v | 0x1df) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 1;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(11);
      } else if (((v & 0xb8) == 0xa8) || ((v & 0x78) == 0x28) || ((v & 0xb4) == 0xa0) || ((v & 0x74) == 0x20)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0xb2) == 0xa2) || ((v & 0x72) == 0x22) || ((v & 0xb1) == 0xa0) || ((v & 0x71) == 0x20)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0x3a) == 0x2a) || ((v & 0x36) == 0x22) || ((v & 0x39) == 0x28) || ((v & 0x35) == 0x20)) {
        currentState = 6;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0x32) == 0x22) || ((v & 0x31) == 0x20)) {
        currentState = 7;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0xb0) == 0xa0) || ((v & 0x70) == 0x20)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x38) == 0x28) || ((v & 0x34) == 0x20)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x30) == 0x20)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xfa) == 0x9a) || ((v & 0xf6) == 0x92) || ((v & 0xf9) == 0x98) || ((v & 0xf5) == 0x90)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xf8) == 0x98) || ((v & 0xf4) == 0x90)) {
        currentState = 5;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xf2) == 0x92) || ((v & 0xf1) == 0x90)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xf0) == 0x90)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0xca) == 0x8a) || ((v & 0xc6) == 0x82) || ((v & 0xc9) == 0x88) || ((v & 0xc5) == 0x80)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 0xc8) == 0x88) || ((v & 0xc4) == 0x80)) {
        currentState = 18;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xc2) == 0x82) || ((v & 0xc1) == 0x80)) {
        currentState = 9;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xc0) == 0x80)) {
        currentState = 10;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x1df) != 0x1ff) && ((v | 0x13f) != 0x17f) && ((v | 0x1ef) != 0x1ef) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(15);
      } else if (((v & 0xb8) == 0x98) || ((v & 0x78) == 24) || ((v & 0xb4) == 0x90) || ((v & 0x74) == 16)) {
        currentState = 5;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v & 0xb2) == 0x92) || ((v & 0x72) == 18) || ((v & 0xb1) == 0x90) || ((v & 0x71) == 16)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xb0) == 0x90) || ((v & 0x70) == 16)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0x3a) == 26) || ((v & 0x36) == 18) || ((v & 0x39) == 24) || ((v & 0x35) == 16)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0x38) == 24) || ((v & 0x34) == 16)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0x32) == 18) || ((v & 0x31) == 16)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0x30) == 16)) {
        currentState = 16;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 18;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 9;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 13;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 2) == 2) || ((v & 1) == 0)) {
        currentState = 15;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f)) {
        currentState = 10;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7)) {
        currentState = 14;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (1) {
        currentState = 16;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      }
      break;
    case 5:
      /* UVW states: 1 2 3 4 5 7 9 */
      if (((v & 0xff) == 0xaa)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
      } else if (((v & 0xbf) == 0xaa) || ((v & 0x7f) == 0x2a)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(8);
      } else if (((v & 0x3f) == 0x2a)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(8);
      } else if (((v & 0xff) == 0x9a)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xcf) == 0x8a)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 0xbf) == 0x9a) || ((v & 0x7f) == 26)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(12);
      } else if (((v & 0x3f) == 26)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0x8f) == 0x8a) || ((v & 0x4f) == 10)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 15) == 10)) {
        currentState = 13;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xfb) == 0xaa) || ((v & 0xf7) == 0xa2)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xf3) == 0xa2)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xbb) == 0xaa) || ((v & 0x7b) == 0x2a) || ((v & 0xb7) == 0xa2) || ((v & 0x77) == 0x22)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(10);
      } else if (((v & 0xb3) == 0xa2) || ((v & 0x73) == 0x22)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0x3b) == 0x2a) || ((v & 0x37) == 0x22)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0x33) == 0x22)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0xfb) == 0x9a) || ((v & 0xf7) == 0x92)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xf3) == 0x92)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xcb) == 0x8a) || ((v & 0xc7) == 0x82)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 0xc3) == 0x82)) {
        currentState = 9;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xbb) == 0x9a) || ((v & 0x7b) == 26) || ((v & 0xb7) == 0x92) || ((v & 0x77) == 18)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(14);
      } else if (((v & 0xb3) == 0x92) || ((v & 0x73) == 18)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0x3b) == 26) || ((v & 0x37) == 18)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0x33) == 18)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0x8b) == 0x8a) || ((v & 0x4b) == 10) || ((v & 0x87) == 0x82) || ((v & 0x47) == 2)) {
        currentState = 21;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(21,&(buf.b0p0),4);
      } else if (((v & 0x83) == 0x82) || ((v & 0x43) == 2)) {
        currentState = 9;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 11) == 10) || ((v & 7) == 2)) {
        currentState = 13;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 3) == 2)) {
        currentState = 15;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xff) == 0xa9)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xfc) == 0xa8)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0xbf) == 0xa9) || ((v & 0x7f) == 0x29)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(9);
      } else if (((v & 0x3f) == 0x29)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xbc) == 0xa8) || ((v & 0x7c) == 0x28)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0x3c) == 0x28)) {
        currentState = 11;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xff) == 0x99)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xcf) == 0x89)) {
        currentState = 18;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xfc) == 0x98)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xcc) == 0x88)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xbf) == 0x99) || ((v & 0x7f) == 25)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(13);
      } else if (((v & 0x3f) == 25)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0x8f) == 0x89) || ((v & 0x4f) == 9)) {
        currentState = 18;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 15) == 9)) {
        currentState = 14;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xbc) == 0x98) || ((v & 0x7c) == 24)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0x3c) == 24)) {
        currentState = 14;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0x8c) == 0x88) || ((v & 0x4c) == 8)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 12) == 8)) {
        currentState = 14;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xfb) == 0xa9) || ((v & 0xf7) == 0xa1)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf3) == 0xa1)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xf8) == 0xa8) || ((v & 0xf4) == 0xa0)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0xf0) == 0xa0)) {
        currentState = 8;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xbb) == 0xa9) || ((v & 0x7b) == 0x29) || ((v & 0xb7) == 0xa1) || ((v & 0x77) == 0x21)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(11);
      } else if (((v & 0xb3) == 0xa1) || ((v & 0x73) == 0x21)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x3b) == 0x29) || ((v & 0x37) == 0x21)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x33) == 0x21)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xb8) == 0xa8) || ((v & 0x78) == 0x28) || ((v & 0xb4) == 0xa0) || ((v & 0x74) == 0x20)) {
        currentState = 17;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(17,&(buf.b0p0),4);
      } else if (((v & 0xb0) == 0xa0) || ((v & 0x70) == 0x20)) {
        currentState = 8;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0x38) == 0x28) || ((v & 0x34) == 0x20)) {
        currentState = 11;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x30) == 0x20)) {
        currentState = 12;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xfb) == 0x99) || ((v & 0xf7) == 0x91)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xf3) == 0x91)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0xcb) == 0x89) || ((v & 0xc7) == 0x81)) {
        currentState = 18;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xc3) == 0x81)) {
        currentState = 10;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0xf8) == 0x98) || ((v & 0xf4) == 0x90)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xf0) == 0x90)) {
        currentState = 10;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0xc8) == 0x88) || ((v & 0xc4) == 0x80)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xc0) == 0x80)) {
        currentState = 10;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0xbb) == 0x99) || ((v & 0x7b) == 25) || ((v & 0xb7) == 0x91) || ((v & 0x77) == 17)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(15);
      } else if (((v & 0xb3) == 0x91) || ((v & 0x73) == 17)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0x3b) == 25) || ((v & 0x37) == 17)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0x33) == 17)) {
        currentState = 16;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v & 0x8b) == 0x89) || ((v & 0x4b) == 9) || ((v & 0x87) == 0x81) || ((v & 0x47) == 1)) {
        currentState = 18;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0x83) == 0x81) || ((v & 0x43) == 1)) {
        currentState = 10;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 11) == 9) || ((v & 7) == 1)) {
        currentState = 14;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 3) == 1)) {
        currentState = 16;
        buf.b0p0 = buf.b7p0 | (v << 9) | (2 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v & 0xb8) == 0x98) || ((v & 0x78) == 24) || ((v & 0xb4) == 0x90) || ((v & 0x74) == 16)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v & 0xb0) == 0x90) || ((v & 0x70) == 16)) {
        currentState = 10;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0x38) == 24) || ((v & 0x34) == 16)) {
        currentState = 14;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0x30) == 16)) {
        currentState = 16;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 18;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(18,&(buf.b0p0),4);
      } else if (((v | 0x13f) != 0x17f)) {
        currentState = 10;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7)) {
        currentState = 14;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (1) {
        currentState = 16;
        buf.b0p0 = buf.b5p0 | (v << 9) | (0 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        buf.b8p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      }
      break;
    case 6:
      /* UVW states: 1 2 3 4 8 9 */
      if (((v & 0xff) == 0xaa)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
      } else if (((v & 0xff) == 0x6a)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(8);
      } else if (((v & 0x3f) == 0x2a)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 0xef) == 0xaa) || ((v & 0xdf) == 0x8a)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xcf) == 0x8a)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xef) == 0x6a) || ((v & 0xdf) == 0x4a)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(12);
      } else if (((v & 0xcf) == 0x4a)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0x2f) == 0x2a) || ((v & 31) == 10)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 15) == 10)) {
        currentState = 13;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xfb) == 0xaa) || ((v & 0xf7) == 0xa2)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xf3) == 0xa2)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xfb) == 0x6a) || ((v & 0xf7) == 0x62)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(10);
      } else if (((v & 0xf3) == 0x62)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(10);
      } else if (((v & 0x3b) == 0x2a) || ((v & 0x37) == 0x22)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 0x33) == 0x22)) {
        currentState = 20;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0xeb) == 0xaa) || ((v & 0xdb) == 0x8a) || ((v & 0xe7) == 0xa2) || ((v & 0xd7) == 0x82)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xe3) == 0xa2) || ((v & 0xd3) == 0x82)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xcb) == 0x8a) || ((v & 0xc7) == 0x82)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xc3) == 0x82)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xeb) == 0x6a) || ((v & 0xdb) == 0x4a) || ((v & 0xe7) == 0x62) || ((v & 0xd7) == 0x42)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(14);
      } else if (((v & 0xe3) == 0x62) || ((v & 0xd3) == 0x42)) {
        currentState = 7;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(14);
      } else if (((v & 0xcb) == 0x4a) || ((v & 0xc7) == 0x42)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xc3) == 0x42)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0x2b) == 0x2a) || ((v & 27) == 10) || ((v & 0x27) == 0x22) || ((v & 23) == 2)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 0x23) == 0x22) || ((v & 19) == 2)) {
        currentState = 20;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 11) == 10) || ((v & 7) == 2)) {
        currentState = 13;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 3) == 2)) {
        currentState = 15;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xfe) == 0xaa) || ((v & 0xfd) == 0xa8)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xfc) == 0xa8)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xfe) == 0x6a) || ((v & 0xfd) == 0x68)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(9);
      } else if (((v & 0xfc) == 0x68)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x3e) == 0x2a) || ((v & 0x3d) == 0x28)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 0x3c) == 0x28)) {
        currentState = 11;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xee) == 0xaa) || ((v & 0xde) == 0x8a) || ((v & 0xed) == 0xa8) || ((v & 0xdd) == 0x88)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xec) == 0xa8) || ((v & 0xdc) == 0x88)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xce) == 0x8a) || ((v & 0xcd) == 0x88)) {
        currentState = 4;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xcc) == 0x88)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xee) == 0x6a) || ((v & 0xde) == 0x4a) || ((v & 0xed) == 0x68) || ((v & 0xdd) == 0x48)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(13);
      } else if (((v & 0xec) == 0x68) || ((v & 0xdc) == 0x48)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xce) == 0x4a) || ((v & 0xcd) == 0x48)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xcc) == 0x48)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0x2e) == 0x2a) || ((v & 30) == 10) || ((v & 0x2d) == 0x28) || ((v & 29) == 8)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 0x2c) == 0x28) || ((v & 28) == 8)) {
        currentState = 11;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 14) == 10) || ((v & 13) == 8)) {
        currentState = 13;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 12) == 8)) {
        currentState = 14;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xfa) == 0xaa) || ((v & 0xf6) == 0xa2) || ((v & 0xf9) == 0xa8) || ((v & 0xf5) == 0xa0)) {
        currentState = 1;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf8) == 0xa8) || ((v & 0xf4) == 0xa0)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf2) == 0xa2) || ((v & 0xf1) == 0xa0)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xf0) == 0xa0)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xfa) == 0x6a) || ((v & 0xf6) == 0x62) || ((v & 0xf9) == 0x68) || ((v & 0xf5) == 0x60)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(11);
      } else if (((v & 0xf2) == 0x62) || ((v & 0xf1) == 0x60)) {
        currentState = 7;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(11);
      } else if (((v & 0xf8) == 0x68) || ((v & 0xf4) == 0x60)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xf0) == 0x60)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0x3a) == 0x2a) || ((v & 0x36) == 0x22) || ((v & 0x39) == 0x28) || ((v & 0x35) == 0x20)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 0x38) == 0x28) || ((v & 0x34) == 0x20)) {
        currentState = 11;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x32) == 0x22) || ((v & 0x31) == 0x20)) {
        currentState = 20;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0x30) == 0x20)) {
        currentState = 12;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v | 0x1bf) != 0x1ff) && ((v | 0x17f) != 0x17f) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 1;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xe8) == 0xa8) || ((v & 0xd8) == 0x88) || ((v & 0xe4) == 0xa0) || ((v & 0xd4) == 0x80)) {
        currentState = 2;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xe2) == 0xa2) || ((v & 0xd2) == 0x82) || ((v & 0xe1) == 0xa0) || ((v & 0xd1) == 0x80)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xca) == 0x8a) || ((v & 0xc6) == 0x82) || ((v & 0xc9) == 0x88) || ((v & 0xc5) == 0x80)) {
        currentState = 4;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xc8) == 0x88) || ((v & 0xc4) == 0x80)) {
        currentState = 5;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xe0) == 0xa0) || ((v & 0xd0) == 0x80)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xc2) == 0x82) || ((v & 0xc1) == 0x80)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xc0) == 0x80)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v | 0x17f) != 0x1ff) && ((v | 0x1bf) != 0x1bf) && ((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(15);
      } else if (((v & 0xe2) == 0x62) || ((v & 0xd2) == 0x42) || ((v & 0xe1) == 0x60) || ((v & 0xd1) == 0x40)) {
        currentState = 7;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b6p0 = b9p0 | (v << 0);
        livenessMonitoring(15);
      } else if (((v & 0xe8) == 0x68) || ((v & 0xd8) == 0x48) || ((v & 0xe4) == 0x60) || ((v & 0xd4) == 0x40)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xe0) == 0x60) || ((v & 0xd0) == 0x40)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xca) == 0x4a) || ((v & 0xc6) == 0x42) || ((v & 0xc9) == 0x48) || ((v & 0xc5) == 0x40)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xc8) == 0x48) || ((v & 0xc4) == 0x40)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xc2) == 0x42) || ((v & 0xc1) == 0x40)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xc0) == 0x40)) {
        currentState = 16;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1f3) != 0x1f7)) {
        currentState = 11;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 20;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 13;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v | 0x1f3) != 0x1f7)) {
        currentState = 14;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df)) {
        currentState = 12;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v | 0x1fc) != 0x1fd)) {
        currentState = 15;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (1) {
        currentState = 16;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b6p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      }
      break;
    case 7:
      /* UVW states: 1 2 3 4 6 8 9 */
      if (((v & 0xff) == 0xaa)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
      } else if (((v & 0xff) == 0x6a)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(8);
      } else if (((v & 0x3f) == 0x2a)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 0xef) == 0xaa) || ((v & 0xdf) == 0x8a)) {
        currentState = 1;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xcf) == 0x8a)) {
        currentState = 4;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(4);
      } else if (((v & 0xef) == 0x6a) || ((v & 0xdf) == 0x4a)) {
        currentState = 6;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(12);
      } else if (((v & 0xcf) == 0x4a)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0x2f) == 0x2a) || ((v & 31) == 10)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 15) == 10)) {
        currentState = 13;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xff) == 0xa6)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(2);
      } else if (((v & 0xf3) == 0xa2)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0xff) == 0x66)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(10);
      } else if (((v & 0x3f) == 0x26)) {
        currentState = 20;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0xf3) == 0x62)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0x33) == 0x22)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0xef) == 0xa6) || ((v & 0xdf) == 0x86)) {
        currentState = 3;
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(6);
      } else if (((v & 0xcf) == 0x86)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xe3) == 0xa2) || ((v & 0xd3) == 0x82)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0xc3) == 0x82)) {
        currentState = 9;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xef) == 0x66) || ((v & 0xdf) == 0x46)) {
        /* Stay in the same DFA state */
        cnt1 = 0;
        buf.b1p0 = b9p0 | (v << 0);
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(14);
      } else if (((v & 0xcf) == 0x46)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0x2f) == 0x26) || ((v & 31) == 6)) {
        currentState = 20;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 15) == 6)) {
        currentState = 15;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xe3) == 0x62) || ((v & 0xd3) == 0x42)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0xc3) == 0x42)) {
        currentState = 15;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0x23) == 0x22) || ((v & 19) == 2)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 3) == 2)) {
        currentState = 15;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xfe) == 0xaa) || ((v & 0xfd) == 0xa8)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xfc) == 0xa8)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(1);
      } else if (((v & 0xfe) == 0x6a) || ((v & 0xfd) == 0x68)) {
        currentState = 6;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(9);
      } else if (((v & 0xfc) == 0x68)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0x3e) == 0x2a) || ((v & 0x3d) == 0x28)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 0x3c) == 0x28)) {
        currentState = 11;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xee) == 0xaa) || ((v & 0xde) == 0x8a) || ((v & 0xed) == 0xa8) || ((v & 0xdd) == 0x88)) {
        currentState = 1;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xec) == 0xa8) || ((v & 0xdc) == 0x88)) {
        currentState = 2;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xce) == 0x8a) || ((v & 0xcd) == 0x88)) {
        currentState = 4;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xcc) == 0x88)) {
        currentState = 5;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        livenessMonitoring(5);
      } else if (((v & 0xee) == 0x6a) || ((v & 0xde) == 0x4a) || ((v & 0xed) == 0x68) || ((v & 0xdd) == 0x48)) {
        currentState = 6;
        cnt1++;
        cnt2 = 0;
        buf.b2p0 = b9p0 | (v << 0);
        cnt3++;
        cnt4++;
        livenessMonitoring(13);
      } else if (((v & 0xec) == 0x68) || ((v & 0xdc) == 0x48)) {
        currentState = 11;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 0xce) == 0x4a) || ((v & 0xcd) == 0x48)) {
        currentState = 13;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 0xcc) == 0x48)) {
        currentState = 14;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0x2e) == 0x2a) || ((v & 30) == 10) || ((v & 0x2d) == 0x28) || ((v & 29) == 8)) {
        currentState = 22;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(22,&(buf.b0p0),4);
      } else if (((v & 0x2c) == 0x28) || ((v & 28) == 8)) {
        currentState = 11;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(11,&(buf.b0p0),4);
      } else if (((v & 14) == 10) || ((v & 13) == 8)) {
        currentState = 13;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(13,&(buf.b0p0),4);
      } else if (((v & 12) == 8)) {
        currentState = 14;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(14,&(buf.b0p0),4);
      } else if (((v & 0xfe) == 0xa6) || ((v & 0xfd) == 0xa4)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(3);
      } else if (((v & 0xfc) == 0xa4)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xf2) == 0xa2) || ((v & 0xf1) == 0xa0)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0xf0) == 0xa0)) {
        currentState = 8;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xfe) == 0x66) || ((v & 0xfd) == 0x64)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3 = 0;
        buf.b3p0 = b9p0 | (v << 0);
        cnt4++;
        livenessMonitoring(11);
      } else if (((v & 0xfc) == 0x64)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0x3e) == 0x26) || ((v & 0x3d) == 0x24)) {
        currentState = 20;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0x3c) == 0x24)) {
        currentState = 12;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xf2) == 0x62) || ((v & 0xf1) == 0x60)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0xf0) == 0x60)) {
        currentState = 12;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0x32) == 0x22) || ((v & 0x31) == 0x20)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0x30) == 0x20)) {
        currentState = 12;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xee) == 0xa6) || ((v & 0xde) == 0x86) || ((v & 0xed) == 0xa4) || ((v & 0xdd) == 0x84)) {
        currentState = 3;
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4 = 0;
        buf.b4p0 = b9p0 | (v << 0);
        livenessMonitoring(7);
      } else if (((v & 0xec) == 0xa4) || ((v & 0xdc) == 0x84)) {
        currentState = 8;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xce) == 0x86) || ((v & 0xcd) == 0x84)) {
        currentState = 9;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xcc) == 0x84)) {
        currentState = 10;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0xe2) == 0xa2) || ((v & 0xd2) == 0x82) || ((v & 0xe1) == 0xa0) || ((v & 0xd1) == 0x80)) {
        currentState = 19;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(19,&(buf.b0p0),4);
      } else if (((v & 0xe0) == 0xa0) || ((v & 0xd0) == 0x80)) {
        currentState = 8;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(8,&(buf.b0p0),4);
      } else if (((v & 0xc2) == 0x82) || ((v & 0xc1) == 0x80)) {
        currentState = 9;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(9,&(buf.b0p0),4);
      } else if (((v & 0xc0) == 0x80)) {
        currentState = 10;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(10,&(buf.b0p0),4);
      } else if (((v & 0xee) == 0x66) || ((v & 0xde) == 0x46) || ((v & 0xed) == 0x64) || ((v & 0xdd) == 0x44)) {
        /* Stay in the same DFA state */
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        livenessMonitoring(15);
      } else if (((v & 0xec) == 0x64) || ((v & 0xdc) == 0x44)) {
        currentState = 12;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xce) == 0x46) || ((v & 0xcd) == 0x44)) {
        currentState = 15;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xcc) == 0x44)) {
        currentState = 16;
        buf.b0p0 = b9p0 | (v << 9) | (4 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v & 0x2e) == 0x26) || ((v & 30) == 6) || ((v & 0x2d) == 0x24) || ((v & 29) == 4)) {
        currentState = 20;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0x2c) == 0x24) || ((v & 28) == 4)) {
        currentState = 12;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 14) == 6) || ((v & 13) == 4)) {
        currentState = 15;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 12) == 4)) {
        currentState = 16;
        buf.b0p0 = buf.b8p0 | (v << 9) | (3 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v & 0xe2) == 0x62) || ((v & 0xd2) == 0x42) || ((v & 0xe1) == 0x60) || ((v & 0xd1) == 0x40)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v & 0xe0) == 0x60) || ((v & 0xd0) == 0x40)) {
        currentState = 12;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v & 0xc2) == 0x42) || ((v & 0xc1) == 0x40)) {
        currentState = 15;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (((v & 0xc0) == 0x40)) {
        currentState = 16;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df) && ((v | 0x1fc) != 0x1fd)) {
        currentState = 20;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(20,&(buf.b0p0),4);
      } else if (((v | 0x1cf) != 0x1df)) {
        currentState = 12;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(12,&(buf.b0p0),4);
      } else if (((v | 0x1fc) != 0x1fd)) {
        currentState = 15;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        logViolationExplanation(15,&(buf.b0p0),4);
      } else if (1) {
        currentState = 16;
        buf.b0p0 = buf.b6p0 | (v << 9) | (1 << 18);
        cnt1++;
        cnt2++;
        cnt3++;
        cnt4++;
        buf.b5p0 = b9p0 | (v << 0);
        buf.b7p0 = b9p0 | (v << 0);
        logViolationExplanation(16,&(buf.b0p0),4);
      }
      break;
    default:
      /* DFA State 8 has UVW states: 0 1 2 3 4 5 6 9 */
      /* DFA State 9 has UVW states: 0 1 2 3 4 6 7 9 */
      /* DFA State 10 has UVW states: 0 1 2 3 4 5 6 7 9 */
      /* DFA State 11 has UVW states: 0 1 2 3 4 5 8 9 */
      /* DFA State 12 has UVW states: 0 1 2 3 4 5 6 8 9 */
      /* DFA State 13 has UVW states: 0 1 2 3 4 7 8 9 */
      /* DFA State 14 has UVW states: 0 1 2 3 4 5 7 8 9 */
      /* DFA State 15 has UVW states: 0 1 2 3 4 6 7 8 9 */
      /* DFA State 16 has UVW states: 0 1 2 3 4 5 6 7 8 9 */
      /* DFA State 17 has UVW states: 0 1 2 3 4 5 9 */
      /* DFA State 18 has UVW states: 0 1 2 3 4 5 7 9 */
      /* DFA State 19 has UVW states: 0 1 2 3 4 6 9 */
      /* DFA State 20 has UVW states: 0 1 2 3 4 6 8 9 */
      /* DFA State 21 has UVW states: 0 1 2 3 4 7 9 */
      /* DFA State 22 has UVW states: 0 1 2 3 4 8 9 */
      /* DFA State 23 has UVW states: 0 1 2 3 4 9 */
      break;
  }
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
