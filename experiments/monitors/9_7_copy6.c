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

const uint16_t lut0[128] = {0xc34c,0xc30d,0xcb0c,0xc30c,0xc34e,0xc307,0xcb0e,0xc30e,
    0xd34c,0xd30d,0xdb04,0xd30c,0xc34c,0xc30d,0xcb0c,0xc30c,
    0xc3cc,0xc38d,0xcb8c,0xc38c,0xc3ce,0xc387,0xcb8e,0xc38e,
    0xd3cc,0xd38d,0xdb84,0xd38c,0xc3cc,0xc38d,0xcb8c,0xc38c,
    0xe048,0xe009,0xe800,0xe008,0xe04a,0xe003,0xe802,0xe00a,
    0xf048,0xf009,0xf800,0xf008,0xe048,0xe009,0xe800,0xe008,
    0xe048,0xe009,0xe800,0xe008,0xe04a,0xe003,0xe802,0xe00a,
    0xf048,0xf009,0xf800,0xf008,0xe048,0xe009,0xe800,0xe008,
    0xc048,0xc001,0xc808,0xc008,0xc04a,0xc003,0xc80a,0xc00a,
    0xd048,0xd001,0xd800,0xd008,0xc048,0xc001,0xc808,0xc008,
    0xc6c8,0xc681,0xce88,0xc688,0xc6ca,0xc683,0xce8a,0xc68a,
    0xd6c8,0xd681,0xde80,0xd688,0xc6c8,0xc681,0xce88,0xc688,
    0xc04c,0xc00d,0xc80c,0xc00c,0xc04e,0xc007,0xc80e,0xc00e,
    0xd04c,0xd00d,0xd804,0xd00c,0xc04c,0xc00d,0xc80c,0xc00c,
    0xc6ec,0xc6ad,0xceac,0xc6ac,0xc6ee,0xc6a7,0xceae,0xc6ae,
    0xd6ec,0xd6ad,0xdea4,0xd6ac,0xc6ec,0xc6ad,0xceac,0xc6ac};
const uint8_t lut1[128] = {0xa,0xa,0xa,0xa,0x1a,0x1a,0x1a,0x1a,
    0xe,0xe,0xe,0xe,0x1e,0x1e,0x1e,0x1e,
    0x1,0x1,0x1,0x1,0x11,0x11,0x11,0x11,
    0x5,0x5,0x1,0x1,0x15,0x15,0x11,0x11,
    0x20,0x20,0x20,0x20,0x30,0x30,0x30,0x30,
    0x24,0x20,0x24,0x20,0x34,0x30,0x34,0x30,
    0x2,0x2,0x2,0x2,0x12,0x12,0x12,0x12,
    0x6,0x6,0x6,0x6,0x16,0x16,0x16,0x16,
    0xa,0xa,0xa,0xa,0xa,0xa,0xa,0xa,
    0xe,0xe,0xe,0xe,0xe,0xe,0xe,0xe,
    0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,
    0x5,0x5,0x1,0x1,0x5,0x5,0x1,0x1,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6};
const uint16_t lut2[128] = {0x2,0x2,0x2,0x2,0x484,0x484,0x484,0x484,
    0x1802,0x2,0x1802,0x2,0x1c84,0x484,0x1c84,0x484,
    0x6002,0x6002,0x6002,0x6002,0x6484,0x6484,0x6484,0x6484,
    0x7802,0x6002,0x7802,0x6002,0x7c84,0x6484,0x7c84,0x6484,
    0x2,0x2,0x1,0x1,0x482,0x484,0x481,0x485,
    0x1808,0x502,0x1809,0x501,0x1c88,0x584,0x1c89,0x585,
    0x6010,0x6602,0x6011,0x6601,0x6490,0x6684,0x6491,0x6685,
    0x7818,0x6702,0x7819,0x6701,0x7c98,0x6784,0x7c99,0x6785,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x1802,0x2,0x1802,0x2,0x1802,0x2,0x1802,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x1802,0x2,0x1802,0x2,0x1802,0x2,0x1802,0x2,
    0x62,0x2,0x62,0x2,0x62,0x2,0x62,0x2,
    0x1868,0x2,0x1868,0x2,0x1868,0x2,0x1868,0x2,
    0x62,0x2,0x62,0x2,0x62,0x2,0x62,0x2,
    0x1868,0x2,0x1868,0x2,0x1868,0x2,0x1868,0x2};
