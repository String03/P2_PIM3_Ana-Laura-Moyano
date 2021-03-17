#pragma once
using namespace System;
using namespace System::Collections::Generic;

[Serializable]
ref class Cuenta
{
public:
	Cuenta();
	void virtual Extraer(double);
	void virtual Depositar(double);
	void virtual Transferir(Cuenta^, double);
	System::String^ Numero;
	double Saldo;
};
