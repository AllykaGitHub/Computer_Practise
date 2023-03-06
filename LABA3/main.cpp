#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <utility>
#include <string>
#include <unordered_set>
template<typename T>
class Graph {
public:
    // Типы
    using value_type = T;

private:
    // Данные
   
    std::unordered_map<T, size_t> vertex_map_;
    std::unordered_map<T, std::vector<T>> adjacency_list_;
    size_t vertex_count_ = 0;
    std::vector<std::vector<T>> adjacency_matrix_;
    std::vector<T> vertices_;

  
public:
    

    // Конструкторы

    // Дефолтный конструктор
    Graph() = default;

    // Конструктор копирования
    Graph(const Graph& other) = default;

    // Конструктор перемещения
    Graph(Graph&& other) noexcept = default;

    // Операторы присваивания

    // Оператор копирующего присваивания
    Graph& operator=(const Graph& other) = default;

    // Оператор перемещающего присваивания
    Graph& operator=(Graph&& other) noexcept = default;
    bool operator==(const T& lhs) {
        return this == lhs.value;
    }

  



  


    // Методы

    // Проверка на пустоту
    bool empty() const {
        return adjacency_matrix_.empty();
    }

    // Получение количества вершин
    size_t size() const {
        return adjacency_matrix_.size();
    }

    // Очистка графа
    void clear() {
        adjacency_matrix_.clear();
    }

    // Метод для обмена двух графов
    void swap(Graph& other) noexcept {
        adjacency_matrix_.swap(other.adjacency_matrix_);
        vertices_.swap(other.vertices_);
    }

    // Метод возвращает список исходящих ребер из вершины i
    std::vector<std::pair<size_t, T>> getOutgoingEdges(size_t i) const {
        std::vector<std::pair<size_t, T>> edges;

        // Проверяем, что вершина i существует в графе
        if (i >= size()) {
            throw std::out_of_range("Vertex index is out of range.");
        }

        // Итерируемся по всем вершинам графа, проверяя есть ли ребро между вершинами i и j
        for (size_t j = 0; j < size(); ++j) {
            if (adjacency_matrix_[i][j] != T()) {
                // Если ребро существует, добавляем его в список ребер
                edges.push_back(std::make_pair(j, adjacency_matrix_[i][j]));
            }
        }

        return edges;
    }

    using iterator = typename std::vector<std::vector<T>>::iterator;
    using const_iterator = typename std::vector<std::vector<T>>::const_iterator;

    iterator begin() {
        return adjacency_matrix_.begin();
    }

    const_iterator begin() const {
        return adjacency_matrix_.cbegin();
    }

    iterator end() {
        return adjacency_matrix_.end();
    }

    const_iterator end() const {
        return adjacency_matrix_.cend();
    }
    // Метод возвращает индекс вершины в списке вершин
    size_t vertex_index(const T& vertex) const {
        const auto it = vertex_map_.find(vertex);
        if (it == vertex_map_.end()) {
            return vertices_.size();
        }
        else {
            return it->second;
        }
    }
   
    T get_weight(size_t from, size_t to) const {
        if (from >= size() || to >= size()) {
            return T();
        }
        if (!adjacency_matrix_.empty()) {
            T weight = adjacency_matrix_[from][to];
            return weight;
        }
        return T();
    }



    bool has_edge(size_t from, size_t to) const {
        if (from >= size() || to >= size()) {
            return false;
        }
        return adjacency_matrix_[from][to] != 0;
    }









    


    // Метод для проверки существования вершины с заданным индексом
    bool has_vertex(size_t index) const {
        return index < size();
    }



    // Метод возвращает количество ребер, входящих в вершину с заданным ключом
    size_t degree_in(const T& vertex) const {
        const auto index = vertex_index(vertex);
        if (index >= size()) {
            throw std::out_of_range("Vertex index is out of range.");
        }

        size_t degree = 0;
        for (size_t i = 0; i < size(); ++i) {
            if (adjacency_matrix_[i][index] != T()) {
                ++degree;
            }
        }

        return degree;
    }

