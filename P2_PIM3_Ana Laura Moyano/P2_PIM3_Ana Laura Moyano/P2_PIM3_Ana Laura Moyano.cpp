#include "stdafx.h"
#include "Cliente.h"
#include "Cuenta.h"
#include "CajaAhorro.h"
#include "CuentaCorriente.h"
#include "DataManager.h"

#define ARCHIVO_CLIENTE "clientes.dat"
#define ARCHIVO_BANCO "banco.dat"

using namespace System;
using namespace System::Collections::Generic;

int main(array<System::String^>^ args);

int EnseniarMenu();
Cliente^ CrearCliente();
Cuenta^  CrearCuenta();
void ListarClientes(List<Cliente^>^);
void ListarCuentas(List<Cuenta^>^);
Cliente^ ManejarCliente(List<Cliente^>^, void(*operacionCliente)(Cliente^));
Cuenta^ ManejarCuenta(List<Cuenta^>^, void(*operacionCuenta)(Cuenta^));
void DetalleCliente(Cliente^);
void DetalleCuenta(Cuenta^);
void OperacionCuentas(Cuenta^, List<Cuenta^>^);
bool LegajoExiste(List<Cliente^>^, String^);
bool CuentaExiste(List<Cuenta^>^, String^);


int main(array<System::String ^> ^args)
{
	int seleccion = 1;
	List <Cliente^>^clientes;
	Banco^ banco;

	// Primera lectura del banco.
	banco = LeerBanco(ARCHIVO_BANCO);

	Console::WriteLine("Bienvenido al banco {0}", banco->Nombre);

	while (seleccion)
	{
		seleccion = EnseniarMenu();

		switch (seleccion)
		{
		case 1: {
			clientes = LeerClientes(ARCHIVO_CLIENTE);
			ListarClientes(clientes);
			Cliente^ cliente = CrearCliente();
			if(!LegajoExiste(clientes, cliente->_Legajo))
				clientes->Add(cliente);
			else
				Console::WriteLine("Este cliente ya existe.");
			GuardarClientes(ARCHIVO_CLIENTE, clientes);
			break;
		}

		case 2: {
			banco = LeerBanco(ARCHIVO_BANCO);
			List<Cuenta^>^ cuentasref = banco->ListarCuentas();
			ListarCuentas(banco->ListarCuentas());
			Cuenta^ cuenta = CrearCuenta();
			if (!CuentaExiste(cuentasref, cuenta->Numero))
				banco->ListarCuentas()->Add(cuenta);
			else
				Console::WriteLine("Esta cuenta ya existe.");
			GuardarBanco(ARCHIVO_BANCO, banco);
			break;
		}

		case 3: {
			clientes = LeerClientes(ARCHIVO_CLIENTE);
			ListarClientes(clientes);
			ManejarCliente(clientes, DetalleCliente);
			break;
		}

		case 4: {
			banco = LeerBanco(ARCHIVO_BANCO);
			clientes = LeerClientes(ARCHIVO_CLIENTE);
			List<Cuenta^>^ cuentasref = banco->ListarCuentas();
			ListarCuentas(cuentasref);
			Cuenta^ cuentaSeleccionada = ManejarCuenta(cuentasref, DetalleCuenta);
			List<Cliente^>^ clientesAsociados = gcnew List<Cliente^>();
			for each (Cliente^ cli in clientes)
			{
				if (CuentaExiste(cli->ListarCuentas(), cuentaSeleccionada->Numero))
					clientesAsociados->Add(cli);
			}
			Console::WriteLine("Clientes asociados: ");
			if (clientesAsociados->Count == 0)
				Console::WriteLine("Esta cuenta no tiene clientes asociados.");
			else
				ListarClientes(clientesAsociados);
			break;
		}

		case 5: {
			banco = LeerBanco(ARCHIVO_BANCO);
			List<Cuenta^>^ cuentasref = banco->ListarCuentas();
			ListarCuentas(cuentasref);
			Cuenta^ c = ManejarCuenta(cuentasref, nullptr);
			OperacionCuentas(c, cuentasref);
			GuardarBanco(ARCHIVO_BANCO, banco);
			break;
		}

		case 6: {
			clientes = LeerClientes(ARCHIVO_CLIENTE);
			ListarClientes(clientes);
			clientes->Remove(ManejarCliente(clientes, nullptr));
			GuardarClientes(ARCHIVO_CLIENTE, clientes);
			break;
		}

		case 7: {
			banco = LeerBanco(ARCHIVO_BANCO);
			List<Cuenta^>^ cuentasref = banco->ListarCuentas();
			ListarCuentas(cuentasref);
			cuentasref->Remove(ManejarCuenta(cuentasref, nullptr));
			GuardarBanco(ARCHIVO_BANCO, banco);
			break;
		}

		case 8: {
			clientes = LeerClientes(ARCHIVO_CLIENTE);
			banco = LeerBanco(ARCHIVO_BANCO);
			List<Cuenta^>^ cuentasref = banco->ListarCuentas();
			try
			{
				ListarClientes(clientes);
				Cliente^ clienteElegido = ManejarCliente(clientes, nullptr);
				ListarCuentas(cuentasref);
				Cuenta^ cuentaElegida = ManejarCuenta(cuentasref, nullptr);
				if (clienteElegido->ListarCuentas()->Contains(cuentaElegida))
				{
					throw gcnew Exception("Este cliente ya tiene esta cuenta!");
				}
				clienteElegido->ListarCuentas()->Add(cuentaElegida);
			}
			catch (Exception^ e)
			{
				Console::WriteLine(e->Message);
			}

			GuardarClientes(ARCHIVO_CLIENTE, clientes);
			GuardarBanco(ARCHIVO_BANCO, banco);
		}

		default:
			break;
		}
	}

	return 0;
}

