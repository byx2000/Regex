#include <iostream>
#include "Test/Test.h"
#include "Pattern/Pattern.h"
#include "Parser/RegParser.h"
#include "Common/Charset.h"

using namespace std;

int main()
{
	//�ڴ�й©���
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//��Ԫ����
	PatternTest::run();

	return 0;
}