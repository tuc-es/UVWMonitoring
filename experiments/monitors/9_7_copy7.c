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

const uint16_t lut0[128] = {0x30f2,0x30e3,0x31e2,0x30e2,0x30d0,0x3081,0x31c0,0x30c0,
    0x32d0,0x32c1,0x3380,0x32c0,0x30d2,0x30c3,0x31c2,0x30c2,
    0x30f2,0x30e3,0x31e2,0x30e2,0x34d8,0x3489,0x35c8,0x34c8,
    0x36d8,0x36c9,0x3788,0x36c8,0x34d2,0x34c3,0x35c2,0x34c2,
    0x3872,0x3863,0x3922,0x3862,0x3850,0x3801,0x3900,0x3840,
    0x3a50,0x3a41,0x3b00,0x3a40,0x3852,0x3843,0x3902,0x3842,
    0x3872,0x3863,0x3922,0x3862,0x3c58,0x3c09,0x3d08,0x3c48,
    0x3e58,0x3e49,0x3f08,0x3e48,0x3c52,0x3c43,0x3d02,0x3c42,
    0x3072,0x3023,0x3162,0x3062,0x3050,0x3001,0x3140,0x3040,
    0x3250,0x3201,0x3300,0x3240,0x3052,0x3003,0x3142,0x3042,
    0x3072,0x3023,0x3162,0x3062,0x3458,0x3409,0x3548,0x3448,
    0x3658,0x3609,0x3708,0x3648,0x3452,0x3403,0x3542,0x3442,
    0x3072,0x3063,0x3162,0x3062,0x3050,0x3001,0x3140,0x3040,
    0x3250,0x3241,0x3300,0x3240,0x3052,0x3043,0x3142,0x3042,
    0x3072,0x3063,0x3162,0x3062,0x3458,0x3409,0x3548,0x3448,
    0x3658,0x3649,0x3708,0x3648,0x3452,0x3443,0x3542,0x3442};
const uint8_t lut1[128] = {0x8,0x8,0x8,0x8,0x8,0xbc,0x8,0xbc,
    0x28,0x38,0x28,0x38,0x8,0xb8,0x8,0xb8,
    0x1,0x1,0x1,0x1,0x1,0xb5,0x1,0xb5,
    0x21,0x31,0x21,0x31,0x1,0xb1,0x1,0xb1,
    0x40,0x40,0x40,0x40,0x40,0xf4,0x40,0xf4,
    0x60,0x70,0x60,0x70,0x40,0xf0,0x40,0xf0,
    0x0,0x0,0x0,0x0,0x0,0xb4,0x0,0xb4,
    0x20,0x30,0x20,0x30,0x0,0xb0,0x0,0xb0,
    0xa,0xa,0xa,0xa,0xa,0xbe,0xa,0xbe,
    0x2a,0x3a,0x2a,0x3a,0xa,0xba,0xa,0xba,
    0x3,0x3,0x3,0x3,0x1,0xb5,0x1,0xb5,
    0x23,0x33,0x23,0x33,0x3,0xb3,0x3,0xb3,
    0x42,0x42,0x40,0x40,0x42,0xf6,0x40,0xf4,
    0x60,0x70,0x60,0x70,0x42,0xf2,0x40,0xf0,
    0x2,0x2,0x2,0x2,0x2,0xb6,0x2,0xb6,
    0x22,0x32,0x22,0x32,0x2,0xb2,0x2,0xb2};
const uint16_t lut2[128] = {0x4,0x4,0x4,0x4,0x482,0x482,0x482,0x482,
    0x1804,0x4,0x1804,0x4,0x1c82,0x482,0x1c82,0x482,
    0x6004,0x6004,0x6004,0x6004,0x6482,0x6482,0x6482,0x6482,
    0x7804,0x6004,0x7804,0x6004,0x7c82,0x6482,0x7c82,0x6482,
    0x4,0x4,0x1,0x1,0x484,0x482,0x481,0x483,
    0x1808,0x504,0x1809,0x501,0x1c88,0x582,0x1c89,0x583,
    0x6010,0x6604,0x6011,0x6601,0x6490,0x6682,0x6491,0x6683,
    0x7818,0x6704,0x7819,0x6701,0x7c98,0x6782,0x7c99,0x6783,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x1804,0x4,0x1804,0x4,0x1804,0x4,0x1804,0x4,
    0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,
    0x1804,0x4,0x1804,0x4,0x1804,0x4,0x1804,0x4,
    0x64,0x4,0x64,0x4,0x64,0x4,0x64,0x4,
    0x1868,0x4,0x1868,0x4,0x1868,0x4,0x1868,0x4,
    0x64,0x4,0x64,0x4,0x64,0x4,0x64,0x4,
    0x1868,0x4,0x1868,0x4,0x1868,0x4,0x1868,0x4};