int EnseniarMenu()
{
	Console::WriteLine("Elija una opción disponible en el sistema");
	Console::WriteLine("Seleccionar opción:\n0-Salir\n1-Agregar Cliente\n2-Agregar Cuenta\n3-Leer Cliente\n4-Leer Cuenta\n5-Operaciones de cuentas\n6-Dar de baja Cliente\n7-Dar de baja Cuenta\n8-Asociar cuenta a un cliente");
	return Convert::ToInt32(Console::ReadLine());
}

Cliente^ CrearCliente()
{
	Console::Write("Introduzca el legajo del cliente: ");
	System::String^ Legajo = Console::ReadLine();
	Console::Write("Introduzca el nombre del cliente: ");
	System::String^ Nombre = Console::ReadLine();
	Console::Write("Introduzca el apellido del cliente: ");
	System::String^ Apellido = Console::ReadLine();
	Console::Write("Introduzca la dirección del cliente: ");
	System::String^ Direccion = Console::ReadLine();
	Console::Write("Introduzca el tipo de dni del cliente: ");
	System::String^ TipoDNI = Console::ReadLine();
	Console::Write("Introduzca el número de dni del cliente: ");
	System::String^ NumeroDNI = Console::ReadLine();
	Console::Write("Introduzca el teléfono del cliente: ");
	System::String^ Telefono = Console::ReadLine();

	Cliente^ cliente = gcnew Cliente();
	cliente->_Legajo = Legajo;
	cliente->_Nombre = Nombre;
	cliente->_Apellido = Apellido;
	cliente->_Direccion = Direccion;
	cliente->_TipoDNI = TipoDNI;
	cliente->_NumDNI = NumeroDNI;
	cliente->_Telefono = Telefono;

	return cliente;
}

Cuenta^ CrearCuenta()
{
	Console::Write("Introduzca el número de la cuenta: ");
	System::String^ Nombre = Console::ReadLine();
	Console::Write("Introduzca el saldo de la cuenta: ");
	double Saldo = Convert::ToDouble(Console::ReadLine());
	Console::WriteLine("Elija tipo de cuenta:\n1.Ahorro\n2.Corriente");
	Cuenta^ cuenta;
	switch (Convert::ToInt32(Console::ReadLine()))
	{
	case 1: {
		cuenta = gcnew CajaAhorro();
		break;
	}
	case 2: {
		CuentaCorriente^ CC = gcnew CuentaCorriente();
		Console::WriteLine("Elija el descubierto de la cuenta corriente: ");
		CC->descubierto = Convert::ToDouble(Console::ReadLine());
		cuenta = CC;
	}
	}
	cuenta->Numero = Nombre;
	cuenta->Saldo = Saldo;

	return cuenta;
}

void ListarClientes(List<Cliente^>^ clientes)
{
	if (clientes->Count > 0)
	{
		int i = 1;
		Console::WriteLine("Clientes inscriptos: ");
		for each (Cliente^ c in clientes)
		{
			Console::WriteLine("{0}.{1}", i, c->_Legajo);
			i++;
		}
	}
}