const uint16_t lut3[128] = {0x8,0x8,0x8,0x8,0x0,0x0,0x1,0x1,
    0x8,0x8,0x8,0x8,0x0,0x0,0x1,0x1,
    0x28,0x28,0x28,0x28,0x20,0x20,0x21,0x21,
    0x1ac,0x1ac,0x1ac,0x1ac,0x1a4,0x1a4,0x1a4,0x1a4,
    0x8,0x8,0x8,0x8,0x0,0x0,0x1,0x1,
    0x8,0x8,0x8,0x8,0x0,0x0,0x1,0x1,
    0x38,0x38,0x38,0x38,0x30,0x30,0x31,0x31,
    0x1bc,0x1bc,0x1bc,0x1bc,0x1b4,0x1b4,0x1b4,0x1b4,
    0x8,0x8,0x8,0x8,0x0,0x8,0x1,0x8,
    0x18c,0x18c,0x18c,0x18c,0x184,0x18c,0x184,0x18c,
    0x8,0x8,0x8,0x8,0x0,0x0,0x1,0x1,
    0x188,0x188,0x188,0x188,0x180,0x180,0x181,0x181,
    0x17a,0x17a,0x17a,0x17a,0x172,0x17a,0x172,0x17a,
    0x1fe,0x1fe,0x1fe,0x1fe,0x1f6,0x1fe,0x1f6,0x1fe,
    0x178,0x178,0x178,0x178,0x170,0x170,0x171,0x171,
    0x1f8,0x1f8,0x1f8,0x1f8,0x1f0,0x1f0,0x1f1,0x1f1};
const uint16_t lut4[128] = {0x20,0x21,0x20,0x21,0x30,0x31,0x30,0x31,
    0x1a0,0x1a1,0x1a0,0x1a1,0x1b0,0x1b1,0x1b0,0x1b1,
    0x0,0x1,0x3008,0x3008,0x170,0x171,0x3178,0x3178,
    0x180,0x181,0x3188,0x3188,0x1f0,0x1f1,0x31f8,0x31f8,
    0x400,0x401,0x3408,0x3408,0x400,0x401,0x3408,0x3408,
    0x400,0x401,0x3408,0x3408,0x400,0x401,0x3408,0x3408,
    0x0,0x1,0x3000,0x3001,0x174,0x175,0x3174,0x3175,
    0x180,0x181,0x3180,0x3181,0x1f4,0x1f5,0x31f4,0x31f5,
    0x20,0x21,0x20,0x21,0x30,0x31,0x30,0x31,
    0x1a0,0x1a1,0x1a0,0x1a1,0x1b0,0x1b1,0x1b0,0x1b1,
    0x2e02,0x2e02,0x3e0a,0x3e0a,0x2f72,0x2f72,0x3f7a,0x3f7a,
    0x2f82,0x2f82,0x3f8a,0x3f8a,0x2ff2,0x2ff2,0x3ffa,0x3ffa,
    0x600,0x601,0x3608,0x3608,0x600,0x601,0x3608,0x3608,
    0x600,0x601,0x3608,0x3608,0x600,0x601,0x3608,0x3608,
    0x2e00,0x2e01,0x3e00,0x3e01,0x2f74,0x2f75,0x3f74,0x3f75,
    0x2f80,0x2f81,0x3f80,0x3f81,0x2ff4,0x2ff5,0x3ff4,0x3ff5};