    // Метод возвращает количество ребер, исходящих из вершины с заданным ключом
    size_t degree_out(const T& vertex) const {
        const auto index = vertex_index(vertex);
        if (index >= size()) {
            throw std::out_of_range("Vertex index is out of range.");
        }

        size_t degree = 0;
        for (size_t i = 0; i < size(); ++i) {
            if (adjacency_matrix_[index][i] != T()) {
                ++degree;
            }
        }

        return degree;
    }

    // Метод возвращает true, если вершина с заданным ключом имеет петлю, иначе false
    bool loop(const T& vertex) const {
        const auto index = vertex_index(vertex);
        if (index >= size()) {
            throw std::out_of_range("Vertex index is out of range.");
        }

        return adjacency_matrix_[index][index] != T();
    }


    std::pair<typename std::unordered_map<T, size_t>::iterator, bool> insert_node(const T& value) {
        auto it = vertex_map_.find(value);
        if (it == vertex_map_.end()) {
            vertices_.push_back(value);
            size_t index = adjacency_matrix_.size();
            adjacency_matrix_.push_back(std::vector<T>(vertices_.size()));
            for (size_t i = 0; i < adjacency_matrix_.size() - 1; ++i) {
                adjacency_matrix_[i].push_back(T());
            }
            vertex_map_[value] = index;
            return std::make_pair(vertex_map_.find(value), true);
        }
        return std::make_pair(it, false);
    }

    // Вставка или замена узла в графе
    std::pair<typename std::unordered_map<T, size_t>::iterator, bool> insert_or_assign_node(const T& value) {
        auto it = vertex_map_.find(value);
        if (it == vertex_map_.end()) {
            vertices_.push_back(value);
            size_t index = adjacency_matrix_.size();
            adjacency_matrix_.push_back(std::vector<T>(vertices_.size()));
            for (size_t i = 0; i < adjacency_matrix_.size() - 1; ++i) {
                adjacency_matrix_[i].push_back(T());
            }
            vertex_map_[value] = index;
            return std::make_pair(vertex_map_.find(value), true);
        }
        return std::make_pair(it, false);
    }

    std::pair<typename std::unordered_map<T, size_t>::iterator, bool> insert_edge(const std::pair<T, T>& edge, const T& weight) {
        auto it_from = vertex_map_.find(edge.first);
        auto it_to = vertex_map_.find(edge.second);
        if (it_from == vertex_map_.end() || it_to == vertex_map_.end()) {
            
            return std::make_pair(vertex_map_.end(), false);
        }
        adjacency_matrix_[it_from->second][it_to->second] = weight;
        return std::make_pair(vertex_map_.find(edge.first), true);
    }

    std::pair<typename std::unordered_map<T, size_t>::iterator, bool> insert_or_assign_edge(const std::pair<T, T>& key, const value_type& weight) {
        auto it_from = vertex_map_.find(key.first);
        auto it_to = vertex_map_.find(key.second);
        if (it_from == vertex_map_.end() || it_to == vertex_map_.end()) {
            throw std::invalid_argument("One or both vertices not found.");
        }
        auto& row = adjacency_matrix_[it_from->second];
        auto it_edge = row.find(it_to->second);
        if (it_edge != row.end()) {
            it_edge->second = weight;
            return std::make_pair(it_edge, false);
        }
        else {
            row[it_to->second] = weight;
            return std::make_pair(row.find(it_to->second), true);
        }
    }
    // Удаление всех ребер в графе
    void clear_edges() {
        for (auto& row : adjacency_matrix_) {
            for (auto& weight : row) {
                weight = T();
            }
        }
    }



    // Удаление всех ребер, выходящих из узла с заданным ключом
    bool erase_edges_go_from(const T& key) {
        auto it = vertex_map_.find(key);
        if (it == vertex_map_.end()) {
            return false;
        }
        size_t index = it->second;
        for (auto& row : adjacency_matrix_) {
            row[index] = T();
        }
        return true;
    }

