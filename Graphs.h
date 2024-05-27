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
	Graph(const int& size); // конструктор
	~Graph() { } // деструктор
	int GetVertPos(const T& vertex); // нахождение позиции вершины в векторе вершин
	bool IsEmpty(); // проверка, пуст ли граф
	bool IsFull(); // проверка, полон ли граф
	int GetAmountVerts(); // возвращает количество вершин в графе
	int GetAmountEdges(); // возвращает количество ребер в графе
	int GetWeight(const T& vertex1, const T& vertex2); // получить вес
	vector<T> GetNbrs(const T& vertex); // получить соседей
	void InsertVertex(const T& vertex); // добавление вершины
	void InsertEdge(const T& vertex1, const T& vertex2, int weight); // вставляет между вершинами ребро
	void Print(); // печать матрицы смежности графа
	void DFS(T& startVertex, bool* visitedVerts); // обход графа в глубину
	void BFS(T& startVertex, bool* visitedVerts); // обход графа в ширину
	bool AllVisited(bool* visitedVerts); // проверка, обработаны ли все вершины
	void FillLabels(T& startVertex); // заполнение очереди вершинами
	int Dijkstra(T& startVertex); // алгоритм Дейкстры
};
template<class T>
Graph<T>::Graph(const int& size) { // конструктор
	this->maxSize = size; // максимальный размер графа
	this->adjMatrix = vector<vector<T>>(size, vector<T>(size));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			this->adjMatrix[i][j] = 0; // по умолчанию устанавливаются все 0
		}
	}
}

template<class T>
int Graph<T>::GetVertPos(const T& vertex) { // нахождение позиции вершины в векторе вершин
	for (int i = 0; i < this->vertList.size(); ++i) {
		if (this->vertList[i] == vertex) // если найдено
			return i;
	}
	return -1;
}

template<class T>
bool Graph<T>::IsEmpty() { // проверка, пуст ли граф
	if (this->vertList.size() != 0) return false;
	else
		return true;
}

template<class T>
bool Graph<T>::IsFull() { // проверка, полон ли граф
	return (this->vertList.size() == maxSize);
}

template<class T>
int Graph<T>::GetAmountVerts() { // возвращает количество вершин в графе
	return this->vertList.size();
}

template<class T>
int Graph<T>::GetAmountEdges() { // возвращает количество ребер в графе
	int amount = 0;	// обнуление счетчика
	if (!this->IsEmpty()) {  // проверка, не пуст ли граф
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			for (int j = 0; j < vertListSize; ++j) {
				if (this->adjMatrix[i][j] == this->adjMatrix[j][i] && this->adjMatrix[i][j] != 0)	// нахождение ребер
					amount += 1; // счет количества ребер
			}
		}
		return (amount / 2); // возврат количества ребер
	}
	else
		return 0; // если граф пуст, возврат 0
}

template<class T>
int Graph<T>::GetWeight(const T& vertex1, const T& vertex2) { // получить вес ребра
	if (!this->IsEmpty()) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2); 
		return adjMatrix[vertPos1][vertPos2];
	}
	return 0;
}

template<class T>
vector<T> Graph<T>::GetNbrs(const T& vertex) { // получить соседей
	vector<T> nbrsList; // создание списка соседей 
	int pos = this->GetVertPos(vertex); // вычисление позиции vertex в матрице смежности
	if (pos != (-1)) { // проверка, что vertex есть в матрице смежности
		for (int i = 0, vertListSize = this -> vertList.size(); i < vertListSize; ++i) {
			if (this->adjMatrix[pos][i] != 0) // вычисление соседей
				nbrsList.push_back(this->vertList[i]); // запись соседей в вектор
		}
	}
	return nbrsList; // возврат списка соседей
}

template<class T>
void Graph<T>::InsertVertex(const T& vertex) { // добавление вершины
	if (!this->IsFull()) {
		this->vertList.push_back(vertex); // добавление вершин в вектор вершин
	}
	else {
		cout << "Граф уже заполнен. Невозможно добавить новую вершину " << endl;
			return;
	}
}

