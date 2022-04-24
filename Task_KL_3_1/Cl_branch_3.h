#ifndef CL_BRANCH_3_H
#define CL_BRANCH_3_H

#include "Cl_base.h"

class Cl_branch_3 :
    public Cl_base
{
public:
	Cl_branch_3(string objectName, Cl_base* root) :
		Cl_base(objectName, root) {};
};

#endif