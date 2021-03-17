#pragma once
#include "Banco.h"
#include "Cuenta.h"
#include "Cliente.h"

using namespace System::IO;
using namespace System::Runtime::Serialization;
using namespace System::Runtime::Serialization::Formatters::Binary;

void GuardarClientes(System::String^ nombreArchivo, List<Cliente^>^ clientes)
{
	FileStream ^ stream;
	try
	{
		stream = gcnew FileStream(nombreArchivo, FileMode::OpenOrCreate, FileAccess::ReadWrite);
		BinaryFormatter^ formatter = gcnew BinaryFormatter();
		formatter->Serialize(stream, clientes);
		stream->Close();
	}
	catch (Exception^ e)
	{
		Console::WriteLine(e);
		stream->Close();
	}
}

void GuardarBanco(System::String^ nombreArchivo, Banco^ banco)
{
	FileStream ^ stream;
	try
	{
		stream = gcnew FileStream(nombreArchivo, FileMode::OpenOrCreate, FileAccess::ReadWrite);
		BinaryFormatter^ formatter = gcnew BinaryFormatter();
		formatter->Serialize(stream, banco);
		stream->Close();
	}
	catch (Exception^ e)
	{
		Console::WriteLine(e);
		stream->Close();
	}
}

void GuardarCuentas(System::String^ nombreArchivo, List<Cuenta^>^ cuentas)
{
	FileStream ^ stream;
	try
	{
		stream = gcnew FileStream(nombreArchivo, FileMode::OpenOrCreate, FileAccess::ReadWrite);
		BinaryFormatter^ formatter = gcnew BinaryFormatter();
		formatter->Serialize(stream, cuentas);
		stream->Close();
	}
	catch (Exception^ e)
	{
		Console::WriteLine(e);
		stream->Close();
	}
}


List<Cliente^>^ LeerClientes(System::String^ nombreArchivo)
{
	FileStream ^ stream;
	try
	{
		stream = gcnew FileStream(nombreArchivo, FileMode::OpenOrCreate, FileAccess::Read);
		BinaryFormatter^ formatter = gcnew BinaryFormatter();
		List<Cliente^> ^ clientes = (List<Cliente^>^)formatter->Deserialize(stream);
		stream->Close();
		return clientes;


	}
	catch (Exception^ e)
	{
		stream->Close();
		return gcnew List<Cliente^>();

	}
}

Banco^ LeerBanco(System::String^ nombreArchivo)
{
	FileStream ^ stream;
	try
	{
		stream = gcnew FileStream(nombreArchivo, FileMode::OpenOrCreate, FileAccess::Read);
		BinaryFormatter^ formatter = gcnew BinaryFormatter();
		Banco^ banco = (Banco^)formatter->Deserialize(stream);
		if (banco == nullptr)
			throw gcnew Exception("Debe de crear un banco nuevo.");
		stream->Close();
		return banco;


	}
	catch (Exception^ e)
	{
		stream->Close();
		Console::Write("Creando banco nuevo, inserte el nombre: ");
		Banco^ banco = gcnew Banco();
		banco->Nombre = Console::ReadLine();
		return banco;
	}
}

List<Cuenta^>^ LeerCuentas(System::String^ nombreArchivo)
{
	FileStream ^ stream;
	try
	{

		stream = gcnew FileStream(nombreArchivo, FileMode::OpenOrCreate, FileAccess::Read);
		BinaryFormatter^ formatter = gcnew BinaryFormatter();
		List<Cuenta^> ^ cuentas = (List<Cuenta^>^)formatter->Deserialize(stream);
		stream->Close();
		return cuentas;
	}
	catch (Exception^ e)
	{
		stream->Close();
		return gcnew List<Cuenta^>();
	}
}


