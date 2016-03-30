#include <iostream>
#include "List.h"

using namespace std;

struct AdjacentVertex {
public:
    int mark;

    AdjacentVertex(int _mark) {
        mark = _mark;
    }
};

struct Vertex {
    int mark;
    int color;
    bool checked;
    List<AdjacentVertex> adjacent;

public:
    Vertex () {
        mark = 0;
        color = 0;
        checked = false;
        adjacent = List<AdjacentVertex>();
    }

    Vertex (int _mark) {
        mark = _mark;
        color = 0;
        checked = false;
        adjacent = List<AdjacentVertex>();
    }
};

class Graph {
public:
    List<Vertex> vertexes;
    bool debug;

    // +
    Graph() {
        vertexes = List<Vertex>();
        vertexes.Add(Vertex(-1));
        debug = false;
    }

    // +
    bool CheckMarkExists(int mark) {
        for (int i = 0; i < vertexes.Count(); i++) {
            if (vertexes[i].color == mark)
                return true;
        }

        return false;
    }

    // +
    int FindVertexIndexByMark(int mark) {
        if (!CheckMarkExists(mark))
            return -1;

        for (int i = 0; i < vertexes.Count(); i++) {
            if (vertexes[i].mark == mark)
                return i;
        }

        return -1;
    }

    // +
    bool CheckEdgeExists(int from, int to, bool isOriented) {
        from = FindVertexIndexByMark(from);
        to = FindVertexIndexByMark(to);

        for (int i = 0; i < 1; i++) {
            for (int j = 0; j < vertexes[from].adjacent.Count(); j++) {
                if (vertexes[from].adjacent[j].mark == to)
                    return true;
            }

            if (isOriented)
                return false;

            int tmp = from;
            from = to;
            to = tmp;
        }
        return false;
    }

    bool CheckEdgeExistsByVertexMark(int mark) {
        for (int i = 0; i < 1; i++) {
            for (int j = 0; j < vertexes[from].adjacent.Count(); j++) {
                if (vertexes[from].adjacent[j].mark == to)
                    return true;
            }

            if (isOriented)
                return false;

            int tmp = from;
            from = to;
            to = tmp;
        }
        return false;
    }

    void ReplaceExistEdgeByNew(int from, int to, bool isOriented) {
        Edge *currentEdge = edgesHead;
        while (currentEdge->next != nullptr) {
            if (((currentEdge->to == to) && (currentEdge->from == from)) || ((currentEdge->to == from) && (currentEdge->from == to))) {
                *currentEdge = Edge(from, to, isOriented);
                return;
            }
            currentEdge = currentEdge->next;
        }
    }

    void AddVertex(int mark) {
        if (CheckMarkExists(mark)) {
            cout << "Cannot add new vertex! Vertex with the same mark exist!" << endl;
            return;
        }

        if (vertexesHead->mark == -1){
            vertexesHead = new Vertex(mark);
            return;
        }

        Vertex *currentVertex = vertexesHead;
        while (currentVertex->next != nullptr)
            currentVertex = currentVertex->next;

        currentVertex->next = new Vertex(mark);
    }

    void AddEdge(int from, int to){AddEdge(from, to, false);}
    void AddEdge(int from, int to, bool isOriented) {
        if (CheckEdgeExists(from, to, false)) {
            ReplaceExistEdgeByNew(from, to, isOriented);
            cout << "Edge existed and was replaced by new edge!" << endl;
            return;
        }

        if ((edgesHead->from == -1) && (edgesHead->to == -1)) {
            edgesHead = new Edge(from, to, isOriented);
            return;
        }

        Edge *currentEdge = edgesHead;
        while (currentEdge->next != nullptr)
            currentEdge = currentEdge->next;

        currentEdge->next = new Edge(from, to, isOriented);
    }

    void DeleteVertex(int mark) {
        if (!CheckMarkExists(mark)) {
            cout << "Vertex with given mark not exist!" << endl;
            return;
        }

        Vertex *currentVertex = vertexesHead;
        while (currentVertex->next->mark != mark) {
            currentVertex = currentVertex->next;
        }

        currentVertex->next = currentVertex->next->next;

        DeleteEdges(mark);
    }

    void DeleteEdges(int mark) {
        while (CheckEdgeExistsByVertexMark(mark)) {

            Edge *currentEdge = edgesHead;
            while (currentEdge->next != nullptr) {
                if ((currentEdge->from == mark) || (currentEdge->to == mark)) {
                    currentEdge = currentEdge->next;
                }
                currentEdge = currentEdge->next;
            }
        }
    }

    void PrintVertexes() {
        Vertex *currentVertex = vertexesHead;
        while (currentVertex->next != nullptr) {
            cout << "Vertex(mark: " << currentVertex->mark << ", color: " << currentVertex->color << ")" << endl;
            currentVertex = currentVertex->next;
        }
    }

    void PrintEdges() {
        Edge *currentEdge = edgesHead;
        while (currentEdge->next != nullptr) {
            cout << "Edge(from: " << currentEdge->from << ", to: " << currentEdge->to << ", is_oriented: " << currentEdge->isOriented << ")" << endl;
            currentEdge = currentEdge->next;
        }
    }

