#include "Cl_base.h"

// Создание объекта-прародителя
Cl_base* Cl_base::root = new Cl_base();

//Конструктор
Cl_base::Cl_base(string objectName, Cl_base* parentPtr)
{
	this->objectName = objectName;
	//Если это не головной объект
	if (parentPtr)
	{
		setParent(parentPtr);
	}
	else
	{
		//Привязываем объект как головной (дочерний объект прародителя)
		setParent(root);
	}
}

//Сетер имени
void Cl_base::setName(string objectName)
{
	this->objectName = objectName;
}

//Сетер родителя
void Cl_base::setParent(Cl_base* parentPtr)
{
	if (this->parentPtr)
	{
		const size_t size = this->parentPtr->childrenList.size();
		for (size_t i = 0; i < size; i++)
		{
			if (this->parentPtr->childrenList.at(i) == this)
			{
				this->parentPtr->childrenList.erase(this->parentPtr->childrenList.begin() + i);
				break;
			}
		}
	}

	if (parentPtr)
	{
		parentPtr->childrenList.push_back(this);
	}

	this->parentPtr = parentPtr;
}

// Сеттер для поля readines
// Устанавливает готовность в соответствии с заданием
void Cl_base::setReadiness(long long numericReadiness) 
{
	if (numericReadiness)
	{
		Cl_base* tempParentPtr = this->parentPtr;
		while (tempParentPtr)
		{
			if (!(tempParentPtr->getReadiness()))
			{
				return;
			}
			tempParentPtr = tempParentPtr->getParent();
		}
		this->readiness = true;
	}
	return;
}

//Гетер родителя (указатель)
Cl_base* Cl_base::getParent() {
	return parentPtr;
}

//Гетер имени
string Cl_base::getName() {
	return objectName;
}

//Гетер готовности
bool Cl_base::getReadiness()
{
	return readiness;
}

//Получить указатель на объект по имени
Cl_base* Cl_base::getObjectByName(string objectName)
{

	/* Получаем указатель с помощью рекурсии - проходим по всем дочерним объектам
	*  Выход из рекурсии происходит когда закончились все дочерние объекты
	*  т.е длинна массива доч.объектов = 0. Выходное значение из рекурсии -
	*  указатель на объект, который был последним в вызове рекурсии. */
	for (size_t i = 0; i < childrenList.size(); i++)
	{
		if (childrenList[i]->getObjectByName(objectName)->getName() == objectName)
		{
			return childrenList[i]->getObjectByName(objectName);
		}
	}
	return this;
}

Cl_base* Cl_base::getObjectByPath(string path)
{
	//Путь указывает на выбранный объект.
	if (path == ".")
	{
		return this;
	}

	//Путь указывает на корневой объект.
	if (path == "/")
	{
		return root->childrenList.front();
	}

	size_t pathSize = path.size();

	//Путь указывает на уникальное имя на дереве объектов.
	if (path.front() == '/' && path.at(1) == '/')
	{
		return (root->getObjectByName(path.substr(2)));
	}

	//Разбиение строки на имена объектов

	size_t iter = 0;
	Cl_base* currentObject = this;
	size_t currentChildrenListSize = currentObject->childrenList.size();
	string nextObjectName = "";
	if (path.front() == '/')
	{
		iter = 1;
	}

	bool isFoundNextObject = false;
	for (; iter <= pathSize; iter++)
	{
		if (iter == pathSize || path.at(iter) == '/')
		{
			isFoundNextObject = false;
			currentChildrenListSize = currentObject->childrenList.size();

			for (size_t j = 0; j < currentChildrenListSize; j++)
			{
				if (currentObject->childrenList.at(j)->getName() == nextObjectName)
				{
					currentObject = currentObject->childrenList.at(j);
					isFoundNextObject = true;
					break;
				}
			}

			if (isFoundNextObject == false)
			{
				return nullptr;
			}

			nextObjectName = "";
		}
		else
		{
			nextObjectName += path.at(iter);
		}
	}

	return currentObject;
}


void Cl_base::printTree(bool isPrintReadiness, unsigned tabLevel) {
	// Дерево печатается рекурсией. Условие выхода - отсутсвие доч.объектов
	// Метод отвеает сразу за вывод дерева и за вывод деерва с готовностями
	// Что из двух деревьев выводить - зависит от isPrintReadiness

	cout << '\n';
	//За вывод табуляции и ее длинны отвечает параметр tabLevel
	for (unsigned i = 0; i < tabLevel; i++)
	{
		cout << "    ";
	}
	cout << this->getName() << (isPrintReadiness ? (this->getReadiness() ? " is ready" : " is not ready") : "");


	//Условие выхода из рекурсии
	if (childrenList.empty())
	{
		return;
	}

	for (size_t i = 0; i < childrenList.size(); i++)
	{
		//Рекурсивный вызов с увеличением значения уровня табуляции
		childrenList[i]->printTree(isPrintReadiness, tabLevel + 1);
	}
}