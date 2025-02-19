#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

// https://github.com/S12cybersecurity/VirtualAlloc-Implementation

enum ProtectionType { R = 1, W = 2, X = 4, RW = 3, RX = 5, WX = 6, RWX = 7 };

char* CustomVirtualAlloc(int size, ProtectionType protectionType) {
    char dll[] = { 'w','i','n','m','m','.','d','l','l','\0' };

    DWORD protection = 0;
    char* address = nullptr;
    DWORD oldProtect;
    HMODULE victimDLL = GetModuleHandleA(dll);

    if (victimDLL == NULL) {
        victimDLL = LoadLibraryA(dll);
        if (victimDLL != NULL) {
            address = (char*)victimDLL;
        }
    }
    else {
        address = (char*)victimDLL;
    }

    char* allocatedMemory = nullptr;

    switch (protectionType) {
    case R:
        protection = PAGE_READONLY;
        allocatedMemory = (char*)address + 2 * 4096 + 12;
        break;
    case W:
        protection = PAGE_WRITECOPY;
        allocatedMemory = (char*)address + 2 * 4096 + 12;
        break;
    case X:
        protection = PAGE_EXECUTE;
        allocatedMemory = (char*)address + 2 * 4096 + 12;
        break;
    case RW:
        protection = PAGE_READWRITE;
        allocatedMemory = (char*)address + 2 * 4096 + 12;
        break;
    case RX:
        protection = PAGE_EXECUTE_READ;
        allocatedMemory = (char*)address + 2 * 4096 + 12;
        break;
    case WX:
        protection = PAGE_EXECUTE_WRITECOPY;
        allocatedMemory = (char*)address + 2 * 4096 + 12;
        break;
    case RWX:
        protection = PAGE_EXECUTE_READWRITE;
        allocatedMemory = (char*)address + 2 * 4096 + 12;
        break;
    default:
        protection = PAGE_NOACCESS;
        break;
    }

    if (allocatedMemory != nullptr) {
        VirtualProtect(allocatedMemory, size, protection, &oldProtect);
    }

    return allocatedMemory;
}