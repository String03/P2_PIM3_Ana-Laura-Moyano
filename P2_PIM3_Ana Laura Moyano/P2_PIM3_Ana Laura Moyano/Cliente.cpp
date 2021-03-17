#pragma once
#include "stdafx.h"
#include "Cliente.h"
#include "Cuenta.h"
using namespace System;
using namespace System::Collections::Generic;
Cliente::Cliente()
{
	this->_Cuentas = gcnew List<Cuenta^>();
}

List<Cuenta^>^ Cliente::ListarCuentas()
{
	return this->_Cuentas;
}