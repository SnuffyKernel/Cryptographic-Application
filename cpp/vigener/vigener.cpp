#include "vigener.h"

vector<int> num(const string& Letter, const string& text) {
	vector<int> num;
	for (char i : text) {
		for (int j = 0; j < Letter.size(); j++) {
			if (i == Letter[j]) {
				num.push_back(j);
				break;
			}
		}
	}
	if (text.size() == num.size()) return num;
	else {
		throw runtime_error("The key or text does not match the alphabet.");
	}
}

vector<int> sum(const string& Letter, const string& key, const string& text, const bool& code) {
	vector<int> keyNum = num(Letter, key);
	vector<int> textNum = num(Letter, text);
	vector<int> newtextNum;
	for (int i = 0, j = 0, sum; i < text.size(); i++, j++) {
		if (j > key.size() - 1) j = 0;

		if (code == 0) {
			sum = textNum[i] + keyNum[j] + 1;
			if (sum > Letter.size()) newtextNum.push_back(sum - Letter.size());
			else newtextNum.push_back(sum);
		}
		else {
			sum = textNum[i] - keyNum[j] - 1;
			if (sum < 0) newtextNum.push_back(sum + Letter.size());
			else newtextNum.push_back(sum);
		}
	}
	return newtextNum;
}

string new_text(string& Letter, string& key, const string& text, const bool& code, const bool& file) {
	try {
		if (Letter == "") Letter = { "!\"#$ % &'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~" };
		if (key == "") key = "gXK6LJRrhPggVDHj";
		vector<int> newtextNum = sum(Letter, key, text, code);
		string newText;
		for (int i : newtextNum) {
			for (int j = 0; j < Letter.size(); j++) {
				if (i == Letter.size()) {
					newText += Letter[0];
					break;
				}
				if (i == j) {
					newText += Letter[j];
					break;
				}
			}
		}

		if (file == 1) {
			ofstream file("Vigener.txt", ios::app);
			if (file.is_open()) {
				if (code == 0) file << "Зашифрованный текст: " << newText << endl;
				else file << "Расшифрованный текст: " << newText << endl;
				file.close();
				cout << "Writing to the file was successful." << endl;
			}
			else throw runtime_error("File opening error.");

		}
		return newText;
	}
	catch (const runtime_error& e) {
		cout << "ERROR: " << e.what() << endl;
		return string("ERROR: ") + e.what();
	}
}
