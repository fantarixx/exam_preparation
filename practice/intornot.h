namespace IntOrNot { 
    class IntOrNot {
        int* data;

    public:
        IntOrNot() : data(nullptr) {}
        IntOrNot(int value) : data(&value) {}

        operator bool() const {
            return data;
        }   

        int operator*() const {
            if (data) {
                return *data;
            }

            return 0x0;
        } 

        IntOrNot& operator=(const int& value) {
            *data = value;    
            
            
            return *this;
        }
    };
    
    void print(const IntOrNot& value) {
        if(value)
            std::cout << *value;
        else 
            std::cout << "no value";
    }
}