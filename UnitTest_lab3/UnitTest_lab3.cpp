#include "pch.h"
#include "CppUnitTest.h"
#include"../lab3/Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestlab3
{
	TEST_CLASS(UnitTestlab3)
	{
	public:
		
		TEST_METHOD(Tree_insert_test)
		{
			BST tree;
			tree.insert(1);
			Assert::IsTrue(tree.contains(1));

			tree.insert(2);
			Assert::IsTrue(tree.contains(2));

			tree.insert(3);
			Assert::IsTrue(tree.contains(3));

			tree.insert(54);
			Assert::IsTrue(tree.contains(54));

			tree.insert(987);
			Assert::IsTrue(tree.contains(987));

			tree.insert(599);
			Assert::IsTrue(tree.contains(599));

			tree.insert(0);
			Assert::IsTrue(tree.contains(0));

			Assert::IsTrue(tree.contains(1) && tree.contains(2) && tree.contains(3)
				&& tree.contains(54) && tree.contains(987) && tree.contains(599) && tree.contains(0));
		}

		TEST_METHOD(Tree_remove_test)
		{
			BST tree;
			tree.insert(5);
			tree.insert(6);
			Assert::IsTrue(tree.contains(5) && tree.contains(6));

			tree.remove(6);
			Assert::IsTrue(tree.contains(5));
			Assert::IsFalse(tree.contains(6));

			tree.insert(9);
			Assert::IsTrue(tree.contains(5) && tree.contains(9));

			tree.remove(5);
			Assert::IsFalse(tree.contains(5));
		}
	};
}
