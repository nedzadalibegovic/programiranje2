# programiranje2
```cpp
class Foo : public Bar {
private:
    std::string _name;
public:
    Foo(std::string name = "World") : _name(name) {}
    
    friend std::ostream& operator<<(std::ostream& out, const Foo& obj) {
        out << "Hello" << obj._name << "!\n";
        return out;
    }
};
```