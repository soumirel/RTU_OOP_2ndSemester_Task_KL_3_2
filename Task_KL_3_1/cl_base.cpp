#include "Cl_base.h"

// Создание объекта-прородителя
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
		return root->childrenList.at(0);
	}

	size_t pathSize = path.size();

	//Путь указывает на уникальное имя на дереве объектов.
	if (path.at(0) == '/' && path.at(1) == '/')
	{
		return (root->getObjectByName(path.substr(2, pathSize)));
	}

	string currentObjectName;
	vector<string> objectsNameFromPath;

	//Если путь абсолютный - строка разбивается 
	// на токены начиная с 1ого символа.
	size_t iter = 0;
	bool isAbsolutePath = false;
	if (path.at(0) == '/')
	{
		isAbsolutePath = true;
		objectsNameFromPath.push_back(root->childrenList.at(0)->getName());
		iter = 1;
	}

	//Разбиение строки на имена объектов
	for (; iter < pathSize; iter++)
	{
		if (path.at(iter) == '/')
		{
			objectsNameFromPath.push_back(currentObjectName);
			currentObjectName = "";
		}
		else
		{
			currentObjectName += path.at(iter);
		}
	}
	objectsNameFromPath.push_back(currentObjectName);

	//Утверждение корректоности введённого пути.
	//Проверка по зависимости родитель-ребёнок на дереве иерархии.
	Cl_base* currentObject = nullptr;
	size_t objectsNumber = objectsNameFromPath.size();
	bool isFindNextObject;

	for (size_t i = 0; i < objectsNumber; i++)
	{
		if (i == 0)
		{
			if (isAbsolutePath)
			{
				currentObject = root->childrenList.at(0);
			}
			else
			{
				currentObject = root->getObjectByName(objectsNameFromPath.at(0));
			}
		}
		else
		{
			isFindNextObject = false;
			size_t currentSize = currentObject->childrenList.size();

			for (size_t j = 0; j < currentSize; j++)
			{
				if (currentObject->childrenList.at(j)->getName() == objectsNameFromPath.at(i))
				{
					currentObject = currentObject->childrenList.at(j);
					isFindNextObject = true;
					break;
				}
			}

			if (!isFindNextObject)
			{
				return nullptr;
			}
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