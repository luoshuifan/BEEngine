#pragma once
#include "BE.h"
#include "RenderGraphFwd.h"

BE_BEGIN

class BERDGResource
{
public:
	BERDGResource(const BERDGResource&) = delete;
	virtual ~BERDGResource() = default;

	BERDGResource* GetRHI()const
	{
		return resourceRHI;
	}


	const String name;

protected:

	BERDGResource* resourceRHI = nullptr;

private:

};

class BERDGViewableResource
	: public BERDGResource
{
public:


private:


};



BE_END
