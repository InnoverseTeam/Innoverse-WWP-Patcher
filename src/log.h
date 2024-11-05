#pragma once

#ifdef DEBUG
#include <whb/log.h>
#include <whb/log_udp.h>

#define log_init() do { WHBLogUdpInit(); } while(0)
#define log(fmt, args...) do { WHBLogPrintf(fmt, ## args); } while(0)

#else // DEBUG

#define log_init() do {} while(0)
#define log(fmt, args...) do {} while(0)

#endif
