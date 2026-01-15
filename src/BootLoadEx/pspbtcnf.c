#include <string.h>

#include <bootloadex.h>
#include <pspbtcnf.h>

// Non-standard strcpy, using the standard version doesn't work for some reason (???)
int my_strcpy(char* dest, const char* orig){
    int i = 0;
    do{
        dest[i] = orig[i];
    } while (orig[i++]);
    return i-1; // TODO: this is NOT standard behavior of strcpy
}

int SearchPrx(char *buffer, const char *modname)
{
    //cast header
    _btcnf_header * header = (_btcnf_header *)buffer;

    if(header->signature != BTCNF_MAGIC) {
        return -1;
    }

    if(header->nmodules <= 0) {
        return -2;
    }

    if(header->nmodes <= 0) {
        return -3;
    }

    //cast module list
    _btcnf_module * module = (_btcnf_module *)(buffer + header->modulestart);

    //iterate modules
    int modnum = 0; for(; modnum < header->nmodules; modnum++)
    {
        //found module name
        if(strcmp(buffer + header->modnamestart + module[modnum].module_path, modname) == 0)
        {
            //stop search
            break;
        }
    }

    //found module
    if(modnum >= header->nmodules) {
        return -4;
    }

    return modnum;
}

int AddPRXNoCopyName(char * buffer, const char * insertbefore, int prxname_offset, u32 flags)
{
    int modnum;

    modnum = SearchPrx(buffer, insertbefore);

    if (modnum < 0) {
        return modnum;
    }

    _btcnf_header * header = (_btcnf_header *)buffer;

    //cast module list
    _btcnf_module * module = (_btcnf_module *)(buffer + header->modulestart);

    //add custom module
    _btcnf_module newmod; memset(&newmod, 0, sizeof(newmod));

    newmod.module_path = prxname_offset - header->modnamestart;

    if(flags >= 0x0000FFFF) {
        newmod.flags = flags;
    } else {
        newmod.flags = 0x80010000 | (flags & 0x0000FFFF);
    }

    memmove(&module[modnum + 1], &module[modnum + 0], (u32)buffer + header->modnameend - (unsigned int)&module[modnum + 0]);
    memcpy(&module[modnum + 0], &newmod, sizeof(newmod));
    header->nmodules++;
    header->modnamestart += sizeof(newmod);
    header->modnameend += sizeof(newmod);

    //make mode include our module
    int modenum = 0; for(; modenum < header->nmodes; modenum++)
    {
        //increase module range
        *(unsigned short *)(buffer + header->modestart + modenum * 32) += 1;
    }

    return header->modnameend;
}

int AddPRX(char * buffer, const char * insertbefore, const char * prxname, u32 flags)
{
    int modnum;
    
    modnum = SearchPrx(buffer, prxname);

    if (modnum >= 0) {
        _btcnf_header * header = (_btcnf_header *)buffer;
        _btcnf_module * module = (_btcnf_module *)(buffer + header->modulestart);

        return AddPRXNoCopyName(buffer, insertbefore, header->modnamestart + module[modnum].module_path, flags);
    }

    modnum = SearchPrx(buffer, insertbefore);

    if (modnum < 0) {
        return modnum;
    }

    _btcnf_header * header = (_btcnf_header *)buffer;
    int prxname_offset = header->modnameend;
    int len = my_strcpy(buffer + prxname_offset, prxname);
    header->modnameend += len+1;
    return AddPRXNoCopyName(buffer, insertbefore, prxname_offset, flags);
}

int RemovePrx(char *buffer, const char *prxname, u32 flags)
{
    u32 old_flags;
    int ret;

    ret = GetPrxFlag(buffer, prxname, &old_flags);

    if (ret < 0)
        return ret;

    old_flags &= 0x0000FFFF;
    flags &= 0x0000FFFF;

    if (old_flags & flags) {
        // rewrite the flags to remove the modules from runlevels indicated by flags
        old_flags = old_flags & (~flags);
    }

    return ModifyPrxFlag(buffer, prxname, 0x80010000 | (old_flags & 0x0000FFFF));
}

int MovePrx(char * buffer, const char * insertbefore, const char * prxname, u32 flags)
{
    RemovePrx(buffer, prxname, flags);

    return AddPRX(buffer, insertbefore, prxname, flags);
}

// Note flags is 32-bits!
int ModifyPrxFlag(char *buffer, const char* modname, u32 flags)
{
    int modnum;

    modnum = SearchPrx(buffer, modname);

    if (modnum < 0) {
        return modnum;
    }

    _btcnf_header * header = (_btcnf_header *)buffer;
    
    //cast module list
    _btcnf_module * module = (_btcnf_module *)(buffer + header->modulestart);

    module[modnum].flags = flags;
    return 0;
}

// Note flags is 32-bits!
int GetPrxFlag(char *buffer, const char* modname, u32 *flags)
{
    int modnum;

    modnum = SearchPrx(buffer, modname);

    if (modnum < 0) {
        return modnum;
    }

    _btcnf_header * header = (_btcnf_header *)buffer;
    
    //cast module list
    _btcnf_module * module = (_btcnf_module *)(buffer + header->modulestart);

    *flags = module[modnum].flags;

    return 0;
}
