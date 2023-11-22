#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <memory>
#include <algorithm>

namespace ggh::graph {

template <class T, class E> class Edge;
template <class T, class E> class Graph;

template <class T, class E>
class Node {
public:
    Node(T data) : data_{data} {};

    T getData() const;

    std::vector<std::shared_ptr<Edge<T, E>>> getEdges() const;

    friend class Graph<T, E>;

    bool operator==(const Node<T, E>& other);

private:
    T data_;
    std::vector<std::shared_ptr<Edge<T, E>>> adj_edges_;

    void addEdge(std::shared_ptr<Node<T, E>> node, E annotation);

    bool removeEdge(std::shared_ptr<Node<T, E>> node);
};

template <class T, class E>
class Edge {
public:
    Edge(std::shared_ptr<Node<T, E>> node_to, E annotation_) : node_to_{node_to}, annotation_{annotation_} {};

    std::shared_ptr<Node<T, E>> getNodeTo() const;

    E getAnnotation() const;
    friend class Node<T, E>;
    friend class Graph<T, E>;

private:
    std::shared_ptr<Node<T, E>> node_to_;
    E annotation_;
};

template<class T, class E>
T Node<T, E>::getData() const {
    return data_;
}

template<class T, class E>
void Node<T, E>::addEdge(std::shared_ptr<Node<T, E>> node, E annotation) {
    adj_edges_.push_back(std::make_shared<Edge<T, E>>(node, annotation));
}

template<class T, class E>
std::vector<std::shared_ptr<Edge<T, E>>> Node<T, E>::getEdges() const {
    return adj_edges_;
}

template<class T, class E>
bool Node<T, E>::operator==(const Node<T, E>& other) {
    return data_ == other.data_;
}

template<class T, class E>
bool Node<T, E>::removeEdge(std::shared_ptr<Node<T, E>> node){
    auto found_node{std::find_if(adj_edges_.cbegin(), adj_edges_.cend(),
                                 [&node](const Edge<T, E>& x){ return node == x.node_to_; })};
    if(found_node == adj_edges_.cend()) {
        return false;
    }
    adj_edges_.erase(found_node);
    return true;
}

template<class T, class E>
std::shared_ptr<Node<T, E>> Edge<T, E>::getNodeTo() const{
    return node_to_;
}

template<class T, class E>
E Edge<T, E>::getAnnotation() const {
    return annotation_;
}

template<class T, class E>
class Graph {
public:
    Graph() = default;
    Graph(const Graph& other);

    bool addNode(const T& in);
    bool removeNode(const T& in);
    bool addEdge(std::shared_ptr<Node<T, E>> node_from, std::shared_ptr<Node<T, E>> node_to, E annotation);
    bool addEdge(const T& data_from, const T& data_to, E annotation);
    bool removeEdge(std::shared_ptr<Node<T, E>> node_from, std::shared_ptr<Node<T, E>> node_to);
    std::shared_ptr<Node<T, E>> getNodeFromData(const T& data) const;
    bool contains(const T& data) const;
private:
    std::vector<std::shared_ptr<Node<T, E>>> node_set_;

    bool contains(std::shared_ptr<Node<T, E>> node) const;

};

template<class T, class E>
bool Graph<T, E>::addNode(const T& in) {
    if(contains(in)) {
        return false;
    }
    node_set_.push_back(std::make_shared<Node<T, E>>(std::move(in)));
    return true;
}

template<class T, class E>
bool Graph<T, E>::removeNode(const T& in) {
    auto node_it{std::find_if(node_set_.cbegin(), node_set_.cend(),
                              [&in](std::shared_ptr<Node<T, E>> x){ return in == x->data_; })};
    if(node_it == node_set_.cend()) {
        return false;
    }
    node_set_.erase(node_it);
    return true;
}

template<class T, class E>
bool Graph<T, E>::contains(std::shared_ptr<Node<T, E>> node) const {
    auto node_it{std::find(node_set_.cbegin(), node_set_.cend(), node)};
    return node_it != node_set_.cend();
}

template<class T, class E>
bool Graph<T, E>::contains(const T& data) const {
    auto node_it{std::find_if(node_set_.cbegin(), node_set_.cend(),
                              [&data](std::shared_ptr<Node<T, E>> x){ return data == x->data_; })};
    return node_it != node_set_.cend();
}

template<class T, class E>
bool Graph<T, E>::addEdge(std::shared_ptr<Node<T, E>> node_from, std::shared_ptr<Node<T, E>> node_to, E annotation) {
    if(!contains(node_to) && !contains(node_from)) {
        return false;
    }
    node_from->addEdge(node_to, annotation);
    return true;
}

template<class T, class E>
std::shared_ptr<Node<T, E>> Graph<T, E>::getNodeFromData(const T& data) const {
    auto node_it{std::find_if(node_set_.cbegin(), node_set_.cend(),
                              [&data](std::shared_ptr<Node<T, E>> x){ return data == x->data_; })};
    return *node_it;
}

template<class T, class E>
bool Graph<T, E>::addEdge(const T& data_from, const T& data_to, E annotation) {
    if(!contains(data_from) && !contains(data_to)) {
        return false;
    }
    auto node_from{getNodeFromData(data_from)};
    auto node_to{getNodeFromData(data_to)};
    node_from->addEdge(node_to, annotation);
    return true;
}
}
#endif // GRAPH_H
