#include "Cliente.h"
#include "Cuenta.h"
#include "DataManager.h"

#define ARCHIVO_CLIENTE "clientes.dat"
#define ARCHIVO_CUENTA "cuentas.dat"

using namespace System;
using namespace System::Collections::Generic;

int EnseniarMenu();
Cliente^ CrearCliente();
Cuenta^  CrearCuenta();
void ListarClientes(List<Cliente^>^);
void ListarCuentas(List<Cuenta^>^);
Cliente^ ManejarCliente(List<Cliente^>^, void(*operacionCliente)(Cliente^));
Cuenta^ ManejarCuenta(List<Cuenta^>^, void(*operacionCuenta)(Cuenta^));
void DetalleCliente(Cliente^);
void DetalleCuenta(Cuenta^);

int main(array<System::String ^> ^args)
{
	int seleccion = 1;
	List <Cliente^>^clientes;
	List <Cuenta^>^cuentas;

	while (seleccion)
	{
		seleccion = EnseniarMenu();

		switch (seleccion)
		{
		case 1:
			clientes = LeerClientes(ARCHIVO_CLIENTE);
			ListarClientes(clientes);
			clientes->Add(CrearCliente());
			GuardarClientes(ARCHIVO_CLIENTE, clientes);
			break;

		case 2:
			cuentas = LeerCuentas(ARCHIVO_CUENTA);
			ListarCuentas(cuentas);
			cuentas->Add(CrearCuenta());
			GuardarCuentas(ARCHIVO_CUENTA, cuentas);
			break;

		case 3:
			clientes = LeerClientes(ARCHIVO_CLIENTE);
			ListarClientes(clientes);
			ManejarCliente(clientes, DetalleCliente);
			break;

		case 4:
			cuentas = LeerCuentas(ARCHIVO_CUENTA);
			ListarCuentas(cuentas);
			ManejarCuenta(cuentas, DetalleCuenta);
			break;

		case 7:
			clientes = LeerClientes(ARCHIVO_CLIENTE);
			ListarClientes(clientes);
			clientes->Remove(ManejarCliente(clientes, nullptr));
			GuardarClientes(ARCHIVO_CLIENTE, clientes);
			break;

		case 8:
			cuentas = LeerCuentas(ARCHIVO_CUENTA);
			ListarCuentas(cuentas);
			cuentas->Remove(ManejarCuenta(cuentas, nullptr));
			GuardarCuentas(ARCHIVO_CUENTA, cuentas);
			break;

		default:
			break;
		}
	}

	return 0;
}

int EnseniarMenu()
{
	Console::WriteLine("Elija una opción disponible en el sistema");
	Console::WriteLine("Seleccionar opción:\n0-Salir\n1-Agregar Cliente\n2-Agregar Cuenta\n3-Leer Cliente\n4-Leer Cuenta\n5-Modificar Cliente\n6-Modificar Cuenta\n7-Dar de baja Cliente\n8-Dar de baja Cuenta");
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
	Cuenta^ cuenta = gcnew Cuenta();
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
}

void DetalleCuenta(Cuenta^ cuenta)
{
	Console::WriteLine("No. Cuenta: {0}\tSaldo disponible: {1}",
		cuenta->Numero,
		cuenta->Saldo);
}
