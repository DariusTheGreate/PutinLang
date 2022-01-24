#ifndef _COMPILER_
#define _COMPILER_

/* LOTS of unnecesery copying. Realy bad needs to be fixed*/

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <tuple>
#include <cstdio>
#include <sstream>
#include <cctype>
#include <algorithm>

#include "enums.h"
#include "VM.h"

class Compiler {
private:
	class Token;
	using Tokens = std::vector<Token>;
public:
	void compile(const char* filename) {
		std::fstream file;
		file.open(filename, std::ios::in);
		
		if(!file){
			std::cout << "dont";
		}

		const int buffer_size = 64;

		char buffer[buffer_size];
		int i = 0;
		char ch;
		
		Tokens tokens;

		bool commentSection = false;

		while(1){
			file >> std::noskipws >> ch;

			if (file.eof())
				break;
			
			if(commentSection)
				continue;

			if(ch == '\n')
				continue;

			if(ch == '|')
				commentSection = !commentSection;

			if(ch == ';'){
				tokens.push_back(Token(std::string(buffer)));
				memset(&buffer, 0, buffer_size);
				i = 0;
				continue;
			}
			
			buffer[i++] = ch;
		}

		processTokens(tokens);
	}	

	void processTokens(const Tokens& tokens) {
		//generate bytecode?
		for(size_t i = 0; i < tokens.size(); ++i){
			if(tokens[i].identifyTokenType() == TokenType::VariableDeclaration)
				vm.AcceptObject(tokens[i].checkForVariableDeclaration());
			if(tokens[i].identifyTokenType() == TokenType::VariableDeletion)
				vm.DeleteObject(tokens[i].checkForVariableDeletion());

			std::cout << "\n";
			
			std::cout << "Token: ";
			tokens[i].printToken();

			std::cout << "\n";
		}
	}

private:
	VM vm;

	class Token {
		std::string token;
	public:
		Token(const std::string& str) noexcept : token(str) {}

		Object checkForVariableDeclaration() const {
			std::pair<StandartTokenVariableType, int> type = checkForType();
			
			auto Name = getTypeName(type.second);
			std::cout << "Name: " << Name << "\n";

			auto MemoryType = getMemoryType();
			if(MemoryType == MemoryType::StackType)
				std::cout << "MemoryType: " << "stack\n";

			if(MemoryType == MemoryType::HeapType)
				std::cout << "MemoryType: " << "heap\n";
			
			auto Type = type.first;
			int Value = 0;
			
			if(Type == StandartTokenVariableType::Int){
				std::cout << "Type: Int\n";
				Value = GetIntValue();
			}

			return Object(Value, MemoryType, Name);
		}

		TokenType identifyTokenType() const{
			if(token.find("free(") != std::string::npos)
				return TokenType::VariableDeletion;
			if(token.find("malloc") != std::string::npos)
				return TokenType::VariableDeclaration;
			if(token.find("type") != std::string::npos)
				return TokenType::StructDeclaration;
			return TokenType::Undefined;	
		}

		std::string checkForVariableDeletion() const {
			if(token.find("free(") == std::string::npos)
				return "";

			int startPos = token.find("free(");

			int endPos = token.find(")");
			//cringe
			std::cout << "Name: " << token.substr(startPos + 5, endPos-5) << "\n";
			return token.substr(startPos + 5, endPos - 5);
		}

		MemoryType getMemoryType() const {
			return token.find("malloc") != std::string::npos ? MemoryType::HeapType : MemoryType::StackType;
		}

		int GetIntValue() const {
			std::string value = getValue();
			std::cout << "value -> " << value << "\n";
			return 0;
		}

		std::string getTypeName(int pos) const {
			std::string delimiter = "=";
			std::string str = token.substr(pos, token.find(delimiter)); 
			remove_repeated_characters(str);
			auto strVec = split(str, ' ');
			if(strVec.size() > 1)
				str = strVec[1];
			str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
			return str;
		}

		std::string getValue() const {
			auto str_vec = split(token, '=');
			std::string str = "";

			if(str_vec.size() > 1)
				str = str_vec[1];

			//remove_repeated_characters(str);
			return str;
		}

		void remove_repeated_characters(std::string& s) const{
			s.erase(std::unique(s.begin(), s.end()), s.end());
		}

		std::vector<std::string> split(const std::string& s, char delimiter) const {
			std::vector<std::string> tokens;
			std::string token;
			std::istringstream tokenStream(s);
			
			while (std::getline(tokenStream, token, delimiter))
			{
				tokens.push_back(token);
			}
			
			return tokens;
		}

		std::pair<StandartTokenVariableType, int> checkForType() const {
			int pos = 0;
			if(token.find("int") != std::string::npos){
				return std::make_pair(StandartTokenVariableType::Int, token.find("int") + 3);
			}
			//...
			return std::make_pair(StandartTokenVariableType::NotStandartType, 0);
		}

		void printToken() const {
			std::cout << token;
		}
	};
};

#endif
