
#include "Cl_application.h"
#include "Cl_branch.h"
#include "Cl_branch_2.h"
#include "Cl_branch_3.h"
#include "Cl_branch_4.h"
#include "Cl_branch_5.h"

Cl_application::Cl_application(Cl_base* parentPtr)
{
	//Использование сетеров обусловленно закрытостью полей
	Cl_base::root->setParent(parentPtr);
	Cl_base::root->setName("sys_root");
	Cl_base::root->setReadiness(1);
}

//Изменено для КЛ_3_2
void Cl_application::buildTree()
{
	string headName, childName, path;
	int classNumber;

	cin >> headName;

	// Головной объект
	Cl_base* head = new Cl_base(headName);

	cin >> path;
	while (path != "endtree") 
	{
		cin >> childName >> classNumber;

		Cl_base* currentParentPtr = root->childrenList.front()->getObjectByPath(path);

		//Досрочное завершение работы программы
		//если на этапе построения системы объектов возникла ошибка.
		if (currentParentPtr == nullptr)
		{
			cout << "Object tree";
			this->printTree(false);
			cout << "The head object " << path << " is not found";

			exit(1);
		}

		// Создание дочернего объекта определённого класса
		// определяемого введённым номером
		switch (classNumber)
		{
		case 2:
		{
			Cl_base* child = new Cl_branch(childName, currentParentPtr);
			break;
		}

		case 3:
		{
			Cl_base* child = new Cl_branch_2(childName, currentParentPtr);
			break;
		}

		case 4:
		{
			Cl_base* child = new Cl_branch_3(childName, currentParentPtr);
			break;
		}

		case 5:
		{
			Cl_base* child = new Cl_branch_4(childName, currentParentPtr);
			break;
		}

		case 6:
		{
			Cl_base* child = new Cl_branch_5(childName, currentParentPtr);
			break;
		}

		}

		cin >> path;
	}

	return;
}

//Функция запуска ввода готовностей объектов
void Cl_application::enterReadiness()
{
	string objectName;
	long long numericReadiness;
	while (cin >> objectName >> numericReadiness)
	{
		(root->getObjectByName(objectName))->setReadiness(numericReadiness);
	}
}


//Функция навигации по дереву объектов.
//Предлагает на ввод команды SET и FIND:
//установку выбранного объекта и поиска объекта по заданному пути.
void Cl_application::treeNavigation()
{
	Cl_base* settedObjectPtr = root->childrenList.front();
	Cl_base* objectFromPath;

	string command, path;

	cin >> command;

	while (command != "END")
	{
		cout << '\n';
		cin >> path;

		objectFromPath = settedObjectPtr->getObjectByPath(path);

		if (command == "SET")
		{
			if (objectFromPath)
			{
				settedObjectPtr = objectFromPath;
				cout << "Object is set: " << settedObjectPtr->getName();
			}
			else
			{
				cout << "Object is not found: " << settedObjectPtr->getName() << " " << path;
			}
		}

		if (command == "FIND")
		{
			if (objectFromPath)
			{
				cout << path << "     " << "Object name: " << objectFromPath->getName();
			}
			else
			{
				cout << path << "     Object is not found";
			}
		}

		cin >> command;
	}
}


int Cl_application::execApp()
{
	// Вывод построенного дерева;
	cout << "Object tree";
	root->childrenList.front()->printTree(false);

	//Запуск навигации по дереву
	this->treeNavigation();

	return 0;
}
