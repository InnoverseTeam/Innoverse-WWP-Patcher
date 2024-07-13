/*
 *   Copyright (C) 2021 GaryOderNichts
 *   Copyright (C) 2022 Pretendo Network contributors
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <mocha/mocha.h>

#include <vpad/input.h>
#include <coreinit/mcp.h>

#include "patches.h"
#include "log.h"

//thanks @Gary#4139 :p
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
        Mocha_IOSUKernelRead32(addr + num, (uint32_t*)&buf, 1);

        for (int i = 0; i < remaining; i++) {
            buf[i] = *(str + num + i);
        }

        Mocha_IOSUKernelWrite32(addr + num, *(uint32_t*)&buf);
    }
}

int main(int argc, char** argv)
{
#ifdef DEBUG
    WHBLogUdpInit();
#endif

    log("Welcome to Innoverse-WWP-Patches!");

    //check Gamepad input to maybe skip patches
    VPADStatus status;
    VPADReadError error = VPAD_READ_SUCCESS;
    VPADRead(VPAD_CHAN_0, &status, 1, &error);

    if (status.hold & VPAD_BUTTON_ZL)
    {
        log("Innoverse-WWP-Patches patches skipped.");
    }
    else
    {
        if (IOSUHAX_Open(NULL) >= 0) {
            /* URL patch */
            for (int i = 0; i < sizeof(url_patches) / sizeof(URL_Patch); i++) {
                write_string(url_patches[i].address, url_patches[i].url);
            }

            IOSUHAX_Close();
            log("Innoverse-WWP-Patches patches succeeded!");
        }
        else
        {
            log("Innoverse-WWP-Patches patches failed!");
        }
    }

#ifdef DEBUG
    WHBLogUdpDeinit();
#endif

    return 0;
}
