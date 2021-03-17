#include "stdafx.h"
#include "Banco.h"
#include "Cuenta.h"
using namespace System;
using namespace System::Collections::Generic;

Banco::Banco()
{
	this->_cuentas = gcnew List<Cuenta^>();
}

List<Cuenta^>^ Banco::ListarCuentas()
{
	return this->_cuentas;
}
