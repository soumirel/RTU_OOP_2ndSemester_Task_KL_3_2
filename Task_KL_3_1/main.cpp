#include "Cl_application.h"

int main()
{
	Cl_application AppObject;

	//Построение системы объектов
	AppObject.buildTree();

	return AppObject.execApp();
}