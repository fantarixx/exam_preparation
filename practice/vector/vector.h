template <typename T>
class vector {
private:
    T* data;

    long size;
    long capacity;

public:
    vector(long start_size = 0) : size(start_size), capacity(2 * (start_size + static_cast<long>(start_size == 0)));

    //push_back
    T* top() {
        return data;
    }
    //back
    T operetor[]() {

    }
    //pop
    //size
};