#pragma once
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

bool* visitedVerts = new bool[20];

template <class T>
class Graph {
	vector<int> vertList;
	vector<vector<int>> adjMatrix;
	int maxSize;
	queue<T> VertsQueue;
	vector<T> labelList;
public:
	Graph(const int& size); // �����������
	~Graph() { } // ����������
	int GetVertPos(const T& vertex); // ���������� ������� ������� � ������� ������
	bool IsEmpty(); // ��������, ���� �� ����
	bool IsFull(); // ��������, ����� �� ����
	int GetAmountVerts(); // ���������� ���������� ������ � �����
	int GetAmountEdges(); // ���������� ���������� ����� � �����
	int GetWeight(const T& vertex1, const T& vertex2); // �������� ���
	vector<T> GetNbrs(const T& vertex); // �������� �������
	void InsertVertex(const T& vertex); // ���������� �������
	void InsertEdge(const T& vertex1, const T& vertex2, int weight); // ��������� ����� ��������� �����
	void Print(); // ������ ������� ��������� �����
	void DFS(T& startVertex, bool* visitedVerts); // ����� ����� � �������
	void BFS(T& startVertex, bool* visitedVerts); // ����� ����� � ������
	bool AllVisited(bool* visitedVerts); // ��������, ���������� �� ��� �������
	void FillLabels(T& startVertex); // ���������� ������� ���������
	int Dijkstra(T& startVertex); // �������� ��������
};
template<class T>
Graph<T>::Graph(const int& size) { // �����������
	this->maxSize = size; // ������������ ������ �����
	this->adjMatrix = vector<vector<T>>(size, vector<T>(size));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			this->adjMatrix[i][j] = 0; // �� ��������� ��������������� ��� 0
		}
	}
}

template<class T>
int Graph<T>::GetVertPos(const T& vertex) { // ���������� ������� ������� � ������� ������
	for (int i = 0; i < this->vertList.size(); ++i) {
		if (this->vertList[i] == vertex) // ���� �������
			return i;
	}
	return -1;
}

template<class T>
bool Graph<T>::IsEmpty() { // ��������, ���� �� ����
	if (this->vertList.size() != 0) return false;
	else
		return true;
}

template<class T>
bool Graph<T>::IsFull() { // ��������, ����� �� ����
	return (this->vertList.size() == maxSize);
}

template<class T>
int Graph<T>::GetAmountVerts() { // ���������� ���������� ������ � �����
	return this->vertList.size();
}

template<class T>
int Graph<T>::GetAmountEdges() { // ���������� ���������� ����� � �����
	int amount = 0;	// ��������� ��������
	if (!this->IsEmpty()) {  // ��������, �� ���� �� ����
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			for (int j = 0; j < vertListSize; ++j) {
				if (this->adjMatrix[i][j] == this->adjMatrix[j][i] && this->adjMatrix[i][j] != 0)	// ���������� �����
					amount += 1; // ���� ���������� �����
			}
		}
		return (amount / 2); // ������� ���������� �����
	}
	else
		return 0; // ���� ���� ����, ������� 0
}

template<class T>
int Graph<T>::GetWeight(const T& vertex1, const T& vertex2) { // �������� ��� �����
	if (!this->IsEmpty()) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2); 
		return adjMatrix[vertPos1][vertPos2];
	}
	return 0;
}

template<class T>
vector<T> Graph<T>::GetNbrs(const T& vertex) { // �������� �������
	vector<T> nbrsList; // �������� ������ ������� 
	int pos = this->GetVertPos(vertex); // ���������� ������� vertex � ������� ���������
	if (pos != (-1)) { // ��������, ��� vertex ���� � ������� ���������
		for (int i = 0, vertListSize = this -> vertList.size(); i < vertListSize; ++i) {
			if (this->adjMatrix[pos][i] != 0) // ���������� �������
				nbrsList.push_back(this->vertList[i]); // ������ ������� � ������
		}
	}
	return nbrsList; // ������� ������ �������
}

