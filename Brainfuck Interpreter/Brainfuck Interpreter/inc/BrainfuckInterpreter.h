#pragma once
#include <vector>
#include <string>
#include <utility>
#include <stack>

class BrainfuckInterpreter
{
	std::vector<unsigned char> cells{0};
	std::string code;
	std::string input;
	std::string output;
	size_t currentCellIndex = 0;

	size_t currentInstructionIndex = 0;
	std::stack<size_t> loopBeginningIndexes{};

public:
	explicit BrainfuckInterpreter(std::string code = std::string(), std::string input = std::string()) :
		code(std::move(code)),
		input(std::move(input))
	{
	}

	std::string Run();

	std::vector<unsigned char> GetCells() const { return cells; }
	std::string GetCode() const { return code; }
	std::string GetInput() const { return input; }
	std::string GetLastOutput() const { return output; }
	size_t GetCurrentCellIndex() const { return currentCellIndex; }

private:
	void ExecuteInstruction(const char instruction);
	void IncrementDataPointer() { ++currentCellIndex; }
	void DecrementDataPointer() { --currentCellIndex; }
	void IncrementValue() { ++cells[currentCellIndex]; }
	void DecrementValue() { --cells[currentCellIndex]; }
	void OutputValue() { output += cells[currentCellIndex]; }
	void ConsumeInputValue();
	void StartLoop();
	void OmitLoop();
	void EndLoop();
	void AddCellIfNeeded();
};
