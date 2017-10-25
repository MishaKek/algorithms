#include <iostream>

const int duration = 100000;

class Object_array
{
private:
    //Мощность универсума
    static int UNIVERSE_POWER;
    //Мощность множества
    int cardinality;
    //Тег и память для множества
    char tag, *array;
public:
    Object_array operator | (const Object_array&) const;
    Object_array operator & (const Object_array&) const;
    Object_array operator ~ () const;
    Object_array operator = (const Object_array &);
    void display();
//    int get_cardinality() { return cardinality; }
    Object_array();
    Object_array(char);
    Object_array(const Object_array &);
};

//class Object_list
//{
//private:
//    char symb;
//    Object_list* next;
//public:
//    Object_list() {}
//    Object_list(char s, Object_list* n = nullptr) : symb(s), next(n) {  std::cout << "+" << symb << std::endl;    }
//    ~Object_list() {
//        if (next) {
//            delete next;
//        }
//        std::cout << "-" << symb << std::endl;
//    }
//
//
//};



class Object_node
{
private:
    char symb;
    Object_node* next;

public:
//    Object_node* next;

    void set_next(Object_node* new_next) {
        next = new_next;
    }

    Object_node* to_next(Object_node* link) {
        if(link != nullptr) {
            if(link != this) {
                std::cout << "Указатель \"Link\" не связан с текущим объектом типа \"Object_node\"" << std::endl;
            } else {
                link = link->next;
            }
        } else {
            std::cout << "Указатель \"Link\" пуст" << std::endl;
        }
        return link;
    }

    Object_node() : symb('0'), next(nullptr) {}

    Object_node(char s) : symb(s), next(nullptr) {}

    void show_node() {
        std::cout << symb << std::endl;
    }

};

class Object_list
{
    friend class Object_node;
private:
    static int UNIVERSE_POWER;
    Object_node* head;
    Object_node* last;
    char tag;
public:
    Object_node* get_head() {   return head;  }
    void set_head(Object_node* new_head) {
        if (new_head != nullptr) {
            head = new_head;
        } else {
            std::cout << "Обнуление головы! Возможна утечка памяти!" << std::endl;
            head = nullptr;
        }
    }
    Object_node* get_last() {   return last;  }
    void set_last(Object_node* new_last) {
        if (new_last == nullptr) {
            if (head != nullptr) {
                std::cout << "Ошибка! Обнуление последнего элемента непустого списка!" << std::endl;
            } else {
                last = nullptr;
            }
        }
    }
    void show_list() {
        if (head != nullptr) {
            Object_node* link = head;
            do {
                link->show_node();
                link = link->to_next(link);
            } while (link != nullptr);
        } else {
            std::cout << "Список пуст" << std::endl;
        }
        std::cout << "Вывод завершен" << std::endl;
    }

    //прописать конструкторы по тегу и тд
    Object_list() : tag('0') {
        head = last = new Object_node();
    }

    Object_list(char tag) {
        //0 лишний создается всегда-исправить
        head = nullptr;
        for (int i = UNIVERSE_POWER - 1; i >= 0; i--) {
            if(rand() % 2) {
                Object_node *link = head;
                head = new Object_node((char)(i + '0'));
                head->set_next(link);
            }
        }
    }
};




int Object_array :: UNIVERSE_POWER = 10;
int Object_list :: UNIVERSE_POWER = 10;

Object_array Object_array ::operator&(const Object_array & B) const {
    Object_array* set = new Object_array;
    for (int i = 0; i < cardinality; i++) {
        for (int j = 0; j < B.cardinality; j++) {
            if (array[i] == B.array[j]) {
                set->array[set->cardinality++] = array[i];
            }
        }
    }
    set->array[set->cardinality] = 0;
    return *set;
}

Object_array Object_array ::operator|(const Object_array & B) const {
    Object_array* set = new Object_array(*this);
    for (int i = 0; i < B.cardinality; i++) {
        bool flag = true;
        for (int j = 0; j < cardinality; j++) {
            if(B.array[i] == array[j]) {
                flag = false;
            }
        }
        if(flag) {
            set->array[set->cardinality++] = B.array[i];
        }
    }
    set->array[set->cardinality] = 0;
    return *set;
}

Object_array Object_array ::operator~() const {
    Object_array* set = new Object_array;
    for (char ch = '0'; ch <= '9'; ch++) {
        bool flag = true;
        for (int j = 0; j < cardinality; j++) {
            if (ch == array[j]) {
                flag = false;
                break;
            }
        }
        if(flag) {
            set->array[set->cardinality++] = ch;
        }
    }
    set->array[set->cardinality] = 0;
    return *set;
}

void Object_array :: display() {
    std::cout << tag << " = [" << array << "]" << std::endl;
}

Object_array::Object_array(): cardinality(0), tag('0'), array(new char[UNIVERSE_POWER + 1]) {
    array[0] = 0;
}


Object_array::Object_array(char symb): tag(symb), cardinality(0), array(new char[UNIVERSE_POWER + 1]) {
    for (int i = 0; i < UNIVERSE_POWER; i++) {
        if(rand() % 2) {
            array[cardinality++] =(char) (i +'0');
        }
    }
    array[cardinality] = 0;
    std::cout << tag << " =[" << array << "]" << std::endl;
}

Object_array::Object_array(const Object_array & B): tag(B.tag), cardinality(B.cardinality), array(new char[UNIVERSE_POWER + 1]) {
    memcpy(array, B.array, (size_t)UNIVERSE_POWER + 1);
}

Object_array Object_array :: operator = (const Object_array& B) {
    if(this != &B) {
        cardinality = B.cardinality;
        memcpy(array, B.array, (size_t)UNIVERSE_POWER + 1);
        tag = 'E';//result
    }
    return *this;
}

//commit test

int main() {
    std::cout << "Hello, World!" << std::endl;

    srand(time(nullptr));
    Object_list A('A');
    A.show_list();


//    Object_array A('A'), B('B'), C('C'), D('D'), E;
//    clock_t start = clock();
//    for (int i = 0; i < duration; i++) {
//        E = (A & ~B) & (C | D);
//    }
//    clock_t end = clock();
//    std::cout << "Time = " << end - start << std::endl;
    return 0;
}