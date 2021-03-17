#pragma once
#include "Cuenta.h"
using namespace System;
using namespace System::Collections::Generic;

[Serializable]
ref class Cliente
{
public:
	Cliente();
	System::String^ _Legajo;
	System::String^ _Nombre;
	System::String^ _Apellido;
	System::String^ _Direccion;
	System::String^ _TipoDNI;
	System::String^ _NumDNI;
	System::String^ _Telefono;
	List<Cuenta^>^ ListarCuentas();
private:
	List<Cuenta^>^ _Cuentas;
};
