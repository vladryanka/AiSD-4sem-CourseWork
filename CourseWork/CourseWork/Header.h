#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int invalidPrice = INT_MAX;

string read()
{
	string text = "";
	string newText;
	ifstream creat;
	char ch;
	creat.open("Net.txt");

	while (!creat.eof()) {
		creat.get(ch);

		text += ch;
	}
	creat.close();
	newText = text.substr(0, text.length() - 1);
	return newText;
}

class List
{
private:
	struct Node
	{
		string name;
		Node* next = NULL;
	};
	Node* head;
	Node* tail;
public:
	List()
	{
		head = tail = NULL;
	}

	void add(string name)
	{
		if (head == NULL)
		{
			Node* buffer = new Node;
			buffer->name = name;
			buffer->next = NULL;
			head = tail = buffer;
		}
		else
		{
			Node* buffer = head;
			Node* prev = head;
			while (buffer != NULL)
			{
				prev = buffer;
				buffer = buffer->next;
			}
			buffer = new Node;
			buffer->name = name;
			buffer->next = NULL;
			prev->next = buffer;
			tail = buffer;
		}
	}
	bool check(string text)
	{
		Node* buffer = head;
		bool i = false;
		while (buffer != NULL)
		{
			if (buffer->name == text)
			{
				i = true;
				break;
			}
			buffer = buffer->next;
		}
		return i;
	}
	void print()
	{
		Node* buffer = head;
		while (buffer != NULL)
		{
			cout << buffer->name << endl;
			buffer = buffer->next;
		}
	}
	Node* stringToList(string text)
	{
		int i = 0;
		string stringText = "";
		while (i != text.length())
		{
			while (text[i] != ' ')
			{
				if (text[i] <= 90 && text[i] >= 65 || text[i] <= 57 && text[i] >= 48)
				{
					stringText += text[i];
				}
				if (text[i] == '\n')
				{
					stringText = "";
				}
				i++;
				if (i == text.length())
				{
					break;
				}
			}
			if (i == text.length())
			{
				break;
			}
			i++;
			if (!check(stringText))
				add(stringText);
			stringText = "";
		}
		Node* buffer = head;
		return buffer;
	}
	int** creatingMatrix(string text)
	{
		int i = 0;
		int** array = new int* [0];
		array = new int* [maxIndex() + 1];
		for (int count = 0; count <= maxIndex(); count++)
			array[count] = new int[maxIndex()];
		for (int count_row = 0; count_row <= maxIndex(); count_row++)
			for (int count_column = 0; count_column <= maxIndex(); count_column++)
				array[count_row][count_column] = invalidPrice;
		i = 0;
		string stringText = "";
		string vertex1 = "";
		int index1 = 0;
		string vertex2 = "";
		int index2 = 0;
		int data1 = 0;
		int data2 = 0;
		while (1)
		{
			while (text[i] != ' ')
			{
				if (text[i] <= 90 && text[i] >= 65 || text[i] <= 57 && text[i] >= 48)
				{
					stringText += text[i];
				}

				if (text[i] == '\n')
				{
					break;
				}
				i++;
				if (i == text.length())
				{
					break;
				}
			}
			if (vertex1 == "")
			{
				vertex1 = stringText;
				index1 = index(vertex1);
				stringText = "";
			}
			else if (vertex2 == "")
			{
				vertex2 = stringText;
				index2 = index(stringText);
				stringText = "";
			}
			if (stringText != vertex1 && stringText != vertex2 && stringText != "")
			{
				data1 = stoi(stringText);
				data2 = 0;
				stringText = "";
			}
			if (data1 != 0 && index1 != -1 && index2 != -1)
			{
				array[index1][index2] = data1;
				array[index2][index1] = data2;
				data1 = data2 = 0;
				index1 = index2 = -1;
				vertex1 = vertex2 = "";
			}
			i++;
			if (i >= text.length())
				break;
		}
		cout << "Initial network matrix:" << endl;
		printMatrix(array);
		return array;
	}
	string find(int index)
	{
		Node* buffer = head;
		int i = 0;
		while (buffer != NULL)
		{
			if (i == index)
			{
				break;
			}
			else {
				buffer = buffer->next;
				i++;
			}
		}
		if (buffer != NULL)
			return buffer->name;
	}
	void printMatrix(int** arrayNew)
	{
		for (int i = 0; i <= maxIndex(); i++)
		{
			for (int j = 0; j <= maxIndex(); j++)
			{
				if (arrayNew[i][j] != invalidPrice)
					cout << arrayNew[i][j] << " ";
				else cout << "N ";
			}
			cout << endl;
		}
		cout << endl;
	}
	int index(string text)
	{
		Node* buffer = head;
		int i = 0;
		while (buffer != NULL)
		{
			if (buffer->name == text)
			{
				break;
			}
			buffer = buffer->next;
			i++;
		}
		return i;
	}
	int maxIndex()
	{
		Node* buffer = head;
		int i = 0;
		while (buffer != NULL)
		{
			buffer = buffer->next;
			i++;
		}
		return i - 1;
	}
};

int AlghoritmFordFalkerson(string graph)
{
	List list;
	list.stringToList(graph);
	int stream = invalidPrice;
	int maxF = 0;
	int check = false;
	int check2 = false;
	int** checkMatrix = new int* [0];
	checkMatrix = new int* [list.maxIndex() + 1];
	for (int count = 0; count <= list.maxIndex(); count++)
		checkMatrix[count] = new int[list.maxIndex()];
	for (int count_row = 0; count_row <= list.maxIndex(); count_row++)
		for (int count_column = 0; count_column <= list.maxIndex(); count_column++)
			checkMatrix[count_row][count_column] = 0;
	int num = 0;
	bool check3 = false;
	int** array = list.creatingMatrix(graph);

	for (int i = 0; i < list.maxIndex(); i++)
	{
		for (int j = 0; j < list.maxIndex(); j++)
		{
			stream = invalidPrice;
			int numI = i;
			int numJ = j;
			while (j != list.maxIndex() + 1)
			{
				if (array[i][j] != invalidPrice && array[i][j] != 0 && checkMatrix[i][j] == 0)
				{
					if (array[i][j] < stream)
						stream = array[i][j];
					check = true;
					num = i;
					i = j;
					j = 0;
				}
				else j++;
			}
			if (check == false)
			{
				check2 = true;
				break;
			}
			i = numI;
			j = numJ;
			while (j != list.maxIndex() + 1)
			{
				if (array[i][j] != invalidPrice && array[i][j] != 0 && checkMatrix[i][j] == 0)
				{
					num = array[i][j];
					array[i][j] -= stream;
					array[j][i] += stream;
					checkMatrix[j][i] = 1;
					num = i;
					i = j;
					j = 0;
				}
				else j++;
			}
			maxF += stream;
			i = 0;
			j = list.maxIndex();
			int count = 0;
			while (i != list.maxIndex() + 1)
			{
				if (array[i][j] == 0)
					count++;
				else
					if (array[i][j] != invalidPrice)
					{
						num = array[i][j];
					}
				i++;
			}
			if (count != 0)
			{
				maxF += num;
				check2 = true;
				break;
			}
			i = -1;
			check = false;
		}
		if (check2 == true)
		{
			check3 = true;
			break;
		}
	}

	cout << "Residual network matrix:" << endl;
	list.printMatrix(array);
	cout << "Maximum network flow = " << maxF << endl;
	return maxF;
}
