#ifndef PSP_UNARCHIVE_H
#define PSP_UNARCHIVE_H

int unarchiveFile(const char* filepath, const char* parent, void (*logger)(const char*, int, int));

#endif