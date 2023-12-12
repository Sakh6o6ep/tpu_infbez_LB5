#include <iostream>
#include <string>
#include <math.h>
#include "md5.h"
#include "EDS.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");

	RSA_EDS crypto;

	crypto.RSA_cryptography();
	crypto.EDS();

	system("pause");
	return 0;
}
