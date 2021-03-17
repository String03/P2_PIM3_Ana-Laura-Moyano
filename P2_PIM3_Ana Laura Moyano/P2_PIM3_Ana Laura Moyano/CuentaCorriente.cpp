#include "stdafx.h"
#include "CuentaCorriente.h"

CuentaCorriente::CuentaCorriente()
{
}

void CuentaCorriente::Extraer(double Monto)
{
	if ((this->Saldo + this->descubierto - Monto) < 0) {
		throw gcnew Exception("No hay fondo suficiente");
	}
	this->Saldo -= Monto;

}