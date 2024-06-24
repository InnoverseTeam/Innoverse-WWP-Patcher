#include <string.h>
#include <mocha/mocha.h>
#include <vpad/input.h>

#include "patches.h"
#include "log.h"

#include "checkInkayStatus.hpp"

static void write_string(uint32_t addr, const char* str)
{
    int len = strlen(str) + 1;
    int remaining = len % 4;
    int num = len - remaining;

    for (int i = 0; i < (num / 4); i++) {
        Mocha_IOSUKernelWrite32(addr + i * 4, *(uint32_t*)(str + i * 4));
    }

    if (remaining > 0) {
        uint8_t buf[4];
        Mocha_IOSUKernelRead32(addr + num, (uint32_t*)&buf);

        for (int i = 0; i < remaining; i++) {
            buf[i] = *(str + num + i);
        }

        Mocha_IOSUKernelWrite32(addr + num, *(uint32_t*)&buf);
    }
}

int main(int argc, char** argv)
{
	int mochaResult;
	if ((mochaResult = Mocha_InitLibrary()) != MOCHA_RESULT_SUCCESS) {
        log("Mocha_InitLibrary() failed with code %d", mochaResult);
    }
	
#ifdef DEBUG
    WHBLogUdpInit();
#endif

    log("Hello world from WWP-Innoverse!");

    VPADStatus status;
    VPADReadError error = VPAD_READ_SUCCESS;
    VPADRead(VPAD_CHAN_0, &status, 1, &error);

	if (mochaResult != MOCHA_RESULT_SUCCESS) {
		log("Nimble-Aquamarine patches failed!");
	}
    else if (skipPatches())
    {
        log("WWP-Innoverse patches skipped.");
    }
    else
    {
		/* URL patch */
		for (int i = 0; i < sizeof(url_patches) / sizeof(URL_Patch); i++) {
			write_string(url_patches[i].address, url_patches[i].url);
		}

        log("WWP-Innoverse patches completed!");
    }
	
    if (mochaResult == MOCHA_RESULT_SUCCESS) {
        Mocha_DeInitLibrary();
    }

#ifdef DEBUG
    WHBLogUdpDeinit();
#endif

    return 0;
}