const uint16_t lut5[128] = {0xc0,0xc8,0x6d0,0x6d8,0x0,0x8,0x600,0x608,
    0x1000,0x1008,0x1000,0x1008,0x0,0x8,0x610,0x618,
    0xc0,0xc8,0x6d0,0x6d8,0xb801,0xb801,0xbe01,0xbe01,
    0x1800,0x1808,0x1800,0x1808,0xb800,0xb808,0xbe10,0xbe18,
    0xc0,0xc8,0x6d0,0x6d8,0xc002,0xc002,0xc602,0xc602,
    0xd002,0xd002,0xd002,0xd002,0xc000,0xc008,0xc610,0xc618,
    0xc0,0xc8,0x6d0,0x6d8,0xf803,0xf803,0xfe03,0xfe03,
    0xd802,0xd802,0xd802,0xd802,0xf800,0xf808,0xfe10,0xfe18,
    0xe0,0xe8,0x6f0,0x6f8,0x5a0,0x5a8,0x7a0,0x7a8,
    0x1000,0x1008,0x1000,0x1008,0x5a4,0x5ac,0x7b4,0x7bc,
    0xe0,0xe8,0x6f0,0x6f8,0xbda1,0xbda1,0xbfa1,0xbfa1,
    0x1800,0x1808,0x1800,0x1808,0xbda4,0xbdac,0xbfb4,0xbfbc,
    0xe0,0xe8,0x6f0,0x6f8,0xc5a2,0xc5a2,0xc7a2,0xc7a2,
    0xd002,0xd002,0xd002,0xd002,0xc5a4,0xc5ac,0xc7b4,0xc7bc,
    0xe0,0xe8,0x6f0,0x6f8,0xfda3,0xfda3,0xffa3,0xffa3,
    0xd802,0xd802,0xd802,0xd802,0xfda4,0xfdac,0xffb4,0xffbc};
const uint16_t lut6[128] = {0x0,0x0,0x20,0x0,0x0,0x0,0x20,0x0,
    0x1,0x1,0x21,0x1,0x1,0x1,0x21,0x1,
    0x0,0x188,0x1a8,0x180,0x0,0x188,0x1a8,0x180,
    0x1,0x188,0x1a8,0x181,0x1,0x188,0x1a8,0x181,
    0x0,0x0,0x20,0x0,0x2,0x2,0x22,0x2,
    0x1,0x1,0x21,0x1,0x2,0x2,0x22,0x2,
    0x0,0x188,0x1a8,0x180,0x2,0x18a,0x1aa,0x182,
    0x1,0x188,0x1a8,0x181,0x2,0x18a,0x1aa,0x182,
    0x0,0x174,0x30,0x170,0x0,0x174,0x30,0x170,
    0x1,0x174,0x31,0x171,0x1,0x174,0x31,0x171,
    0x0,0x1fc,0x1b8,0x1f0,0x0,0x1fc,0x1b8,0x1f0,
    0x1,0x1fc,0x1b8,0x1f1,0x1,0x1fc,0x1b8,0x1f1,
    0x0,0x174,0x30,0x170,0x2,0x176,0x32,0x172,
    0x1,0x174,0x31,0x171,0x2,0x176,0x32,0x172,
    0x0,0x1fc,0x1b8,0x1f0,0x2,0x1fe,0x1ba,0x1f2,
    0x1,0x1fc,0x1b8,0x1f1,0x2,0x1fe,0x1ba,0x1f2};
const uint8_t lut7[128] = {0x0,0x1,0x0,0x1,0x0,0x0,0x0,0x0,
    0x0,0x1,0x2,0x2,0x0,0x0,0x2,0x2,
    0x4,0x5,0x4,0x5,0x4,0x4,0x4,0x4,
    0x4,0x5,0x6,0x6,0x4,0x4,0x6,0x6,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x2,0x2,0x0,0x0,0x2,0x2,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x4,0x4,0x6,0x6,0x4,0x4,0x6,0x6,
    0x4,0x5,0x4,0x5,0x4,0x4,0x4,0x4,
    0x4,0x5,0x6,0x6,0x4,0x4,0x6,0x6,
    0x4,0x5,0x4,0x5,0x4,0x4,0x4,0x4,
    0x4,0x5,0x6,0x6,0x4,0x4,0x6,0x6,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x4,0x4,0x6,0x6,0x4,0x4,0x6,0x6,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x4,0x4,0x6,0x6,0x4,0x4,0x6,0x6};
