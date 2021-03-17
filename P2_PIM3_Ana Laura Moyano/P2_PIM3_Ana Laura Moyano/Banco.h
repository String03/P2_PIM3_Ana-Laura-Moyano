#pragma once
#include "Cuenta.h"
using namespace System;
using namespace System::Collections::Generic;

[Serializable]

ref class Banco
{
private:
	List<Cuenta^>^ _cuentas;
public:
	Banco();
	System::String^ Nombre;
	List<Cuenta^>^ ListarCuentas();
};

