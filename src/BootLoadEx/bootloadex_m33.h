#ifndef BOOTLOADEX_M33_H
#define BOOTLOADEX_M33_H

extern u8 g_recovery_mode;

int UnpackBootConfigM33PSP(char *buffer, int length);

#endif