#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*@exposed@*//*@null@*/char *pw_encrypt (const char *clear, const char *salt)
{
	static char cipher[128];
	char *cp;

	cp = crypt (clear, salt);
	if (NULL == cp) {
		/*
		 * Single Unix Spec: crypt() may return a null pointer,
		 * and set errno to indicate an error. In this case return
		 * the NULL so the caller can handle appropriately.
		 */
		return NULL;
	}

	/* Some crypt() do not return NULL if the algorithm is not
	 * supported, and return a DES encrypted password. */
	if ((NULL != salt) && (salt[0] == '$') && (strlen (cp) <= 13))
	{
		/*@observer@*/const char *method;
		switch (salt[1])
		{
			case '1':
				method = "MD5";
				break;
			case '5':
				method = "SHA256";
				break;
			case '6':
				method = "SHA512";
				break;
			default:
			{
				static char nummethod[4] = "$x$";
				nummethod[1] = salt[1];
				method = &nummethod[0];
			}
		}
		printf("crypt method not supported by libcrypt? (%s)\n", method);
		exit (EXIT_FAILURE);
	}

	if (strlen (cp) != 13) {
		return cp;	/* nonstandard crypt() in libc, better bail out */
	}

	strcpy (cipher, cp);

	return cipher;
}

void main(int argc, char *argv[])
{
	char clear[256] = "haibotu511*";
	char salt[256] = "$6$E6SwLEpr$";
	char *cipher;

	cipher = pw_encrypt(clear, salt);

	printf("clear pwd %s, salt %s, cipher %s\n", clear, salt, cipher);

	return;
}

