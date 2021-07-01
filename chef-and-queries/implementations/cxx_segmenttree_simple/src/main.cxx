#include <iostream>
#include <string>
#include <vector>

class Range {
public:
  size_t start;
  size_t end;

  Range() : start{1}, end{1} {}

  Range(size_t _start, size_t _end) : start{_start}, end{_end} {}

  size_t len() const { return this->end - this->start + 1; }

  bool contains(const Range &_other) const {
    return this->start <= _other.start && this->end >= _other.end;
  }

  bool overlaps(const Range &_other) const {
    return this->end >= _other.start && this->start <= _other.end;
  }
};

struct Node {
    Range range;
    int64_t invariant;
};

class SegmentTree {
private:
    std::vector<Node> nodes;

    void init(size_t _index, const Range &_range) {
        this->get_mut(_index) = {
            _range, // range
            0,      // passes
        };

        if (_range.len() == 1) return;

        auto left_index = _index * 2;
        Range left_range {_range.start, _range.start + _range.len() / 2 - 1};
        this->init(left_index, left_range);

        auto right_index = _index * 2 + 1;
        Range right_range {_range.start + _range.len() / 2, _range.end};
        this->init(right_index, right_range);
    }

    void apply_internal(size_t _index, const Range &_range, int64_t _x) {
        auto &node = this->get(_index);
        if (_range.contains(node.range)) {
            auto &current = this->get_mut(_index);
            current.invariant += _x;
        } else {
            auto left_index = _index * 2;
            auto left_child = this->get(left_index);
            if (_range.overlaps(left_child.range)) {
                this->apply_internal(left_index, _range, _x);
            }

            auto right_index = _index * 2 + 1;
            auto right_child = this->get(right_index);
            if (_range.overlaps(right_child.range)) {
                this->apply_internal(right_index, _range, _x);
            }
        }
    }

    Node query_internal(size_t _index) const {
        auto current = this->get(_index);
        if (_index == 1) return current; // We're at the root, stop recursion

        const auto &parent = query_internal(_index / 2);
        return {
            current.range,
            current.invariant + parent.invariant,
        };
    }

    Node& get_mut(size_t _index) {
        return this->nodes[_index];
    }

    const Node& get(size_t _index) const{
        return this->nodes[_index];
    }


public:
    SegmentTree(size_t _size) {
        size_t pow2 = 1;
        for (; pow2 < _size * 2; pow2 *= 2);

        this->nodes = std::vector<Node>(pow2);
        this->init(1, {1, pow2/2});
    }

    ~SegmentTree() {}

    size_t size() const {
        return this->nodes.size();
    }

    void set(size_t _index, int64_t _val) {
        this->get_mut(_index + this->nodes.size()/2 - 1).invariant = _val;
    }

    void apply(const Range &_range, int64_t _x) {
        this->apply_internal(1, {_range.start, _range.end}, _x);
    }

    int64_t query(size_t _index) const {
        const auto &node = this->query_internal(_index + this->nodes.size()/2 - 1);
        return node.invariant;
    }
};

int main() {
    size_t N, Q;
    std::cin >> N >> Q;

    auto tree = SegmentTree(N);
    for (auto i = 1; i <= N; ++i) {
        int64_t initial_value;
        std::cin >> initial_value;
        tree.set(i, initial_value);
    }


    for (auto i = 0; i < Q; ++i) {
        size_t command;
        std::cin >> command;
        if (command == 1) {
            size_t L, R;
            int64_t X;
            std::cin >> L >> R >> X;
            tree.apply({L, R}, X);
        } else {
            size_t Y;
            std::cin >> Y;
            std::cout << tree.query(Y) << std::endl;
        }
    }

    return 0;
}