const uint8_t lut8[128] = {0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff,
    0x10,0x0,0x0,0x0,0x14,0x4,0x4,0x4,
    0xd6,0xc0,0x0,0xc6,0xd6,0xc4,0x4,0xc6,
    0x14,0x4,0x4,0x4,0x14,0x4,0x4,0x4,
    0xd6,0xc4,0x4,0xc6,0xd6,0xc4,0x4,0xc6,
    0x18,0xb8,0x0,0xbd,0x1c,0xbc,0x4,0xbd,
    0xde,0xf8,0x0,0xff,0xde,0xfc,0x4,0xff,
    0x1c,0xbc,0x4,0xbd,0x1c,0xbc,0x4,0xbd,
    0xde,0xfc,0x4,0xff,0xde,0xfc,0x4,0xff};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = (uvwState7>0?16:0) | ((apValues & 128)>0?32:0) | (apValues & 79);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((lut0output & 4096)>0?1:0) | (uvwState8>0?4:0) | ((lut0output & 8192)>0?64:0) | (lut0output & 10) | (apValues & 48);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = (uvwState18>0?2:0) | (uvwState19>0?4:0) | (uvwState20>0?8:0) | (uvwState21>0?16:0) | ((apValues & 256)>0?32:0) | ((lut0output & 2048)>0?64:0) | (lut0output & 1);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (uvwState16>0?8:0) | ((apValues & 128)>0?16:0) | (uvwState15>0?32:0) | (lut1output & 5) | (lut2output & 2) | (apValues & 64);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = (uvwState14>0?2:0) | (uvwState5>0?4:0) | (uvwState6>0?8:0) | (uvwState13>0?64:0) | (lut3output & 1) | (apValues & 48);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState4>0?2:0) | (uvwState11>0?16:0) | (uvwState12>0?32:0) | (uvwState3>0?64:0) | (lut4output & 1) | (apValues & 12);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = (uvwState10>0?16:0) | (uvwState8>0?32:0) | (uvwState9>0?64:0) | (apValues & 3) | (lut0output & 4) | (lut5output & 8);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState6>0?8:0) | ((lut0output & 1024)>0?64:0) | (lut6output & 1) | (lut1output & 18) | (lut4output & 4) | (lut0output & 32);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = (uvwState2>0?8:0) | (uvwState1>0?32:0) | ((lut7output & 1)>0?64:0) | (apValues & 3) | (lut5output & 20);
  uint32_t lut8output = lut8[lut8input];
  if ((lut0output & 16)) {
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
  } else if ((lut5output & 16)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 4)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 32)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 8)) {
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
  } else if ((lut4output & 8)) {
        buf.b0p0 = buf.b14p0 | (apValues << 18) | (13 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 2)) {
        buf.b0p0 = buf.b15p0 | (apValues << 18) | (14 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 4)) {
        buf.b0p0 = buf.b16p0 | (apValues << 18) | (15 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut3output & 8)) {
        buf.b0p0 = b17p0 | (apValues << 18) | (16 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 1)) {
        buf.b0p0 = buf.b18p0 | (apValues << 18) | (17 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 4)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 8)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 16)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut8output & 8)) {
  } else if ((lut0output & 64)) {
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
  if ((lut4output & 16)) {
  } else if ((lut1output & 8)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 64)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut4output & 128)) {
  }
  if ((lut0output & 128)) {
  } else if ((lut0output & 256)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut0output & 1024)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut1output & 16)) {
  }
  if ((lut6output & 16)) {
  } else if ((lut0output & 2048)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 64)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut6output & 128)) {
  }
  if ((lut5output & 2048)) {
  } else if ((lut0output & 4096)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 8192)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut5output & 16384)) {
  }
  if ((lut4output & 512)) {
  } else if ((lut1output & 32)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 2048)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut4output & 4096)) {
  }
  if ((lut3output & 16)) {
  } else if ((lut0output & 8192)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 64)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut3output & 128)) {
  }
  if ((lut0output & 16384)) {
  }
  if ((lut2output & 32)) {
        buf.b18p0 = b17p0 | (apValues << 0);
  }
  if ((lut2output & 128)) {
  } else if ((lut2output & 256)) {
        buf.b19p0 = b20p0 | (apValues << 0) | (0 << 9);
  } else if ((lut2output & 512)) {
        buf.b19p0 = b21p0 | (apValues << 0) | (1 << 9);
  }
  if ((lut2output & 2048)) {
  }
  if ((lut2output & 8192)) {
  }
  uvwState0 = (lut8output & 4);
  uvwState1 = (lut8output & 16);
  uvwState2 = (lut8output & 128);
  uvwState3 = (lut5output & 128);
  uvwState4 = (lut5output & 1024);
  uvwState5 = (lut4output & 32);
  uvwState6 = (lut4output & 256);
  uvwState7 = (lut0output & 512);
  uvwState8 = (lut7output & 4);
  uvwState9 = (lut6output & 32);
  uvwState10 = (lut6output & 256);
  uvwState11 = (lut5output & 4096);
  uvwState12 = (lut5output & 32768);
  uvwState13 = (lut4output & 1024);
  uvwState14 = (lut4output & 8192);
  uvwState15 = (lut3output & 32);
  uvwState16 = (lut3output & 256);
  uvwState17 = (lut0output & 32768);
  uvwState18 = (lut2output & 64);
  uvwState19 = (lut2output & 1024);
  uvwState20 = (lut2output & 4096);
  uvwState21 = (lut2output & 16384);
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
  -> Inputs a1 a2 b1 b2 uvwState7 d2 d1
  -> Outputs new_n34 new_n40 new_n54 new_n69 uvwState0incoming0 uvwState0incoming7 uvwState1incoming1 uvwState7incoming0 uvwState7incoming1 uvwState7Next uvwState8incoming0 uvwState9incoming1 uvwState11incoming1 uvwState15incoming1 uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs uvwState11incoming1 new_n40 uvwState8 new_n69 c1 c2 uvwState15incoming1
  -> Outputs new_n46 new_n48 new_n75 uvwState5incoming1 uvwState8incoming1 uvwState13incoming1
