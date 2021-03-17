#include "stdafx.h"
#include "CajaAhorro.h"

CajaAhorro::CajaAhorro()
{
}

void CajaAhorro::Extraer(double Monto) 
{
	if (this->Saldo - Monto -(Monto / 100 * 0.01) < 0) 
	{
		throw gcnew Exception("No tiene saldo suficiente.");
	}
	this->Saldo -= Monto - (Monto / 100 * 0.01);
}