void ListarCuentas(List<Cuenta^>^ cuentas)
{
	if (cuentas->Count > 0)
	{
		int i = 1;
		Console::WriteLine("Cuentas inscriptas: ");
		for each (Cuenta^ c in cuentas)
		{
			Console::WriteLine("{0}.{1}", i, c->Numero);
			i++;
		}
	}
}

Cliente^ ManejarCliente(List<Cliente^>^ clientes, void(*operacionCliente)(Cliente^))
{
	if (clientes->Count == 0)
	{
		Console::WriteLine("No hay clientes almacenados.");
		return nullptr;
	}
	Console::WriteLine("Seleccione un cliente");
	try
	{
		Cliente^ cliente = clientes->ToArray()[Convert::ToInt32(Console::ReadLine()) - 1];
		if (operacionCliente != nullptr)
			operacionCliente(cliente);
		return cliente;
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error leyendo cliente.");
		return nullptr;
	}
}

Cuenta^ ManejarCuenta(List<Cuenta^>^ cuentas, void(*operacionCuenta)(Cuenta^))
{
	if (cuentas->Count == 0)
	{
		Console::WriteLine("No hay cuentas almacenadas.");
		return nullptr;
	}
	Console::WriteLine("Seleccione una cuenta: ");
	try
	{
		Cuenta^ cuenta = cuentas->ToArray()[Convert::ToInt32(Console::ReadLine()) - 1];
		if (operacionCuenta != nullptr)
			operacionCuenta(cuenta);
		return cuenta;
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Error leyendo cuenta.");
		return nullptr;
	}
}

void DetalleCliente(Cliente^ cliente)
{
	Console::WriteLine("Legajo: {0}\nNombre: {1}\nApellido: {2}\nDirección: {3}\nTeléfono: {4}\nTipo DNI: {5}",
		cliente->_Legajo,
		cliente->_Nombre,
		cliente->_Apellido,
		cliente->_Direccion,
		cliente->_Telefono,
		cliente->_TipoDNI);
	Console::WriteLine("Cuentas disponibles:");
	if (cliente->ListarCuentas()->Count == 0)
	{
		Console::WriteLine("No hay cuentas disponibles.");
	}
	else
	{
		for each (Cuenta^ c in cliente->ListarCuentas())
		{
			Console::WriteLine("No. Cuenta: {0}\tSaldo: {1}", c->Numero, c->Saldo);
		}
	}
}

void DetalleCuenta(Cuenta^ cuenta)
{
	Console::WriteLine("No. Cuenta: {0}\tSaldo disponible: {1}",
		cuenta->Numero,
		cuenta->Saldo);
}

void OperacionCuentas(Cuenta^ cuenta, List<Cuenta^>^ cuentas)
{
	Console::WriteLine("Elija una operación::\n1.Depositar\n2.Extraer\n3.Transferir");
	int seleccion = Convert::ToInt32(Console::ReadLine());
	switch (seleccion)
	{
	case 1: {
		try
		{
			Console::WriteLine("Elija el monto: ");
			cuenta->Depositar(Convert::ToDouble(Console::ReadLine()));
		}
		catch (Exception^ ex)
		{
			Console::WriteLine(ex->Message);
		}
		break;
	}
	case 2: {
		try
		{
			Console::WriteLine("Elija el monto: ");
			cuenta->Extraer(Convert::ToDouble(Console::ReadLine()));
		}
		catch (Exception^ ex)
		{
			Console::WriteLine(ex->Message);
		}
		break;
	}
	case 3: {
		try
		{
			Cuenta^ cuentaATransferir = ManejarCuenta(cuentas, nullptr);
			if (cuenta == cuentaATransferir)
				throw gcnew Exception("Es la misma cuenta.");

			Console::WriteLine("Elija el monto: ");
			cuenta->Extraer(Convert::ToInt32(Console::ReadLine()));
		}
		catch (Exception^ ex)
		{
			Console::WriteLine(ex->Message);
		}
		break;
	}
	default:
		Console::WriteLine("Opción no soportada");
		break;
	}
}

bool LegajoExiste(List<Cliente^>^ clientes, String^ legajo)
{
	bool resultado = false;
	for each (Cliente^ var in clientes)
	{
		if (var->_Legajo == legajo) 
		{
			resultado = true;
			break;
		}
	}
	return resultado;
}


bool CuentaExiste(List<Cuenta^>^ cuentas, String^ noCuenta)
{
	bool resultado = false;
	for each (Cuenta^ var in cuentas)
	{
		if (var->Numero == noCuenta) 
		{
			resultado = true;
			break;
		}
	}
	return resultado;
}