- LUT 2 has:
  -> Inputs new_n34 uvwState18 uvwState19 uvwState20 uvwState21 m uvwState9incoming1
  -> Outputs uvwState0incoming18 new_n89 uvwState0incoming19 uvwState0incoming20 uvwState0incoming21 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 3 has:
  -> Inputs new_n46 new_n89 new_n75 uvwState16 d2 uvwState15 d1
  -> Outputs new_n92 uvwState0incoming15 uvwState0incoming16 uvwState0incoming17 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 4 has:
  -> Inputs new_n92 uvwState14 uvwState5 uvwState6 c1 c2 uvwState13
  -> Outputs new_n94 uvwState0incoming13 uvwState0incoming5 uvwState0incoming14 uvwState5incoming0 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next uvwState13incoming0 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next
- LUT 5 has:
  -> Inputs new_n94 uvwState4 b1 b2 uvwState11 uvwState12 uvwState3
  -> Outputs uvwState0incoming11 uvwState0incoming12 uvwState0incoming3 new_n96 uvwState0incoming4 uvwState3incoming0 uvwState3incoming1 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next uvwState11incoming0 uvwState11Next uvwState12incoming0 uvwState12incoming1 uvwState12Next
- LUT 6 has:
  -> Inputs a1 a2 new_n54 new_n96 uvwState10 uvwState8 uvwState9
  -> Outputs new_n99 uvwState0incoming8 uvwState0incoming9 uvwState0incoming10 uvwState9incoming0 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 7 has:
  -> Inputs new_n99 new_n48 uvwState0incoming5 uvwState6 uvwState8incoming1 uvwState0incoming7 uvwState8incoming0
  -> Outputs new_n102 uvwState0incoming6 uvwState8Next
- LUT 8 has:
  -> Inputs a1 a2 uvwState0incoming3 uvwState2 uvwState0incoming4 uvwState1 new_n102
  -> Outputs uvwState0incoming1 uvwState0incoming2 uvwState0Next uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next
*/
