#pragma once

//class ITestOutClass
//{
//public:
//	virtual void FuncA() abstract;
//	virtual bool FuncB() abstract;
//
//};

__interface ITestOutClass
{
public:
	void FuncA() abstract;
	bool FuncB() abstract;

};

class TestOutClass : public ITestOutClass
{
public:
	TestOutClass();
	virtual ~TestOutClass();

	virtual void FuncA() override;
	virtual bool FuncB() override;

	int a;
private:
	bool b;
};

class TestOutStruct
{
public:
	TestOutStruct() {};
	~TestOutStruct() {};

	void FuncA() {};
	bool FuncB() {};

	int a;

	bool b;
};

