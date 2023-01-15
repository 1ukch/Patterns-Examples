#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T, typename U>
class Iterator {
public:
    typedef typename vector<T>::iterator iter_type;
    Iterator(U* p_data, bool reverse = false) : m_p_data_(p_data) {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void First() {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void Next() {
        m_it_++;
    }

    bool IsDone() {
        return (m_it_ == m_p_data_->m_data_.end());
    }

    iter_type Current() {
        return m_it_;
    }

private:
    U* m_p_data_;
    iter_type m_it_;
};


template <class T>
class Container {
    friend class Iterator<T, Container>;

public:
    void Add(T a) {
        m_data_.push_back(a);
    }

    Iterator<T, Container>* CreateIterator() {
        return new Iterator<T, Container>(this);
    }

private:
    std::vector<T> m_data_;
};

class Data {
public:
    Data(int a = 0) : m_data_(a) {}

    void set_data(int a) {
        m_data_ = a;
    }

    int data() {
        return m_data_;
    }

private:
    int m_data_;
};

int main() {
	Container<Data> con;
	for (int i = 0; i < 10; i++) {
		Data d(i);
		con.Add(d);
	}

	Iterator<Data, Container<Data>>* it = con.CreateIterator();
	for (it->First(); !it->IsDone(); it->Next()) {
		cout << (*it->Current()).data() << endl;
	}

	return 0;
}
