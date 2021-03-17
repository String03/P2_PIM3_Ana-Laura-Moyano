#pragma once
#include "Cuenta.h"
using namespace System;

[Serializable]
ref class CajaAhorro :
	public Cuenta
{
public:
	CajaAhorro();
	void Extraer(double) override;
};