    // Удаление всех ребер, входящих в узел с заданным ключом
    bool erase_edges_go_to(const T& key) {
        auto it = vertex_map_.find(key);
        if (it == vertex_map_.end()) {
            return false;
        }
        size_t index = it->second;
        adjacency_matrix_[index].clear();
        return true;
    }

    // Удаление узла с заданным ключом
    bool erase_node(const T& key) {
        auto it = vertex_map_.find(key);
        if (it == vertex_map_.end()) {
            return false;
        }
        size_t index = it->second;
        vertex_map_.erase(it);
        vertices_.erase(vertices_.begin() + index);
        for (auto& row : adjacency_matrix_) {
            row.erase(row.begin() + index);
        }
        adjacency_matrix_.erase(adjacency_matrix_.begin() + index);
        --vertex_count_;
        return true;
    }
    void add_vertex(const T& vertex) {
        // Проверяем, существует ли уже вершина с таким значением.
        if (vertex_map_.count(vertex) == 0) {
            // Добавляем вершину в вектор vertices_ и создаем для нее пустой список смежности.
            vertices_.push_back(vertex);
            adjacency_list_.push_back(std::unordered_set<int>());
            // Добавляем в map соответствие между значением вершины и ее индексом в векторе vertices_.
            vertex_map_[vertex] = vertices_.size() - 1;
        }
    }
    std::unordered_map<T, T> get_neighbors(const T& value) const {
        std::unordered_map<T, T> neighbors;
        auto it_from = vertex_map_.find(value);
        if (it_from == vertex_map_.end()) {
            throw std::invalid_argument("Vertex not found");
        }
        size_t from_index = it_from->second;
        for (size_t to_index = 0; to_index < adjacency_matrix_.size(); ++to_index) {
            if (adjacency_matrix_[from_index][to_index] != T()) {
                T to_value = vertices_[to_index];
                neighbors[to_value] = adjacency_matrix_[from_index][to_index];
            }
        }
        return neighbors;
    }