    void PaintForward(int index, int max, int indexOfMax) {

        int maximumColor = max;
        int indexOfMaximum = indexOfMax;

        //for (int i = index + 1; i < vertexesCount; i++) {
        Vertex *currentVertex = vertexesHead;
        while (currentVertex->next != nullptr) {
            currentVertex->color = 1;
            if (debug)
                cout << "Color changed. Vertex mark: " << currentVertex->mark << ", color: " << currentVertex->color << endl;
            ChangeColor(currentVertex->mark);
        }


        *currentVertex = vertexesHead;
        while (currentVertex->next != nullptr) {
            if (currentVertex->color > maximumColor) {
                maximumColor = currentVertex->color;
                indexOfMaximum = i;
            }
        }

        if (indexOfMaximum == 0) {
            return;
        }
        StepBack(indexOfMaximum, maximumColor);

    }

    void ChangeColor(int index) {

        int i = 0;
        while (i < index) {
            if (CheckEdgeExists(i, index, false)) {
                if (vertexes[i].color == vertexes[index].color) {
                    vertexes[index].color++;
                    if (debug)
                        cout << "Color changed. Vertex index: " << index << ", color: " << vertexes[index].color <<
                        endl;
                    i = -1;
                }
            }
            i += 1;
        }
    }

    void StepBack(int index, int max) {
        if (debug)
            cout << "Step back. Index: " << index << ", max: " << max << endl;
        int last = index - 1;
        for (int i = index - 1; i >= 0; i--) {
            if (CheckEdgeExists(i, index, false)) {
                last = i;
                break;
            }
        }

        vertexes[last].color++;
        if (debug)
            cout << "Color changed. Vertex index: " << last << ", color: " << vertexes[last].color << endl;
        ChangeColor(last);

        if (vertexes[last].color < max || last == 0) {
            max = 0;
            int localIndex = 0;
            for (int i = 0; i <= last; i++) {
                if (vertexes[i].color > max) {
                    max = vertexes[i].color;
                    localIndex = i;
                }
            }
            PaintForward(last, max, localIndex);
        } else {
            StepBack(last, max);
        }
    }

    void Paint() {
        PaintForward(-1, 0, 0);
    }

    void DFS() {
        for (int i = 0; i < vertexesCount; i++) {
            mark[i] = false;
        }

        for (int i = 0; i < vertexesCount; i++) {
            if (!mark[i]) {
                dfs_helper(i);
            }
        }

        cout << endl;
    }

    void dfs_helper(int index) {
        mark[index] = true;
        cout << vertexes[index].mark << " ";
        for (int i = 0; i < vertexesCount; i++) {
            if (CheckEdgeExists(index, i, true)) {
                if (!mark[i]) {
                    dfs_helper(i);
                }
            }
        }
    }*/
};

int main() {
    Graph graph = Graph();

    /// GRAPH ONE
/*
    graph.AddVertex(1);
    graph.AddVertex(2);
    graph.AddVertex(3);
    graph.AddVertex(4);
    graph.AddVertex(5);
    graph.AddVertex(6);
    graph.AddVertex(7);
    graph.AddVertex(8);

    cout << endl;
    graph.PrintVertexes();

    graph.AddEdge(1,3);
    graph.AddEdge(3,4);
    graph.AddEdge(4,2);
    graph.AddEdge(2,7);
    graph.AddEdge(7,6);
    graph.AddEdge(6,5);
    graph.AddEdge(5,8);
    graph.AddEdge(8,1);
*/

/*
    /// GRAPH TWO
    graph.AddVertex(1);
    graph.AddVertex(2);
    graph.AddVertex(3);
    graph.AddVertex(4);
    graph.AddVertex(5);
    graph.AddVertex(6);
    graph.AddVertex(7);
    graph.AddVertex(8);

    cout << endl;
    graph.PrintVertexes();

    graph.AddEdge(1,8);
    graph.AddEdge(8,2);
    graph.AddEdge(2,3);
    graph.AddEdge(3,7);
    graph.AddEdge(7,6);
    graph.AddEdge(6,5);
    graph.AddEdge(5,4);
    graph.AddEdge(4,1);

    graph.AddEdge(1,3);
    graph.AddEdge(1,6);
    graph.AddEdge(2,5);
    graph.AddEdge(2,7);
    graph.AddEdge(3,6);
    graph.AddEdge(7,5);
*/

    /// GRAPH THREE
    graph.AddVertex(1);
    graph.AddVertex(2);
    graph.AddVertex(3);
    graph.AddVertex(4);
    graph.AddVertex(5);
    graph.AddVertex(6);

    cout << endl;
    graph.PrintVertexes();

    graph.AddEdge(1,5);
    graph.AddEdge(5,2);
    graph.AddEdge(2,6);
    graph.AddEdge(6,3);
    graph.AddEdge(3,4);
    graph.AddEdge(4,1);
    graph.AddEdge(4,5);
    graph.AddEdge(4,6);
    graph.AddEdge(6,5);

    cout << endl;
    graph.PrintEdges();

    //graph.Paint();
    cout << endl << "graph.Paint();" << endl << endl;
    graph.PrintVertexes();

    cout << endl << "DFS:" << endl;
    //graph.DFS();

    system("pause");
    return 0;
}