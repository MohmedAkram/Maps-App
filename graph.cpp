#include "graph.h"

Graph::Graph() {}

void Graph::AddCity(QString city) //adds a city
{
    adjList.insert({ city, vector<pair<QString, float>>() });

}

void Graph::AddEdge(QString citysrc, QString citydest, float distance) //adds edge between two cities
{
    adjList[citysrc].push_back({ citydest, distance });
    adjList[citydest].push_back({ citysrc, distance });

}


void Graph::DeleteCity(QString city)
{
    adjList.erase(city); //removing city from the adjacency list

    //removing all its edges
    for (auto& it : adjList) //iterating over adjList
    {
        auto edges = it.second; //vector of the edges

        vector<pair<QString, float>> newEdges; //vector for storing edges after removal

        for (int i = 0; i < edges.size(); i++) //iterating over the vector
        {
            if (edges.at(i).first != city)
            {
                newEdges.push_back(edges.at(i));
            }
        }

        it.second = newEdges; //replacing old edges vector with the new one
    }
}


vector<QString> Graph::findPath(unordered_map<QString, QString> previous, QString location, QString destination) //helper function for find shortest dist, returns a vector with the cities in the path
{
    stack<QString> cityStack;
    QString current = destination;

    while (current != location)
    {
        current = previous[current];
        cityStack.push(current);
    }

    vector<QString> path;

    while (!cityStack.empty())
    {
        path.push_back(cityStack.top());
        cityStack.pop();
    }

    return path;

}

pair<vector<QString>, float> Graph::FindShortestDis(QString location, QString destination)
{
    if (adjList[location].empty()) //if city has no neighbors, then there is no path and no need to continue the function
        return make_pair(vector<QString>(), -1); //returns empty vector and -1

    unordered_map<QString, float> distances;
    unordered_map<QString, QString> previousCities;

    for (const auto& city : adjList)
    {
        distances[city.first] = INT_MAX;
    }

    distances[location] = 0;

    queue<QString> q;
    q.push(location);

    while (!q.empty())
    {

        QString u = q.front();
        q.pop();

        for (const auto& neighbors : adjList[u])
        {
            QString v = neighbors.first;
            float distance = neighbors.second;

            if (distances[u] + distance < distances[v])
            {
                distances[v] = distances[u] + distance;
                previousCities[v] = u;
                q.push(v);

            }
        }
    }


    if (distances[destination] == INT_MAX) //no path exists
        return make_pair(vector<QString>(), -1); //returns an empty vector and -1 as the distance

    return make_pair(findPath(previousCities, location, destination), distances[destination]); //findPath creates a vector out of the previousCities map. distances[destination] returns the shortest distance to the destination

}


void Graph::UpdateGraph(QString city1, QString city2, float distance)
{
    for (auto& edge : adjList[city1]) {
        if (edge.first == city2) {
            edge.second = distance;

            break;
        }
    }

    // update reverse direction
    for (auto& edge : adjList[city2]) {
        if (edge.first == city1) {
            edge.second = distance;

            break;
        }
    }

}

void Graph::removeEdge(QString city1, QString city2)
{
    //delete path from city1 to city2
    vector<pair<QString, float>> deletededges1;
    for (const auto& edge : adjList[city1]) {
        if (edge.first != city2) {
            deletededges1.push_back(edge);
        }
    }
    adjList[city1] = deletededges1;

    //delete path from city2 to city1
    vector<pair<QString, float>> deletededges2;
    for (const auto& edge : adjList[city2]) {
        if (edge.first != city1) {
            deletededges2.push_back(edge);
        }
    }
    adjList[city2] = deletededges2;

}


// void Graph::DisplayGraphData()
// {
//     for (const auto& city : adjList)
//     {
//         cout << city.first << endl;
//         for (const auto& edge : city.second) {
//             cout << "  -> " << edge.first << " (distance: " << edge.second << ")" << endl;
//         }
//     }

//     cout << endl;
// }

void Graph::loadGraph(QString filename)
{
    QFile file(filename);

    // ifstream file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file.isOpen()) {
        // QMessageBox::information(this, "Error", "Failed to open file: " + filename);
        qDebug()<< "cant open file";
        return;
    }

    QTextStream input(&file);
    QString line;

    while (!input.atEnd()) {
        // istringstream iss(line);
        line = input.readLine();
        QStringList iss = line.split(" ");
        QString city1 = iss[0];
        QString city2 = iss[1];
        QString distanceString = iss[2];

        if (!cityExists(city1)) //if city is not already in the graph, add it
            AddCity(city1);

        if (!city2.isEmpty()) //if city2 is an empty string then city1 has no neighbors and no edges
        {
            if (!cityExists(city2)) //if city 2 is not already in the graph, add it
                AddCity(city2);

            float distance = distanceString.toFloat();
            if (!edgeExists(city1, city2, distance))
                AddEdge(city1, city2, distance); //connect city1 and city2
        }

    }

    file.close();
}

void Graph::WriteToFile(const QString& filename)
{
    QFile outFile(filename);

    if (!outFile.setPermissions(QFile::WriteUser)) {
        qDebug() << "Failed to set file permissions:" << outFile.errorString();
        return;
    }
    outFile.open(QIODevice::WriteOnly);
    if (!outFile.isOpen()) {
        qDebug() << "cant open file" << outFile.errorString();
        qDebug() << filename;
        return;
    }

    QTextStream output(&outFile);

    for (const auto& city: adjList)
    {
        QString line;
        if (city.second.empty())
        {
            line = city.first + " " + " " + "\n";
        }
        else
        {
            for (const auto& edge: city.second)
            {
                line += city.first + " " + edge.first + " " + QString::number(edge.second) + "\n";
            }
        }

        output << line;
    }

    outFile.close();
}



bool Graph::cityExists(QString city) //needed for the delete city function and add edge
{
    return (adjList.find(city) != adjList.end()); //returns true if city exists/ false if it does not
}

bool Graph::edgeExists(QString city, QString city2, float distance) //checks for path AND its weight
{
    for (const auto& edges : adjList[city])
    {
        if (edges.first == city2 && edges.second == distance)
            return true;
    }
    return false;
}

bool Graph::edgeExists(QString city, QString city2) //checks for existence of path only
{
    for (const auto& edges : adjList[city])
    {
        if (edges.first == city2)
            return true;
    }
    return false;

}

int Graph::count() //returns number of cities available
{
    return adjList.size();
}