template<class T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2, int weight) {  // вставляет между вершинами ребро
	if (this->GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) {
		int vertPos1 = GetVertPos(vertex1); // переменная с номером вершины
		int vertPos2 = GetVertPos(vertex2); // переменная с номером вершины
		if (this->adjMatrix[vertPos1][vertPos2] != 0 && this->adjMatrix[vertPos2][vertPos1] != 0) {
			cout << "Ребро между вершинами уже есть" << endl;
			return;
		}
		else {
			this->adjMatrix[vertPos1][vertPos2] = weight; // установка ребра
			this->adjMatrix[vertPos2][vertPos1] = weight; // установка ребра
		}
	}
	else {
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
		return;
	}
}


template<class T>
void Graph<T>::Print() { // печать матрицы смежности
	if (!this->IsEmpty()) {
		cout << "Матрица смежности графа: " << endl;
		for (int i = 0, vertListSize = this -> vertList.size(); i < vertListSize; ++i) {
			cout << this->vertList[i] << " ";
			for (int j = 0; j < vertListSize; ++j) {
				cout << " " << this-> adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "Граф пуст " << endl;
	}
}

template<class T>
void Graph<T>::DFS(T& startVertex, bool* visitedVerts) { // обход графа в глубину
	cout << "Вершина " << startVertex << " посещена" << endl;
	visitedVerts[this->GetVertPos(startVertex)] = true; // пометка в массиве посещенных вершин
	vector<T> neighbors = this -> GetNbrs(startVertex); // вектор соседей
	for (int i = 0, size = this -> GetNbrs(startVertex).size(); i < size; ++i) {
		if (visitedVerts[this -> GetVertPos(neighbors[i])] != true) // проверка, не посещены ли соседи
			this->DFS(neighbors[i], visitedVerts);
	}
}

template<class T>
void Graph<T>::BFS(T& startVertex, bool *  visitedVerts) {  // обход графа в ширину
    if (visitedVerts[this->GetVertPos(startVertex)] == false) { // проверка, была ли ранее посещена вершина startVertex
        this->VertsQueue.push(startVertex);
        cout << "Вершина " << startVertex << " обработана" << endl;
        visitedVerts[this->GetVertPos(startVertex)] = true;
    } 

    vector<T> neighbors = this->GetNbrs(startVertex); // вектор соседей
	if (!VertsQueue.empty())
		this->VertsQueue.pop(); // удаление головы очереди
    for (int i = 0, size = neighbors.size(); i < size; ++i) {
        if (visitedVerts[this->GetVertPos(neighbors[i])] != true) {
			this->VertsQueue.push(neighbors[i]);
            visitedVerts[this->GetVertPos(neighbors[i])] = true; // пометка в векторе о том, что вершина обработана
            cout << "Вершина " << neighbors[i] << " обработана" << endl;
        }
    }
    while (!this->VertsQueue.empty()) {
        BFS(this->VertsQueue.front(), visitedVerts); // повторение цикла для остальных вершин
    }
}

template<class T>
bool Graph<T>::AllVisited(bool* visitedVerts) {  // проверка, обработаны ли все вершины
	bool flag = true;
	for (int i = 0, size = this->vertList.size(); i < size; ++i) { // если в массиве посещенных вершин есть хотя бы одно значение false
		if (visitedVerts[i] != true) flag = false;
	}
	if (flag == false) // еще не все вершины посещены
		return false;

	else return true; // все вершины посещены
}

template<class T>
void Graph<T>::FillLabels(T& startVertex) { // заполнение очереди вершинами
	for (int i = 0, size = vertList.size(); i < size; ++i) {
		this->labelList.push_back(1000000); // изначально все расстояние равны недостижимо большому числу
	}
	int pos = this->GetVertPos(startVertex);
	(this->labelList)[pos] = 0;
}

template<class T>
int Graph<T>::Dijkstra(T& startVertex) { // алгоритм Дейкстры
	for (int i = 0, size = this->vertList.size(); i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (this->adjMatrix[i][j] < 0) // проверка, нет ли ребер с отрицательным весом
				return -1;
		}
	}
	T curSrc; 
    int counter = 0; 
	int minLabel = 1000000;
	vector<T> neighbors = this -> GetNbrs(startVertex); // вектор из соседей текущей начальной вершины

	for (int i = 0; i < neighbors.size(); ++i) {
		if (this->labelList[this->GetVertPos(startVertex)] + this->GetWeight(startVertex, neighbors[i]) <
			this->labelList[this->GetVertPos(neighbors[i])]) { // проверка, есть ли в векторе меток метка по индексу соседа в векторе вершин
			this->labelList[this->GetVertPos(neighbors[i])] = this->GetWeight(startVertex, neighbors[i]);
		}
		if (this->labelList[this->GetVertPos(neighbors[i])]
			< minLabel)
			minLabel = this->labelList[this->GetVertPos(neighbors[i])]; // наименьшая метка у соседних опорной вершине вершин
	}

	for (int i = 0; i < neighbors.size(); ++i) { // проверка, рассмотрели ли всех соседей
		if (this->labelList[this -> GetVertPos(neighbors[i])] != 1000000)
			counter += 1;
	} 

	if (counter == neighbors.size())
		visitedVerts[this->GetVertPos(startVertex)] = true; // начальная вершина теперь считается посещенной
	for (int i = 0; i < neighbors.size(); ++i) { // поиск новуй опорной вершины, у которой из всех соседей метка наименьшая
		if (this->labelList[this->GetVertPos(neighbors[i])] == minLabel)
			curSrc = neighbors[i];
	}
	neighbors = this->GetNbrs(curSrc);
	while (!AllVisited(visitedVerts)) { // пока все вершины не будут считаться посещенными
		int count = 0;
		minLabel = 10000;
		for (int i = 0; i < neighbors.size(); ++i) { // проверка, была ли вершина-соседуже рассмотрена ранее
			if (visitedVerts[this->GetVertPos(neighbors[i])] != true) {
				if (this->labelList[this->GetVertPos(curSrc)] + GetWeight(curSrc, neighbors[i]) < this->labelList[this->GetVertPos(neighbors[i])]) {
					this->labelList[this->GetVertPos(neighbors[i])] = (this->labelList[this->GetVertPos(curSrc)]
						+ this->GetWeight(curSrc, neighbors[i]));
				}
				if (this->labelList[this->GetVertPos(neighbors[i])] < minLabel) {
					minLabel = this->labelList[this->GetVertPos(neighbors[i])];
				}
			}
			count += 1; // счет соседей
		}
		if (count == neighbors.size()) // проверка, посетили ли всех соседей текущей опорной вершины
			visitedVerts[this->GetVertPos(curSrc)] = true; // текущая опорная вершина отмечается как посещенная

		for (int i = 0; i < neighbors.size(); ++i) { // поиск среди соседей новую опорную вершину 
			if (this->labelList[this->GetVertPos(neighbors[i])] == minLabel)
				curSrc = neighbors[i];
		}
		neighbors = this->GetNbrs(curSrc); // занесение в вектор соседей соседей новой опорной вершины
	}
	for (int i = 0; i < this->GetVertPos(startVertex); ++i) {
		cout << "Кратчайшее расстояние от вершины " << startVertex << " до вершины " << this->vertList[i] << 
			" равно " << this->labelList[this ->GetVertPos(this->vertList[i])] << endl;
	}

	for (int i = this->GetVertPos(startVertex) + 1; i < this->vertList.size(); ++i) {
		cout << "Кратчайшее расстояние от вершины " << startVertex << " до вершины " << this->vertList[i] <<
			" равно " << this->labelList[this -> GetVertPos(this->vertList[i])] << endl;
	}
}