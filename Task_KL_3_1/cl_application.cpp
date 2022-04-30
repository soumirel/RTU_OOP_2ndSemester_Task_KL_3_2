
#include "Cl_application.h"
#include "Cl_branch.h"
#include "Cl_branch_2.h"
#include "Cl_branch_3.h"
#include "Cl_branch_4.h"
#include "Cl_branch_5.h"

Cl_application::Cl_application(Cl_base* parentPtr)
{
	//������������� ������� ������������ ����������� �����
	Cl_base::root->setParent(parentPtr);
	Cl_base::root->setName("sys_root");
	Cl_base::root->setReadiness(1);
}

//�������� ��� ��_3_2
void Cl_application::buildTree()
{
	string headName, childName, path;
	int classNumber;

	cin >> headName;

	// �������� ������
	Cl_base* head = new Cl_base(headName);

	cin >> path;
	while (path != "endtree") 
	{
		cin >> childName >> classNumber;

		Cl_base* currentParentPtr = getObjectByPath(path);

		//��������� ���������� ������ ���������
		//���� �� ����� ���������� ������� �������� �������� ������.
		if (currentParentPtr == nullptr)
		{
			cout << "Object tree";
			this->printTree(false);
			cout << "The head object " << path << " is not found";

			exit(1);
		}

		// �������� ��������� ������� ������������ ������
		// ������������� �������� �������
		switch (classNumber)
		{
		case 2:
		{
			Cl_base* child = new Cl_branch(childName, currentParentPtr);
			break;
		}

		case 3:
		{
			if (childName == "object_7")
			{
				cout << "flag!";
			}
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

//������� ������� ����� ����������� ��������
void Cl_application::enterReadiness()
{
	string objectName;
	long long numericReadiness;
	while (cin >> objectName >> numericReadiness)
	{
		(root->getObjectByName(objectName))->setReadiness(numericReadiness);
	}
}


//������� ��������� �� ������ ��������.
//���������� �� ���� ������� SET � FIND:
//��������� ���������� ������� � ������ ������� �� ��������� ����.
void Cl_application::treeNavigation()
{
	Cl_base* setedObjectPtr = root->childrenList.at(0);
	Cl_base* objectFromPath;

	string command, path;

	cin >> command;

	while (command != "END")
	{
		cout << '\n';
		cin >> path;

		objectFromPath = setedObjectPtr->getObjectByPath(path);

		if (command == "SET")
		{
			if (objectFromPath)
			{
				setedObjectPtr = objectFromPath;
				cout << "Object is set: " << setedObjectPtr->getName();
			}
			else
			{
				cout << "Object is not found: " << setedObjectPtr->getName() << " " << path;
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
	// ����� ������������ ������;
	cout << "Object tree";
	root->childrenList.at(0)->printTree(false);

	//������ ��������� �� ������
	this->treeNavigation();

	return 0;
}