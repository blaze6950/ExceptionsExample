#include <iostream>
#include <string>
#include <errno.h>  
#include <stdio.h>
#include <stdexcept>
using namespace std;

#pragma warning(disable:4996)

void errors();

double divide1(double num1, double num2)
{
	if (num2 == 0)
	{
		//cout << "divide by zero" << endl;
		exit(1);
	}

	return num1 / num2;
}
errno_t divide2(double num1, double num2, double& res)
{
	if (num2 == 0)
	{
		//cout << "divide by zero" << endl;
		return EINVAL;
	}
	res = num1 / num2;
	return 0;
}

class divide_by_zero_exception
{
	string _message;
	int _line;
public:
	divide_by_zero_exception(int line)
	{
		_message = "divide by zero";
		_line = line;
		//func = __func__;
	}

	string getMessage()
	{
		return _message;
	}
	
	int getLine()
	{
		return _line;
	}
	
	
};

class divide_by_zero : public invalid_argument
{
public:
	divide_by_zero() : invalid_argument("Divide by zero")
	{			
	}
	
};

double divideException(double num1, double num2)
{
	if (num2 == 0)
		throw divide_by_zero();

	return num1 / num2;
}

void foo()
{
	FILE* file;

	auto err = fopen_s(&file, "test.txt", "w");
	if (err != 0)
		throw runtime_error("file not oppened");

	try
	{
		double num1, num2;
		cout << "Enter num1: ";
		cin >> num1;
		cout << "Enter num2: ";
		cin >> num2;

		double res = divideException(num1, num2);

		char* str = new char[51];

		fputs(_gcvt(num1, 50, str), file);
		fputs(" / ", file);
		fputs(_gcvt(num2, 50, str), file);
		fputs(" = ", file);
		fputs(_gcvt(res, 50, str), file);

		fclose(file);
	}
	catch (divide_by_zero& ex)
	{
		fclose(file);
		throw;
	}

	
}

int main()
{
	/*double num1, num2;
	cout << "Enter num1: ";
	cin >> num1;
	cout << "Enter num2: ";
	cin >> num2;
	
	//cout << "Result: " << divide1(num1, num2) << endl;

	double res;
	auto err = divide2(num1, num2, res);
	if (err == 0)
		cout << "Result: " << res << endl;
	else if (err == EINVAL)
		cout << "divide by zero" << endl;*/

	try
	{
		foo();
	}
	catch (divide_by_zero& ex)
	{
		cout << "divide_by_zero: " << ex.what() << endl;		
	}
	catch (exception& ex)
	{
		cout << "exception: " << ex.what() << endl;
	}
	catch (...)
	{
		cout << "error" << endl;
	}
	
	
	
	
	
	
	
	
	
	
}





void errors()
{
	char path[50], name[50];
	cout << "Enter a path: ";
	cin >> path;
	cout << "Enter a name: ";
	cin >> name;
	strcat(path, name);


	FILE* file = fopen(path, "r");
	if (file == nullptr)
	{
		int err;
		_get_errno(&err);
		if (err == ENOENT)
			cout << "No such file or directory" << endl;
		else if (err == EINVAL)
			cout << "Invalid path name" << endl;
		exit(1);
	}

	char data[255];

	while (!feof(file))
	{
		char* str = fgets(data, 255, file);
		if (str == nullptr)
		{
			int err;
			_get_errno(&err);
			//......
		}
		cout << data;
	}
	cout << endl;
	fclose(file);
}