#include "pch.h"
#include "..\CourseWork\Header.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestCourseWork
{
	TEST_CLASS(UnitTestCourseWork)
	{
	public:
		
		TEST_METHOD(TestMethodDoMatrix)
		{
			string text = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			List list;
			list.stringToList(text);
			int** array = list.creatingMatrix(text);
			int arrayTest[6][6] = {
				{invalidPrice, 3, 3, invalidPrice,invalidPrice,invalidPrice},
				{0, invalidPrice, 2, 3, invalidPrice,invalidPrice },
				{0, 0, invalidPrice, invalidPrice, 2, invalidPrice},
				{invalidPrice, 0 ,invalidPrice, invalidPrice, 4, 2},
				{invalidPrice, invalidPrice, 0 ,0 ,invalidPrice ,3},
				{invalidPrice ,invalidPrice ,invalidPrice, 0, 0, invalidPrice}
			};
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					Assert::IsTrue(arrayTest[i][j] == array[i][j]);
				}
			}
			
		}
		TEST_METHOD(TestMethodMaxIndex)
		{
			string text = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			List list;
			list.stringToList(text);
			Assert::IsTrue(list.maxIndex() == 5);
		}
		TEST_METHOD(TestMethodIndex)
		{
			string text = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			List list;
			list.stringToList(text);
			Assert::IsTrue(list.index("S") == 0);
			Assert::IsTrue(list.index("O") == 1);
			Assert::IsTrue(list.index("P") == 2);
			Assert::IsTrue(list.index("Q") == 3);
			Assert::IsTrue(list.index("R") == 4);
			Assert::IsTrue(list.index("T") == 5);
		}
		TEST_METHOD(TestMethodFind)
		{
			string text = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			List list;
			list.stringToList(text);
			Assert::IsTrue(list.find(0) == "S");
			Assert::IsTrue(list.find(1) == "O");
			Assert::IsTrue(list.find(2) == "P");
			Assert::IsTrue(list.find(3) == "Q");
			Assert::IsTrue(list.find(4) == "R");
			Assert::IsTrue(list.find(5) == "T");
		}
		TEST_METHOD(TestMethodFordFalkerson)
		{
			string graph = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			Assert::IsTrue(AlghoritmFordFalkerson(graph)==5);
		}
	};
}
