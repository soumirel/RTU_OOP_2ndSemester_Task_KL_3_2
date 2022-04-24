#include "Cl_base.h"

// �������� �������-�����������
Cl_base* Cl_base::root = new Cl_base();

//�����������
Cl_base::Cl_base(string objectName, Cl_base* parentPtr)
{
	this->objectName = objectName;
	//���� ��� �� �������� ������
	if (parentPtr)
	{
		setParent(parentPtr);
	}
	else
	{
		//����������� ������ ��� �������� (�������� ������ �����������)
		setParent(root);
	}
}

//����� �����
void Cl_base::setName(string objectName)
{
	this->objectName = objectName;
}

//����� ��������
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

// ������ ��� ���� readines
// ������������� ���������� � ������������ � ��������
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

//����� �������� (���������)
Cl_base* Cl_base::getParent() {
	return parentPtr;
}

//����� �����
string Cl_base::getName() {
	return objectName;
}

//����� ����������
bool Cl_base::getReadiness()
{
	return readiness;
}

//�������� ��������� �� ������ �� �����
Cl_base* Cl_base::getObjectByName(string objectName)
{

	/* �������� ��������� � ������� �������� - �������� �� ���� �������� ��������
	*  ����� �� �������� ���������� ����� ����������� ��� �������� �������
	*  �.� ������ ������� ���.�������� = 0. �������� �������� �� �������� -
	*  ��������� �� ������, ������� ��� ��������� � ������ ��������. */
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
	//���� ��������� �� ��������� ������.
	if (path == ".")
	{
		return this;
	}

	//���� ��������� �� �������� ������.
	if (path == "/")
	{
		return root->childrenList.at(0);
	}

	size_t pathSize = path.size();

	//���� ��������� �� ���������� ��� �� ������ ��������.
	if (path.at(0) == '/' && path.at(1) == '/')
	{
		return (root->getObjectByName(path.substr(2, pathSize)));
	}

	string currentObjectName;
	vector<string> objectsNameFromPath;

	//���� ���� ���������� - ������ ����������� 
	// �� ������ ������� � 1��� �������.
	size_t iter = 0;
	bool isAbsolutePath = false;
	if (path.at(0) == '/')
	{
		isAbsolutePath = true;
		objectsNameFromPath.push_back(root->childrenList.at(0)->getName());
		iter = 1;
	}

	//��������� ������ �� ����� ��������
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

	//����������� ������������� ��������� ����.
	//�������� �� ����������� ��������-������ �� ������ ��������.
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
	// ������ ���������� ���������. ������� ������ - ��������� ���.��������
	// ����� ������� ����� �� ����� ������ � �� ����� ������ � ������������
	// ��� �� ���� �������� �������� - ������� �� isPrintReadiness

	cout << '\n';
	//�� ����� ��������� � �� ������ �������� �������� tabLevel
	for (unsigned i = 0; i < tabLevel; i++)
	{
		cout << "    ";
	}
	cout << this->getName() << (isPrintReadiness ? (this->getReadiness() ? " is ready" : " is not ready") : "");


	//������� ������ �� ��������
	if (childrenList.empty())
	{
		return;
	}

	for (size_t i = 0; i < childrenList.size(); i++)
	{
		//����������� ����� � ����������� �������� ������ ���������
		childrenList[i]->printTree(isPrintReadiness, tabLevel + 1);
	}
}