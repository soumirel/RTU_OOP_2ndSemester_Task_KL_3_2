#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H

#include  "Cl_base.h"

class Cl_application : public Cl_base {
public:
	//Конструктор
	Cl_application(Cl_base* parentPtr = nullptr);

	//Построение дерева объектов (ввод)
	void buildTree();

	//Установка состояний готовности для объектов
	void enterReadiness();

	//Осуществление навигации по дереву путём ввода команд "SET" и "FIND"
	void treeNavigation();

	//"Запуск приложения"
	int execApp();
	
};

#endif