    // Считывание графа из файла
    bool load_from_file(const std::string& path) {
        std::ifstream file(path);
        if (!file) {
            std::cerr << "Error opening file " << path << std::endl;
            return false;
        }

        size_t n;
        file >> n;
        if (!file) {
            throw std::invalid_argument("Invalid file format.");
        }

        adjacency_matrix_.resize(n, std::vector<T>(n));

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                file >> adjacency_matrix_[i][j];
                if (!file) {
                    throw std::invalid_argument("Invalid file format.");
                }
            }
        }

        return true;
    }

    // Сохранение графа в файл
    void save_to_file(const std::string& path) const {
        std::ofstream file(path);
        if (!file) {
            std::cerr << "Error opening file " << path << std::endl;
            return;
        }

        const size_t n = adjacency_matrix_.size();
        file << n << std::endl;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                file << adjacency_matrix_[i][j] << " ";
            }
            file << std::endl;
        }
    }

    template<typename T>
    Graph<T> read_edge_list_from_file(const std::string& filename) {
        std::ifstream input(filename);
        if (!input) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        size_t vertex_count, edge_count;
        input >> vertex_count >> edge_count;

        Graph<T> graph(vertex_count);

        for (size_t i = 0; i < edge_count; ++i) {
            size_t from, to;
            input >> from >> to;
            graph.add_edge(from, to);
        }

        return graph;
    }
    template<typename T>
    Graph<T> read_adjacency_matrix_from_file(const std::string& filename) {
        std::ifstream input(filename);
        if (!input) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        size_t vertex_count;
        input >> vertex_count;

        Graph<T> graph(vertex_count);

        for (size_t i = 0; i < vertex_count; ++i) {
            for (size_t j = 0; j < vertex_count; ++j) {
                int adjacency;
                input >> adjacency;

                if (adjacency == 1) {
                    graph.add_edge(i, j);
                }
            }
        }

        return graph;
    }
    void print_graph(const Graph<std::string>& g) {
        for (const auto& vertex : g.vertices_) {
            std::cout << vertex << ": ";
            for (const auto& edge : g.getOutgoingEdges(g.vertex_index(vertex))) {
                std::cout << "(" << g.vertices_[edge.first] << ", " << edge.second << ") ";
            }
            std::cout << std::endl;
        }
    }

    void test_insert_node() {
        Graph<int> graph;
        auto [it1, res1] = graph.insert_node(1);
        assert(res1 == true);
        auto [it2, res2] = graph.insert_node(2);
        assert(res2 == true);
        auto [it3, res3] = graph.insert_node(1);
        assert(res3 == false);
    }

    void test_insert_or_assign_node() {
        Graph<int> graph;
        auto [it1, res1] = graph.insert_or_assign_node(1);
        assert(res1 == true);
        auto [it2, res2] = graph.insert_or_assign_node(2);
        assert(res2 == true);
        auto [it3, res3] = graph.insert_or_assign_node(1);
        assert(res3 == false);
    }



    void test_insert_edge() {
        Graph<int> graph;
        graph.insert_node(1);
        graph.insert_node(2);
        auto [it1, res1] = graph.insert_edge({ 1, 2 }, 10);
        assert(res1 == true);
        auto [it2, res2] = graph.insert_edge({ 1, 2 }, 5);
        assert(res2 == true);
    }


    

    void test_clear_edges() {

        Graph<int> graph;
        graph.insert_node(1);
        graph.insert_node(2);
        graph.insert_edge({ 1, 2 }, 10);
        graph.clear_edges();
        assert(graph.has_edge(1, 2) == false);
        assert(graph.has_edge(2, 1) == false);
    }
    void test_insert_or_assign_edge() {
        Graph<std::string> graph;
        graph.insert_node("A");
        graph.insert_node("B");
        graph.insert_node("C");
        graph.insert_node("D");
    }
    void test_erase_edges_go_from() {
        Graph<std::string> graph;
        graph.insert_node("A");
        graph.insert_node("B");
        graph.insert_node("C");
      

        bool res = graph.erase_edges_go_from("B");
        assert(res == true);
    }

    void test_erase_edges_go_to() {
        Graph<std::string> graph;
        graph.insert_node("A");
        graph.insert_node("B");
        graph.insert_node("C");
       

        bool res = graph.erase_edges_go_to("B");
        assert(res == true);

        
    }

    void test_erase_node() {
        Graph<std::string> graph;
        graph.insert_node("A");
        graph.insert_node("B");
        graph.insert_node("C");
       

        bool res = graph.erase_node("B");
        assert(res == true);
       
       
    }




};

int main() {
    Graph<int> graph;  
    graph.test_insert_node();
    graph.test_insert_or_assign_node();
    graph.test_insert_edge();
    graph.test_insert_or_assign_edge();
    graph.test_clear_edges();
    graph.test_insert_or_assign_edge();
    graph.test_erase_edges_go_from();
    graph.test_erase_edges_go_to();
    graph.test_erase_node();
    Graph<int> g;

    bool result = g.load_from_file("test.txt");
    //std::cout << g.size();
    assert(result == true);

    // проверяем размерность матрицы
    assert(g.size() == 3);

    // проверяем значения матрицы

    assert(g.get_weight(0, 0) == 0);
    assert(g.get_weight(0, 1) == 1);
    assert(g.get_weight(0, 2) == 2);
    assert(g.get_weight(1, 0) == 3);
    assert(g.get_weight(1, 1) == 0);
    assert(g.get_weight(1, 2) == 4);
    assert(g.get_weight(2, 0) == 5);
    assert(g.get_weight(2, 1) == 6);
    assert(g.get_weight(2, 2) == 0);
   

    std::cout << "All tests passed" << std::endl;

    
    
  



}
