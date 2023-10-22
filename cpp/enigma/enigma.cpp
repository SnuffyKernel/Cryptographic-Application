#include "enigma.h"

char cript(string& rot, string& alf, char symbol) {
	for (uint8_t index = 0; index < rot.size(); index++) {
		if (symbol == rot[index]) {
			if (index >= alf.size()) throw runtime_error("The alphabet is smaller than the components");
			return alf[index];
		}
		if (index + 1 == rot.size()) throw runtime_error("The symbol \"" + string(1, symbol) + "\" does not correspond to one of the components");
	}
}

void permutation(string& rot) {
	rot.push_back(rot[0]);
	rot = rot.substr(1);
}

string enigma(string alf, string rot1, string rot2, string rot3, string reflector, const string text, const bool file) {
	try {
		if (alf == "") alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		if (rot1 == "") rot1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
		if (rot2 == "") rot2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
		if (rot3 == "") rot3 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
		if (reflector == "") reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
		if (text == "") throw runtime_error("Enter a message");
		string symbol;
		uint8_t scrolling = 0;
		for (char letter : text) {
			symbol.push_back(cript(alf, rot1, cript(alf, rot2, cript(alf, rot3, cript(reflector, alf, cript(rot3, alf, cript(rot2, alf, cript(rot1, alf, letter))))))));
			permutation(rot1);
			if (scrolling % rot1.size() == 0) {
				permutation(rot2);
				if (scrolling % (rot2.size() * rot1.size()) == 0) {
					permutation(rot3);
				}
			}
			scrolling++;
		}
		if (file == 1) {
			ofstream file("Enigma.txt", ios::app);
			if (file.is_open()) {
				file << "Обработанный текст: " << symbol << endl;
				file.close();
				cout << "Writing to the file was successful." << endl;
			}
			else throw runtime_error("File opening error.");

		}
		return symbol;
	}
	catch (const runtime_error& e) {
		cout << "ERROR: " << e.what() << endl;
		return string("ERROR: ") + e.what();
	}
}
