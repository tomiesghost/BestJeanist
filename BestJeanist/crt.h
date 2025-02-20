#pragma once
#include <Windows.h>

// https://github.com/malxau/minicrt/blob/master/crt/minicrt.h
#ifdef __cplusplus
extern "C" {
#endif


	//  On x86 systems, use __stdcall wherever possible.  Use the default
	//  on every other architecture.


#ifdef _M_IX86
#define MCRT_FN __stdcall
#define MCRT_VARARGFN __cdecl
#else
#define MCRT_FN
#define MCRT_VARARGFN
#endif


	INT MCRT_FN mini_strlen(const PCHAR str);
	PVOID MCRT_FN mini_memcpy(PVOID dest, PVOID src, UINT len);

#ifndef MINICRT_BUILD 

#undef  strlen
#define strlen    mini_strlen

#undef  malloc
#define malloc(x)   HeapAlloc(GetProcessHeap(), 0, x)

#endif

#ifdef __cplusplus
}
#endif