template<class T>
void Graph<T>::InsertVertex(const T& vertex) { // ���������� �������
	if (!this->IsFull()) {
		this->vertList.push_back(vertex); // ���������� ������ � ������ ������
	}
	else {
		cout << "���� ��� ��������. ���������� �������� ����� ������� " << endl;
			return;
	}
}

template<class T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2, int weight) {  // ��������� ����� ��������� �����
	if (this->GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) {
		int vertPos1 = GetVertPos(vertex1); // ���������� � ������� �������
		int vertPos2 = GetVertPos(vertex2); // ���������� � ������� �������
		if (this->adjMatrix[vertPos1][vertPos2] != 0 && this->adjMatrix[vertPos2][vertPos1] != 0) {
			cout << "����� ����� ��������� ��� ����" << endl;
			return;
		}
		else {
			this->adjMatrix[vertPos1][vertPos2] = weight; // ��������� �����
			this->adjMatrix[vertPos2][vertPos1] = weight; // ��������� �����
		}
	}
	else {
		cout << "����� ������ (��� ����� �� ���) ��� � ����� " << endl;
		return;
	}
}


template<class T>
void Graph<T>::Print() { // ������ ������� ���������
	if (!this->IsEmpty()) {
		cout << "������� ��������� �����: " << endl;
		for (int i = 0, vertListSize = this -> vertList.size(); i < vertListSize; ++i) {
			cout << this->vertList[i] << " ";
			for (int j = 0; j < vertListSize; ++j) {
				cout << " " << this-> adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "���� ���� " << endl;
	}
}

template<class T>
void Graph<T>::DFS(T& startVertex, bool* visitedVerts) { // ����� ����� � �������
	cout << "������� " << startVertex << " ��������" << endl;
	visitedVerts[this->GetVertPos(startVertex)] = true; // ������� � ������� ���������� ������
	vector<T> neighbors = this -> GetNbrs(startVertex); // ������ �������
	for (int i = 0, size = this -> GetNbrs(startVertex).size(); i < size; ++i) {
		if (visitedVerts[this -> GetVertPos(neighbors[i])] != true) // ��������, �� �������� �� ������
			this->DFS(neighbors[i], visitedVerts);
	}
}

template<class T>
void Graph<T>::BFS(T& startVertex, bool *  visitedVerts) {  // ����� ����� � ������
    if (visitedVerts[this->GetVertPos(startVertex)] == false) { // ��������, ���� �� ����� �������� ������� startVertex
        this->VertsQueue.push(startVertex);
        cout << "������� " << startVertex << " ����������" << endl;
        visitedVerts[this->GetVertPos(startVertex)] = true;
    } 

    vector<T> neighbors = this->GetNbrs(startVertex); // ������ �������
	if (!VertsQueue.empty())
		this->VertsQueue.pop(); // �������� ������ �������
    for (int i = 0, size = neighbors.size(); i < size; ++i) {
        if (visitedVerts[this->GetVertPos(neighbors[i])] != true) {
			this->VertsQueue.push(neighbors[i]);
            visitedVerts[this->GetVertPos(neighbors[i])] = true; // ������� � ������� � ���, ��� ������� ����������
            cout << "������� " << neighbors[i] << " ����������" << endl;
        }
    }
    while (!this->VertsQueue.empty()) {
        BFS(this->VertsQueue.front(), visitedVerts); // ���������� ����� ��� ��������� ������
    }
}

template<class T>
bool Graph<T>::AllVisited(bool* visitedVerts) {  // ��������, ���������� �� ��� �������
	bool flag = true;
	for (int i = 0, size = this->vertList.size(); i < size; ++i) { // ���� � ������� ���������� ������ ���� ���� �� ���� �������� false
		if (visitedVerts[i] != true) flag = false;
	}
	if (flag == false) // ��� �� ��� ������� ��������
		return false;

	else return true; // ��� ������� ��������
}

template<class T>
void Graph<T>::FillLabels(T& startVertex) { // ���������� ������� ���������
	for (int i = 0, size = vertList.size(); i < size; ++i) {
		this->labelList.push_back(1000000); // ���������� ��� ���������� ����� ����������� �������� �����
	}
	int pos = this->GetVertPos(startVertex);
	(this->labelList)[pos] = 0;
}

template<class T>
int Graph<T>::Dijkstra(T& startVertex) { // �������� ��������
	for (int i = 0, size = this->vertList.size(); i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (this->adjMatrix[i][j] < 0) // ��������, ��� �� ����� � ������������� �����
				return -1;
		}
	}
	T curSrc; 
    int counter = 0; 
	int minLabel = 1000000;
	vector<T> neighbors = this -> GetNbrs(startVertex); // ������ �� ������� ������� ��������� �������

	for (int i = 0; i < neighbors.size(); ++i) {
		if (this->labelList[this->GetVertPos(startVertex)] + this->GetWeight(startVertex, neighbors[i]) <
			this->labelList[this->GetVertPos(neighbors[i])]) { // ��������, ���� �� � ������� ����� ����� �� ������� ������ � ������� ������
			this->labelList[this->GetVertPos(neighbors[i])] = this->GetWeight(startVertex, neighbors[i]);
		}
		if (this->labelList[this->GetVertPos(neighbors[i])]
			< minLabel)
			minLabel = this->labelList[this->GetVertPos(neighbors[i])]; // ���������� ����� � �������� ������� ������� ������
	}

	for (int i = 0; i < neighbors.size(); ++i) { // ��������, ����������� �� ���� �������
		if (this->labelList[this -> GetVertPos(neighbors[i])] != 1000000)
			counter += 1;
	} 

	if (counter == neighbors.size())
		visitedVerts[this->GetVertPos(startVertex)] = true; // ��������� ������� ������ ��������� ����������
	for (int i = 0; i < neighbors.size(); ++i) { // ����� ����� ������� �������, � ������� �� ���� ������� ����� ����������
		if (this->labelList[this->GetVertPos(neighbors[i])] == minLabel)
			curSrc = neighbors[i];
	}
	neighbors = this->GetNbrs(curSrc);
	while (!AllVisited(visitedVerts)) { // ���� ��� ������� �� ����� ��������� �����������
		int count = 0;
		minLabel = 10000;
		for (int i = 0; i < neighbors.size(); ++i) { // ��������, ���� �� �������-�������� ����������� �����
			if (visitedVerts[this->GetVertPos(neighbors[i])] != true) {
				if (this->labelList[this->GetVertPos(curSrc)] + GetWeight(curSrc, neighbors[i]) < this->labelList[this->GetVertPos(neighbors[i])]) {
					this->labelList[this->GetVertPos(neighbors[i])] = (this->labelList[this->GetVertPos(curSrc)]
						+ this->GetWeight(curSrc, neighbors[i]));
				}
				if (this->labelList[this->GetVertPos(neighbors[i])] < minLabel) {
					minLabel = this->labelList[this->GetVertPos(neighbors[i])];
				}
			}
			count += 1; // ���� �������
		}
		if (count == neighbors.size()) // ��������, �������� �� ���� ������� ������� ������� �������
			visitedVerts[this->GetVertPos(curSrc)] = true; // ������� ������� ������� ���������� ��� ����������

		for (int i = 0; i < neighbors.size(); ++i) { // ����� ����� ������� ����� ������� ������� 
			if (this->labelList[this->GetVertPos(neighbors[i])] == minLabel)
				curSrc = neighbors[i];
		}
		neighbors = this->GetNbrs(curSrc); // ��������� � ������ ������� ������� ����� ������� �������
	}
	for (int i = 0; i < this->GetVertPos(startVertex); ++i) {
		cout << "���������� ���������� �� ������� " << startVertex << " �� ������� " << this->vertList[i] << 
			" ����� " << this->labelList[this ->GetVertPos(this->vertList[i])] << endl;
	}

	for (int i = this->GetVertPos(startVertex) + 1; i < this->vertList.size(); ++i) {
		cout << "���������� ���������� �� ������� " << startVertex << " �� ������� " << this->vertList[i] <<
			" ����� " << this->labelList[this -> GetVertPos(this->vertList[i])] << endl;
	}
}