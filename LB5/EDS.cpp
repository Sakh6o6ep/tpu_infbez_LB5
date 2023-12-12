#include "EDS.h"

bool RSA_EDS::prime(long int num) {
	for (i = 2; i <= (sqrt(num)); i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

long int RSA_EDS::calculateD(long int e) {
	long int k = 1;
	while (1) {
		k = k + Phi;
		if (k % e == 0) {
			return (k / e);
		}
	}
}

void RSA_EDS::calculateE() {
	if (e_choose == 1) {
		for (j = 2; i < Phi; j++) {
			if (Phi % j == 0) {
				continue;
			}
			if (prime(j) && j != p && j != q) {
				e = j;
				flag = calculateD(e);
				if (flag > 0) {
					d = flag;
					break;
				}
			}
		}
	}
	else if (e_choose == 2) {
		while (!flag_input_e) {
			cout << "Введите e = ";
			cin >> e;
			if (Phi % e == 0) {
				cout << "e не взаимно простое с Phi" << endl;
				flag_input_e = false;
			}
			else if (prime(e) && e != p && e != q && e < Phi) {
				d = calculateD(e);
				flag_input_e = true;
			}
			else {
				flag_input_e = false;
				cout << "e не простое число" << endl;
			}
		}
	}

}

void RSA_EDS::RSA_cryptography() {

	while (!flag_input) {
		cout << "Введите p = ";
		cin >> p;
		cout << "Введите q = ";
		cin >> q;
		if (p < 7) {
			cout << "p должно быть больше 7" << endl;
		}
		if (q < 7) {
			cout << "q должно быть больше 7" << endl;
		}
		if (!prime(p)) {
			cout << "p не простое число" << endl;
		}
		if (!prime(q)) {
			cout << "q не простое число" << endl;
		}
		if (!prime(p) || !prime(q)) flag_input = false;
		else flag_input = true;
	}
	n = p * q;
	Phi = (p - 1) * (q - 1);


	cout << "1 - Автоматическое вычисление e" << endl;
	cout << "2 - Ручной ввод взаимно простого e с Phi" << endl;
	cin >> e_choose;
	if (e_choose < 1 || e_choose > 2) exit(1);
	calculateE();

	cout << "Введите сообщение для шифрования" << endl;
	cin.ignore();
	getline(cin, oMsg);
	cout << "p\tq\tn\tPhi\tmessage" << endl;
	cout << p << "\t" << q << "\t" << n << "\t" << Phi << "\t" << oMsg << endl;

	cout << "e = " << e << endl;
	cout << "d = " << d << endl;


	for (int a = 0; oMsg[a] != '\0'; a++) {
		// Шифрование
		m = oMsg[a];
		k = 1;
		for (i = 0; i < e; i++) {
			k = k * m;
			k = k % n;
		}
		c = k;
		eMsg.push_back(eMsg[a] = c);

		// Дешифрование
		k = 1;
		for (i = 0; i < d; i++) {
			k = k * c;
			k = k % n;
		}
		m = k;
		dMsg.push_back(dMsg[a] = m);

	}

	cout << "Зашифрованное сообщение: " << eMsg << endl;
	cout << "Зашифрованное сообщение: ";
	for (int i = 0; i < eMsg.length(); i++)
	{
		unsigned char a = (unsigned char)(eMsg[i]);
		printf("%02x ", a);
	}
	cout << endl;

	cout << "Дешифрованное сообщение: " << dMsg << endl;
}

void RSA_EDS::EDS() {
	m_md5 = md5(oMsg);
	cout << "md5: " << md5(oMsg) << endl;
	for (int a = 0; m_md5[a] != '\0'; a++) {
		// Цифровая подпись: отправитель
		m = m_md5[a];
		k = 1;
		for (i = 0; i < d; i++) {
			k = k * m;
			k = k % n;
		}
		s = k;
		podpis.push_back(podpis[a] = s);

		// Цифровая подпись: получатель
		m_ = md5(oMsg);
		k = 1;
		for (i = 0; i < e; i++) {
			k = k * s;
			k = k % n;
		}
		m = k;
		podpis_.push_back(podpis_[a] = m);

	}

	cout << "{M,s} = {" << oMsg << ",";
	for (int i = 0; i < podpis.length(); i++)
	{
		unsigned char a = (unsigned char)(podpis[i]);
		printf("%02x ", a);
	}
	cout << "}" << endl;


	cout << "Хэш-образ по полученному сообщению: " << m_ << endl;
	cout << "Хэш-образ из цифровой подписи: " << podpis_ << endl;

	if (m_ == podpis_) {
		cout << "Цифровая подпись совпала" << endl;
	}
	else {
		cout << "Цифровая подпись не совпала" << endl;
	}
}