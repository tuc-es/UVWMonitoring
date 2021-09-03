#ifndef __UVW_MONITOR_H__
#define __UVW_MONITOR_H__
#include <stdint.h>

void monitorUpdate(uint32_t v);
void logViolationExplanation(void *violationBuffer,uint32_t sizeBuffer);
void logLivenessStarvation(uint32_t uvwState,uint32_t counter,void *violationBuffer,uint32_t sizeBuffer);

#define FREQUENCY_MASK_STARVATION_LOGGING 0x7fff

#endif