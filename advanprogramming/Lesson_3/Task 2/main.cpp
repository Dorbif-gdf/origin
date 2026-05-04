#include <catch2/catch_test_macros.hpp>
#include <iostream>

// Код

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};

class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

// Тесты

TEST_CASE("PushBack и PopBack работают корректно", "[List]") {
    List list;

    list.PushBack(10);
    list.PushBack(20);

    REQUIRE(list.PopBack() == 20);
    REQUIRE(list.PopBack() == 10);
    REQUIRE(list.Empty());
}

TEST_CASE("PushFront и PopFront работают корректно", "[List]") {
    List list;

    list.PushFront(10);
    list.PushFront(20);

    REQUIRE(list.PopFront() == 20);
    REQUIRE(list.PopFront() == 10);
    REQUIRE(list.Empty());
}

TEST_CASE("PopBack бросает исключение на пустом списке", "[List]") {
    List list;

    REQUIRE_THROWS(list.PopBack());
}

TEST_CASE("PopFront бросает исключение на пустом списке", "[List]") {
    List list;

    REQUIRE_THROWS(list.PopFront());
}

TEST_CASE("Сложный сценарий работы списка", "[List]") {
    List list;

    list.PushBack(1);   // [1]
    list.PushFront(2);  // [2,1]
    list.PushBack(3);   // [2,1,3]

    REQUIRE(list.PopFront() == 2); // [1,3]
    REQUIRE(list.PopBack() == 3);  // [1]

    list.PushFront(4);  // [4,1]

    REQUIRE(list.PopBack() == 1);  // [4]
    REQUIRE(list.PopFront() == 4); // []

    REQUIRE(list.Empty());
}