const uint16_t lut3[128] = {0x8,0x8,0x0,0x0,0x8,0x8,0x1,0x1,
    0x8,0x8,0x0,0x0,0x8,0x8,0x1,0x1,
    0x8,0x8,0x0,0x0,0x8,0x8,0x1,0x1,
    0x8,0x8,0x0,0x0,0x8,0x8,0x1,0x1,
    0x28,0x28,0x20,0x20,0x28,0x28,0x21,0x21,
    0x1ac,0x1ac,0x1a4,0x1a4,0x1ac,0x1ac,0x1a4,0x1a4,
    0x38,0x38,0x30,0x30,0x38,0x38,0x31,0x31,
    0x1bc,0x1bc,0x1b4,0x1b4,0x1bc,0x1bc,0x1b4,0x1b4,
    0x8,0x8,0x0,0x8,0x8,0x8,0x1,0x8,
    0x18c,0x18c,0x184,0x18c,0x18c,0x18c,0x184,0x18c,
    0x17a,0x17a,0x172,0x17a,0x17a,0x17a,0x172,0x17a,
    0x1fe,0x1fe,0x1f6,0x1fe,0x1fe,0x1fe,0x1f6,0x1fe,
    0x8,0x8,0x0,0x0,0x8,0x8,0x1,0x1,
    0x188,0x188,0x180,0x180,0x188,0x188,0x181,0x181,
    0x178,0x178,0x170,0x170,0x178,0x178,0x171,0x171,
    0x1f8,0x1f8,0x1f0,0x1f0,0x1f8,0x1f8,0x1f1,0x1f1};
const uint8_t lut4[128] = {0x0,0x4,0x0,0x4,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x4,0xb9,0xb9,0x0,0x0,0xb9,0xb9,
    0x0,0x0,0xb9,0xb9,0x0,0x0,0xb9,0xb9,
    0x10,0x14,0x18,0x1c,0x10,0x10,0x18,0x18,
    0x10,0x10,0x18,0x18,0x10,0x10,0x18,0x18,
    0x0,0x4,0xb8,0xbc,0x0,0x0,0xb8,0xb8,
    0x0,0x0,0xb8,0xb8,0x0,0x0,0xb8,0xb8,
    0x0,0x4,0x0,0x4,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0xc2,0xc2,0xfb,0xfb,0xc2,0xc2,0xfb,0xfb,
    0xc2,0xc2,0xfb,0xfb,0xc2,0xc2,0xfb,0xfb,
    0xd2,0xd2,0xda,0xda,0xd2,0xd2,0xda,0xda,
    0xd2,0xd2,0xda,0xda,0xd2,0xd2,0xda,0xda,
    0xc0,0xc4,0xf8,0xfc,0xc0,0xc0,0xf8,0xf8,
    0xc0,0xc0,0xf8,0xf8,0xc0,0xc0,0xf8,0xf8};
