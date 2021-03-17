#include "stdafx.h"
#include "Cuenta.h"

Cuenta::Cuenta()
{
	Saldo = 0.0;
}


void Cuenta::Extraer(double Monto)
{
	this->Saldo -= Monto;
}


void Cuenta::Depositar(double Monto)
{
	this->Saldo += Monto;
	
}
void Cuenta::Transferir(Cuenta^ cuenta, double Monto) 
{
	cuenta->Extraer(Monto);
	this->Depositar(Monto);
}
