#include <iostream>
#include <string>
#include <math.h>
#include "md5.h"

using namespace std;

class RSA_EDS {
	long int p, q, n, Phi, e, d, i, j, m, c, flag, e_choose, s;
	long int k = 1;
	string oMsg, eMsg, dMsg;
	bool flag_input = false;
	bool flag_input_e = false;
	string m_md5, podpis, podpis_;
	string m_;
public:

	bool prime(long int num);
	long int calculateD(long int e);
	void calculateE();
	void RSA_cryptography();
	void EDS();
};