const uint16_t lut5[128] = {0x40,0x0,0x800,0x0,0x41,0x1,0x801,0x1,
    0x350,0x300,0x800,0x310,0x351,0x301,0x801,0x311,
    0x40,0x5c04,0xc00,0x5c00,0x41,0x5c04,0xc01,0x5c01,
    0x350,0x5f04,0xc00,0x5f10,0x351,0x5f04,0xc01,0x5f11,
    0x40,0x6008,0x6808,0x6000,0x41,0x6008,0x6808,0x6001,
    0x350,0x6308,0x6808,0x6310,0x351,0x6308,0x6808,0x6311,
    0x40,0x7c0c,0x6c08,0x7c00,0x41,0x7c0c,0x6c08,0x7c01,
    0x350,0x7f0c,0x6c08,0x7f10,0x351,0x7f0c,0x6c08,0x7f11,
    0x60,0x2e0,0x800,0x2e2,0x61,0x2e1,0x801,0x2e3,
    0x370,0x3e0,0x800,0x3f2,0x371,0x3e1,0x801,0x3f3,
    0x60,0x5ee4,0xc00,0x5ee2,0x61,0x5ee4,0xc01,0x5ee3,
    0x370,0x5fe4,0xc00,0x5ff2,0x371,0x5fe4,0xc01,0x5ff3,
    0x60,0x62e8,0x6808,0x62e2,0x61,0x62e8,0x6808,0x62e3,
    0x370,0x63e8,0x6808,0x63f2,0x371,0x63e8,0x6808,0x63f3,
    0x60,0x7eec,0x6c08,0x7ee2,0x61,0x7eec,0x6c08,0x7ee3,
    0x370,0x7fec,0x6c08,0x7ff2,0x371,0x7fec,0x6c08,0x7ff3};
const uint16_t lut6[128] = {0x10,0x11,0x0,0x1,0x18,0x19,0x0,0x1,
    0xd4,0xd4,0x0,0x1,0xdc,0xdc,0x0,0x1,
    0x110,0x111,0x100,0x101,0x118,0x119,0x100,0x101,
    0x1d4,0x1d4,0x100,0x101,0x1dc,0x1dc,0x100,0x101,
    0x110,0x111,0x100,0x101,0x118,0x119,0x100,0x101,
    0x1d4,0x1d4,0x100,0x101,0x1dc,0x1dc,0x100,0x101,
    0x110,0x111,0x100,0x101,0x118,0x119,0x100,0x101,
    0x1d4,0x1d4,0x100,0x101,0x1dc,0x1dc,0x100,0x101,
    0x0,0x1,0x0,0x1,0xb8,0xb9,0xba,0xba,
    0xc0,0xc1,0xc4,0xc4,0xf8,0xf9,0xfe,0xfe,
    0x100,0x101,0x100,0x101,0x1b8,0x1b9,0x1ba,0x1ba,
    0x1c0,0x1c1,0x1c4,0x1c4,0x1f8,0x1f9,0x1fe,0x1fe,
    0x100,0x101,0x100,0x101,0x1b8,0x1b9,0x1ba,0x1ba,
    0x1c0,0x1c1,0x1c4,0x1c4,0x1f8,0x1f9,0x1fe,0x1fe,
    0x100,0x101,0x100,0x101,0x1b8,0x1b9,0x1ba,0x1ba,
    0x1c0,0x1c1,0x1c4,0x1c4,0x1f8,0x1f9,0x1fe,0x1fe};
const uint16_t lut7[128] = {0x20,0x21,0x20,0x21,0x20,0x21,0x22,0x23,
    0x30,0x31,0x30,0x31,0x30,0x31,0x32,0x33,
    0x0,0x1,0x0,0x1,0x0,0x1,0x2,0x3,
    0x170,0x171,0x170,0x171,0x170,0x171,0x172,0x173,
    0x0,0x1,0x0,0x1,0x0,0x1,0x2,0x3,
    0x0,0x1,0x0,0x1,0x0,0x1,0x2,0x3,
    0x0,0x1,0x0,0x1,0x0,0x1,0x2,0x3,
    0x174,0x174,0x174,0x174,0x174,0x174,0x176,0x176,
    0x1a8,0x1a8,0x1a8,0x1a8,0x1a8,0x1a8,0x1aa,0x1aa,
    0x1b8,0x1b8,0x1b8,0x1b8,0x1b8,0x1b8,0x1ba,0x1ba,
    0x180,0x181,0x180,0x181,0x180,0x181,0x182,0x183,
    0x1f0,0x1f1,0x1f0,0x1f1,0x1f0,0x1f1,0x1f2,0x1f3,
    0x0,0x1,0x0,0x1,0x0,0x1,0x2,0x3,
    0x0,0x1,0x0,0x1,0x0,0x1,0x2,0x3,
    0x188,0x188,0x188,0x188,0x188,0x188,0x18a,0x18a,
    0x1fc,0x1fc,0x1fc,0x1fc,0x1fc,0x1fc,0x1fe,0x1fe};
