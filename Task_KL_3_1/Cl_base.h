#ifndef CL_BASE_H
#define CL_BASE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cl_base 
{
private:
	// Имя объекта
	string objectName = "";

	// Указатель на родителя объекта
	Cl_base* parentPtr = nullptr;

	//Состояние готовности объекта
	bool readiness = false;
	

public:
	//Объект root - "родитель" всех объектов
	static Cl_base* root;

	//Вектор указателей дочерних объектов
	vector<Cl_base*> childrenList;


	//Конструкторы
	Cl_base() { parentPtr = nullptr; };
	Cl_base(string objectName, Cl_base* parentPtr = nullptr);

	//Сетеры
	void setName(string objectName);
	void setParent(Cl_base* parentPtr);
	void setReadiness(long long numericReadiness);

	//Гетеры
	Cl_base* getParent();
	string getName();
	bool getReadiness();

	//Получение указателя на объект через его имя
	Cl_base* getObjectByName(string name);

	//Получение указателя на объект через заданный путь
	Cl_base* getObjectByPath(string path);

	//Вывод дерева объектов
	void printTree(bool isPrintReadiness, unsigned tabLevel = 0);
};

#endif