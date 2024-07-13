#ifndef _PATCHER_H
#define _PATCHER_H

typedef struct URL_Patch
{
    int address;
    char url[80];
} URL_Patch;

static  const URL_Patch url_patches[] = {
    {0xE2299990, "nppl-innoverse-app.alwaysdata.net"},
    
    //nim-boss .bss
    {0xE24B8A24, "https://nppl-innoverse-app.alwaysdata.net/p01/policylist/1/1/UNK"}
};

#endif