const uint8_t lut8[128] = {0xa,0x8,0xa,0xa,0x2,0x0,0x2,0x2,
    0x2,0x0,0x2,0x2,0x2,0x0,0x2,0x2,
    0xa,0xa,0xa,0xa,0x2,0x2,0x2,0x2,
    0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,
    0x6a,0x6a,0x6a,0x6a,0x62,0x60,0x62,0x62,
    0x2,0x0,0x2,0x2,0x62,0x62,0x62,0x62,
    0x6a,0x6a,0x6a,0x6a,0x62,0x62,0x62,0x62,
    0x2,0x2,0x2,0x2,0x62,0x62,0x62,0x62,
    0xe,0xc,0xe,0xe,0x5e,0x5c,0x5e,0x5e,
    0x2,0x0,0x2,0x2,0x5f,0x5f,0x5f,0x5f,
    0xe,0xe,0xe,0xe,0x5e,0x5e,0x5e,0x5e,
    0x2,0x2,0x2,0x2,0x5f,0x5f,0x5f,0x5f,
    0x6e,0x6e,0x6e,0x6e,0x7e,0x7c,0x7e,0x7e,
    0x2,0x0,0x2,0x2,0x7f,0x7f,0x7f,0x7f,
    0x6e,0x6e,0x6e,0x6e,0x7e,0x7e,0x7e,0x7e,
    0x2,0x2,0x2,0x2,0x7f,0x7f,0x7f,0x7f};

