#include "../stdafx.h"
#include "CppUnitTest.h"
#include "../../Brainfuck Interpreter/inc/BrainfuckInterpreter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using std::string;

TEST_CLASS(UnitTests)
{
public:
	TEST_METHOD(InitializesCorrectly)
	{
		string code = "><";
		string input = "test";
		BrainfuckInterpreter test(code, input);
		Assert::AreEqual(code, test.GetCode());
		Assert::AreEqual(input, test.GetInput());
	}

	TEST_METHOD(IncrementsDataPointer)
	{
		string code = ">>";
		BrainfuckInterpreter test(code);
		test.Run();
		Assert::AreEqual(size_t(2), test.GetCurrentCellIndex());
		Assert::AreEqual(size_t(3), test.GetCells().size());
	}

	TEST_METHOD(DecrementsDataPointer)
	{
		string code = "><";
		BrainfuckInterpreter test(code);
		test.Run();
		Assert::AreEqual(size_t(0), test.GetCurrentCellIndex());
		Assert::AreEqual(size_t(2), test.GetCells().size());
	}

	TEST_METHOD(IncrementsValue)
	{
		string code = "++";
		BrainfuckInterpreter test(code);
		test.Run();
		Assert::AreEqual(unsigned char(2), test.GetCells()[0]);
	}

	TEST_METHOD(DecrementsValue)
	{
		string code = "+++-";
		BrainfuckInterpreter test(code);
		test.Run();
		Assert::AreEqual(unsigned char(2), test.GetCells()[0]);
	}

	TEST_METHOD(OutputsValue)
	{
		string code = "+.";
		BrainfuckInterpreter test(code);
		Assert::AreEqual(unsigned char(1), unsigned char(test.Run()[0]));
	}

	TEST_METHOD(ConsumesInput)
	{
		string code = ",.";
		string input = "c";
		BrainfuckInterpreter test(code, input);
		Assert::AreEqual('c', test.Run()[0]);
	}

	TEST_METHOD(GivesCorrectOutputForBasicInstructionsCombined)
	{
		string code = "+.>,-.";
		string input = "c";
		BrainfuckInterpreter test(code, input);
		string output = test.Run();
		Assert::AreEqual(unsigned char(1), unsigned char(output[0]));
		Assert::AreEqual('b', output[1]);
	}

	TEST_METHOD(HandlesSimpleLoop)
	{
		string code = "+++[>+<-]";
		BrainfuckInterpreter test(code);
		test.Run();
		auto cells = test.GetCells();
		Assert::AreEqual(unsigned char(0), cells[0]);
		Assert::AreEqual(unsigned char(3), cells[1]);
	}

	TEST_METHOD(HandlesDoubleLoop)
	{
		string code = "+++[>++[>+<-]<-]";
		BrainfuckInterpreter test(code);
		test.Run();
		auto cells = test.GetCells();
		Assert::AreEqual(unsigned char(0), cells[0]);
		Assert::AreEqual(unsigned char(0), cells[1]);
		Assert::AreEqual(unsigned char(6), cells[2]);
		Assert::AreEqual(size_t(3), cells.size());
	}

	TEST_METHOD(HandlesOverflow)
	{
		string code = ",+";
		string input{char(255)};
		BrainfuckInterpreter test(code, input);
		test.Run();
		Assert::AreEqual(unsigned char(0), test.GetCells()[0]);
	}

	TEST_METHOD(HandlesUnderflow)
	{
		string code = ",-";
		string input{char(0)};
		BrainfuckInterpreter test(code, input);
		test.Run();
		Assert::AreEqual(unsigned char(255), test.GetCells()[0]);
	}

	//Test from Codewars. Author: ssineriz.
	TEST_METHOD(EchoesUntil255)
	{
		string code = ",+[-.,+]";
		string input = "codewars" + string(1, char(255));
		BrainfuckInterpreter test(code, input);
		Assert::AreEqual(string("codewars"), test.Run());
	}

	//Test from Codewars. Author: ssineriz.
	TEST_METHOD(EchoesUntil0)
	{
		string code = ",[.[-],]";
		string input = "codewars" + string(1, char(0));
		BrainfuckInterpreter test(code, input);
		Assert::AreEqual(string("codewars"), test.Run());
	}

	//Test from Codewars. Author: ssineriz.
	TEST_METHOD(MultipliesTwoNumbers)
	{
		string code = ",>,<[>[->+>+<<]>>[-<<+>>]<<<-]>>.";
		string input{char(7), char(3)};
		BrainfuckInterpreter test(code, input);
		Assert::AreEqual(string(1, char(21)), test.Run());
	}

	TEST_METHOD(OmitsLoop)
	{
		string code = "[],.";
		string input{'c'};
		BrainfuckInterpreter test(code, input);
		test.Run();
		Assert::AreEqual(size_t(0), test.GetCurrentCellIndex());
	}

	//Test code source: http://esoteric.sange.fi/brainfuck/bf-source/prog/fibonacci.txt
	TEST_METHOD(ExecutesLargerCode)
	{
		string code =
			"+++++++++++>+>>>>++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++<<<<<<[>[>>>>>>+>+<<<<<<<-]>>>>>>>[<<<<<<<+>>>>>>>-]<[>++++++++++[-<-[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<[>>>+<<<-]>>[-]]<<]>>>[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<+>>[-]]<<<<<<<]>>>>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]++++++++++<[->-<]>++++++++++++++++++++++++++++++++++++++++++++++++.[-]<<<<<<<<<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<-[>>.>.<<<[-]]<<[>>+>+<<<-]>>>[<<<+>>>-]<<[<+>-]>[<+>-]<<<-]";
		BrainfuckInterpreter test(code);
		Assert::AreEqual(string("1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89"), test.Run());
	}
};
