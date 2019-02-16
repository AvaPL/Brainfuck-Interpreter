#include "../stdafx.h"
#include "../inc/BrainfuckInterpreter.h"

using std::string;

std::string BrainfuckInterpreter::Run()
{
	for (; currentInstructionIndex < code.size(); ++currentInstructionIndex)
	{
		ExecuteInstruction(code[currentInstructionIndex]);
	}
	return output;
}

void BrainfuckInterpreter::ExecuteInstruction(const char instruction)
{
	switch (instruction)
	{
	case '>':
		IncrementDataPointer();
		AddCellIfNeeded();
		break;
	case '<':
		DecrementDataPointer();
		break;
	case '+':
		IncrementValue();
		break;
	case '-':
		DecrementValue();
		break;
	case '.':
		OutputValue();
		break;
	case ',':
		ConsumeInputValue();
		break;
	case '[':
		StartLoop();
		break;
	case ']':
		EndLoop();
		break;
	default:
		break;
	}
}

void BrainfuckInterpreter::ConsumeInputValue()
{
	if (input.empty()) return;
	cells[currentCellIndex] = input.front();
	input.erase(input.begin());
}

void BrainfuckInterpreter::StartLoop()
{
	if (cells[currentCellIndex] != 0)
		loopBeginningIndexes.push(currentInstructionIndex);
	else
		OmitLoop();
}

void BrainfuckInterpreter::OmitLoop()
{
	size_t closingBracesNeeded = 1;
	while (closingBracesNeeded > 0)
	{
		++currentInstructionIndex;
		if (code[currentInstructionIndex] == '[') ++closingBracesNeeded;
		else if (code[currentInstructionIndex] == ']') --closingBracesNeeded;
	}
}

void BrainfuckInterpreter::EndLoop()
{
	if (cells[currentCellIndex] != 0)
		currentInstructionIndex = loopBeginningIndexes.top();
	else
		loopBeginningIndexes.pop();
}

void BrainfuckInterpreter::AddCellIfNeeded()
{
	if (currentCellIndex == cells.size())
		cells.push_back(0);
}