void monitorUpdate(uint32_t apValues) {
  uint32_t lut0input = (uvwState12>0?16:0) | ((apValues & 128)>0?32:0) | (apValues & 79);
  uint32_t lut0output = lut0[lut0input];
  uint32_t lut1input = ((lut0output & 2048)>0?2:0) | (uvwState11 & 1) | (apValues & 60) | (lut0output & 64);
  uint32_t lut1output = lut1[lut1input];
  uint32_t lut2input = (uvwState18>0?2:0) | (uvwState19>0?4:0) | (uvwState20>0?8:0) | (uvwState21>0?16:0) | ((apValues & 256)>0?32:0) | ((lut0output & 256)>0?64:0) | (lut0output & 1);
  uint32_t lut2output = lut2[lut2input];
  uint32_t lut3input = (uvwState16>0?8:0) | (uvwState15>0?16:0) | ((apValues & 128)>0?32:0) | (lut1output & 3) | (lut2output & 4) | (apValues & 64);
  uint32_t lut3output = lut3[lut3input];
  uint32_t lut4input = (uvwState13>0?2:0) | (uvwState14>0?64:0) | (lut3output & 1) | (lut1output & 4) | (lut0output & 8) | (apValues & 48);
  uint32_t lut4output = lut4[lut4input];
  uint32_t lut5input = (uvwState2>0?8:0) | (uvwState9>0?16:0) | (uvwState10>0?32:0) | (uvwState1>0?64:0) | (apValues & 3) | (lut4output & 4);
  uint32_t lut5output = lut5[lut5input];
  uint32_t lut6input = ((apValues & 128)>0?2:0) | (uvwState7>0?4:0) | (uvwState8>0?8:0) | ((lut0output & 1024)>0?16:0) | ((lut1output & 128)>0?32:0) | (lut5output & 1) | (apValues & 64);
  uint32_t lut6output = lut6[lut6input];
  uint32_t lut7input = (uvwState4>0?4:0) | (uvwState5>0?8:0) | (uvwState6>0?64:0) | (lut6output & 1) | (lut0output & 2) | (apValues & 48);
  uint32_t lut7output = lut7[lut7input];
  uint32_t lut8input = (uvwState4>0?32:0) | (uvwState3>0?64:0) | (lut7output & 1) | (lut5output & 18) | (apValues & 12);
  uint32_t lut8output = lut8[lut8input];
  if ((lut0output & 4)) {
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 2)) {
        buf.b0p0 = buf.b1p0 | (apValues << 18) | (0 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 16)) {
        buf.b0p0 = buf.b2p0 | (apValues << 18) | (1 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut8output & 1)) {
        buf.b0p0 = buf.b3p0 | (apValues << 18) | (2 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 2)) {
        buf.b0p0 = buf.b4p0 | (apValues << 18) | (3 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 4)) {
        buf.b0p0 = buf.b5p0 | (apValues << 18) | (4 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut7output & 8)) {
        buf.b0p0 = buf.b6p0 | (apValues << 18) | (5 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 2)) {
        buf.b0p0 = buf.b7p0 | (apValues << 18) | (6 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut6output & 4)) {
        buf.b0p0 = buf.b8p0 | (apValues << 18) | (7 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 4)) {
        buf.b0p0 = buf.b9p0 | (apValues << 18) | (8 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut5output & 8)) {
        buf.b0p0 = buf.b10p0 | (apValues << 18) | (9 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut1output & 4)) {
        buf.b0p0 = buf.b11p0 | (apValues << 18) | (10 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut0output & 8)) {
        buf.b0p0 = buf.b12p0 | (apValues << 18) | (11 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 1)) {
        buf.b0p0 = buf.b13p0 | (apValues << 18) | (12 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut4output & 2)) {
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
  } else if ((lut2output & 2)) {
        buf.b0p0 = buf.b19p0 | (apValues << 18) | (18 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 8)) {
        buf.b0p0 = b20p0 | (apValues << 18) | (19 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  } else if ((lut2output & 16)) {
        buf.b0p0 = b21p0 | (apValues << 18) | (20 << 27);
    logViolationExplanation(&(buf.b0p0),4);
  }
  if ((lut5output & 32)) {
  } else if ((lut0output & 16)) {
        buf.b1p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 128)) {
        buf.b2p0 = buf.b1p0 | (apValues << 9);
  } else if ((lut5output & 256)) {
  }
  if ((lut8output & 4)) {
  } else if ((lut0output & 32)) {
        buf.b3p0 = b17p0 | (apValues << 0);
  }
  if ((lut8output & 16)) {
        buf.b4p0 = buf.b3p0 | (apValues << 9);
  } else if ((lut8output & 32)) {
  }
  if ((lut7output & 16)) {
  } else if ((lut1output & 8)) {
        buf.b5p0 = b17p0 | (apValues << 0);
  }
  if ((lut7output & 64)) {
        buf.b6p0 = buf.b5p0 | (apValues << 9);
  } else if ((lut7output & 128)) {
  }
  if ((lut6output & 8)) {
  } else if ((lut0output & 128)) {
        buf.b7p0 = b17p0 | (apValues << 0);
  }
  if ((lut6output & 32)) {
        buf.b8p0 = buf.b7p0 | (apValues << 9);
  } else if ((lut6output & 64)) {
  }
  if ((lut5output & 1024)) {
  } else if ((lut0output & 256)) {
        buf.b9p0 = b17p0 | (apValues << 0);
  }
  if ((lut5output & 4096)) {
        buf.b10p0 = buf.b9p0 | (apValues << 9);
  } else if ((lut5output & 8192)) {
  }
  if ((lut1output & 16)) {
  } else if ((lut0output & 512)) {
        buf.b11p0 = b17p0 | (apValues << 0);
  }
  if ((lut1output & 128)) {
        buf.b12p0 = buf.b11p0 | (apValues << 9);
  } else if ((lut0output & 1024)) {
  }
  if ((lut4output & 8)) {
  } else if ((lut1output & 64)) {
        buf.b13p0 = b17p0 | (apValues << 0);
  }
  if ((lut4output & 32)) {
        buf.b14p0 = buf.b13p0 | (apValues << 9);
  } else if ((lut4output & 64)) {
  }
  if ((lut3output & 16)) {
  } else if ((lut0output & 2048)) {
        buf.b15p0 = b17p0 | (apValues << 0);
  }
  if ((lut3output & 64)) {
        buf.b16p0 = buf.b15p0 | (apValues << 9);
  } else if ((lut3output & 128)) {
  }
  if ((lut0output & 4096)) {
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
  uvwState0 = (lut8output & 2);
  uvwState1 = (lut5output & 64);
  uvwState2 = (lut5output & 512);
  uvwState3 = (lut8output & 8);
  uvwState4 = (lut8output & 64);
  uvwState5 = (lut7output & 32);
  uvwState6 = (lut7output & 256);
  uvwState7 = (lut6output & 16);
  uvwState8 = (lut6output & 128);
  uvwState9 = (lut5output & 2048);
  uvwState10 = (lut5output & 16384);
  uvwState11 = (lut1output & 32);
  uvwState12 = (lut6output & 256);
  uvwState13 = (lut4output & 16);
  uvwState14 = (lut4output & 128);
  uvwState15 = (lut3output & 32);
  uvwState16 = (lut3output & 256);
  uvwState17 = (lut0output & 8192);
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
  -> Inputs a1 a2 b1 b2 uvwState12 d2 d1
  -> Outputs new_n34 new_n42 uvwState0incoming0 uvwState0incoming12 uvwState1incoming1 uvwState3incoming1 new_n69 uvwState7incoming1 uvwState9incoming1 uvwState11incoming1 uvwState12incoming1 uvwState15incoming1 uvwState17incoming0 uvwState17Next
- LUT 1 has:
  -> Inputs uvwState11 uvwState15incoming1 b1 b2 c1 c2 new_n69
  -> Outputs new_n46 new_n75 uvwState0incoming11 uvwState5incoming1 uvwState11incoming0 uvwState11Next uvwState13incoming1 uvwState12incoming0
- LUT 2 has:
  -> Inputs new_n34 uvwState18 uvwState19 uvwState20 uvwState21 m uvwState9incoming1
  -> Outputs uvwState0incoming18 uvwState0incoming19 new_n89 uvwState0incoming20 uvwState0incoming21 uvwState18incoming0 uvwState18Next uvwState19incoming0 uvwState19incoming1 uvwState19incoming2 uvwState19Next uvwState20incoming0 uvwState20Next uvwState21incoming0 uvwState21Next
- LUT 3 has:
  -> Inputs new_n46 new_n75 new_n89 uvwState16 uvwState15 d2 d1
  -> Outputs new_n92 uvwState0incoming15 uvwState0incoming16 uvwState0incoming17 uvwState15incoming0 uvwState15Next uvwState16incoming0 uvwState16incoming1 uvwState16Next
- LUT 4 has:
  -> Inputs new_n92 uvwState13 uvwState0incoming11 uvwState0incoming12 c1 c2 uvwState14
  -> Outputs uvwState0incoming13 uvwState0incoming14 new_n96 uvwState13incoming0 uvwState13Next uvwState14incoming0 uvwState14incoming1 uvwState14Next
- LUT 5 has:
  -> Inputs a1 a2 new_n96 uvwState2 uvwState9 uvwState10 uvwState1
  -> Outputs new_n98 uvwState0incoming1 uvwState0incoming9 uvwState0incoming10 uvwState0incoming2 uvwState1incoming0 uvwState1Next uvwState2incoming0 uvwState2incoming1 uvwState2Next uvwState9incoming0 uvwState9Next uvwState10incoming0 uvwState10incoming1 uvwState10Next
- LUT 6 has:
  -> Inputs new_n98 d2 uvwState7 uvwState8 uvwState12incoming1 uvwState12incoming0 d1
  -> Outputs new_n100 uvwState0incoming7 uvwState0incoming8 uvwState7incoming0 uvwState7Next uvwState8incoming0 uvwState8incoming1 uvwState8Next uvwState12Next
- LUT 7 has:
  -> Inputs new_n100 new_n42 uvwState4 uvwState5 c1 c2 uvwState6
  -> Outputs new_n102 uvwState0incoming4 uvwState0incoming5 uvwState0incoming6 uvwState5incoming0 uvwState5Next uvwState6incoming0 uvwState6incoming1 uvwState6Next
- LUT 8 has:
  -> Inputs new_n102 uvwState0incoming1 b1 b2 uvwState0incoming2 uvwState4 uvwState3
  -> Outputs uvwState0incoming3 uvwState0Next uvwState3incoming0 uvwState3Next uvwState4incoming0 uvwState4incoming1 uvwState4Next
*/
