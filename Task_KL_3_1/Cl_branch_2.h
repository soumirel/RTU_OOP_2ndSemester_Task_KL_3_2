#ifndef CL_BRANCH_2_H
#define CL_BRANCH_2_H

#include "Cl_base.h"

class Cl_branch_2 :
    public Cl_base
{
public:
	Cl_branch_2(string objectName, Cl_base* root) :
		Cl_base(objectName, root) {};
};

#endif