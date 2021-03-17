#pragma once
#include "Cuenta.h"
using namespace System;

[Serializable]
ref class CuentaCorriente :
	public Cuenta
{
public:
	CuentaCorriente();
	void Extraer(double) override;
	double descubierto;
};

