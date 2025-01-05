#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <unordered_map>
#include <vector>
#include <QFile>
#include <QTextStream>
// #include <fstream>
// #include <sstream>
#include <queue>
#include <stack>
#include <limits>
#include <QMessageBox>
using namespace std;

class Graph
{


    vector<QString> findPath(unordered_map<QString, QString> previous, QString location, QString destination);
public:
    Graph();
    unordered_map<QString, vector<pair<QString, float>>> adjList;

    void AddCity(QString city);
    void AddEdge(QString citysrc, QString citydest, float distance);

    void DeleteCity(QString city);

    pair<vector<QString>, float> FindShortestDis(QString location, QString destination);


    void UpdateGraph(QString city1, QString city2, float distance);
    void removeEdge(QString city1, QString city2);

    // void DisplayGraphData();
    void loadGraph(QString filename);
    void WriteToFile(const QString& filename);

    bool cityExists(QString city);
    bool edgeExists(QString city, QString city2, float distance);
    bool edgeExists(QString city, QString city2);
    int count();

};

#endif // GRAPH_H
